import express, { Request, Response, NextFunction } from 'express';
import cors from 'cors';
import { PrismaClient } from '@prisma/client';
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import { z } from 'zod';
import 'dotenv/config'; // Load .env variables



import Stripe from 'stripe';
const stripe = new Stripe(process.env.STRIPE_SECRET_KEY!, {
  apiVersion: '2024-04-10'
});


const prisma = new PrismaClient();
const app = express();
const PORT = process.env.PORT || 3001;
const JWT_SECRET = process.env.JWT_SECRET || 'YOUR_SUPER_SECRET_KEY'; // Change this!

app.use(cors()); // Allow frontend requests
app.use(express.json());

// --- Zod Schemas for Validation ---
const signupSchema = z.object({
    email: z.string().email(),
    username: z.string().min(3).regex(/^[a-zA-Z0-9_]+$/, "Username can only contain letters, numbers, and underscores"),
    password: z.string().min(6),
});

const loginSchema = z.object({
    email: z.string().email(),
    password: z.string(),
});

// Update linkSchema in server.ts
const linkSchema = z.object({
    title: z.string().min(1),
    url: z.string().url(),
    type: z.enum(['STANDARD', 'IMAGE', 'PLATFORM']),
    price: z.number().int().min(0).optional(),
    imageUrl: z.string().url().optional()
  }).superRefine((data, ctx) => {
    if (data.type === 'IMAGE' && !data.imageUrl) {
      ctx.addIssue({
        code: z.ZodIssueCode.custom,
        message: "Image URL is required for IMAGE type links",
      });
    }
    if (data.type === 'IMAGE' && (!data.price || data.price < 100)) {
      ctx.addIssue({
        code: z.ZodIssueCode.custom,
        message: "Price must be at least $1 (100 cents) for IMAGE type links",
      });
    }
  });

// --- Middleware ---
interface AuthRequest extends Request {
    user?: { id: string };
}

const authenticateToken = (req: AuthRequest, res: Response, next: NextFunction) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1]; // Bearer TOKEN

    if (token == null) return res.sendStatus(401); // No token

    jwt.verify(token, JWT_SECRET, (err: any, user: any) => {
        if (err) return res.sendStatus(403); // Invalid token
        req.user = user as { id: string }; // Add user payload to request object
        next();
    });
};


// --- Routes ---

// Check Username Availability
app.get('/api/username/check', async (req: Request, res: Response) => {
    const username = req.query.username as string;
    if (!username) {
        return res.status(400).json({ available: false, message: 'Username query parameter is required' });
    }
    try {
        const existingUser = await prisma.user.findUnique({ where: { username } });
        res.json({ available: !existingUser });
    } catch (error) {
        console.error("Username check error:", error);
        res.status(500).json({ available: false, message: 'Error checking username availability' });
    }
});


// Signup
app.post('/api/auth/signup', async (req: Request, res: Response) => {
    try {
        const result = signupSchema.safeParse(req.body);
        if (!result.success) {
            return res.status(400).json({ errors: result.error.errors });
        }
        const { email, username, password } = result.data;

        // Check if email or username already exists
        const existingUser = await prisma.user.findFirst({
            where: { OR: [{ email }, { username }] }
        });
        if (existingUser) {
            return res.status(409).json({ message: 'Email or username already taken' });
        }

        const passwordHash = await bcrypt.hash(password, 10);
        const user = await prisma.user.create({
            data: { email, username, passwordHash },
        });

        // Don't send password hash back
        const { passwordHash: _, ...userWithoutPassword } = user;
        res.status(201).json(userWithoutPassword);

    } catch (error) {
        console.error("Signup error:", error);
        res.status(500).json({ message: 'Error creating user' });
    }
});

// Login
app.post('/api/auth/login', async (req: Request, res: Response) => {
     try {
        const result = loginSchema.safeParse(req.body);
        if (!result.success) {
            return res.status(400).json({ errors: result.error.errors });
        }
        const { email, password } = result.data;

        const user = await prisma.user.findUnique({ where: { email } });
        if (!user || !(await bcrypt.compare(password, user.passwordHash))) {
            return res.status(401).json({ message: 'Invalid email or password' });
        }

        const token = jwt.sign({ id: user.id }, JWT_SECRET, { expiresIn: '1d' }); // Token expires in 1 day
         // Don't send password hash back
        const { passwordHash: _, ...userWithoutPassword } = user;

        res.json({ token, user: userWithoutPassword });

    } catch (error) {
         console.error("Login error:", error);
        res.status(500).json({ message: 'Error logging in' });
    }
});

// Get Logged-in User's Profile (Example protected route)
app.get('/api/auth/me', authenticateToken, async (req: AuthRequest, res: Response) => {
    if (!req.user) return res.sendStatus(401); // Should be caught by middleware, but safety check

    try {
        const user = await prisma.user.findUnique({
            where: { id: req.user.id },
            select: { id: true, email: true, username: true, displayName: true, bio: true, profilePicUrl: true } // Select fields to return
        });
        if (!user) return res.sendStatus(404);
        res.json(user);
    } catch (error) {
        console.error("Get me error:", error);
        res.status(500).json({ message: "Error fetching user profile" });
    }
});

// Get Public Profile Data
app.get('/api/public/:username', async (req: Request, res: Response) => {
    const { username } = req.params;
    try {
        const user = await prisma.user.findUnique({
            where: { username },
            select: {
                id: true, // Keep id for potential client-side use, but maybe remove later
                username: true,
                displayName: true,
                bio: true,
                profilePicUrl: true,
                links: {
                    where: { isEnabled: true },
                    orderBy: { order: 'asc' },
                    select: {
                        id: true,
                        title: true,
                        url: true,
                        type: true,
                        // Select Unlockt/Platform fields here when added
                    }
                }
            }
        });

        if (!user) {
            return res.status(404).json({ message: 'User not found' });
        }
        res.json(user);
    } catch (error) {
        console.error("Public profile error:", error);
        res.status(500).json({ message: 'Error fetching public profile' });
    }
});

// --- Link Management (Protected) ---

// Get User's Links (for editor)
app.get('/api/links', authenticateToken, async (req: AuthRequest, res: Response) => {
    if (!req.user) return res.sendStatus(401);
    try {
        const links = await prisma.link.findMany({
            where: { userId: req.user.id },
            orderBy: { order: 'asc' }
        });
        res.json(links);
    } catch (error) {
        console.error("Get links error:", error);
        res.status(500).json({ message: "Error fetching links" });
    }
});

// Create Link
app.post('/api/links', authenticateToken, async (req: AuthRequest, res: Response) => {
    if (!req.user) return res.sendStatus(401);
     try {
        const result = linkSchema.safeParse(req.body);
         if (!result.success) {
            return res.status(400).json({ errors: result.error.errors });
        }
        const { title, url } = result.data;

        // Get max current order for the user to append the new link
        const maxOrderLink = await prisma.link.findFirst({
            where: { userId: req.user.id },
            orderBy: { order: 'desc' },
            select: { order: true }
        });
        const newOrder = (maxOrderLink?.order ?? -1) + 1;

        const newLink = await prisma.link.create({
            data: {
                title,
                url,
                order: newOrder,
                userId: req.user.id,
                type: 'STANDARD' // Default type for now
            }
        });
        res.status(201).json(newLink);
    } catch (error) {
         console.error("Create link error:", error);
        res.status(500).json({ message: "Error creating link" });
    }
});




// Add after login route
// Stripe Webhook Route
app.post('/api/stripe/webhook', express.raw({type: 'application/json'}), 
async (req: Request, res: Response) => {
  const sig = req.headers['stripe-signature']!;
  const endpointSecret = process.env.STRIPE_WEBHOOK_SECRET!;

  let event;
  try {
    event = stripe.webhooks.constructEvent(req.body, sig, endpointSecret);
  } catch (err) {
    return res.status(400).send(`Webhook Error: ${err.message}`);
  }

  switch (event.type) {
    case 'checkout.session.completed':
      const session = event.data.object as Stripe.Checkout.Session;
      // Handle successful payment here
      // You can update link access in your database
      break;
    default:
      console.log(`Unhandled event type ${event.type}`);
  }

  res.json({received: true});
});

// Create Stripe Checkout Session
app.post('/api/stripe/create-session', authenticateToken, 
async (req: AuthRequest, res: Response) => {
  if (!req.user) return res.sendStatus(401);

  const { linkId } = req.body;
  try {
    // Get the link from database
    const link = await prisma.link.findUnique({
      where: { id: linkId, userId: req.user.id }
    });

    if (!link || !link.price) {
      return res.status(400).json({ error: 'Invalid link' });
    }

    // Create Stripe product and price
    const product = await stripe.products.create({
      name: link.title,
      images: link.imageUrl ? [link.imageUrl] : [],
    });

    const price = await stripe.prices.create({
      product: product.id,
      unit_amount: link.price,
      currency: 'usd',
    });

    // Update link with Stripe IDs
    await prisma.link.update({
      where: { id: linkId },
      data: {
        stripeProductId: product.id,
        stripePriceId: price.id
      }
    });

    // Create checkout session
    const session = await stripe.checkout.sessions.create({
      payment_method_types: ['card'],
      line_items: [{
        price: price.id,
        quantity: 1,
      }],
      mode: 'payment',
      success_url: `${process.env.FRONTEND_URL}/success?session_id={CHECKOUT_SESSION_ID}`,
      cancel_url: `${process.env.FRONTEND_URL}/cancel`,
    });

    res.json({ url: session.url });
  } catch (error) {
    console.error('Stripe error:', error);
    res.status(500).json({ error: 'Payment processing failed' });
  }
});

// TODO: Add PUT /api/links/:id (Update Link)
// TODO: Add DELETE /api/links/:id (Delete Link)
// TODO: Add PUT /api/links/reorder (Update multiple link orders)
// TODO: Add PUT /api/profile (Update User Profile)


// --- Start Server ---
app.listen(PORT, () => {
    console.log(`Backend server running on http://localhost:${PORT}`);
});
