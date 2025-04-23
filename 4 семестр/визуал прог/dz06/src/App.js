import React, { useState, useEffect } from 'react';
import axios from 'axios';
import WeatherDisplay from './WeatherDisplay';

const API_KEY = 'eb4825f6f3d9d0ae861db8f355075906';

function App() {
  const [weatherData, setWeatherData] = useState(null);
  const [city, setCity] = useState('Novosibirsk');
  const [inputCity, setInputCity] = useState('');
  const [coordinates, setCoordinates] = useState({ lat: null, lon: null });
  const [error, setError] = useState(null); 
  useEffect(() => {
    fetchWeather();
  }, [city]);

  const fetchWeather = async () => {
    try {
      const geoResponse = await axios.get(
        `http://api.openweathermap.org/geo/1.0/direct?q=${city}&limit=1&appid=${API_KEY}`
      );

      if (!geoResponse.data || geoResponse.data.length === 0) {
        setError('Город не найден. Попробуйте другой.');
        setWeatherData(null); 
        return;
      }

      const { lat, lon } = geoResponse.data[0];
      setCoordinates({ lat, lon });

      const weatherResponse = await axios.get(
        `https://api.openweathermap.org/data/2.5/forecast?lat=${lat}&lon=${lon}&appid=${API_KEY}&units=metric`
      );
      setWeatherData(weatherResponse.data);
      setError(null); 
    } catch (error) {
      console.error('Error fetching weather data', error);
      setError('Ошибка при загрузке данных. Проверьте название города.');
      setWeatherData(null); 
    }
  };

  const handleSearch = (e) => {
    e.preventDefault();
    if (!inputCity.trim()) {
      setError('Введите название города');
      return;
    }
    setCity(inputCity);
    setInputCity('');
  };

  let backgroundColor = '#4e71f3';
  if (weatherData) {
    const currentHour = new Date(weatherData.list[0].dt_txt).getHours();
    if (currentHour >= 18 || currentHour < 6) {
      backgroundColor = '#010c39';
    }
  }

  return (
    <div style={{ textAlign: 'center', padding: '20px', minHeight: '100vh', margin: 0, backgroundColor }}>
      <form onSubmit={handleSearch} style={{ marginBottom: '20px' }}>
        <input
          type="text"
          placeholder="Введите город"
          value={inputCity}
          onChange={(e) => setInputCity(e.target.value)}
          style={{ padding: '10px', fontSize: '16px', borderRadius: '5px', border: '1px solid #ccc' }}
        />
        <button
          type="submit"
          style={{
            padding: '10px 20px',
            fontSize: '16px',
            borderRadius: '5px',
            border: 'none',
            backgroundColor: '#4e71f3',
            color: 'white',
            marginLeft: '10px',
            cursor: 'pointer',
          }}
        >
          Поиск
        </button>
      </form>

      {error && (
        <div style={{ color: 'red', marginBottom: '20px' }}>
          {error}
        </div>
      )}

      {weatherData && <WeatherDisplay weatherData={weatherData} city={city} coordinates={coordinates} />}
    </div>
  );
}

export default App;
