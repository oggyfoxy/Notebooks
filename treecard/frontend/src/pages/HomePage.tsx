// treecard/frontend/src/pages/HomePage.tsx
import { Link } from 'react-router-dom';
import { Button } from '@/components/ui/button'; // Assuming button component exists now

const HomePage = () => {
  return (
    <div className="flex flex-col items-center justify-center min-h-screen text-center px-4 bg-gradient-to-br from-green-50 via-white to-green-100">
       <img src="/path/to/your/logo.svg" alt="TreeCard Logo" className="h-12 mb-6" /> 
       <h1 className="text-5xl font-extrabold mb-4 text-gray-800">
         Your Links, <span className="text-primary">Monetized</span>.
       </h1>
       <p className="text-lg text-muted-foreground mb-8 max-w-xl">
         The simple, elegant way to share all your content and unlock exclusive links with TreeCard.
       </p>
       <div className="space-x-4">
          <Button asChild size="lg">
            <Link to="/signup">Get Started Free</Link>
          </Button>
          <Button asChild variant="outline" size="lg">
             <Link to="/login">Log In</Link>
          </Button>
          <Button asChild variant="outline" size="lg">
             <Link to="/landing">Landing</Link>
          </Button>
       </div>
       <p className="mt-12 text-sm text-muted-foreground">
         Explore an example: <Link to="/demo_user" className="text-primary hover:underline">treecard.me/demo_user</Link>
         {/* Replace demo_user with a real example username once available */}
       </p>
    </div>
  );
};

export default HomePage;