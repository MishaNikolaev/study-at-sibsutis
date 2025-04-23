import React from 'react';
import DataSet from './DataSet';

const App = () => {
  const sampleData = [
    { id: 1, name: 'Egor', value: '0' },
    { id: 2, name: 'Denis', value: '2' },
    { id: 3, name: 'Stepan', value: '10' },
    { id: 4, name: 'Gleb', value: '100' },
  ];

  return (
    <div style={{ 
      padding: '20px', 
      maxWidth: '800px', 
      margin: '0 auto',
      fontFamily: 'Arial, sans-serif'
    }}>
      <h1 style={{ 
        textAlign: 'center',
        color: '#333',
        marginBottom: '20px'
      }}>
        DataSet homework #7
      </h1>
      <DataSet 
        data={sampleData}
        headers={['ID', 'Имена', 'Сколько лет в программировании']} 
        renderCell={(item, header) => {
          const keyMap = {
            'ID': 'id',
            'Имена': 'name',
            'Сколько лет в программировании': 'value'
          };
          return item[keyMap[header]];
        }}
      />
    </div>
  );
};

export default App;
