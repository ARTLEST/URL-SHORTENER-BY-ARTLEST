#include <iostream>  // needed for input/output operations
#include <string>    // for string manipulation
#include <vector>    // dynamic arrays
#include <cstdlib>   // random functions
#include <ctime>     // time functions for seeding
#include <algorithm> // utility functions
#include <iomanip>   // output formatting

using namespace std;

// Global storage - I'm using these to keep track of everything
vector<string> urls;           // stores original URLs
vector<string> codes;          // stores the shortened codes
vector<int> clicks;            // tracks how many times each link was clicked
int totalCount = 0;            // total URLs processed

// Function to create a random short code
// I spent some time figuring out the best way to make these unique
string makeShortCode() {
    // Characters I can use - letters and numbers work best
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    string code = "";
    bool unique = false;
    
    // Keep trying until I get a unique code
    while (!unique) {
        code = "art-"; // my little signature :)
        
        // Generate 6 random characters
        for (int i = 0; i < 6; i++) {
            int pos = rand() % chars.length();
            code += chars[pos];
        }
        
        // Check if this code already exists
        unique = true;
        for (int j = 0; j < codes.size(); j++) {
            if (codes[j] == code) {
                unique = false;
                break;
            }
        }
    }
    
    return code;
}

// Main function to shorten URLs
string shortenURL(string longURL) {
    // First, let me check if this URL was already shortened
    for (int i = 0; i < urls.size(); i++) {
        if (urls[i] == longURL) {
            cout << "   Hey! This URL was already shortened before.\n";
            return codes[i];
        }
    }
    
    // Create new short code
    string newCode = makeShortCode();
    
    // Store everything
    urls.push_back(longURL);
    codes.push_back(newCode);
    clicks.push_back(0); // start with zero clicks
    
    totalCount++;
    
    return newCode;
}

// Function to get original URL from short code
string getOriginalURL(string shortCode) {
    // Search through my codes
    for (int i = 0; i < codes.size(); i++) {
        if (codes[i] == shortCode) {
            clicks[i]++; // increment click counter
            cout << "   Found it! Click recorded.\n";
            return urls[i];
        }
    }
    
    return "NOT_FOUND"; // couldn't find it
}

// Display all URLs with some stats
void showAllURLs() {
    cout << "\n================================\n";
    cout << "    URL Database (by ARTLEST)\n";
    cout << "================================\n";
    
    if (totalCount == 0) {
        cout << "No URLs shortened yet. Go ahead and add some!\n\n";
        return;
    }
    
    cout << "Total URLs: " << totalCount << "\n\n";
    
    // Show each URL with details
    for (int i = 0; i < totalCount; i++) {
        cout << "[" << (i + 1) << "] Code: " << codes[i] << "\n";
        cout << "    URL: " << urls[i] << "\n";
        cout << "    Clicks: " << clicks[i] << "\n";
        cout << "    -------------------------\n";
    }
    cout << "\n";
}

// Simple URL validation - not perfect but good enough
bool isValidURL(string url) {
    if (url.empty() || url.length() < 4) {
        return false;
    }
    
    // Check for common URL patterns
    if (url.find("http://") == 0 || url.find("https://") == 0 || url.find("www.") == 0) {
        return true;
    }
    
    // Check if it has a dot (like .com, .org)
    if (url.find('.') != string::npos) {
        return true;
    }
    
    return false;
}

// Show some basic statistics
void showStats() {
    cout << "\n*** Statistics ***\n";
    
    if (totalCount == 0) {
        cout << "No data yet. Start shortening some URLs!\n\n";
        return;
    }
    
    // Calculate total clicks
    int totalClicks = 0;
    for (int i = 0; i < clicks.size(); i++) {
        totalClicks += clicks[i];
    }
    
    // Find most clicked URL
    int maxClicks = 0;
    int popularIndex = 0;
    for (int i = 0; i < clicks.size(); i++) {
        if (clicks[i] > maxClicks) {
            maxClicks = clicks[i];
            popularIndex = i;
        }
    }
    
    cout << "URLs created: " << totalCount << "\n";
    cout << "Total clicks: " << totalClicks << "\n";
    cout << "Most popular: " << codes[popularIndex] << " (" << maxClicks << " clicks)\n";
    if (totalCount > 0) {
        cout << "Average clicks: " << (totalClicks / totalCount) << "\n";
    }
    cout << "\n";
}

int main() {
    // Seed random number generator
    srand(time(0));
    
    cout << "\n=================================\n";
    cout << "    ARTLEST's URL Shortener\n";
    cout << "    Simple & Effective Tool\n";
    cout << "=================================\n\n";
    
    int choice;
    string input;
    
    // Main program loop
    while (true) {
        cout << "What do you want to do?\n";
        cout << "1. Shorten a URL\n";
        cout << "2. Expand a short code\n";
        cout << "3. View all URLs\n";
        cout << "4. Show statistics\n";
        cout << "5. Quit\n";
        cout << "\nYour choice (1-5): ";
        
        // Get user input with basic error handling
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number!\n\n";
            continue;
        }
        
        cin.ignore(); // clear buffer
        
        if (choice == 1) {
            // Shorten URL
            cout << "\nEnter the URL to shorten: ";
            getline(cin, input);
            
            if (!isValidURL(input)) {
                cout << "Hmm, that doesn't look like a valid URL.\n";
                cout << "Try something like: https://www.example.com\n\n";
                continue;
            }
            
            cout << "Processing...\n";
            string shortCode = shortenURL(input);
            
            cout << "\nDone! Here's your shortened URL:\n";
            cout << "Short code: " << shortCode << "\n";
            cout << "Original: " << input << "\n\n";
        }
        else if (choice == 2) {
            // Expand URL
            cout << "\nEnter the short code: ";
            getline(cin, input);
            
            cout << "Looking it up...\n";
            string original = getOriginalURL(input);
            
            if (original == "NOT_FOUND") {
                cout << "Sorry, couldn't find that code.\n";
                cout << "Make sure you typed it correctly!\n\n";
            } else {
                cout << "\nFound it!\n";
                cout << "Short code: " << input << "\n";
                cout << "Original URL: " << original << "\n\n";
            }
        }
        else if (choice == 3) {
            // Show all URLs
            showAllURLs();
        }
        else if (choice == 4) {
            // Show statistics
            showStats();
        }
        else if (choice == 5) {
            // Exit
            cout << "\nThanks for using ARTLEST's URL Shortener!\n";
            cout << "Session summary:\n";
            cout << "- URLs shortened: " << totalCount << "\n";
            cout << "- Total database entries: " << codes.size() << "\n";
            cout << "\nCreated with care by ARTLEST\n";
            cout << "Hope this tool was helpful! Goodbye!\n\n";
            break;
        }
        else {
            cout << "That's not a valid option. Please choose 1-5.\n\n";
        }
        
        // Small pause for better user experience
        cout << "Press Enter to continue...";
        cin.get();
        cout << "\n";
    }
    
    return 0;
}