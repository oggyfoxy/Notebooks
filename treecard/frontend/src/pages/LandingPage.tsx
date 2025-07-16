// src/pages/LandingPage.tsx
import { Link } from "react-router-dom";
import { Button } from "@/components/ui/button"; // or replace with your own <button>

export default function LandingPage() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-primary/10 via-secondary/10 to-primary/20 flex flex-col">
      {/* Hero Section */}
      <header className="flex flex-col items-center justify-center text-center flex-1 px-6 py-16 animate-in fade-in zoom-in duration-500">
        <h1 className="text-4xl md:text-6xl font-extrabold tracking-tight mb-4 text-primary">
          TreeCard
        </h1>
        <p className="text-lg md:text-2xl max-w-xl text-muted-foreground mb-8">
          All your important links in one place – beautifully displayed and
          ready to monetize.
        </p>

        <div className="space-x-4">
          <Button asChild size="lg">
            <Link to="/signup">Get Started</Link>
          </Button>
          <Button asChild variant="outline" size="lg">
            <Link to="/login">Log In</Link>
          </Button>
        </div>

        <div className="mt-8 text-sm text-muted-foreground">
          <span>Or visit an example: </span>
          <Link
            to="/demo_user"
            className="text-primary hover:underline transition-colors"
          >
            treecard.me/demo_user
          </Link>
        </div>
      </header>

      {/* Features / Testimonials Section */}
      <main className="bg-background px-4 py-16 border-t animate-in fade-in slide-in-from-bottom-8 duration-500">
        <div className="max-w-4xl mx-auto">
          <h2 className="text-3xl md:text-4xl font-bold text-center mb-8">
            Why TreeCard?
          </h2>

          <div className="grid grid-cols-1 md:grid-cols-3 gap-8">
            {/* Card 1 */}
            <div className="p-6 rounded-lg bg-muted hover:bg-muted/50 transition-colors shadow-md">
              <h3 className="text-xl font-semibold mb-2">Monetize Effortlessly</h3>
              <p className="text-sm text-muted-foreground">
                Lock your premium links behind a paywall. Earn from your content
                without any complex setup.
              </p>
            </div>

            {/* Card 2 */}
            <div className="p-6 rounded-lg bg-muted hover:bg-muted/50 transition-colors shadow-md">
              <h3 className="text-xl font-semibold mb-2">Gorgeous Themes</h3>
              <p className="text-sm text-muted-foreground">
                Choose from stunning layouts and color schemes to match your
                brand or personal style.
              </p>
            </div>

            {/* Card 3 */}
            <div className="p-6 rounded-lg bg-muted hover:bg-muted/50 transition-colors shadow-md">
              <h3 className="text-xl font-semibold mb-2">Easy to Use</h3>
              <p className="text-sm text-muted-foreground">
                Our simple dashboard lets you add, rearrange, and edit your links
                with just a few clicks.
              </p>
            </div>
          </div>
        </div>
      </main>

      {/* Call to Action */}
      <footer className="px-4 py-16 bg-gradient-to-r from-background to-muted animate-in fade-in zoom-in-75 duration-500">
        <div className="max-w-xl mx-auto text-center">
          <h2 className="text-3xl md:text-4xl font-bold mb-4 text-foreground">
            Ready to build your own link hub?
          </h2>
          <p className="text-muted-foreground mb-8">
            Join TreeCard now and transform how you share your content online.
          </p>
          <Button asChild size="lg">
            <Link to="/signup">Sign Up Free</Link>
          </Button>
        </div>
      </footer>
    </div>
  );
}
