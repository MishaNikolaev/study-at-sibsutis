import React, { useState } from 'react';
import PropTypes from 'prop-types';

const DataSet = ({ data, onDelete, onUpdate, headers }) => {
  const [selectedIds, setSelectedIds] = useState([]);
  const [editingId, setEditingId] = useState(null);
  const [editData, setEditData] = useState({});

  const handleDeleteSelected = () => {
    if (selectedIds.length > 0) {
      if (window.confirm(`Delete ${selectedIds.length} selected items?`)) {
        onDelete(selectedIds);
        setSelectedIds([]);
      }
    }
  };

  const startEditing = (item) => {
    setEditingId(item.id);
    setEditData({ ...item });
    delete editData.id; 
  };

  const saveEdit = () => {
    if (editingId) {
      onUpdate(editingId, editData);
      setEditingId(null);
    }
  };

  const handleEditChange = (e) => {
    const { name, value, type, checked } = e.target;
    setEditData(prev => ({
      ...prev,
      [name]: type === 'checkbox' ? checked : value
    }));
  };

  const allHeaders = ['Select', 'ID', ...headers, 'Actions'];

  return (
    <div style={{ padding: '20px' }}>
      <div style={{ marginBottom: '10px' }}>
        <button 
          onClick={handleDeleteSelected}
          disabled={selectedIds.length === 0}
          style={{ 
            padding: '8px',
            backgroundColor: selectedIds.length ? '#f44336' : '#cccccc',
            color: 'white',
            border: 'none',
            cursor: selectedIds.length ? 'pointer' : 'not-allowed'
          }}
        >
          Delete Selected ({selectedIds.length})
        </button>
      </div>

      <table style={{
        borderCollapse: 'collapse',
        width: '100%',
        border: '1px solid #ddd',
        fontFamily: 'Arial, sans-serif'
      }}>
        <thead>
          <tr>
            {allHeaders.map((header, idx) => (
              <th key={idx} style={{
                border: '1px solid #ddd',
                padding: '12px',
                backgroundColor: '#f2f2f2',
                textAlign: 'left'
              }}>
                {header}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {data.map(item => (
            <tr key={item.id} style={{
              backgroundColor: selectedIds.includes(item.id) ? '#b3e0ff' : 'transparent'
            }}>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                <input
                  type="checkbox"
                  checked={selectedIds.includes(item.id)}
                  onChange={(e) => {
                    if (e.target.checked) {
                      setSelectedIds([...selectedIds, item.id]);
                    } else {
                      setSelectedIds(selectedIds.filter(id => id !== item.id));
                    }
                  }}
                />
              </td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{item.id}</td>
              
              {headers.map(header => (
                <td key={header} style={{ border: '1px solid #ddd', padding: '8px' }}>
                  {editingId === item.id ? (
                    header === 'completed' ? (
                      <input
                        type="checkbox"
                        name={header}
                        checked={editData[header] || false}
                        onChange={handleEditChange}
                      />
                    ) : (
                      <input
                        type={header === 'email' ? 'email' : 'text'}
                        name={header}
                        value={editData[header] || ''}
                        onChange={handleEditChange}
                        style={{ width: '100%', padding: '4px' }}
                      />
                    )
                  ) : (
                    header === 'completed' ? 
                      (item[header] ? 'Yes' : 'No') : 
                      item[header]
                  )}
                </td>
              ))}
              
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                {editingId === item.id ? (
                  <>
                    <button 
                      onClick={saveEdit}
                      style={{ marginRight: '5px', padding: '4px 8px', backgroundColor: '#4CAF50', color: 'white' }}
                    >
                      Save
                    </button>
                    <button 
                      onClick={() => setEditingId(null)}
                      style={{ padding: '4px 8px', backgroundColor: '#f44336', color: 'white' }}
                    >
                      Cancel
                    </button>
                  </>
                ) : (
                  <button 
                    onClick={() => startEditing(item)}
                    style={{ padding: '4px 8px', backgroundColor: '#2196F3', color: 'white' }}
                  >
                    Edit
                  </button>
                )}
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

DataSet.propTypes = {
  data: PropTypes.array.isRequired,
  onDelete: PropTypes.func.isRequired,
  onUpdate: PropTypes.func.isRequired,
  headers: PropTypes.array.isRequired,
};

export default DataSet;
