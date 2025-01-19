#include <iostream>
#include <string>
//File Handling Libraries
#include <fstream> // For opening and closing.
#include <sstream> // For stringstream
#include <stdexcept> // For error handling
//UI Design Library
#include <thread> // For time waiting delays
//Animation Library.
#include <thread>
#include <chrono>
#include <cstdlib> // For rand()
#include <windows.h>
using namespace std;

// ANSI escape codes for colors
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string ORANGE = "\033[38;5;214m"; // For flame color
const string YELLOW = "\033[33m";

// File paths
const string USERS_FILE = "users.txt";
const string ADMINS_FILE = "admins.txt";
const string MOVIES_FILE = "movies.txt";
const string REQUESTS_FILE = "requests.txt";
const string FINANCES_FILE = "finances.txt";


//Global Variables, Structs, Arrays

int currentUser = 0; // Assuming the last logged-in user is the current user
const int MAX_USERS = 10;
const int MAX_ADMINS = 10;
const int MAX_MOVIES = 20;
int num_of_users = 0;
int num_of_admins = 0;
int requestCount[MAX_USERS] = { 0 };
string requests[MAX_USERS][MAX_MOVIES];

struct users
{
    string email;
    string password;
    int subscribed;
    int serialNum;
};
struct admins
{
    string email;
    string password;
};
struct Movie
{
    string name;
    string category;
    int duration;
    string description;
    int views;
};

Movie movies[MAX_MOVIES] = {};

string watchHistoryList[MAX_USERS][MAX_MOVIES]; // Each user has their own watch history
int watchCount[MAX_USERS] = { 0 }; // Keeps track of the number of movies watched by each user

int movie_count = MAX_MOVIES;
users userdata[MAX_USERS];
admins admindata[MAX_ADMINS];

// Maximum number of playlists a user can have
const int MAX_PLAYLISTS = 10;
const int MAX_MOVIES_PER_PLAYLIST = 20;

// To store the playlists
string playlists[MAX_USERS][MAX_PLAYLISTS][MAX_MOVIES_PER_PLAYLIST];  // User -> Playlist -> Movies
int playlistCounts[MAX_USERS][MAX_PLAYLISTS] = { 0 };  // To track the number of movies in each playlist
int userPlaylistCount[MAX_USERS] = { 0 };  // Number of playlists each user has


//________________Prototypes__________________

// Ahmad Akhtar
void userLoginSignup();
void loggedinUser();//
void userProfile();
void adminLoginSignup();
void loggedinadmin();
bool validateuserLogin(string email, string password);
bool validateuserSignup(string email);
bool validateadminLogin(string email, string password);
bool validateadminSignup(string email);
bool validateEmail(string email);
void subscriptionPage();
void clearconsole();
void waitForSeconds(int seconds);
void setConsoleColor(int textColor, int backgroundColor);
void resetConsoleColor();
// Hassan Ahmad
void searchMovie();
void displayCategories();
void trending();
void upcomingRelease();
void playlistManagement();
void recommendations();
void createPlaylist(int);
void viewPlaylists(int);
void addMovieToPlaylist(int);
void removeMovieFromPlaylist(int);
void editPlaylistName(int);
// Abdul Wahab
void watchHistory();
void viewAndMakeRequestsUserSide();
void subscriptionsUserSide();
// Muhammad Saad
void updateContent(Movie movies[], int& movieCount);
void viewFinances();
void viewRequests();

// File Handlings
void saveUsersToFile();
void loadUsersFromFile();
void loadAdminsFromFile();
void saveAdminsToFile();
void saveMoviesToFile();
void loadMoviesFromFile();
void saveRequestsToFile();
void loadRequestsFromFile();
void saveFinancesToFile(int totalRevenue, int weekly, int monthly, int yearly);
void loadFinancesFromFile(int& totalRevenue, int& weekly, int& monthly, int& yearly);
void saveWatchHistoryToFile();
void loadWatchHistoryFromFile();
void savePlaylistsToFile();
void loadPlaylistsFromFile();

// More Functionality
void updateAccountSettings();

// Hot Air Ballon Animatin.
void hotAirBallon();
void clearScreen();
void displayHotAirBalloon(int positionY, int positionX, bool crashing);
void displayCloud(int positionY, int positionX);
void displayBird(int positionY, int positionX);
void displayRain();
void displayLightning(int positionX);
void displayGround();

// Define the block letters for "NEBULA"
const char* N[8] = {
    "NN      NN",
    "NNN     NN",
    "NNNN    NN",
    "NN NN   NN",
    "NN  NN  NN",
    "NN   NN NN",
    "NN    NNNN",
    "NN     NNN"
};
const char* E[8] = {
    "EEEEEEEEEE",
    "EE        ",
    "EE        ",
    "EEEEEEEEE ",
    "EE        ",
    "EE        ",
    "EEEEEEEEEE",
    "          "
};
const char* B[8] = {
    "BBBBBBBB  ",
    "BB      BB",
    "BB      BB",
    "BBBBBBBB  ",
    "BB      BB",
    "BB      BB",
    "BBBBBBBB  ",
    "          "
};
const char* U[8] = {
    "UU      UU",
    "UU      UU",
    "UU      UU",
    "UU      UU",
    "UU      UU",
    "UU      UU",
    " UUUUUUUU ",
    "          "
};
const char* L[8] = {
    "LL        ",
    "LL        ",
    "LL        ",
    "LL        ",
    "LL        ",
    "LL        ",
    "LLLLLLLLLL",
    "          "
};
const char* A[8] = {
    "    AAA    ",
    "   AA AA   ",
    "  AA   AA  ",
    " AA     AA ",
    " AAAAAAAAA ",
    " AA     AA ",
    " AA     AA ",
    "           "
};
// Function to render the word "NEBULA"
void renderWord(const char** letters[], int letterCount) {
    cout << "\n\n\n\n";
    for (int row = 0; row < 8; ++row) {
        cout << "              ";
        for (int i = 0; i < letterCount; ++i) {
            cout << letters[i][row] << "  ";
        }
        cout << endl;
    }
}
// Function to change console text and background colors
void setConsoleColor(int textColor, int backgroundColor) {
    int colorCode = textColor /*+ (backgroundColor * 16);*/;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}
// Function to pulse the word "NEBULA"
void pulseWord(const char** letters[], int letterCount) {
    // Colors for pulsing (text and background)
    int textColors[] = { 14, 12, 10 };    // Yellow, Red, Green
    int backgroundColors[] = { 1, 3, 4 }; // Blue, Aqua, Red

    for (int pulse = 0; pulse < 3; ++pulse) {
        for (int i = 0; i < 3; ++i) { // Cycle through 3 color sets
            system("cls"); // Clear the console
            setConsoleColor(textColors[i], backgroundColors[i]); // Change colors
            renderWord(letters, letterCount); // Render "NEBULA"
            Sleep(300); // Pause for 300ms
        }
    }
    // Reset colors to default
    setConsoleColor(15, 0); // White text on black background
}
void logo() {
    // Array of letter pointers for "NEBULA"
    const char** nebula[] = { N, E, B, U, L, A };

    // Animate the building of "NEBULA"
    for (int i = 1; i <= 6; ++i) {
        system("cls"); // Clear the console
        renderWord(nebula, i); // Render the current letters
        Sleep(500); // Delay for half a second
    }

    // Pulse the word "NEBULA" three times
    pulseWord(nebula, 6);
    waitForSeconds(2);
    resetConsoleColor();
    //clearconsole();
    //cout << "\nAnimation complete!" << endl;
}

//-----------------Main-----------------------

int chjk = 1;
int ckjl = 1;
int main() {
    if (chjk == 1) {
        loadUsersFromFile();
        loadAdminsFromFile();
        loadMoviesFromFile();
        loadRequestsFromFile();
        loadWatchHistoryFromFile();
        loadPlaylistsFromFile();
        chjk++;
        waitForSeconds(2);
        clearconsole();
        cout << "\n\n\n";
        logo();
        cout << "\n\n";
    }

    int choice = 1;
    do
    {

        if (ckjl != 1) {
            setConsoleColor(10, 0);
            cout << "\n\n\n";
            cout << "              NN      NN  EEEEEEEEEE  BBBBBBBB    UU      UU  LL              AAA\n";
            cout << "              NNN     NN  EE          BB      BB  UU      UU  LL             AA AA\n";
            cout << "              NNNN    NN  EE          BB      BB  UU      UU  LL            AA   AA\n";
            cout << "              NN NN   NN  EEEEEEEEE   BBBBBBBB    UU      UU  LL           AA     AA\n";
            cout << "              NN  NN  NN  EE          BB      BB  UU      UU  LL           AAAAAAAAA\n";
            cout << "              NN   NN NN  EE          BB      BB  UU      UU  LL           AA     AA\n";
            cout << "              NN    NNNN  EEEEEEEEEE  BBBBBBBB     UUUUUUUU   LLLLLLLLLL   AA     AA\n";
            cout << "              NN     NNN\n";
            resetConsoleColor();
        }
        ckjl++;
        cout << "\n                 1. User                 \n";
        cout << "                 2. Admin                \n\n";
        cout << "             3. Close Program\n";
        if (choice < 1 || choice > 3) {
            setConsoleColor(4, 0);
            cout << "                 Please select a valid range!";
            resetConsoleColor();
        }
        cout << "\n                 Enter: ";
        cin >> choice;
        clearconsole();
        if (choice == 1 || choice == 2) {
            cout << "\n\n\n\n\n                           Redirecing please wait!\n\n\n";
            waitForSeconds(1);
        }
    } while (choice < 1 || choice > 3);
    switch (choice)
    {
    case 1:
        userLoginSignup();
        break;
    case 2:
        adminLoginSignup();
        break;
    case 3:
        cout << "\n..................................Closing the Program\n";
        waitForSeconds(2);
        saveUsersToFile();
        saveAdminsToFile();
        saveMoviesToFile();
        saveRequestsToFile();
        saveWatchHistoryToFile();
        savePlaylistsToFile();
        waitForSeconds(2);
        return 0;
        break;
    default:
        break;
    }

    return 0;
}


// _________________Functions__________________


// Ahmad Akhtar
void userLoginSignup() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n-----------USER-----------\n\n\n";
        resetConsoleColor();
        cout << "   1. Login                \n";
        cout << "   2. Sign Up              \n\n";
        cout << "3. Main Page            \n\n";
        if (choice < 1 || choice > 3) {
            setConsoleColor(4, 0);
            cout << "                 Please select a valid range!";
            resetConsoleColor();
        }
        cout << "\nEnter: ";
        cin >> choice;
        clearconsole();
    } while (choice < 1 or choice > 3);
    string email, password, signupEmail;
    switch (choice)
    {
    case 1:
        setConsoleColor(10, 0);
        cout << "\n-------------Secure Login----------\n\n\n";
        resetConsoleColor();
        cout << "\n   Enter E-mail: ";
        cin >> email;
        cout << "   Enter Password: ";
        cin.ignore();
        getline(cin, password);
        if (validateuserLogin(email, password)) {
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     * Logged In Successfuly!\n";
            resetConsoleColor();
            for (int i = 0; i < MAX_USERS; i++) {
                if (email.compare(userdata[i].email) == 0) {
                    currentUser = userdata[i].serialNum;
                }
            }
            waitForSeconds(2);
            loggedinUser();
        }
        else
        {
            clearconsole();
            setConsoleColor(4, 0);
            cout << "\n     * Your Account Doesn't Exist Create a new Account.\nOr You have Entered incorrect credentials\nTry Again!\n";
            resetConsoleColor();
            waitForSeconds(2);
            userLoginSignup();
        }
        break;
    case 2:
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n-------------Secure Sign Up--------------\n\n";
        resetConsoleColor();
        cout << "\n   Enter your E-mail: ";
        cin.ignore();
        getline(cin, signupEmail);
        if (validateEmail(signupEmail)) {
            clearconsole();
            setConsoleColor(4, 0);
            cout << "\n     * Invalid Email address. Try again!\n";
            resetConsoleColor();
            waitForSeconds(2);
            userLoginSignup();
        }
        if (validateuserSignup(signupEmail)) {
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     *  Account already exists! Login.\n";
            resetConsoleColor();
            resetConsoleColor();
            waitForSeconds(2);
            userLoginSignup();
        }
        else {
            userdata[num_of_users].email = signupEmail;
            cout << "   Enter Password: ";
            cin >> userdata[num_of_users].password;
            subscriptionPage();
            userdata[num_of_users].serialNum = num_of_users;
            num_of_users++;
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     *  Account created successfully, Login Now.\n";
            resetConsoleColor();
            waitForSeconds(2);
            clearconsole();
            userLoginSignup();
        }
        break;
    case 3:
        main();
        break;
    default:
        break;
    }
}
void loggedinUser() {
    clearconsole();
    int choice = 1;
    do
    {
        setConsoleColor(10, 0);
        cout << "\n----------Nebula Stream----------\n\n\n";
        resetConsoleColor();
        cout << "   1. Search Movie\n";
        cout << "   2. Categories\n";
        cout << "   3. Trending\n";
        cout << "   4. Upcoming Releases\n";
        cout << "   5. Recomendations\n";
        cout << "   6. Playlists\n";
        cout << "   7. Profile\n\n";
        cout << " 8. Log Out\n\n";
        if (choice < 1 || choice > 8) {
            setConsoleColor(4, 0);
            cout << " Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << " Enter: ";
        cin >> choice;
        clearconsole();
    } while (choice < 1 || choice > 8);
    if (choice == 1) {
        searchMovie();
    }
    else if (choice == 2) {
        displayCategories();
    }
    else if (choice == 3) {
        trending();
    }
    else if (choice == 4) {
        upcomingRelease();
    }
    else if (choice == 5) {
        recommendations();
    }
    else if (choice == 6) {
        playlistManagement();
    }
    else if (choice == 7) {
        userProfile();
    }
    else if (choice == 8) {
        setConsoleColor(9, 0);
        cout << "\n   * Logged Out Successfully\n";
        resetConsoleColor();
        waitForSeconds(1);
        clearconsole();
        main();
    }
}
void userProfile() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n----------------Your Profile--------------\n\n\n";
        resetConsoleColor();
        cout << "   1. Watch History\n";
        cout << "   2. Requested Movies\n";
        cout << "   3. Subscription\n";
        cout << "   4. Account Settings\n\n";
        cout << "5. Back\n\n\n";
        if (choice < 1 || choice > 5) {
            setConsoleColor(4, 0);
            cout << "Please enter valid rnge.\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
        clearconsole();
    } while (choice < 1 || choice > 5);

    if (choice == 1) {
        watchHistory();
    }
    else if (choice == 2) {
        viewAndMakeRequestsUserSide();
    }
    else if (choice == 3) {
        subscriptionsUserSide();
    }
    else if (choice == 4) {
        updateAccountSettings();
    }
    else if (choice == 5) {
        loggedinUser();
    }
}
void adminLoginSignup() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n-----------ADMIN-----------\n\n\n";
        resetConsoleColor();
        cout << "   1. Login                \n";
        cout << "   2. Sign Up              \n\n";
        cout << "3. Main Page            \n\n";
        if (choice < 1 or choice > 3) {
            setConsoleColor(4, 0);
            cout << "Enter a Valid range.";
            resetConsoleColor();
        }
        cout << "\nEnter: ";
        cin >> choice;
        clearconsole();
    } while (choice < 1 or choice > 3);

    string email, password, signupEmail;
    switch (choice)
    {
    case 1:
        clearconsole();
        cout << "\nEnter E-mail: ";
        cin >> email;
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, password);
        if (validateadminLogin(email, password)) {
            clearconsole();
            loggedinadmin();
        }
        else
        {
            clearconsole();
            setConsoleColor(4, 0);
            cout << "\n     *   Your Account Doesn't Exist Create a new Account.\n      Or You have Entered incorrect credentials\n\nTry Again\n";
            resetConsoleColor();
            waitForSeconds(2);
            clearconsole();
            adminLoginSignup();
        }
        break;
    case 2:
        clearconsole();
        cout << "\nEnter your E-mail: ";
        cin.ignore();
        getline(cin, signupEmail);
        if (validateEmail(signupEmail)) {
            clearconsole();
            setConsoleColor(4, 0);
            cout << "\n     * Invalid Email address. Try again!\n";
            resetConsoleColor();
            waitForSeconds(2);
            clearconsole();
            adminLoginSignup();
        }
        if (validateadminSignup(signupEmail)) {
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     * Account already exists!\nLog In Now\n";
            resetConsoleColor();
            waitForSeconds(2);
            clearconsole();
            adminLoginSignup();
        }
        else {
            admindata[num_of_admins].email = signupEmail;
            cout << "Enter Password: ";
            cin >> admindata[num_of_admins].password;
            num_of_admins++;
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     * Admin registered Successfully\n";
            resetConsoleColor();
            waitForSeconds(2);
            clearconsole();
            adminLoginSignup();
        }
        break;
    case 3:
        clearconsole();
        main();
    default:
        break;
    }
}
void loggedinadmin() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n------------CONTROL PANNEL------------\n\n\n";
        resetConsoleColor();
        cout << "   1. Update Content\n";
        cout << "   2. View Finances\n";
        cout << "   3. View Requests\n\n";
        cout << "4. Log out\n\n";
        if (choice < 1 || choice > 4) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid choice";
            resetConsoleColor();
        }
        cout << "\nEnter: ";
        cin >> choice;
        clearconsole();
    } while (choice < 1 || choice > 4);

    if (choice == 1) {
        updateContent(movies, movie_count);
    }
    else if (choice == 2) {
        viewFinances();
    }
    else if (choice == 3) {
        viewRequests();
    }
    else if (choice == 4) {
        clearconsole();
        setConsoleColor(9, 0);
        cout << "\n     * Logged Out Successfuly\n";
        resetConsoleColor();
        waitForSeconds(2);
        clearconsole();
        main();
    }
}
// Helper Function.
bool validateuserLogin(string email, string password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (email.compare(userdata[i].email) == 0 and password.compare(userdata[i].password) == 0) {
            return true;
        }
    }
    return false;
}
bool validateuserSignup(string email) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (email.compare(userdata[i].email) == 0) {
            return true;
        }
    }
    return false;
}
bool validateadminLogin(string email, string password) {
    for (int i = 0; i < MAX_ADMINS; i++) {
        if (email.compare(admindata[i].email) == 0 and password.compare(admindata[i].password) == 0) {
            return true;
        }
    }
    return false;
}
bool validateadminSignup(string email) {
    for (int i = 0; i < MAX_ADMINS; i++) {
        if (email.compare(admindata[i].email) == 0) {
            return true;
        }
    }
    return false;
}
bool validateEmail(string email) {
    int len = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        len++;
    }
    bool x = false, y = false;
    for (int i = 0; i <= len; i++) {
        if (email[i] == '@') {
            x = true;
        }
        if (email[i] == '.') {
            y = true;
        }
    }
    if (x and y) {
        return false;
    }
    return true;
}
void subscriptionPage() {
    int choice = 1;
    do
    {
        setConsoleColor(10, 0);
        cout << "\n\n-----------Subscription Plans------------\n\n\n";
        resetConsoleColor();
        cout << "   1. Weekly  ($7.00)\n";
        cout << "   2. Monthly ($31.00)\n";
        cout << "   3. Yearly  ($365.00)\n\n";
        cout << " 4. Later\n\n";
        if (choice < 1 || choice > 4) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range.";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
    } while (choice <= 0 or choice > 4);

    switch (choice)
    {
    case 1:
        userdata[num_of_users].subscribed = 7;
        break;
    case 2:
        userdata[num_of_users].subscribed = 31;
        break;
    case 3:
        userdata[num_of_users].subscribed = 365;
        break;
    case 4:
        userdata[num_of_users].subscribed = 0;
        break;
    default:
        break;
    }
}
void clearconsole() {
    system("cls");  // use "clear" for linux/mac
    //clearconsole();
}
void waitForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
// Function to reset console color
void resetConsoleColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default color
}

// Hassan Ahmad
string playlistNames[MAX_USERS][MAX_PLAYLISTS]; // Playlist names per user
void searchMovie() {
    clearconsole();

    // Subscription check: If user is not subscribed
    if (userdata[currentUser].subscribed == 0) {
        setConsoleColor(9, 0);
        cout << "\n-----------Subscription Required-----------\n";
        resetConsoleColor();
        setConsoleColor(4, 0);
        cout << "You must have an active subscription to search and play movies.\n";
        cout << "Redirecting you to the subscription page...\n";
        resetConsoleColor();
        waitForSeconds(3);
        subscriptionPage();  // Redirect to subscription page
        loggedinUser();
    }

    int cjkl = 1;
    while (true) {
        clearconsole();
        string searchQuery;
        setConsoleColor(9, 0);
        cout << "   (*- Search \"menu\" to go back)  \n\n\n";
        resetConsoleColor();
        setConsoleColor(10, 0);
        cout << "__________----------------__________\n";
        cout << "             Search Bar             \n";
        cout << "__________----------------__________\n\n";
        resetConsoleColor();
        cout << "Search: ";
        if (cjkl == 1) {
            cin.ignore(); // Clear input buffer
            cjkl++;
        }
        getline(cin, searchQuery);

        // Go back to menu if the user types "menu"
        if (searchQuery == "menu") {
            loggedinUser();
            return;
        }
        string currentMovie;
        bool match = false;
        for (int i = 0; i < MAX_MOVIES; i++) {
            if (movies[i].name == searchQuery) {
                match = true;

                // Display movie details
                cout << "\n\nMovie Found: " << movies[i].name << " (" << movies[i].category << ", "
                    << movies[i].duration << " mins)\n";
                currentMovie = movies[i].name;
                cout << "Description: " << movies[i].description << endl;
                cout << "Views: " << movies[i].views << "\n";

                // Increment movie views
                movies[i].views++;

                // Show options to play or search again
                int choice;
                setConsoleColor(9, 0);
                cout << "\nWhat would you like to do?\n";
                resetConsoleColor();
                cout << "   1. Play Movie\n";
                cout << "   2. Search Again\n";
                cout << "   3. Back to Menu\n\n";
                cout << "Enter: ";
                cin >> choice;

                if (choice == 1) {
                    // Play movie and update watch history
                    clearconsole();
                    if (currentMovie.compare("Hot Air Ballon") == 0) hotAirBallon();
                    else cout << "Playing \"" << movies[i].name << "\"...\n";
                    waitForSeconds(3); // Simulate movie playing

                    // Add to watch history
                    if (watchCount[currentUser] < MAX_MOVIES) {
                        watchHistoryList[currentUser][watchCount[currentUser]++] = movies[i].name;
                        setConsoleColor(4, 0);
                        cout << "\"" << movies[i].name << "\" has been added to your watch history.\n";
                        resetConsoleColor();
                    }
                    else {
                        setConsoleColor(4, 0);
                        cout << "Watch history is full. Cannot add more movies.\n";
                        resetConsoleColor();
                    }

                    waitForSeconds(2); // Pause before returning
                    loggedinUser();
                    return;
                }
                else if (choice == 2) {
                    // Search again
                    searchMovie();
                    break;
                }
                else if (choice == 3) {
                    // Go back to menu
                    loggedinUser();
                    return;
                }
                else {
                    setConsoleColor(4, 0);
                    cout << "Invalid choice. Returning to menu.\n";
                    resetConsoleColor();
                    waitForSeconds(2);
                    loggedinUser();
                    return;
                }
            }
        }

        if (!match) {
            setConsoleColor(4, 0);
            cout << "\nNo movies found matching \"" << searchQuery << "\".\n";
            resetConsoleColor();
            cout << "Press Enter key to search again\n";
            cin.ignore();
        }
    }
}
void displayCategories() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n________Categories_________\n\n";
        resetConsoleColor();
        cout << "    * Sci-fi      * Thriller\n";
        cout << "    * Action      * Fantasy\n";
        cout << "    * Crime       * Romance\n";
        cout << "    * Drama       * Adventure\n";
        cout << "    * Thriller    * War\n";
        cout << "    * Fantasy     * Comedy\n";
        cout << "\n1. Go Back\n";
        if (choice != 1) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
    } while (choice != 1);
    if (choice == 1) {
        loggedinUser();
    }
}
void trending() {
    // Sorting movies by the number of views in descending order
    for (int i = 0; i < MAX_MOVIES - 1; i++) {
        for (int j = i + 1; j < MAX_MOVIES; j++) {
            if (movies[i].views < movies[j].views) {
                // Swap the movies[i] and movies[j]
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n--------------Trending Movies----------------\n\n";
        resetConsoleColor();
        // Display the top 5 trending movies based on views
        int count = 5;
        for (int i = 0; i < count; i++) {
            cout << "   " << i + 1 << ". " << movies[i].name << "        (" << movies[i].category << ", "
                << movies[i].views << " views)\n";
        }
        cout << "\n1. Menu\n";
        if (choice != 1) {
            setConsoleColor(4, 0);
            cout << "Please enter valid range.\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
        if (choice == 1) {
            loggedinUser();
        }
    } while (choice != 1);

}
void upcomingRelease() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "____________Upcoming Releases______________\n\n";
        resetConsoleColor();
        cout << "    * Dune (Part-II)      * The Marvels\n";
        cout << "    * The Flash           * Avatar II\n";
        cout << "    * Superman            * Mission (Impossible VII)\n";
        cout << "\n1. Go Back\n";
        if (choice != 1) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
    } while (choice != 1);
    if (choice == 1) {
        loggedinUser();
    }
}
void playlistManagement() {
    //int currentUser = num_of_users - 1; // Get the current user
    int choice = 1;
    do {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n--------------Playlist Management-------------\n";
        resetConsoleColor();
        cout << "\n   1. Create a Playlist\n";
        cout << "   2. View Playlists\n";
        cout << "   3. Add Movie to Playlist\n";
        cout << "   4. Remove Movie from Playlist\n";
        cout << "   5. Edit Playlist Name\n";  // New option to edit playlist name
        cout << "   6. Menu\n\n";
        if (choice < 1 || choice > 6) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
    } while (choice < 1 || choice > 6); // Exit when the user chooses to return to menu

    if (choice == 1) {
        createPlaylist(currentUser);
    }
    else if (choice == 2) {
        viewPlaylists(currentUser);
    }
    else if (choice == 3) {
        addMovieToPlaylist(currentUser);
    }
    else if (choice == 4) {
        removeMovieFromPlaylist(currentUser);
    }
    else if (choice == 5) {
        editPlaylistName(currentUser);  // Function to edit playlist names
    }
    else if (choice == 6) {
        loggedinUser();
    }
}
void removeMovieFromPlaylist(int currentUser) {
    int playlistChoice = 1;
    do {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n----------Remove Video from Playlists------------\n";
        resetConsoleColor();
        cout << "\nSelect a playlist to remove a movie from:\n";

        // Display playlist names
        for (int i = 0; i < userPlaylistCount[currentUser]; i++) {
            cout << i + 1 << ". " << playlistNames[currentUser][i] << endl;
        }
        cout << "\n" << userPlaylistCount[currentUser] + 1 << ". Playlist Management\n\n";

        if (playlistChoice < 1 || playlistChoice > userPlaylistCount[currentUser] + 1) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> playlistChoice;

        if (playlistChoice == userPlaylistCount[currentUser] + 1) playlistManagement();
        playlistChoice--; // Convert to zero-based index

        if (playlistChoice >= 0 && playlistChoice < userPlaylistCount[currentUser]) {
            int movieChoice = 1;
            do {
                clearconsole();
                setConsoleColor(10, 0);
                cout << "\n------------Select Movie to Remove from Playlist------------\n\n";
                resetConsoleColor();
                cout << "Movies in \"" << playlistNames[currentUser][playlistChoice] << "\":\n";

                // Display movies in the selected playlist
                for (int i = 0; i < playlistCounts[currentUser][playlistChoice]; i++) {
                    cout << i + 1 << ". " << playlists[currentUser][playlistChoice][i] << endl;
                }
                cout << playlistCounts[currentUser][playlistChoice] + 1 << ". Back to Playlist Management\n\n";

                if (movieChoice < 1 || movieChoice > playlistCounts[currentUser][playlistChoice] + 1) {
                    setConsoleColor(4, 0);
                    cout << "Please enter a valid range\n";
                    resetConsoleColor();
                }
                cout << "Enter: ";
                cin >> movieChoice;

                if (movieChoice == playlistCounts[currentUser][playlistChoice] + 1) playlistManagement();
                movieChoice--; // Convert to zero-based index

                if (movieChoice >= 0 && movieChoice < playlistCounts[currentUser][playlistChoice]) {
                    // Remove the movie
                    for (int i = movieChoice; i < playlistCounts[currentUser][playlistChoice] - 1; i++) {
                        playlists[currentUser][playlistChoice][i] = playlists[currentUser][playlistChoice][i + 1];
                    }
                    playlistCounts[currentUser][playlistChoice]--;
                    clearconsole();
                    setConsoleColor(9, 0);
                    cout << "Movie removed from playlist successfully!\n";
                    resetConsoleColor();
                    playlistManagement();
                }
            } while (movieChoice < 1 || movieChoice > playlistCounts[currentUser][playlistChoice] + 1);
        }
    } while (playlistChoice < 1 || playlistChoice > userPlaylistCount[currentUser] + 1);
}
void editPlaylistName(int currentUser) {
    int playlistChoice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "------------------Edit Playlist Name-------------------\n";
        resetConsoleColor();
        cout << "\nSelect a playlist to edit its name:\n";
        for (int i = 0; i < userPlaylistCount[currentUser]; i++) {
            cout << i + 1 << ". " << playlists[currentUser][i][0] << endl;
        }
        cout << userPlaylistCount[currentUser] + 1 << ". Playlist Managment\n";
        if (playlistChoice < 1 || playlistChoice > userPlaylistCount[currentUser] + 1) {
            setConsoleColor(4, 0);
            cout << "Please enter valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> playlistChoice;
        if (playlistChoice == userPlaylistCount[currentUser] + 1)playlistManagement();
        playlistChoice--; // Convert to zero-based index

        if (playlistChoice >= 0 && playlistChoice < userPlaylistCount[currentUser]) {
            cout << "\nEnter the new name for this playlist: ";
            string newName;
            cin.ignore();
            getline(cin, newName);

            // Change the name of the playlist
            playlists[currentUser][playlistChoice][0] = newName;
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\nPlaylist name updated successfully!\n";
            resetConsoleColor();
            playlistManagement();
        }
        else {
            setConsoleColor(4, 0);
            cout << "Invalid playlist choice.\n";
            resetConsoleColor();
        }
    } while (playlistChoice < 1 || playlistChoice > userPlaylistCount[currentUser] + 1);
}
void createPlaylist(int currentUser) {
    clearconsole();
    setConsoleColor(10, 0);
    cout << "\n------------Create Playlists--------------\n";
    resetConsoleColor();
    if (userPlaylistCount[currentUser] < MAX_PLAYLISTS) {
        cout << "\nEnter the name of your new playlist: ";
        string playlistName;
        cin.ignore();
        getline(cin, playlistName);

        // Store the playlist name in the dedicated array
        playlistNames[currentUser][userPlaylistCount[currentUser]] = playlistName;

        // Increment the playlist count for this user
        userPlaylistCount[currentUser]++;
        clearconsole();
        setConsoleColor(9, 0);
        cout << "\n     Playlist created successfully!\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
    }
    else {
        clearconsole();
        setConsoleColor(4, 0);
        cout << "\n     You have reached the maximum number of playlists.\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
    }
}
void viewPlaylists(int currentUser) {
    clearconsole();
    setConsoleColor(10, 0);
    cout << "\n--------------Your Playlists--------------\n";
    resetConsoleColor();
    if (userPlaylistCount[currentUser] == 0) {
        setConsoleColor(9, 0);
        cout << "\n     You don't have any playlists yet.\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
        return;
    }

    // Display all playlists
    for (int i = 0; i < userPlaylistCount[currentUser]; i++) {
        cout << i + 1 << ". " << playlistNames[currentUser][i] << endl;

        int movieCount = playlistCounts[currentUser][i];
        cout << "   Movies in this playlist:\n";
        if (movieCount == 0) {
            setConsoleColor(9, 0);
            cout << "      * No movies in this playlist yet.\n";
            resetConsoleColor();
        }
        else {
            for (int j = 0; j < movieCount; j++) {
                cout << "      * " << playlists[currentUser][i][j] << endl;
            }
        }
        cout << "\n";
    }
    cout << "Press any key to return.\n";
    cin.ignore();
    cin.get();
    playlistManagement();
}
void addMovieToPlaylist(int currentUser) {
    clearconsole();
    setConsoleColor(10, 0);
    cout << "\n----------Add Movies to Playlists----------\n\n";
    resetConsoleColor();
    if (userPlaylistCount[currentUser] == 0) {
        setConsoleColor(4, 0);
        cout << "\n     You don't have any playlists to add movies to.\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
        return;
    }

    // Select a playlist
    cout << "Select a playlist:\n";
    for (int i = 0; i < userPlaylistCount[currentUser]; i++) {
        cout << "   " << i + 1 << ". " << playlistNames[currentUser][i] << endl;
    }
    int playlistChoice;
    cin >> playlistChoice;
    playlistChoice--; // Convert to zero-based index

    if (playlistChoice < 0 || playlistChoice >= userPlaylistCount[currentUser]) {
        clearconsole();
        setConsoleColor(4, 0);
        cout << "\n     Invalid choice. Returning to menu.\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
        return;
    }

    // Select a movie to add
    clearconsole();
    cout << "\nSelect a movie to add:\n";
    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << "   " << i + 1 << ". " << movies[i].name << endl;
    }
    int movieChoice;
    cin >> movieChoice;
    movieChoice--; // Convert to zero-based index

    if (movieChoice < 0 || movieChoice >= MAX_MOVIES) {
        clearconsole();
        setConsoleColor(4, 0);
        cout << "\n     Invalid choice. Returning to menu.\n";
        resetConsoleColor();
        waitForSeconds(2);
        playlistManagement();
        return;
    }

    // Add the movie to the playlist
    if (playlistCounts[currentUser][playlistChoice] < MAX_MOVIES_PER_PLAYLIST) {
        playlists[currentUser][playlistChoice][playlistCounts[currentUser][playlistChoice]] = movies[movieChoice].name;
        playlistCounts[currentUser][playlistChoice]++;
        clearconsole();
        setConsoleColor(9, 0);
        cout << "\n     Movie added to playlist successfully!\n";
        resetConsoleColor();
    }
    else {
        clearconsole();
        setConsoleColor(4, 0);
        cout << "\n     This playlist is full. Cannot add more movies.\n";
        resetConsoleColor();
    }
    waitForSeconds(2);
    playlistManagement();
}
void recommendations() {
    clearconsole();

    // Check if the user is subscribed
    if (userdata[currentUser].subscribed == 0) {
        setConsoleColor(9, 0);
        cout << "\n-----------Subscription Required-----------\n";
        resetConsoleColor();
        setConsoleColor(4, 0);
        cout << "You must have an active subscription to view recommendations.\n";
        cout << "Redirecting you to the subscription page...\n";
        resetConsoleColor();
        waitForSeconds(3);
        subscriptionPage();
        loggedinUser();
    }
    setConsoleColor(10, 0);
    cout << "\n-----------Recommendations Based on Your Watch History-----------\n\n";
    resetConsoleColor();
    if (watchCount[currentUser] == 0) {
        setConsoleColor(9, 0);
        cout << "You haven't watched any movies yet, so we can't recommend movies.\n";
        resetConsoleColor();
        cout << "\n1. Back to Profile\n";
        int choice;
        cin >> choice;
        if (choice == 1) userProfile();
        return;
    }

    // Step 1: Count the occurrences of each category in watch history
    string categories[MAX_MOVIES];   // To store unique categories
    int categoryCounts[MAX_MOVIES] = { 0 }; // To store count of each category
    int uniqueCategoryCount = 0;

    for (int i = 0; i < watchCount[currentUser]; i++) {
        string watchedMovie = watchHistoryList[currentUser][i];

        // Find the category of the watched movie
        for (int j = 0; j < movie_count; j++) {
            if (movies[j].name == watchedMovie) {
                string category = movies[j].category;

                // Check if the category is already in the list
                bool found = false;
                for (int k = 0; k < uniqueCategoryCount; k++) {
                    if (categories[k] == category) {
                        categoryCounts[k]++;
                        found = true;
                        break;
                    }
                }

                // If the category is not found, add it to the list
                if (!found) {
                    categories[uniqueCategoryCount] = category;
                    categoryCounts[uniqueCategoryCount] = 1;
                    uniqueCategoryCount++;
                }
                break;
            }
        }
    }

    // Step 2: Sort categories by count (Descending Order)
    for (int i = 0; i < uniqueCategoryCount - 1; i++) {
        for (int j = i + 1; j < uniqueCategoryCount; j++) {
            if (categoryCounts[i] < categoryCounts[j]) {
                // Swap counts
                int tempCount = categoryCounts[i];
                categoryCounts[i] = categoryCounts[j];
                categoryCounts[j] = tempCount;

                // Swap categories
                string tempCategory = categories[i];
                categories[i] = categories[j];
                categories[j] = tempCategory;
            }
        }
    }

    // Step 3: Recommend movies based on top categories
    cout << "Movies you might like:\n";
    int recommendationsShown = 0;

    for (int i = 0; i < uniqueCategoryCount && recommendationsShown < 5; i++) {
        string topCategory = categories[i];

        for (int j = 0; j < movie_count && recommendationsShown < 5; j++) {
            if (movies[j].category == topCategory &&
                // Ensure the movie is not already in the watch history
                find(begin(watchHistoryList[currentUser]), begin(watchHistoryList[currentUser]) + watchCount[currentUser], movies[j].name) == begin(watchHistoryList[currentUser]) + watchCount[currentUser]) {
                cout << "  - " << movies[j].name << " (" << movies[j].category << ", " << movies[j].duration << " mins)\n";
                recommendationsShown++;
            }
        }
    }

    if (recommendationsShown == 0) {
        cout << "No new recommendations available based on your history.\n";
    }

    cout << "\n1. Back to Profile\n";
    int choice;
    cin >> choice;
    if (choice == 1) userProfile();
}

// Abdul Wahab
void watchHistory() {
    clearconsole();

    // Subscription check: If user is not subscribed
    if (userdata[currentUser].subscribed == 0) {
        setConsoleColor(9, 0);
        cout << "\n-----------Subscription Required-----------\n";
        resetConsoleColor();
        setConsoleColor(4, 0);
        cout << "You must have an active subscription to view and play movies from your watch history.\n";
        cout << "Redirecting you to the subscription page...\n";
        resetConsoleColor();
        waitForSeconds(3);
        subscriptionPage();  // Redirect to subscription page
        loggedinUser();
    }
    setConsoleColor(10, 0);
    cout << "\n-------------Watch History--------------\n\n\n";
    resetConsoleColor();
    if (watchCount[currentUser] == 0) {
        int choice = 1;
        do {
            setConsoleColor(9, 0);
            cout << "   *  You haven't watched any movies yet.\n\n";
            resetConsoleColor();
            cout << "1. Menu\n";
            cin >> choice;
            clearconsole();
        } while (choice != 1);

        if (choice == 1) {
            loggedinUser();
        }
    }
    else {
        int choice = 1;
        do {
            for (int i = 0; i < watchCount[currentUser]; i++) {
                cout << i + 1 << ". " << watchHistoryList[currentUser][i] << endl;
            }
            cout << "\n\n1. Menu\n";
            cin >> choice;
            clearconsole();
        } while (choice != 1);

        if (choice == 1) {
            loggedinUser();
        }
    }
}
void viewAndMakeRequestsUserSide()
// To be Done By Abdul Wahab.
{
    int choice = 1;
    do {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n---------------Request Pannel------------\n\n\n";
        resetConsoleColor();
        cout << "View and Make Requests\n";
        cout << "   1. View Requests\n";
        cout << "   2. Make a Request\n";
        cout << " 3. Return to Menu\n\n";
        if (choice < 1 || choice > 3) {
            setConsoleColor(4, 0); {
                cout << "   Please enter a valid range\n";
                resetConsoleColor();
            }
        }
        cout << "\n   Enter: ";
        cin >> choice;
    } while (choice != 3);
    if (choice == 1) {
        if (requestCount[currentUser] == 0) {
            clearconsole();
            setConsoleColor(10, 0);
            cout << "\n---------------Request Pannel------------\n\n\n";
            resetConsoleColor();
            setConsoleColor(9, 0);
            cout << "     *  No requests have been made yet.\n";
            resetConsoleColor();
            waitForSeconds(3);
            userProfile();
        }
        else {
            int choice2 = 1;
            do
            {
                clearconsole();
                setConsoleColor(4, 0);
                cout << "\n---------------Request Pannel-------------\n\n\n";
                resetConsoleColor();
                cout << "Your Requests:\n";
                for (int i = 0; i < requestCount[currentUser]; i++) {
                    cout << "   " << i + 1 << ". " << requests[currentUser][i] << endl;
                }
                cout << endl << requestCount[currentUser] + 1 << ". Back\n\n";
                if (choice2 < 1 || choice2 > requestCount[currentUser] + 1) {
                    setConsoleColor(4, 0);
                    cout << "Please enter valid range\n";
                    resetConsoleColor();
                }
                cout << "Enter: ";
                cin >> choice2;
            } while (choice2 < 1 || choice2 > requestCount[currentUser] + 1);
            if (choice2 == requestCount[currentUser] + 1) userProfile();
        }
    }
    else if (choice == 2) {
        if (requestCount[currentUser] < MAX_MOVIES) {
            clearconsole();
            setConsoleColor(10, 0);
            cout << "\n---------------Request Pannel------------\n\n\n";
            resetConsoleColor();
            cout << "\nEnter your request: ";
            cin.ignore(); // To handle input buffer
            getline(cin, requests[currentUser][requestCount[currentUser]]);
            requestCount[currentUser]++;
            clearconsole();
            setConsoleColor(10, 0);
            cout << "\n---------------Request Pannel------------\n\n\n";
            resetConsoleColor();
            setConsoleColor(9, 0);
            cout << "\n    * Your request has been saved!\n";
            resetConsoleColor();
            waitForSeconds(3);
            userProfile();
        }
        else {
            clearconsole();
            setConsoleColor(4, 0);
            cout << "\n    * Request limit reached. Cannot add more requests.\n";
            resetConsoleColor();
            waitForSeconds(3);
            userProfile();
        }
    }
    else if (choice == 3) {
        userProfile();
    }
}
void subscriptionsUserSide()
{
    //int currentUser = num_of_users - 1; // Assuming the last logged-in user is the current user
    int currentPlan = userdata[currentUser].subscribed;
    int choice = 1;
    do
    {
        setConsoleColor(10, 0);
        cout << "\n-----------Current Subscription-----------\n\n";
        resetConsoleColor();
        cout << "Subscription Status\n";
        if (currentPlan == 0) {
            cout << "   *  No active subscription.\n";
        }
        else if (currentPlan == 7) {
            cout << "   *  Weekly Plan\n";
        }
        else if (currentPlan == 31) {
            cout << "   *  Monthly Plan\n";
        }
        else if (currentPlan == 365) {
            cout << "   *  Yearly Plan\n";
        }
        if (choice < 1 || choice > 2) {
            setConsoleColor(4, 0);
            cout << "Pleaase enter a valid Range\n";
            resetConsoleColor();
        }
        setConsoleColor(9, 0);
        cout << "\nDo you want to change your subscription? (1 for Yes, 2 for No): ";
        resetConsoleColor();
        cin >> choice;

        if (choice == 1) {
            clearconsole();
            subscriptionPage(); // Calls the existing subscription page function
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     Subscribtion changed successfully\n";
            resetConsoleColor();
            waitForSeconds(2);
            userProfile();
        }
        else {
            clearconsole();
            setConsoleColor(9, 0);
            cout << "Returning to menu...\n";
            resetConsoleColor();
            waitForSeconds(1);
            userProfile();
        }
    } while (choice < 1 || choice > 2);
}
void watchMovie(string movieName)
{
    if (watchCount[currentUser] < MAX_MOVIES) {
        watchHistoryList[currentUser][watchCount[currentUser]] = movieName;
        watchCount[currentUser]++;
        setConsoleColor(9, 0);
        cout << "You have watched \"" << movieName << "\". It has been added to your watch history.\n";
        resetConsoleColor();
    }
    else {
        setConsoleColor(4, 0);
        cout << "Watch history is full. Cannot add more movies.\n";
        resetConsoleColor();
    }
}

// Muhammad Saad
void updateContent(Movie movies[], int& movieCount) {
    int choice = 1;
    do {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n====== Update Content ======\n\n";
        resetConsoleColor();
        cout << "   1. Display Movies\n";
        cout << "   2. Add Movie\n";
        cout << "   3. Remove Movie\n";
        cout << " 4. Main Menu\n\n";
        if (choice < 1 || choice > 4) {
            setConsoleColor(4, 0);
            cout << "Please a valid range.";
            resetConsoleColor();
        }
        cout << "\nEnter: ";
        cin >> choice;

        if (choice == 1) {
            if (movieCount == 0) {
                clearconsole();
                setConsoleColor(9, 0);
                cout << "\n\nNo movies available.\n";
                resetConsoleColor();
                waitForSeconds(3);
                updateContent(movies, movie_count);
            }
            else {
                int choice2 = movieCount + 1;
                do
                {
                    clearconsole();
                    setConsoleColor(10, 0);
                    cout << "\n------------------Current Movies------------------\n\n";
                    resetConsoleColor();
                    for (int i = 0; i < movieCount; i++) {
                        cout << "Movie " << i + 1 << ":\n";
                        cout << "Name: " << movies[i].name << endl;
                        cout << "Category: " << movies[i].category << endl;
                        cout << "Duration: " << movies[i].duration << " minutes\n";
                        cout << "Description: " << movies[i].description << "\n\n\n";
                    }
                    cout << movieCount + 1 << ". Back\n";
                    if (choice2 != movieCount + 1) {
                        setConsoleColor(4, 0);
                        cout << "Please enter a valid range\n";
                        resetConsoleColor();
                    }
                    cout << "Enter: ";
                    cin >> choice2;
                    if (choice2 == movieCount + 1) updateContent(movies, movie_count);
                } while (choice2 != movieCount + 1);
            }
        }
        else if (choice == 2) {
            if (movieCount >= MAX_MOVIES) {
                clearconsole();
                setConsoleColor(4, 0);
                cout << "\nCannot add more movies. Maximum limit reached.\n";
                resetConsoleColor();
                waitForSeconds(5);
                updateContent(movies, movie_count);
            }
            else {
                clearconsole();
                cin.ignore();
                Movie newMovie;
                setConsoleColor(9, 0);
                cout << "           (Enter \"back\" in at movie name to go back)           \n\n";
                resetConsoleColor();
                getline(cin, newMovie.name);
                if (newMovie.name.compare("back") == 0) updateContent(movies, movie_count);
                cout << "Enter Category: ";
                getline(cin, newMovie.category);
                cout << "Enter Duration (minutes): ";
                cin >> newMovie.duration;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, newMovie.description);

                movies[movieCount] = newMovie;
                movieCount++;
                clearconsole();
                setConsoleColor(9, 0);
                cout << "\n     Movie added successfully!\n";
                resetConsoleColor();
                waitForSeconds(3);
                updateContent(movies, movie_count);
            }
        }
        else if (choice == 3) {
            if (movieCount == 0) {
                clearconsole();
                setConsoleColor(4, 0);
                cout << "\n     No movies to remove.\n";
                resetConsoleColor();
                waitForSeconds(3);
                updateContent(movies, movie_count);
            }
            else {
                clearconsole();
                setConsoleColor(10, 0);
                cout << "\n------------Remove a Movie------------\n\n";
                resetConsoleColor();
                for (int i = 0; i < movieCount; i++) {
                    cout << "Movie " << i + 1 << ":\n";
                    cout << "   Name: " << movies[i].name << endl;
                    cout << "   Category: " << movies[i].category << endl;
                    cout << "   Duration: " << movies[i].duration << " minutes\n";
                    cout << "   Description: " << movies[i].description << "\n\n\n";
                }
                cout << "Enter the movie number to remove: ";
                int movieIndex;
                cin >> movieIndex;

                if (movieIndex > 0 && movieIndex <= movieCount) {
                    for (int i = movieIndex - 1; i < movieCount - 1; i++) {
                        movies[i] = movies[i + 1];
                    }
                    movieCount--;
                    clearconsole();
                    setConsoleColor(9, 0);
                    cout << "\n     Movie removed successfully!\n";
                    resetConsoleColor();
                    waitForSeconds(5);
                    updateContent(movies, movie_count);
                }
                else {
                    clearconsole();
                    setConsoleColor(4, 0);
                    cout << "\n     Invalid movie number! Try again.\n";
                    resetConsoleColor();
                    waitForSeconds(5);
                    updateContent(movies, movie_count);
                }
            }
        }
        else if (choice == 4) {
            loggedinadmin();
        }
    } while (choice < 1 || choice > 4);
}
void viewFinances() {
    int choice = 1;
    int weekly_count = 0;
    int monthly_count = 0;
    int yearly_count = 0;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n------------Finance Department-----------\n";
        resetConsoleColor();
        // Define the subscription plan costs
        const int WEEKLY_COST = 7;   // Weekly plan cost
        const int MONTHLY_COST = 31; // Monthly plan cost
        const int YEARLY_COST = 365; // Yearly plan cost

        // Initialize total revenue
        int totalRevenue = 0;
        loadFinancesFromFile(totalRevenue, weekly_count, monthly_count, yearly_count);
        weekly_count = 0;
        monthly_count = 0;
        yearly_count = 0;
        totalRevenue = 0;
        // Display each user's subscription status and calculate revenue
        setConsoleColor(9, 0);
        cout << "\nView Subscription Finances:\n";
        resetConsoleColor();
        for (int user = 0; user < num_of_users; user++) {
            cout << "   User Email: " << userdata[user].email << "\n";

            if (userdata[user].subscribed == 0) {
                cout << "    * No active subscription.\n";
            }
            else if (userdata[user].subscribed == 7) {
                cout << "    * Weekly Plan\n";
                weekly_count++;
                totalRevenue += WEEKLY_COST; // Add weekly plan cost to total revenue
            }
            else if (userdata[user].subscribed == 31) {
                cout << "    * Monthly Plan\n";
                monthly_count++;
                totalRevenue += MONTHLY_COST; // Add monthly plan cost to total revenue
            }
            else if (userdata[user].subscribed == 365) {
                cout << "    * Yearly Plan\n";
                yearly_count++;
                totalRevenue += YEARLY_COST; // Add yearly plan cost to total revenue
            }
        }

        // Display the total revenue
        cout << "\nTotal Revenue Generated from Subscriptions: $" << totalRevenue << endl;
        saveFinancesToFile(totalRevenue, weekly_count, monthly_count, yearly_count);
        cout << "\n\n1. Menu\n";
        if (choice != 1) {
            setConsoleColor(4, 0);
            cout << "Please enter a valid range\n";
            resetConsoleColor();
        }
        cout << "Enter: ";
        cin >> choice;
        if (choice == 1) loggedinadmin();
    } while (choice != 1);
}
void viewRequests() {
    int choice = 1;
    do
    {
        clearconsole();
        setConsoleColor(10, 0);
        cout << "\n-----------Requests Section-----------\n\n";
        resetConsoleColor();
        cout << "View All User Requests:\n";

        bool noRequests = true;
        for (int user = 0; user < num_of_users; user++) {
            if (requestCount[user] > 0) {
                noRequests = false;
                cout << "   Requests by User " << user + 1 << ":\n"; // Assuming users are 1-indexed
                for (int i = 0; i < requestCount[user]; i++) {
                    cout << "       " << i + 1 << ". " << requests[user][i] << endl;
                }
            }
        }

        if (noRequests) {
            clearconsole();
            setConsoleColor(9, 0);
            cout << "\n     No requests have been made by any users.\n\n";
            resetConsoleColor();
            cout << "1. Menu\n";
            if (choice != 1) {
                setConsoleColor(4, 0);
                cout << "Please enter a valid range\n";
                resetConsoleColor();
            }
            cout << "Enter: ";
            cin >> choice;
            if (choice == 1) loggedinadmin();
        }
        else {
            setConsoleColor(9, 0);
            cout << "\nEnd of Requests.\n\n";
            resetConsoleColor();
            cout << "1. Menu\n";
            if (choice != 1) {
                setConsoleColor(4, 0);
                cout << "Please enter a valid range\n";
                resetConsoleColor();
            }
            cout << "Enter: ";
            cin >> choice;
            if (choice == 1) loggedinadmin();
        }
    } while (choice != 1);
}

// File Handlings.
void saveUsersToFile() {
    ofstream outFile(USERS_FILE);
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open users file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < num_of_users; i++) {
        outFile << userdata[i].email << "," << userdata[i].password << ","
            << userdata[i].subscribed << "\n";
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Users saved successfully.\n";
    resetConsoleColor();
}
void loadUsersFromFile() {
    ifstream inFile(USERS_FILE);
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open users file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    num_of_users = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, userdata[num_of_users].email, ',');
        getline(ss, userdata[num_of_users].password, ',');
        ss >> userdata[num_of_users].subscribed;
        num_of_users++;
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Users loaded successfully.\n";
    resetConsoleColor();
}
void saveAdminsToFile() {
    ofstream outFile(ADMINS_FILE);
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open admins file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < num_of_admins; i++) {
        outFile << admindata[i].email << "," << admindata[i].password << "\n";
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Admins saved successfully.\n";
    resetConsoleColor();
}
void loadAdminsFromFile() {
    ifstream inFile(ADMINS_FILE);
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open admins file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    num_of_admins = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, admindata[num_of_admins].email, ',');
        getline(ss, admindata[num_of_admins].password, ',');
        num_of_admins++;
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Admins loaded successfully.\n";
    resetConsoleColor();
}
void saveMoviesToFile() {
    ofstream outFile(MOVIES_FILE);
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open movies file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < movie_count; i++) {
        outFile << movies[i].name << "," << movies[i].category << ","
            << movies[i].duration << "," << movies[i].description << ","
            << movies[i].views << "\n";
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Movies saved successfully.\n";
    resetConsoleColor();
}
void loadMoviesFromFile() {
    ifstream inFile(MOVIES_FILE);
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open movies file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    movie_count = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, movies[movie_count].name, ',');
        getline(ss, movies[movie_count].category, ',');
        ss >> movies[movie_count].duration;
        ss.ignore(); // Skip the comma
        getline(ss, movies[movie_count].description, ',');
        ss >> movies[movie_count].views;
        movie_count++;
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Movies loaded successfully.\n";
    resetConsoleColor();
}
void saveRequestsToFile() {
    ofstream outFile(REQUESTS_FILE);
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open requests file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < num_of_users; i++) {
        outFile << userdata[i].email << "\n";
        for (int j = 0; j < requestCount[i]; j++) {
            outFile << requests[i][j] << "\n";
        }
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Requests saved successfully.\n";
    resetConsoleColor();
}
void loadRequestsFromFile() {
    ifstream inFile(REQUESTS_FILE);
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open requests file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    int currentUser = -1;
    while (getline(inFile, line)) {
        if (line.find('@') != string::npos) { // Assume email lines contain '@'
            currentUser++;
        }
        else {
            requests[currentUser][requestCount[currentUser]++] = line;
        }
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Requests loaded successfully.\n";
    resetConsoleColor();
}
void saveFinancesToFile(int totalRevenue, int weekly, int monthly, int yearly) {
    ofstream outFile(FINANCES_FILE);
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open finances file for writing.\n";
        resetConsoleColor();
        return;
    }

    outFile << "total_revenue:" << totalRevenue << "\n";
    outFile << "weekly_subscriptions:" << weekly << "\n";
    outFile << "monthly_subscriptions:" << monthly << "\n";
    outFile << "yearly_subscriptions:" << yearly << "\n";
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Finances saved successfully.\n";
    resetConsoleColor();
}
void loadFinancesFromFile(int& totalRevenue, int& weekly, int& monthly, int& yearly) {
    ifstream inFile(FINANCES_FILE);
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open finances file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line, key;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, key, ':');
        if (key == "total_revenue") ss >> totalRevenue;
        else if (key == "weekly_subscriptions") ss >> weekly;
        else if (key == "monthly_subscriptions") ss >> monthly;
        else if (key == "yearly_subscriptions") ss >> yearly;
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Finances loaded successfully.\n";
    resetConsoleColor();
}
void saveWatchHistoryToFile() {
    ofstream outFile("watch_history.txt");
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open watch history file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < num_of_users; i++) {
        outFile << userdata[i].email << ":";
        for (int j = 0; j < watchCount[i]; j++) {
            outFile << watchHistoryList[i][j];
            if (j < watchCount[i] - 1) outFile << ",";
        }
        outFile << "\n";
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Watch history saved successfully.\n";
    resetConsoleColor();
}
void loadWatchHistoryFromFile() {
    ifstream inFile("watch_history.txt");
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open watch history file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(':');
        string email = line.substr(0, pos);
        string history = line.substr(pos + 1);

        for (int i = 0; i < num_of_users; i++) {
            if (userdata[i].email == email) {
                stringstream ss(history);
                string movie;
                while (getline(ss, movie, ',')) {
                    watchHistoryList[i][watchCount[i]++] = movie;
                }
                break;
            }
        }
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Watch history loaded successfully.\n";
    resetConsoleColor();
}
void savePlaylistsToFile() {
    ofstream outFile("playlists.txt");
    if (!outFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open playlists file for writing.\n";
        resetConsoleColor();
        return;
    }

    for (int i = 0; i < num_of_users; i++) {
        outFile << userdata[i].email << ":";
        for (int j = 0; j < userPlaylistCount[i]; j++) {
            outFile << playlistNames[i][j] << ":";
            for (int k = 0; k < playlistCounts[i][j]; k++) {
                outFile << playlists[i][j][k];
                if (k < playlistCounts[i][j] - 1) outFile << ",";
            }
            if (j < userPlaylistCount[i] - 1) outFile << ";";
        }
        outFile << "\n";
    }
    outFile.close();
    setConsoleColor(9, 0);
    cout << "Playlists saved successfully.\n";
    resetConsoleColor();
}
void loadPlaylistsFromFile() {
    ifstream inFile("playlists.txt");
    if (!inFile) {
        setConsoleColor(4, 0);
        cerr << "Error: Unable to open playlists file for reading.\n";
        resetConsoleColor();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(':');
        string email = line.substr(0, pos);
        string playlistData = line.substr(pos + 1);

        for (int i = 0; i < num_of_users; i++) {
            if (userdata[i].email == email) {
                stringstream ss(playlistData);
                string playlist;
                while (getline(ss, playlist, ';')) {
                    size_t pos = playlist.find(':');
                    string playlistName = playlist.substr(0, pos);
                    playlistNames[i][userPlaylistCount[i]] = playlistName;

                    string movies = playlist.substr(pos + 1);
                    stringstream movieStream(movies);
                    string movie;
                    while (getline(movieStream, movie, ',')) {
                        playlists[i][userPlaylistCount[i]]
                            [playlistCounts[i][userPlaylistCount[i]]++] = movie;
                    }
                    userPlaylistCount[i]++;
                }
                break;
            }
        }
    }
    inFile.close();
    setConsoleColor(9, 0);
    cout << "Playlists loaded successfully.\n";
    resetConsoleColor();
}


//Account Settings
void updateAccountSettings() {
    string newEmail, newPassword;
    setConsoleColor(9, 0);
    cout << "            * (Enter \"menu\" to go Back)\n";
    resetConsoleColor();
    setConsoleColor(10, 0);
    cout << "---------------Account Setting Wizard---------------\n\n\n";
    resetConsoleColor();
    cout << "Enter new email: ";
    cin >> newEmail;
    if (newEmail.compare("menu") == 0) userProfile();
    cout << "Enter new password: ";
    cin >> newPassword;

    userdata[currentUser].email = newEmail;
    userdata[currentUser].password = newPassword;
    clearconsole();
    setConsoleColor(9, 0);
    cout << "       \nAccount settings updated successfully.\n";
    resetConsoleColor();
    waitForSeconds(3);
    userProfile();
}


//Hot Air Ballon Animation
void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Clear the screen and move cursor to top-left
}

// Function to display the hot air balloon
void displayHotAirBalloon(int positionY, int positionX, bool crashing = false) {
    for (int y = 0; y < positionY; y++) {
        cout << endl; // Move the balloon up by adding empty lines
    }

    // Balloon structure
    cout << string(positionX, ' ') << RED << "   ___   " << RESET << endl;
    cout << string(positionX, ' ') << RED << "  /   \\  " << RESET << endl;
    cout << string(positionX, ' ') << RED << " /     \\ " << RESET << endl;
    cout << string(positionX, ' ') << RED << " \\     / " << RESET << endl;
    cout << string(positionX, ' ') << RED << "  \\___/  " << RESET << endl;

    // Flame and string
    if (!crashing) {
        cout << string(positionX, ' ') << ORANGE << "   | |   " << RESET << endl;
        cout << string(positionX, ' ') << ORANGE << "   | |   " << RESET << endl;
        cout << string(positionX, ' ') << WHITE << "    ||    " << RESET << endl;
        cout << string(positionX, ' ') << WHITE << "    ||    " << RESET << endl;
    }
    else {
        cout << string(positionX, ' ') << "          " << endl; // No flame when crashing
    }

    // Basket
    cout << string(positionX, ' ') << GREEN << "   ____   " << RESET << endl;
    cout << string(positionX, ' ') << GREEN << "  |____|  " << RESET << endl;
}

// Function to display clouds
void displayCloud(int positionY, int positionX) {
    for (int y = 0; y < positionY; y++) {
        cout << endl; // Move the cloud to the appropriate vertical position
    }
    cout << string(positionX, ' '); // Indent horizontally
    cout << WHITE << "   ~*~*~   " << RESET << endl; // Cloud ASCII art
}

// Function to display birds
void displayBird(int positionY, int positionX) {
    for (int y = 0; y < positionY; y++) {
        cout << endl; // Move the bird to the appropriate vertical position
    }
    cout << string(positionX, ' '); // Indent horizontally
    cout << CYAN << " ~(o )~ " << RESET << endl; // Bird ASCII art
}

// Function to display rain
void displayRain() {
    for (int i = 0; i < 20; i++) {
        if (rand() % 3 == 0) {
            cout << string(rand() % 80, ' ') << BLUE << "|" << RESET << endl; // Rain
        }
    }
}

// Function to display lightning
void displayLightning(int positionX) {
    cout << string(positionX, ' ') << YELLOW << "/^" << RESET << endl; // Lightning bolt
    cout << "\a"; // Play beep for lightning
}

// Function to display the ground
void displayGround() {
    cout << GREEN;
    for (int i = 0; i < 80; i++) {
        cout << "="; // Ground as a green strip
    }
    cout << RESET << endl;
}

// Main animation logic
void hotAirBallon() {
    int balloonY = 20; // Start position of the balloon (from the bottom)
    int balloonX = 30; // Horizontal position
    int maxHeight = 3; // The maximum height the balloon will reach
    int drift = 1;     // Drift direction for wind effect
    bool crashed = false;
    int flightTime = 15; // Extended flight time at max height

    while (true) {
        clearScreen();

        // Display the ground when the balloon is near it
        if (balloonY > 10) {
            displayGround();
        }

        // Random weather effects
        if (rand() % 3 == 0) {
            displayCloud(balloonY - rand() % 5 - 5, balloonX + (rand() % 20 - 10)); // Random clouds
        }
        if (rand() % 10 == 0) {
            displayLightning(balloonX + (rand() % 10 - 5)); // Random lightning
        }
        if (rand() % 5 == 0) {
            displayRain(); // Random rain
        }

        // Display birds randomly
        if (rand() % 5 == 0) {
            displayBird(balloonY - rand() % 5 - 3, balloonX + (rand() % 20 - 10));
        }

        // Display the hot air balloon
        if (!crashed) {
            displayHotAirBalloon(balloonY, balloonX);
            if (balloonY > maxHeight) {
                balloonY--; // Lift the balloon up
                balloonX += drift; // Apply wind drift
                if (balloonX < 10 || balloonX > 70) {
                    drift = -drift; // Reverse drift direction at boundaries
                }
            }
            else if (flightTime > 0) {
                flightTime--; // Balloon floats for some time
                balloonX += drift; // Drift during flight
            }
            else {
                crashed = true; // Trigger the crash sequence
            }
        }
        else {
            // Balloon crashes down
            for (int i = 0; i < 5; i++) {
                clearScreen();
                displayHotAirBalloon(balloonY + i, balloonX, true);
                displayGround();
                this_thread::sleep_for(chrono::milliseconds(150));
            }
            break;
        }

        // Delay for smoother animation
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Display crash message
    clearScreen();
    displayGround();
    cout << YELLOW << "The hot air balloon has crashed into the ground!" << RESET << endl;
}

