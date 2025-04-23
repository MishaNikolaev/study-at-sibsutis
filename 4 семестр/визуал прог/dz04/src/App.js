import React, { useEffect, useState } from 'react';
import axios from 'axios';
import BookCard from './BookCard';

const App = () => {
  const [books, setBooks] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchBooks = async () => {
      try {
        const booksResponse = await axios.get('https://fakeapi.extendsclass.com/books');
        const booksData = booksResponse.data;

        const delay = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

        const booksWithCovers = await Promise.all(
          booksData.slice(0, 20).map(async (book, index) => { 
            await delay(index * 2000); 
            try {
              const coverResponse = await axios.get(
                `https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`
              );
              const cover = coverResponse.data.items?.[0]?.volumeInfo?.imageLinks?.thumbnail || '';
              return { ...book, cover };
            } catch (error) {
              console.error(`Error fetching cover for ISBN ${book.isbn}:`, error);
              return { ...book, cover: '' }; 
            }
          })
        );

        setBooks(booksWithCovers);
      } catch (error) {
        console.error('Error fetching books:', error);
        setError('Ошибка при загрузке данных. Пожалуйста, попробуйте позже.');
      } finally {
        setLoading(false);
      }
    };

    fetchBooks();
  }, []);

  if (loading) {
    return <div>Не злите Глеба</div>;
  }

  if (error) {
    return <div>{error}</div>;
  }

  return (
    <div style={styles.container}>
      {books.map((book) => (
        <BookCard
          key={book.id}
          title={book.title}
          authors={book.authors}
          cover={book.cover}
        />
      ))}
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
