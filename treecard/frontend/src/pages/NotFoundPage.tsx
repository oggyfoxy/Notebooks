// src/pages/NotFoundPage.tsx
import { Link } from 'react-router-dom';
import { Button } from '@/components/ui/button'; // Use the shadcn button

const NotFoundPage = () => {
  return (
    <div className="flex flex-col items-center justify-center min-h-screen text-center px-4 bg-background">
      <h1 className="text-6xl font-bold text-primary mb-4">404</h1>
      <h2 className="text-2xl font-semibold mb-3 text-foreground">Page Not Found</h2>
      <p className="text-muted-foreground mb-8">
        Oops! The page you're looking for doesn't seem to exist.
      </p>
      <Button asChild>
        <Link to="/">Go Back Home</Link>
      </Button>
    </div>
  );
};

export default NotFoundPage;