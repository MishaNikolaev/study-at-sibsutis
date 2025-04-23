import React, { useState } from 'react';
import PropTypes from 'prop-types';

const DataSet = ({ data, onAdd, onDelete, onUpdate }) => {
  const [selectedIds, setSelectedIds] = useState([]);
  const [newComment, setNewComment] = useState({
    postId: 1,
    name: '',
    email: '',
    body: ''
  });
  const [editingId, setEditingId] = useState(null);
  const [editData, setEditData] = useState({});

  const handleAdd = () => {
    if (!newComment.name || !newComment.body) {
      alert('Input name or body');
      return;
    }
    onAdd(newComment);
    setNewComment({
      postId: 1,
      name: '',
      email: '',
      body: ''
    });
  };

  const handleDeleteSelected = () => {
    if (selectedIds.length > 0) {
      if (window.confirm(`Delete ${selectedIds.length} selected comments?`)) {
        onDelete(selectedIds);
        setSelectedIds([]);
      }
    }
  };

  const startEditing = (comment) => {
    setEditingId(comment.id);
    setEditData({
      name: comment.name,
      email: comment.email,
      body: comment.body
    });
  };

  const saveEdit = () => {
    if (editingId) {
      onUpdate(editingId, editData);
      setEditingId(null);
    }
  };

  const headers = ['Select', 'ID', 'Post ID', 'Name', 'Email', 'Body', 'Actions'];

  return (
    <div style={{ padding: '20px' }}>
      <div style={{ marginBottom: '20px', padding: '10px', border: '1px solid #ddd', borderRadius: '5px' }}>
        <h3>Add New Comment</h3>
        <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
          <input
            type="number"
            value={newComment.postId}
            onChange={(e) => setNewComment({...newComment, postId: +e.target.value})}
            placeholder="Post ID"
            style={{ padding: '8px' }}
          />
          <input
            value={newComment.name}
            onChange={(e) => setNewComment({...newComment, name: e.target.value})}
            placeholder="Name"
            style={{ padding: '8px' }}
            required
          />
          <input
            value={newComment.email}
            onChange={(e) => setNewComment({...newComment, email: e.target.value})}
            placeholder="Email"
            style={{ padding: '8px' }}
          />
          <textarea
            value={newComment.body}
            onChange={(e) => setNewComment({...newComment, body: e.target.value})}
            placeholder="Comment body"
            style={{ padding: '8px', minHeight: '60px' }}
            required
          />
          <button 
            onClick={handleAdd}
            style={{ padding: '8px', backgroundColor: '#4CAF50', color: 'white', border: 'none' }}
          >
            Add Comment
          </button>
        </div>
      </div>

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
            {headers.map((header, idx) => (
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
          {data.map(comment => (
            <tr key={comment.id} style={{
              backgroundColor: selectedIds.includes(comment.id) ? '#b3e0ff' : 'transparent'
            }}>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                <input
                  type="checkbox"
                  checked={selectedIds.includes(comment.id)}
                  onChange={(e) => {
                    if (e.target.checked) {
                      setSelectedIds([...selectedIds, comment.id]);
                    } else {
                      setSelectedIds(selectedIds.filter(id => id !== comment.id));
                    }
                  }}
                />
              </td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{comment.id}</td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{comment.postId}</td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                {editingId === comment.id ? (
                  <input
                    value={editData.name}
                    onChange={(e) => setEditData({...editData, name: e.target.value})}
                    style={{ width: '100%', padding: '4px' }}
                  />
                ) : (
                  comment.name
                )}
              </td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                {editingId === comment.id ? (
                  <input
                    value={editData.email}
                    onChange={(e) => setEditData({...editData, email: e.target.value})}
                    style={{ width: '100%', padding: '4px' }}
                  />
                ) : (
                  comment.email
                )}
              </td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                {editingId === comment.id ? (
                  <textarea
                    value={editData.body}
                    onChange={(e) => setEditData({...editData, body: e.target.value})}
                    style={{ width: '100%', padding: '4px', minHeight: '50px' }}
                  />
                ) : (
                  comment.body
                )}
              </td>
              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                {editingId === comment.id ? (
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
                    onClick={() => startEditing(comment)}
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
  onAdd: PropTypes.func.isRequired,
  onDelete: PropTypes.func.isRequired,
  onUpdate: PropTypes.func.isRequired,
};

export default DataSet;
