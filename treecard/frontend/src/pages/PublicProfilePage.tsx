import { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import axios from 'axios';
import { Avatar, AvatarFallback, AvatarImage } from "@/components/ui/avatar";
import { Button } from '@/components/ui/button'; // Use Button for links now
import { Skeleton } from "@/components/ui/skeleton"; // For loading state
import { Lock } from 'lucide-react'; // Icon for Unlockt links

// Define the structure of the data expected from the API
export interface LinkData {
    id: string;
    title: string;
    url: string;
    type: 'STANDARD' | 'UNLOCKT' | 'PLATFORM'; // Matches Prisma Enum
    // Add unlockt/platform specific fields later
}

interface PublicProfileData {
    username: string;
    displayName?: string | null;
    bio?: string | null;
    profilePicUrl?: string | null;
    links: LinkData[];
}

const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:3001/api';

const PublicProfilePage = () => {
    const { username } = useParams<{ username: string }>();
    const [profile, setProfile] = useState<PublicProfileData | null>(null);
    const [isLoading, setIsLoading] = useState(true);
    const [error, setError] = useState<string | null>(null);

    // TODO: State and handler for Unlockt Modal

    useEffect(() => {
        const fetchProfile = async () => {
            if (!username) return;
            setIsLoading(true);
            setError(null);
            try {
                const response = await axios.get<PublicProfileData>(`${API_URL}/public/${username}`);
                setProfile(response.data);
            } catch (err: any) {
                console.error("Error fetching profile:", err);
                setError(err.response?.status === 404 ? 'User not found.' : 'Could not load profile.');
            } finally {
                setIsLoading(false);
            }
        };
        fetchProfile();
    }, [username]); // Refetch if username changes

    const handleUnlocktClick = (link: LinkData) => {
        console.log("Unlockt link clicked:", link);
        // TODO: Implement modal logic here - fetch price/details if needed, show modal
        alert(`Simulating Unlock for: ${link.title}\nURL (hidden): ${link.url}`);
    };

    // --- Render Logic ---

    if (isLoading) {
        return <ProfileSkeleton />; // Show loading skeleton
    }

    if (error) {
        return (
            <div className="flex flex-col items-center justify-center min-h-screen text-center px-4">
                 <h1 className="text-2xl font-semibold text-red-600 mb-4">Error</h1>
                 <p>{error}</p>
                 <Button variant="link" onClick={() => window.location.reload()} className="mt-4">Try Again</Button>
            </div>
        );
    }

    if (!profile) {
        return <div className="flex items-center justify-center min-h-screen">Profile data missing.</div>; // Should ideally not happen if no error
    }

    // Helper to get initials for Avatar fallback
    const getInitials = (name?: string | null) => {
        return name ? name.split(' ').map(n => n[0]).join('').toUpperCase() : 'TC';
    };

    return (
        <div className="flex justify-center min-h-screen bg-brand-secondary-bg py-8 px-4">
            <div className="w-full max-w-lg">
                {/* Header */}
                <header className="text-center mb-8">
                    <Avatar className="w-24 h-24 mx-auto mb-4 border-2 border-primary">
                        <AvatarImage src={profile.profilePicUrl || undefined} alt={profile.displayName || profile.username} />
                        <AvatarFallback className="text-3xl">{getInitials(profile.displayName)}</AvatarFallback>
                    </Avatar>
                    <h1 className="text-2xl font-bold">{profile.displayName || `@${profile.username}`}</h1>
                    {profile.displayName && <p className="text-md text-muted-foreground">@{profile.username}</p>}
                    {profile.bio && <p className="mt-2 text-sm text-foreground/80">{profile.bio}</p>}
                </header>

                {/* Links */}
                <main className="space-y-4">
                    {profile.links.map((link) => (
                        <Button
                            key={link.id}
                            asChild // Makes the Button act as a wrapper for the <a> tag
                            variant={link.type === 'UNLOCKT' ? "secondary" : "default"} // Style Unlockt differently
                            className={`link-button-public ${link.type === 'UNLOCKT' ? 'link-button-unlockt' : 'link-button-standard'} justify-center relative`}
                            onClick={link.type === 'UNLOCKT' ? (e) => { e.preventDefault(); handleUnlocktClick(link); } : undefined}
                        >
                            <a
                                href={link.type !== 'UNLOCKT' ? link.url : '#'} // Prevent direct navigation for Unlockt
                                target="_blank"
                                rel="noopener noreferrer"
                                className="flex items-center justify-center w-full" // Ensure link fills button
                            >
                                {link.type === 'UNLOCKT' && (
                                    <Lock className="w-4 h-4 mr-2 absolute left-4 opacity-80" /> // Lock icon
                                )}
                                {link.title}
                                {/* Add platform icons later based on link.type === 'PLATFORM' */}
                            </a>
                        </Button>
                    ))}
                     {profile.links.length === 0 && <p className="text-center text-muted-foreground">No links added yet.</p>}
                </main>

                {/* Footer */}
                <footer className="text-center mt-12">
                     <a href="/" target="_blank" rel="noopener noreferrer" className="text-sm text-muted-foreground hover:text-primary transition-colors">
                        Powered by TreeCard
                     </a>
                </footer>
            </div>
             {/* TODO: Add Unlockt Modal Component here */}
        </div>
    );
};

// Skeleton Component for Loading State
const ProfileSkeleton = () => (
    <div className="flex justify-center min-h-screen bg-brand-secondary-bg py-8 px-4">
        <div className="w-full max-w-lg animate-pulse">
            <header className="text-center mb-8 flex flex-col items-center">
                <Skeleton className="w-24 h-24 rounded-full mx-auto mb-4" />
                <Skeleton className="h-7 w-48 mb-2" />
                <Skeleton className="h-5 w-32 mb-3" />
                <Skeleton className="h-4 w-64" />
            </header>
            <main className="space-y-4">
                <Skeleton className="h-12 w-full rounded-lg" />
                <Skeleton className="h-12 w-full rounded-lg" />
                <Skeleton className="h-12 w-full rounded-lg" />
            </main>
             <footer className="text-center mt-12">
                 <Skeleton className="h-4 w-32 mx-auto" />
             </footer>
        </div>
    </div>
);

export default PublicProfilePage;
