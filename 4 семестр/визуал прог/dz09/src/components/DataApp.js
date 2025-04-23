import { useState, useEffect } from 'react';
import { Formik, Form, Field, ErrorMessage } from 'formik';
import * as Yup from 'yup';
import DataSet from './DataSet';

export default function DataApp({ endpoint, initialValues, validationSchema, fields }) {
  const [data, setData] = useState([]);
  const [optimisticData, setOptimisticData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [nextId, setNextId] = useState(1);

  useEffect(() => {
    async function fetchData() {
      try {
        const response = await fetch(`https://jsonplaceholder.typicode.com/${endpoint}`);
        
        if (!response.ok) {
          throw new Error(`Failed to fetch ${endpoint}`);
        }
        
        const responseData = await response.json();
        setData(responseData);
        setOptimisticData(responseData);
        
        const maxId = responseData.reduce((max, item) => Math.max(max, item.id), 0);
        setNextId(maxId + 1);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    }

    fetchData();
  }, [endpoint]);

  const handleAdd = async (values) => {
    const tempId = nextId;
    const newItem = { ...values, id: tempId };
    
    setNextId(prev => prev + 1);
    setOptimisticData(prev => [...prev, newItem]);
    
    try {
      const response = await fetch(`https://jsonplaceholder.typicode.com/${endpoint}`, {
        method: 'POST',
        body: JSON.stringify(newItem),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) {
        throw new Error(`Failed to add ${endpoint} item`);
      }
      
      const serverItem = await response.json();
      
      setData(prev => [...prev, serverItem]);
      setNextId(prev => Math.max(prev, serverItem.id + 1));
    } catch (err) {
      setOptimisticData(prev => prev.filter(item => item.id !== tempId));
      setError(err.message);
    }
  };

  const handleDelete = async (ids) => {
    const backup = [...optimisticData];
    setOptimisticData(prev => prev.filter(item => !ids.includes(item.id)));
    
    try {
      const responses = await Promise.all(
        ids.map(id => 
          fetch(`https://jsonplaceholder.typicode.com/${endpoint}/${id}`, {
            method: 'DELETE',
          })
        )
      );
      
      const allOk = responses.every(r => r.ok);
      if (!allOk) {
        throw new Error(`Failed to delete ${endpoint} items`);
      }
      
      setData(prev => prev.filter(item => !ids.includes(item.id)));
    } catch (err) {
      setOptimisticData(backup);
      setError(err.message);
    }
  };

  const handleUpdate = async (id, updates) => {
    const original = optimisticData.find(item => item.id === id);
    setOptimisticData(prev => prev.map(item => item.id === id ? {...item, ...updates} : item));
    
    try {
      const response = await fetch(`https://jsonplaceholder.typicode.com/${endpoint}/${id}`, {
        method: 'PATCH',
        body: JSON.stringify(updates),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) {
        throw new Error(`Failed to update ${endpoint} item`);
      }
      
      const updatedItem = await response.json();
      setData(prev => prev.map(item => item.id === id ? updatedItem : item));
    } catch (err) {
      setOptimisticData(prev => prev.map(item => item.id === id ? original : item));
      setError(err.message);
    }
  };

  if (loading) {
    return <div>Loading...</div>;
  }

  if (error) {
    return <div>Error: {error}</div>;
  }

  return (
    <div className="data-app" style={{ maxWidth: '1200px', margin: '0 auto', padding: '20px' }}>
      <h1 style={{ color: '#333', marginBottom: '30px' }}>
        {endpoint.charAt(0).toUpperCase() + endpoint.slice(1)}
      </h1>
      
      <div style={{ 
        marginBottom: '30px', 
        padding: '25px', 
        border: '1px solid #e0e0e0',
        borderRadius: '8px',
        backgroundColor: '#fff',
        boxShadow: '0 2px 10px rgba(0,0,0,0.05)'
      }}>
        <h3 style={{ marginTop: '0', color: '#444' }}>Add New Item</h3>
        <Formik
          initialValues={initialValues}
          validationSchema={validationSchema}
          onSubmit={(values, { resetForm }) => {
            handleAdd(values);
            resetForm();
          }}
        >
          {({ errors, touched }) => (
            <Form style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '20px' }}>
              {fields.map(field => (
                <div 
                  key={field.name} 
                  style={{ 
                    gridColumn: field.as === 'textarea' ? '1 / -1' : 'auto',
                    marginBottom: '15px',
                    ...(field.type === 'checkbox' && {
                      display: 'flex',
                      alignItems: 'center',
                      marginLeft: '-10px'
                    })
                  }}
                >
                  {field.type === 'checkbox' ? (
                    <>
                      <Field 
                        type="checkbox"
                        name={field.name}
                        id={field.name}
                        style={{
                          width: '24px',
                          height: '24px',
                          marginRight: '12px',
                          cursor: 'pointer',
                          accentColor: '#4a90e2'
                        }}
                      />
                      <label 
                        htmlFor={field.name}
                        style={{
                          fontWeight: '500',
                          color: '#555',
                          fontSize: '15px',
                          cursor: 'pointer',
                          marginLeft: '5px'
                        }}
                      >
                        {field.label}
                      </label>
                    </>
                  ) : (
                    <>
                      <label 
                        htmlFor={field.name}
                        style={{
                          display: 'block',
                          marginBottom: '8px',
                          fontWeight: '500',
                          color: '#555',
                          fontSize: '14px'
                        }}
                      >
                        {field.label}
                      </label>
                      <Field 
                        type={field.type || 'text'} 
                        name={field.name} 
                        id={field.name}
                        as={field.as || 'input'}
                        style={{
                          width: '100%',
                          padding: '12px',
                          border: '1px solid #ddd',
                          borderRadius: '6px',
                          fontSize: '15px',
                          boxSizing: 'border-box',
                          transition: 'border 0.2s',
                          backgroundColor: field.as === 'textarea' ? '#f9f9f9' : '#fff',
                          ':focus': {
                            outline: 'none',
                            borderColor: '#4a90e2',
                            boxShadow: '0 0 0 2px rgba(74,144,226,0.2)'
                          }
                        }}
                      />
                    </>
                  )}
                  <ErrorMessage 
                    name={field.name} 
                    component="div" 
                    style={{ 
                      color: '#e74c3c',
                      fontSize: '13px',
                      marginTop: '5px'
                    }} 
                  />
                </div>
              ))}
              <div style={{ gridColumn: '1 / -1', textAlign: 'right' }}>
                <button 
                  type="submit" 
                  style={{
                    padding: '12px 24px',
                    backgroundColor: '#4a90e2',
                    color: 'white',
                    border: 'none',
                    borderRadius: '6px',
                    cursor: 'pointer',
                    fontSize: '15px',
                    fontWeight: '500',
                    transition: 'background-color 0.2s',
                    ':hover': {
                      backgroundColor: '#3a80d2'
                    }
                  }}
                >
                  Add Item
                </button>
              </div>
            </Form>
          )}
        </Formik>
      </div>

      <DataSet 
        data={optimisticData}
        onDelete={handleDelete}
        onUpdate={handleUpdate}
        headers={Object.keys(initialValues)}
      />
      
      {error && (
        <div style={{
          color: '#e74c3c',
          padding: '15px',
          backgroundColor: '#fdecea',
          borderRadius: '6px',
          marginTop: '20px'
        }}>
          {error}
        </div>
      )}
    </div>
  );
}
