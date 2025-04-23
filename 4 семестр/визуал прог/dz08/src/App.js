import { useState, useEffect } from 'react';
import DataSet from './DataSet';

export default function CommentsApp() {
  const [comments, setComments] = useState([]);
  const [optimisticComments, setOptimisticComments] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [nextId, setNextId] = useState(501); 

  useEffect(() => {
    async function fetchComments() {
      try {
        const response = await fetch('http://localhost:5136/comments');
        
        if (!response.ok) {
          throw new Error('жёсткий фейл Глебыча');
        }
        
        const data = await response.json();
        setComments(data);
        setOptimisticComments(data);
        
        const maxId = data.reduce((max, comment) => Math.max(max, comment.id), 0);
        setNextId(maxId + 1);
      } catch (err) {
        if (err instanceof Error) {
          setError(err.message);
        } else {
          setError('error произошёл ');
        }
      } finally {
        setLoading(false);
      }
    }

    fetchComments();
  }, []);

  const calculatePostId = (index) => {
    return Math.floor((index - 1) / 5) + 1;
  };

  const handleAdd = async (comment) => {
    const tempId = nextId;
    const newComment = { 
      ...comment, 
      id: tempId,
      postId: calculatePostId(optimisticComments.length + 1) 
    };
    
    setNextId(prev => prev + 1);
    setOptimisticComments(prev => [...prev, newComment]);
    
    try {
      const response = await fetch('http://localhost:5136/comments', {
        method: 'POST',
        body: JSON.stringify(newComment),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) {
        throw new Error('фейл ёмаё');
      }
      
      const serverComment = await response.json();
      
      setComments(prev => [...prev, serverComment]);
      setNextId(prev => Math.max(prev, serverComment.id + 1));
  } catch (err) {
    setOptimisticComments(prev => prev.filter(c => c.id !== tempId));
    
    if (err instanceof Error) {
      setError(err.message);
    } else {
      setError('фейл');
      }
    }
  };

  const handleDelete = async (ids) => {
    const backup = [...optimisticComments];
    setOptimisticComments(prev => prev.filter(c => !ids.includes(c.id)));
    
    try {
      const responses = await Promise.all(
        ids.map(id => 
          fetch(`http://localhost:5136/comments/${id}`, {
            method: 'DELETE',
          })
        )
      );
      
      const allOk = responses.every(r => r.ok);
      if (!allOk) {
        throw new Error('fail');
      }
      
      setComments(prev => prev.filter(c => !ids.includes(c.id)));
    } catch (err) {
      setOptimisticComments(backup);
      setError(err instanceof Error ? err.message : 'Failed to delete comments');
    }
  };

  const handleUpdate = async (id, updates) => {
    const original = optimisticComments.find(c => c.id === id);
    setOptimisticComments(prev => prev.map(c => c.id === id ? {...c, ...updates} : c));
    
    try {
      const response = await fetch(`http://localhost:5136/comments/${id}`, {
        method: 'PATCH',
        body: JSON.stringify(updates),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) {
        throw new Error('Failed to update comment');
      }
      
      const updatedComment = await response.json();
      setComments(prev => prev.map(c => c.id === id ? updatedComment : c));
    } catch (err) {
      setOptimisticComments(prev => prev.map(c => c.id === id ? original : c));
      setError(err instanceof Error ? err.message : 'Failed to update comment');
    }
  };

  if (loading) {
    return <div>Глебасик легенда...</div>;
  }

  if (error) {
    return <div>uf, ошибка снова ААХХХХХХХХХХХХХХХХХХХ: {error}</div>;
  }

  return (
    <div className="comments-app">
      <h1>Comments</h1>
      <DataSet 
        data={optimisticComments}
        onAdd={handleAdd}
        onDelete={handleDelete}
        onUpdate={handleUpdate}
      />
      {error && <div className="error">{error}</div>}
    </div>
  );
}
