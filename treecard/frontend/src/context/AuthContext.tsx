import React, { createContext, useState, useContext, useEffect, ReactNode } from 'react';
import axios from 'axios'; // For API calls

const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:3001/api'; // Use env var

interface User {
    id: string;
    email: string;
    username: string;
    displayName?: string | null;
    bio?: string | null;
    profilePicUrl?: string | null;
}

interface AuthContextType {
    user: User | null;
    token: string | null;
    isLoading: boolean;
    login: (token: string, user: User) => void;
    logout: () => void;
}

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export const AuthProvider = ({ children }: { children: ReactNode }) => {
    const [user, setUser] = useState<User | null>(null);
    const [token, setToken] = useState<string | null>(localStorage.getItem('authToken'));
    const [isLoading, setIsLoading] = useState(true);

    useEffect(() => {
        const verifyToken = async () => {
            if (token) {
                try {
                    // Add token to default axios headers for subsequent requests
                    axios.defaults.headers.common['Authorization'] = `Bearer ${token}`;
                    // Fetch user data using the token
                    const response = await axios.get(`${API_URL}/auth/me`);
                    setUser(response.data);
                } catch (error) {
                    console.error("Token verification failed:", error);
                    logout(); // Clear invalid token/user
                }
            }
            setIsLoading(false);
        };
        verifyToken();
    }, [token]); // Re-run if token changes

    const login = (newToken: string, userData: User) => {
        localStorage.setItem('authToken', newToken);
        axios.defaults.headers.common['Authorization'] = `Bearer ${newToken}`;
        setToken(newToken);
        setUser(userData);
    };

    const logout = () => {
        localStorage.removeItem('authToken');
        delete axios.defaults.headers.common['Authorization'];
        setToken(null);
        setUser(null);
    };

    return (
        <AuthContext.Provider value={{ user, token, isLoading, login, logout }}>
            {children}
        </AuthContext.Provider>
    );
};

export const useAuth = () => {
    const context = useContext(AuthContext);
    if (context === undefined) {
        throw new Error('useAuth must be used within an AuthProvider');
    }
    return context;
};