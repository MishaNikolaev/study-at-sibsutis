import React, { useState } from 'react';

const BookSearch = ({ onSearch, onSort }) => {
  const [searchTitle, setSearchTitle] = useState('');
  const [searchAuthor, setSearchAuthor] = useState('');
  const [sortTitle, setSortTitle] = useState('asc');

  const updateSearchTitle = (event) => {
    const value = event.target.value;
    setSearchTitle(value);
    onSearch(value, searchAuthor);
  };

  const updateSearchAuthor = (event) => {
    const value = event.target.value;
    setSearchAuthor(value);
    onSearch(searchTitle, value);
  };

  const updateSortTitle = (event) => {
    const value = event.target.value;
    setSortTitle(value);
    onSort('title', value);
  };

  return (
    <div style={styles.searchSortContainer}>
      <input
        type="text"
        placeholder="Поиск по названию"
        value={searchTitle}
        onChange={updateSearchTitle}
        style={styles.searchInput}
      />
      <input
        type="text"
        placeholder="Поиск по автору"
        value={searchAuthor}
        onChange={updateSearchAuthor}
        style={styles.searchInput}
      />
      <select value={sortTitle} onChange={updateSortTitle} style={styles.select}>
        <option value="asc">По возрастанию</option>
        <option value="desc">По убыванию</option>
      </select>
    </div>
  );
};

const styles = {
  searchSortContainer: {
    margin: '20px',
    textAlign: 'center',
  },
  searchInput: {
    padding: '10px',
    marginRight: '10px',
    width: '300px',
    border: '2px solid #000',
    borderRadius: '5px',
    backgroundColor: '#fff',
    color: '#000',
    fontSize: '16px',
    outline: 'none',
  },
  select: {
    padding: '10px',
    marginRight: '10px',
    border: '2px solid #000',
    borderRadius: '5px',
    backgroundColor: '#fff',
    color: '#000',
    fontSize: '16px',
    outline: 'none',
  },
};

export default BookSearch;
