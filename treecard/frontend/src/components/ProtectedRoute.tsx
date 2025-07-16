import React from 'react';
import { Navigate } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';

const ProtectedRoute = ({ children }: { children: React.ReactNode }) => {
  const { user, isLoading } = useAuth();

  if (isLoading) {
    // Optional: Show a loading spinner while checking auth state
    return <div>Loading...</div>;
  }

  if (!user) {
    // User not logged in, redirect to login page
    return <Navigate to="/login" replace />;
  }

  // User is logged in, render the children components (e.g., Dashboard)
  return <>{children}</>;
};

export default ProtectedRoute;