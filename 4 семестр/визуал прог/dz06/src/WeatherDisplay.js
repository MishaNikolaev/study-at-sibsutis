import React from 'react';

function WeatherDisplay({ weatherData, city, coordinates }) {
  const { list } = weatherData;
  const currentWeather = list[0];
  const currentDate = new Date(currentWeather.dt_txt);
  const isNight = currentDate.getHours() >= 18 || currentDate.getHours() < 6;

  const roundTemp = (temp) => Math.round(temp);

  const getDayNightTemps = (dayData) => {
    const dayTemp = roundTemp(dayData.find((item) => new Date(item.dt_txt).getHours() === 12)?.main.temp);
    const nightTemp = roundTemp(dayData.find((item) => new Date(item.dt_txt).getHours() === 0)?.main.temp);
    return { dayTemp, nightTemp };
  };

  const styles = {
    weatherContainer: {
      marginTop: '20px',
      borderRadius: '20px',
      padding: '20px',
      color: 'white',
      margin: 0,
      backgroundColor: isNight ? '#010c39' : '#4e71f3',
      //backgroundColor: isNight ? '#4e71f3' : '#010c39',
    },
    header: {
      marginBottom: '20px',
    },
    headerH1: {
      fontSize: '1.5rem',
      margin: 0,
      color: 'gray',
      fontWeight: 'normal',
      fontFamily: '"Gantauluauope Numbers", sans-serif',
    },
    headerH2: {
      fontSize: '2rem',
      margin: '10px 0',
      fontWeight: 'bold',
      textAlign: 'left',
      fontFamily: '"Gantauluauope Numbers", sans-serif',
    },
    currentWeather: {
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'space-between',
      marginTop: '10px',
    },
    currentWeatherImg: {
      width: '100px',
      height: '100px',
    },
    currentWeatherTemp: {
      fontSize: '3rem',
      marginLeft: '20px',
      fontFamily: '"Gantauluauope Numbers", sans-serif',
    },
    hourlyWeather: {
      display: 'flex',
      overflowX: 'auto',
      gap: '20px',
      marginBottom: '20px',
      scrollbarWidth: 'true',
    },
    hourlyCard: {
      backgroundColor: 'rgba(255, 255, 255, 0.2)',
      borderRadius: '10px',
      padding: '10px',
      textAlign: 'center',
    },
    hourlyCardImg: {
      width: '50px',
      height: '50px',
    },
    details: {
      display: 'flex',
      justifyContent: 'space-around',
      marginBottom: '20px',
    },
    detail: {
      textAlign: 'center',
    },
    detailLabel: {
      color: 'gray',
    },
    coordinates: {
      marginBottom: '20px',
      fontFamily: '"Gantauluauope Numbers", sans-serif',
    },
    weeklyWeather: {
      display: 'flex',
      flexDirection: 'column',
      gap: '10px',
      backgroundColor: 'rgba(255, 255, 255, 0.2)',
      borderRadius: '10px',
      padding: '10px',
    },
    weeklyCard: {
      display: 'flex',
      justifyContent: 'space-between',
      alignItems: 'center',
      padding: '10px',
    },
    weeklyCardImg: {
      width: '50px',
      height: '50px',
    },
  };

  return (
    <div style={styles.weatherContainer}>
      <div style={styles.header}>
        <h1 style={styles.headerH1}>{currentDate.toLocaleDateString('en-US', { weekday: 'long', day: 'numeric' })}</h1>
        <h2 style={styles.headerH2}>{city}</h2>
        <div style={styles.currentWeather}>
          <p style={styles.currentWeatherTemp}>{roundTemp(currentWeather.main.temp)}°C</p>
          <img src={`http://openweathermap.org/img/wn/${currentWeather.weather[0].icon}@2x.png`} alt="weather icon" style={styles.currentWeatherImg} />
        </div>
      </div>
      <div style={styles.coordinates}>
        <p>Latitude: {coordinates.lat}</p>
        <p>Longitude: {coordinates.lon}</p>
      </div>
      <div style={styles.hourlyWeather}>
        {list.slice(0, 8).map((item, index) => (
          <div key={index} style={styles.hourlyCard}>
            <p>{new Date(item.dt_txt).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })}</p>
            <img src={`http://openweathermap.org/img/wn/${item.weather[0].icon}.png`} alt="weather icon" style={styles.hourlyCardImg} />
            <p>{roundTemp(item.main.temp)}°C</p>
          </div>
        ))}
      </div>
      <div style={styles.details}>
        <div style={styles.detail}>
          <p style={styles.detailLabel}>Humidity</p>
          <p>{currentWeather.main.humidity}%</p>
        </div>
        <div style={styles.detail}>
          <p style={styles.detailLabel}>Wind</p>
          <p>{currentWeather.wind.speed} m/s</p>
        </div>
        <div style={styles.detail}>
          <p style={styles.detailLabel}>Air Pressure</p>
          <p>{currentWeather.main.pressure} hPa</p>
        </div>
        <div style={styles.detail}>
          <p style={styles.detailLabel}>UV</p>
          <p>3</p>
        </div>
      </div>
      <div style={styles.weeklyWeather}>
        {list.filter((item, index) => index % 8 === 0).map((item, index) => {
          const { dayTemp, nightTemp } = getDayNightTemps(list.slice(index * 8, (index + 1) * 8));
          return (
            <div key={index} style={styles.weeklyCard}>
              <p>{new Date(item.dt_txt).toLocaleDateString('en-US', { weekday: 'long' })}</p>
              <div style={{ display: 'flex', alignItems: 'center', gap: '10px' }}>
                <img src={`http://openweathermap.org/img/wn/${item.weather[0].icon}.png`} alt="weather icon" style={styles.weeklyCardImg} />
                <p>{dayTemp}°C / {nightTemp}°C</p>
              </div>
            </div>
          );
        })}
      </div>
    </div>
  );
}

export default WeatherDisplay;
