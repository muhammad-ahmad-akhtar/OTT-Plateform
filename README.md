# Nebula Stream Application

Nebula Stream is an interactive streaming platform with features like user and admin access, movie recommendations, playlists, and much more. This guide explains how to set up and use the program.

> [!IMPORTANT]
> Credit to the original creators when using the code yourself.

---

## Features

1. **User Authentication:** Secure login and signup for users and admins.
2. **Movie Streaming:** Search and play movies from a customizable collection.
3. **Subscription Plans:** Weekly, monthly, and yearly subscription options.
4. **Personalized Recommendations:** Recommendations based on watch history.
5. **Playlists:** Create, edit, and manage custom playlists.
6. **Admin Panel:** Admins can add/remove movies, view finances, and manage user requests.
7. **Watch History:** Track movies watched by each user.
8. **File Handling:** Data persistence using text files for users, movies, requests, finances, and playlists.
9. **Dynamic Animation:** Engaging logo animations and UI effects.
10. **Images and Visuals:** Add screenshots and visuals for better understanding.

---

## Prerequisites

1. **Operating System:** Windows (for proper functioning of `system("cls")` and color features).
2. **C++ Compiler:** Ensure you have a C++17 or newer compiler installed.
3. **Libraries:**
   - Standard C++ Libraries (`<iostream>`, `<fstream>`, `<sstream>`, `<stdexcept>`).
   - Platform-specific libraries (`<windows.h>` for console effects).

> [!NOTE]
> Try running this code on visual studio 2022 for the best experience.


---

## Project Structure

> [!WARNING]
>  Don't edit or update the .txt files yourself.

- **users.txt:** Stores user email, password, and subscription status.
- **admins.txt:** Stores admin email and password.
- **movies.txt:** Stores movie details like name, category, duration, description, and views.
- **requests.txt:** Logs user movie requests.
- **finances.txt:** Keeps track of total revenue and subscription counts.
- **watch_history.txt:** Tracks movies watched by users.
- **playlists.txt:** Stores user-specific playlists.

> [!CAUTION]
> Name the .txt files carefully.

---

## How to Run

### Step 1: Compile the Program
Use a C++ compiler to compile the program. For example:
```bash
g++ -o nebula_stream main.cpp -std=c++17
```

### Step 2: Execute the Program
Run the compiled executable:
```bash
./nebula_stream
```
---

## Instructions for Users

### **Main Menu**
1. Select your role:
   - **User**: For accessing the streaming platform.
   - **Admin**: For managing content and platform settings.
2. **Exit**: Close the program.

### **User Features**

#### 1. **Login/Signup**
   - Enter your email and password to log in.
   - Create a new account if you don’t have one.

#### 2. **Stream Movies**
   - Use the search bar to find movies by title.
   > [!TIP]
   > Search for "Hot Air Ballon" in the movies search section to start the animation.

   - Browse categories, trending movies, and upcoming releases.
     
   ##### **Featured Movie**
   ![Hot-Air-Ballon-Poster](Hot-Air-Ballon.png)
   

#### 3. **Manage Playlists**
   - Create and name custom playlists.
   - Add, remove, or rename movies in your playlists.

#### 4. **Subscription Plans**
   - Choose from weekly ($7), monthly ($31), or yearly ($365) plans.

#### 5. **Recommendations**
   - Get personalized recommendations based on your watch history.

#### 6. **Profile Management**
   - View your watch history.
   - Check your subscription status.
   - Manage account settings.

### **Admin Features**

#### 1. **Content Management**
   - Add new movies with name, category, duration, and description.
   - Remove existing movies.
   - View the complete movie catalog.

#### 2. **View Finances**
   - Monitor revenue generated from user subscriptions.

#### 3. **User Requests**
   - View and manage movie requests submitted by users.

---

## Preview of Output :tada:

[![Screen Recording of the Project](https://img.youtube.com/vi/FN1vuqLx1vA/0.jpg)](https://www.youtube.com/watch?v=FN1vuqLx1vA)

---

## Error Handling

1. **Invalid Input:** The program ensures valid input ranges and prompts users to re-enter values when incorrect data is provided.
2. **File Errors:** If a file fails to load or save, an error message is displayed.

---

## Developer Credits

- **Ahmad Akhtar**: User Authentication, Profile Management
- **Hassan Ahmad**: Playlist Management, Search Movies
- **Abdul Wahab**: Watch History, User Requests
- **Muhammad Saad**: Admin Panel, Content Management

---

## Future Enhancements

1. Multi-language support.
2. Enhanced recommendation algorithms.
3. Mobile and web versions of the platform.

---

## License
> This project is open-source and licensed under the MIT License.

---
