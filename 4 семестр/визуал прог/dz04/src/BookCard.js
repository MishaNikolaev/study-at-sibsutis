import React from 'react';

const BookCard = ({ title, authors, cover }) => {
  return (
    <div style={styles.card}>
      {cover ? (
        <img src={cover} alt={title} style={styles.cover} />
      ) : (
        <div style={styles.placeholder}>Нет обложки</div>
      )}
      <h2 style={styles.title}>{title}</h2>
      <p style={styles.authors}>{authors.join(', ')}</p>
    </div>
  );
};

const styles = {
  card: {
    width: '200px',
    margin: '10px',
    padding: '10px',
    border: '1px solid #ccc',
    borderRadius: '5px',
    textAlign: 'center',
  },
  cover: {
    width: '100%',
    height: 'auto',
    marginBottom: '10px',
  },
  placeholder: {
    width: '100%',
    height: '250px',
    backgroundColor: '#f0f0f0',
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
    borderRadius: '5px',
    marginBottom: '10px',
  },
  title: {
    fontSize: '18px',
    margin: '5px 0',
  },
  authors: {
    fontSize: '14px',
    color: '#555',
  },
};

export default BookCard;
