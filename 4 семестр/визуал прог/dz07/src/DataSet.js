import React, { useState } from 'react';
import PropTypes from 'prop-types';

const DataSet = ({ headers, data, renderHeader, renderCell }) => {
  const [selectedCells, setSelectedCells] = useState(new Set());

  const handleCellClick = (rowIndex, colIndex, event) => {
    const cellKey = `${rowIndex}-${colIndex}`;
    const newSelection = new Set(selectedCells);

    if (event.ctrlKey || event.metaKey) {
      if (newSelection.has(cellKey)) {
        newSelection.delete(cellKey);
      } else {
        newSelection.add(cellKey);
      }
    } else {
      if (newSelection.size === 1 && newSelection.has(cellKey)) {
        newSelection.clear();
      } else {
        newSelection.clear();
        newSelection.add(cellKey);
      }
    }

    setSelectedCells(newSelection);
  };

  const isRowSelected = (rowIndex) => {
    return Array.from(selectedCells).some(key => key.startsWith(`${rowIndex}-`));
  };

  const effectiveHeaders = headers || (data.length > 0 ? Object.keys(data[0]) : []);

  return (
    <table style={{
      borderCollapse: 'collapse',
      width: '100%',
      border: '1px solid #ddd',
      fontFamily: 'Arial, sans-serif'
    }}>
      <thead>
        <tr>
          {effectiveHeaders.map((header, idx) => (
            <th key={idx} style={{
              border: '1px solid #ddd',
              padding: '8px',
              backgroundColor: '#f2f2f2',
              textAlign: 'left'
            }}>
              {renderHeader ? renderHeader(header, idx) : header}
            </th>
          ))}
        </tr>
      </thead>
      <tbody>
        {data.map((item, rowIndex) => (
          <tr key={rowIndex} style={{
            backgroundColor: isRowSelected(rowIndex) ? '#b3e0ff' : 'transparent'
          }}>
            {effectiveHeaders.map((header, colIndex) => (
              <td 
                key={colIndex}
                style={{
                  border: '1px solid #ddd',
                  padding: '8px',
                  cursor: 'pointer'
                }}
                onClick={(e) => handleCellClick(rowIndex, colIndex, e)}
              >
                {renderCell ? renderCell(item, header, rowIndex, colIndex) : item[header]}
              </td>
            ))}
          </tr>
        ))}
      </tbody>
    </table>
  );
};

DataSet.propTypes = {
  headers: PropTypes.array,
  data: PropTypes.array.isRequired,
  renderHeader: PropTypes.func,
  renderCell: PropTypes.func,
};

export default DataSet;
