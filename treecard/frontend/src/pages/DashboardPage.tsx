import React, { useState } from 'react';
import axios from 'axios';
import { useAuth } from '../context/AuthContext';
import { Button } from '@/components/ui/button';
import { Card, CardContent, CardHeader, CardTitle, CardDescription } from '@/components/ui/card';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { toast } from 'sonner';
import { Dialog, DialogContent, DialogHeader, DialogTitle, DialogTrigger } from '@/components/ui/dialog';
import { Lock, ImagePlus, Instagram, TikTok, Snapchat, Youtube, Twitter, Twitch } from 'lucide-react';
import type { LinkData } from "./PublicProfilePage";

const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:3001/api';

interface EditableLinkData extends LinkData {
  order: number;
  isEnabled: boolean;
  type: 'STANDARD' | 'IMAGE' | 'PLATFORM';
  price?: number;
  imageUrl?: string;
}

// Platform templates
const PLATFORM_TEMPLATES = [
  { id: 'instagram', name: 'Instagram', icon: <Instagram className="w-5 h-5" />, urlPrefix: 'https://instagram.com/' },
  { id: 'tiktok', name: 'TikTok', icon: <TikTok className="w-5 h-5" />, urlPrefix: 'https://tiktok.com/@' },
  { id: 'snapchat', name: 'Snapchat', icon: <Snapchat className="w-5 h-5" />, urlPrefix: 'https://snapchat.com/add/' },
  { id: 'youtube', name: 'YouTube', icon: <Youtube className="w-5 h-5" />, urlPrefix: 'https://youtube.com/@' },
  { id: 'twitter', name: 'Twitter', icon: <Twitter className="w-5 h-5" />, urlPrefix: 'https://twitter.com/' },
  { id: 'twitch', name: 'Twitch', icon: <Twitch className="w-5 h-5" />, urlPrefix: 'https://twitch.tv/' },
];

const DashboardPage = () => {
  // ... existing state and auth code ...

  const [isImageDialogOpen, setImageDialogOpen] = useState(false);
  const [imagePrice, setImagePrice] = useState(0);
  const [imageFile, setImageFile] = useState<File | null>(null);

  const handleAddPremiumImage = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!imageFile || imagePrice <= 0) {
      toast.error("Please select an image and set a price");
      return;
    }

    setIsAddingLink(true);
    try {
      // Upload image to your storage (e.g., Cloudinary)
      const imageUrl = await uploadImage(imageFile);
      
      const response = await axios.post<EditableLinkData>(`${API_URL}/links`, {
        title: `Premium Content - $${imagePrice}`,
        url: '#', // Will be replaced with Stripe link
        type: 'IMAGE',
        price: imagePrice * 100, // Store in cents
        imageUrl,
      });

      setLinks([...links, response.data]);
      setImageDialogOpen(false);
      toast.success("Premium content added!");
    } catch (error) {
      toast.error("Error adding premium content");
    } finally {
      setIsAddingLink(false);
    }
  };

  const handlePlatformSelect = (platform: typeof PLATFORM_TEMPLATES[number]) => {
    setNewLinkTitle(`${platform.name} Profile`);
    setNewLinkUrl(platform.urlPrefix);
  };

  const initiateStripePayment = async (linkId: string) => {
    try {
      const { data } = await axios.post(`${API_URL}/stripe/create-session`, {
        linkId,
        successUrl: window.location.href,
        cancelUrl: window.location.href,
      });
      window.location.href = data.url;
    } catch (error) {
      toast.error("Failed to initiate payment");
    }
  };

  return (
    <div className="container mx-auto py-8 px-4">
      {/* ... existing header and profile section ... */}

      {/* Add Content Section */}
      <div className="grid grid-cols-1 md:grid-cols-2 gap-4 mb-8">
        <Card className="p-6">
          <h3 className="font-semibold mb-4">Add Premium Content</h3>
          <Dialog open={isImageDialogOpen} onOpenChange={setImageDialogOpen}>
            <DialogTrigger asChild>
              <Button variant="outline" className="w-full h-32 flex flex-col gap-2">
                <ImagePlus className="w-8 h-8" />
                Upload Image
              </Button>
            </DialogTrigger>
            <DialogContent>
              <DialogHeader>
                <DialogTitle>Create Premium Content</DialogTitle>
              </DialogHeader>
              <form onSubmit={handleAddPremiumImage} className="space-y-4">
                <div>
                  <Label>Image</Label>
                  <Input 
                    type="file" 
                    accept="image/*"
                    onChange={(e) => setImageFile(e.target.files?.[0] || null)}
                  />
                </div>
                <div>
                  <Label>Price (USD)</Label>
                  <Input
                    type="number"
                    min="1"
                    value={imagePrice}
                    onChange={(e) => setImagePrice(Number(e.target.value))}
                  />
                </div>
                <Button type="submit">Create Premium Link</Button>
              </form>
            </DialogContent>
          </Dialog>
        </Card>

        <Card className="p-6">
          <h3 className="font-semibold mb-4">Add Platform Links</h3>
          <div className="grid grid-cols-2 gap-3">
            {PLATFORM_TEMPLATES.map((platform) => (
              <Button 
                key={platform.id}
                variant="outline" 
                className="h-14 flex gap-2"
                onClick={() => handlePlatformSelect(platform)}
              >
                {platform.icon}
                {platform.name}
              </Button>
            ))}
          </div>
        </Card>
      </div>

      {/* Links List */}
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        {links.map((link) => (
          <Card key={link.id} className="relative group">
            {link.type === 'IMAGE' && (
              <>
                <div className="absolute inset-0 bg-background/80 backdrop-blur-sm flex items-center justify-center opacity-0 group-hover:opacity-100 transition-opacity">
                  <Button onClick={() => initiateStripePayment(link.id)}>
                    <Lock className="mr-2" /> Unlock for ${(link.price || 0) / 100}
                  </Button>
                </div>
                <img 
                  src={link.imageUrl} 
                  alt={link.title}
                  className="w-full h-48 object-cover rounded-t-lg"
                />
              </>
            )}
            <CardContent className="p-4">
              <div className="flex items-center gap-2 mb-2">
                {link.t   ype === 'PLATFORM' && PLATFORM_TEMPLATES.find(p => p.name === link.title.split(' ')[0])?.icon}
                <h3 className="font-medium">{link.title}</h3>
              </div>
              <p className="text-sm text-muted-foreground truncate">{link.url}</p>
              <div className="mt-4 flex gap-2">
                <Button variant="outline" size="sm">Edit</Button>
                <Button variant="destructive" size="sm">Delete</Button>
              </div>
            </CardContent>
          </Card>
        ))}
      </div>
    </div>
  );
};

// Example image upload function
async function uploadImage(file: File): Promise<string> {
  const formData = new FormData();
  formData.append('file', file);
  formData.append('upload_preset', 'your_upload_preset');
  
  const response = await axios.post(
    'https://api.cloudinary.com/v1_1/your-cloud-name/image/upload',
    formData
  );
  return response.data.secure_url;
}

export default DashboardPage;