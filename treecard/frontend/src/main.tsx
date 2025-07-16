import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import './index.css'
import { BrowserRouter } from 'react-router-dom';
import { AuthProvider } from './context/AuthContext'; // We'll create this
import { Toaster } from "@/components/ui/sonner" // For notifications

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <BrowserRouter>
      <AuthProvider> {/* Wrap App with Auth context */}
        <App />
        <Toaster /> {/* Add Sonner Toaster */}
      </AuthProvider>
    </BrowserRouter>
  </React.StrictMode>,
)