import React, { useEffect, useState } from 'react';
import axios from 'axios';
import BookCard from './BookCard';
import BookSearch from './BookSearch';

const App = () => {
  const [books, setBooks] = useState([]);
  const [filteredBooks, setFilteredBooks] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchBooks = async () => {
      try {
        const booksResponse = await axios.get('https://fakeapi.extendsclass.com/books');
        const booksData = booksResponse.data;

        const delay = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

        const booksWithCovers = await Promise.all(
          booksData.slice(0, 10).map(async (book, index) => { 
            await delay(index * 2000); 
            try {
              const coverResponse = await axios.get(
                `https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`
              );
              const cover = coverResponse.data.items?.[0]?.volumeInfo?.imageLinks?.thumbnail || '';
              return { ...book, cover };
            } catch (error) {
              console.error(`Error fetch image ${book.isbn}:`, error);
              return { ...book, cover: '' }; 
            }
          })
        );

        setBooks(booksWithCovers);
        setFilteredBooks(booksWithCovers);
      } catch (error) {
        console.error('Error fetch kall:', error);
        setError('Error.');
      } finally {
        setLoading(false);
      }
    };

    fetchBooks();
  }, []);

  const searchBooks = (searchTitle, searchAuthor) => {
    const filtered = books.filter(book =>
      book.title.toLowerCase().includes(searchTitle.toLowerCase()) &&
      book.authors.join(', ').toLowerCase().includes(searchAuthor.toLowerCase())
    );
    setFilteredBooks(filtered);
  };

  const sortBooks = (field, order) => {
    const sorted = orderBy([...filteredBooks], field, order);
    setFilteredBooks(sorted);
  };

  function QuickSortV2(array, L, R, compare) {
    if (L < R) {
      let i = L, j = R;
      let pivot = array[Math.floor((L + R) / 2)];

      while (i <= j) {
        while (compare(array[i], pivot) < 0) {
          i++;
        }
        while (compare(array[j], pivot) > 0) {
          j--;
        }

        if (i <= j) {
          [array[i], array[j]] = [array[j], array[i]];
          i++;
          j--;
        }
      }

      if (L < j) {
        QuickSortV2(array, L, j, compare);
      }
      if (i < R) {
        QuickSortV2(array, i, R, compare);
      }
    }
  }

  function compareBooks(a, b, field) {
    if (a[field] < b[field]) return -1;
    if (a[field] > b[field]) return 1;
    return 0;
  }

  function orderBy(array, field, order) {
    const sortedArray = [...array];
    const compare = (a, b) => {
      const result = compareBooks(a, b, field);
      return order === 'asc' ? result : -result;
    };
    QuickSortV2(sortedArray, 0, sortedArray.length - 1, compare);
    return sortedArray;
  }

  if (loading) {
    return <div>LOLading uf wait pleaaaaseee</div>;
  }

  if (error) {
    return <div>{error}</div>;
  }

  return (
    <div>
      <BookSearch onSearch={searchBooks} onSort={sortBooks} />
      <div style={styles.container}>
        {filteredBooks.map((book) => (
          <BookCard
            key={book.id}
            title={book.title}
            authors={book.authors}
            cover={book.cover}
          />
        ))}
      </div>
    </div>
  );
};

const styles = {
  container: {
    display: 'flex',
    flexWrap: 'wrap',
    justifyContent: 'center',
    padding: '20px',
  },
};

export default App;
