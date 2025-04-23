import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import Comments from './components/Comments';
import Posts from './components/Posts';
import Albums from './components/Albums';
import TODOS from './components/TODOS';
import Users from './components/Users';

function App() {
  return (
    <Router>
      <div style={{ display: 'flex', minHeight: '100vh' }}>
        <nav style={{
          width: '220px',
          backgroundColor: '#d5d5d5', 
          color: '#333333', 
          padding: '0',
          boxShadow: '2px 0 5px rgba(0,0,0,0.05)',
          position: 'sticky',
          top: 0,
          height: '100vh',
          borderRight: '1px solid #b0b0b0'
        }}>
          <div style={{
            padding: '20px',
            marginBottom: '10px',
            fontSize: '22px',
            fontWeight: 'bold',
            display: 'flex',
            alignItems: 'center',
            backgroundColor: '#8a7f8e', 
            color: 'white'
          }}>
            <span>Menu azaza</span>
          </div>
          
          <ul style={{ listStyle: 'none', padding: 0, margin: 0 }}>
            {[
              { to: '/posts', icon: '📝', text: 'Posts' },
              { to: '/albums', icon: '📷', text: 'Albums' },
              { to: '/todos', icon: '✅', text: 'Todos' },
              { to: '/users', icon: '👥', text: 'Users' },
              { to: '/comments', icon: '💬', text: 'Comments' }
            ].map((item, index) => (
              <li key={index} style={{ margin: 0 }}>
                <Link 
                  to={item.to}
                  style={{
                    display: 'flex',
                    alignItems: 'center',
                    padding: '12px 20px',
                    color: '#333333',
                    textDecoration: 'none',
                    transition: 'all 0.2s ease',
                    fontSize: '15px',
                    borderLeft: '3px solid transparent',
                    ':hover': {
                      backgroundColor: '#c0c0c0',
                      borderLeft: '3px solid rgb(3, 111, 170)'
                    }
                  }}
                  activeStyle={{
                    backgroundColor: '#c0c0c0',
                    fontWeight: 'bold',
                    borderLeft: '3px solid rgb(19, 115, 166)'
                  }}
                >
                  <span style={{ marginRight: '12px', fontSize: '16px' }}>{item.icon}</span>
                  {item.text}
                </Link>
              </li>
            ))}
          </ul>
          
          <div style={{
            marginTop: 'auto',
            padding: '15px',
            fontSize: '11px',
            color: '#555555',
            textAlign: 'center',
            borderTop: '1px solid #b0b0b0',
            backgroundColor: '#d5d5d5'
          }}>
            © 2025 made by Glebasik and Mishanya
          </div>
        </nav>

        <main style={{ 
          flex: 1, 
          padding: '25px',
          backgroundColor: '#f5f5f5'
        }}>
          <Routes>
            <Route path="/posts" element={<Posts />} />
            <Route path="/albums" element={<Albums />} />
            <Route path="/todos" element={<TODOS />} />
            <Route path="/users" element={<Users />} />
            <Route path="/comments" element={<Comments />} />
            <Route path="/" element={<Posts />} />
          </Routes>
        </main>
      </div>
    </Router>
  );
}

export default App;
