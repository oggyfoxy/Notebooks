import { Routes, Route } from 'react-router-dom';
import PublicProfilePage from './pages/PublicProfilePage';
import LoginPage from './pages/LoginPage';
import SignupPage from './pages/SignupPage';
import DashboardPage from './pages/DashboardPage';
import HomePage from './pages/HomePage.tsx';
import LandingPage from './pages/LandingPage.tsx';
import ProtectedRoute from './components/ProtectedRoute'; // We'll create this
import NotFoundPage from './pages/NotFoundPage.tsx';

function App() {
  return (
    <Routes>
      <Route path="/" element={<LandingPage />} />
      <Route path="/login" element={<LoginPage />} />
      <Route path="/signup" element={<SignupPage />} />

      {/* Protected Dashboard Route */}
      <Route
        path="/dashboard"
        element={
          <ProtectedRoute>
            <DashboardPage />
          </ProtectedRoute>
        }
      />

      {/* Public Profile Route - MUST BE LAST generic match */}
      <Route path="/:username" element={<PublicProfilePage />} />

      <Route path="*" element={<NotFoundPage />} /> {/* Catch-all for 404 */}
    </Routes>
  );
}

export default App;