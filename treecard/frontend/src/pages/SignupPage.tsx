import { useState, useEffect, useCallback } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useForm } from 'react-hook-form';
import { zodResolver } from '@hookform/resolvers/zod';
import * as z from 'zod';
import axios from 'axios';
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Form, FormControl, FormField, FormItem, FormLabel, FormMessage } from "@/components/ui/form";
import { toast } from "sonner";
import { Loader2, CheckCircle, XCircle } from 'lucide-react'; // Icons for feedback

const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:3001/api';

// Zod schema for signup form validation
const signupSchema = z.object({
    email: z.string().email({ message: "Please enter a valid email address." }),
    // Added regex to match backend expectations
    username: z.string()
        .min(3, { message: "Username must be at least 3 characters." })
        .regex(/^[a-zA-Z0-9_]+$/, "Username can only contain letters, numbers, and underscores."),
    password: z.string().min(6, { message: "Password must be at least 6 characters." }),
    confirmPassword: z.string()
})
.refine((data) => data.password === data.confirmPassword, {
    message: "Passwords don't match",
    path: ["confirmPassword"], // Error applies to the confirmPassword field
});

type SignupFormValues = z.infer<typeof signupSchema>;

// Debounce function utility
function debounce<F extends (...args: any[]) => any>(func: F, waitFor: number) {
  let timeoutId: ReturnType<typeof setTimeout> | null = null;

  return (...args: Parameters<F>): Promise<ReturnType<F>> =>
    new Promise(resolve => {
      if (timeoutId) {
        clearTimeout(timeoutId);
      }
      timeoutId = setTimeout(() => resolve(func(...args)), waitFor);
    });
}


const SignupPage = () => {
    const navigate = useNavigate();
    const [isLoading, setIsLoading] = useState(false);
    const [apiError, setApiError] = useState<string | null>(null);

    // State for username availability check
    const [isCheckingUsername, setIsCheckingUsername] = useState(false);
    const [usernameAvailable, setUsernameAvailable] = useState<boolean | null>(null);
    const [usernameToCheck, setUsernameToCheck] = useState<string>('');

    const form = useForm<SignupFormValues>({
        resolver: zodResolver(signupSchema),
        defaultValues: { email: "", username: "", password: "", confirmPassword: "" },
        mode: 'onChange', // Validate fields as they change
    });

    // --- Username Availability Check ---
    const checkUsernameAvailability = useCallback(async (username: string) => {
        if (!username || username.length < 3 || !/^[a-zA-Z0-9_]+$/.test(username)) {
             setUsernameAvailable(null); // Reset if invalid format or too short
            return;
        }
        setIsCheckingUsername(true);
        setUsernameAvailable(null); // Reset availability status while checking
        try {
            const response = await axios.get(`${API_URL}/username/check`, { params: { username } });
            setUsernameAvailable(response.data.available);
        } catch (error) {
            console.error("Username check failed:", error);
            setUsernameAvailable(false); // Assume unavailable on error
            toast.error("Could not check username availability.");
        } finally {
            setIsCheckingUsername(false);
        }
    }, []); // No dependencies, it's stable

    // Debounced version of the username check function
    const debouncedCheckUsername = useCallback(debounce(checkUsernameAvailability, 500), [checkUsernameAvailability]); // Debounce by 500ms

     // Effect to trigger debounced check when username field changes
     const currentUsernameValue = form.watch('username');
     useEffect(() => {
        if (currentUsernameValue !== usernameToCheck) { // Only check if value actually changed
            setUsernameToCheck(currentUsernameValue); // Update the value being checked
            debouncedCheckUsername(currentUsernameValue);
        }
     }, [currentUsernameValue, debouncedCheckUsername, usernameToCheck]);
    // --- End Username Check ---


    const onSubmit = async (values: SignupFormValues) => {
        // Don't submit if username is known to be unavailable
        if (usernameAvailable === false) {
             toast.error("Username is already taken. Please choose another.");
             form.setError("username", { type: "manual", message: "Username is already taken."});
            return;
        }
        // Prevent submission while checking username just in case
        if (isCheckingUsername) {
            toast.warning("Please wait for username check to complete.");
            return;
        }

        setIsLoading(true);
        setApiError(null);

        // Destructure confirmPassword, it's not sent to backend
        const { confirmPassword, ...signupData } = values;

        try {
            await axios.post(`${API_URL}/auth/signup`, signupData);
            toast.success("Account created successfully! Please log in.");
            navigate('/login'); // Redirect to login page
        } catch (err: any) {
            const message = err.response?.data?.message || "Signup failed. Please try again.";
            setApiError(message);
            toast.error(message);
            console.error("Signup error:", err);
             // Optionally set specific form errors if backend provides field info
            if (message.toLowerCase().includes('email')) {
                 form.setError("email", { type: "manual", message: "Email already in use." });
            } else if (message.toLowerCase().includes('username')) {
                form.setError("username", { type: "manual", message: "Username already taken." });
                setUsernameAvailable(false); // Update availability state
            }
        } finally {
            setIsLoading(false);
        }
    };

    return (
        <div className="flex items-center justify-center min-h-screen bg-gray-100">
            <Card className="w-full max-w-md">
                <CardHeader className="text-center">
                    <CardTitle className="text-2xl font-bold">Create your TreeCard</CardTitle>
                    <CardDescription>Join us and start sharing your links!</CardDescription>
                </CardHeader>
                <CardContent>
                    <Form {...form}>
                        <form onSubmit={form.handleSubmit(onSubmit)} className="space-y-4">
                            <FormField
                                control={form.control}
                                name="email"
                                render={({ field }) => (
                                    <FormItem>
                                        <FormLabel>Email</FormLabel>
                                        <FormControl>
                                            <Input type="email" placeholder="you@example.com" {...field} />
                                        </FormControl>
                                        <FormMessage />
                                    </FormItem>
                                )}
                            />
                             <FormField
                                control={form.control}
                                name="username"
                                render={({ field }) => (
                                    <FormItem>
                                        <FormLabel>Username</FormLabel>
                                         <div className="relative">
                                            <FormControl>
                                                <Input placeholder="your_unique_username" {...field} />
                                            </FormControl>
                                            <div className="absolute inset-y-0 right-0 pr-3 flex items-center text-sm leading-5">
                                                 {isCheckingUsername && <Loader2 className="h-4 w-4 animate-spin text-muted-foreground" />}
                                                 {!isCheckingUsername && usernameAvailable === true && form.getFieldState('username').invalid === false && (
                                                     <CheckCircle className="h-4 w-4 text-green-500" />
                                                 )}
                                                 {!isCheckingUsername && usernameAvailable === false && (
                                                     <XCircle className="h-4 w-4 text-red-500" />
                                                 )}
                                            </div>
                                        </div>
                                        {/* Show "already taken" message directly if known */}
                                        {usernameAvailable === false && !form.getFieldState('username').error && (
                                             <p className="text-sm font-medium text-destructive">Username is already taken.</p>
                                        )}
                                        {/* Show validation errors from react-hook-form */}
                                        <FormMessage />
                                    </FormItem>
                                )}
                            />
                            <FormField
                                control={form.control}
                                name="password"
                                render={({ field }) => (
                                    <FormItem>
                                        <FormLabel>Password</FormLabel>
                                        <FormControl>
                                            <Input type="password" placeholder="********" {...field} />
                                        </FormControl>
                                        <FormMessage />
                                    </FormItem>
                                )}
                            />
                             <FormField
                                control={form.control}
                                name="confirmPassword"
                                render={({ field }) => (
                                    <FormItem>
                                        <FormLabel>Confirm Password</FormLabel>
                                        <FormControl>
                                            <Input type="password" placeholder="********" {...field} />
                                        </FormControl>
                                        <FormMessage />
                                    </FormItem>
                                )}
                            />
                            {apiError && !form.formState.isDirty && <p className="text-sm text-red-600">{apiError}</p>}
                            <Button type="submit" className="w-full" disabled={isLoading || isCheckingUsername || usernameAvailable === false}>
                                {isLoading ? "Creating Account..." : "Sign Up"}
                            </Button>
                        </form>
                    </Form>
                    <p className="mt-4 text-center text-sm text-gray-600">
                        Already have an account?{' '}
                        <Link to="/login" className="font-medium text-primary hover:underline">
                            Log In
                        </Link>
                    </p>
                </CardContent>
            </Card>
        </div>
    );
};

export default SignupPage;