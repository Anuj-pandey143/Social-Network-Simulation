# SocialNet Simulator

This project is a command-line simulator for a social network's backend services, implemented in C++. It manages users, their friendships, and their content using custom-built graph and tree data structures. The system allows users to add friends, find degrees of separation, post content, and receive friend suggestions.

---

## Key Features 📝

* **User Management**: Add new users to the social network.
* **Friendship Graph**: Create bidirectional friendships between users.
* **Content Management**: Users can create posts, which are stored chronologically.
* **Social Analysis**:
    * List a user's friends alphabetically.
    * Calculate the shortest path (degrees of separation) between two users.
    * Suggest new friends based on "friends of friends," ranked by mutual connections.
* **Post Retrieval**: Fetch a user's `N` most recent posts.

---

## Data Structures Implemented 🏗️

As per the assignment requirements, the core data structures were implemented to handle the system's logic.

* **Undirected Graph**
    * The entire social network is represented as an undirected graph. Each `user` object is a vertex, and an edge between two vertices represents a bidirectional friendship.
    * An `std::unordered_map` (as permitted by the assignment) is used to map username strings to their corresponding `user` vertex pointers for $O(1)$ average-time lookups.
    * The **Breadth-First Search (BFS)** algorithm is implemented to find the shortest path for the `DEGREES_OF_SEPARATION` command.

* **AVL Tree**
    * Each `user` object has a pointer to the root of their own AVL Tree.
    * This self-balancing binary search tree is used to store all posts created by that user.
    * Posts are sorted by their `time_t creation` timestamp, allowing for efficient insertion and retrieval of the most recent posts. A **reverse in-order traversal** is used to fetch posts from newest to oldest for the `OUTPUT_POSTS` command.

---

## How to Compile and Run ⚙️

The project includes a shell script (`compiler.sh`) to simplify compilation.

1.  **Give Execution Permission**: First, make the compile script executable.
    ```bash
    chmod +x compiler.sh
    ```
2.  **Compile the Code**: Run the script to compile the `main.cpp` file. This will generate an executable named `anuj`.
    ```bash
    ./compiler.sh
    ```
3.  **Run the Program**: Execute the compiled program to start the simulator.
    ```bash
    ./anuj
    ```
4.  **Enter Commands**: Once running, you can enter commands directly into the terminal.

---

## Command Reference ⌨️

The program accepts commands from standard input. Per the assignment, usernames and post content are treated as **case-insensitive**.

### Social Network Operations

* **`ADD_USER <username>`**
    * Adds a new user to the network.
    * Example: `ADD_USER Alice`

* **`ADD_FRIEND <username1> <username2>`**
    * Establishes a bidirectional friendship between two existing users.
    * Example: `ADD_FRIEND Alice Bob`

* **`LIST_FRIENDS <username>`**
    * Prints an alphabetically sorted list of the specified user's friends.
    * Example: `LIST_FRIENDS Alice`

* **`SUGGEST_FRIENDS <username> <N>`**
    * Recommends up to `N` new friends who are "friends of a friend" but not already friends.
    * Recommendations are ranked by the number of mutual friends (descending), with ties broken by alphabetical order.
    * Example: `SUGGEST_FRIENDS Alice 3`

* **`DEGREES_OF_SEPARATION <username1> <username2>`**
    * Calculates the length of the shortest path of friendships between two users. Reports -1 if no path exists.
    * Example: `DEGREES_OF_SEPARATION Alice Charlie`

### User Content Operations

* **`ADD_POST <username> "<post_content>"`**
    * Adds a new post to the specified user's timeline. The post content must be enclosed in double quotes.
    * Example: `ADD_POST Alice "This is my first post!"`

* **`OUTPUT_POSTS <username> <N>`**
    * Outputs the `N` most recent posts for the user, in reverse chronological order.
    * If `N` is -1, all posts are shown.
    * If the user has fewer than `N` posts, all available posts are shown.
    * Example: `OUTPUT_POSTS Alice 5`

---

## Error Handling ⚠️

The system provides clear error messages for invalid input, including:

* **Invalid Command**: If the command (e.g., `ADD_USER`) is misspelled or unknown.
* **Incorrect Argument Count**: If a command is given too few or too many arguments.
* **User Not Found**: If a command refers to a username that does not exist.
* **User Already Exists**: If `ADD_USER` is called with a username that is already taken.
* **Invalid Numeric Input**: If `N` for `SUGGEST_FRIENDS` or `OUTPUT_POSTS` is not a valid number.
* **Malformed Post**: If `ADD_POST` is called without the content being properly enclosed in `"quotes"`.
* **Invalid Friendship**: If `ADD_FRIEND` is called trying to add a user to themself.

---

## Project Structure 📁

The submission contains the following files:

* `main.cpp`: The main program file that handles command parsing and execution.
* `Graph.hpp`: Header file containing the implementation of the `user` and `net` (Graph) classes.
* `AVL.hpp`: Header file containing the implementation of the `node` (Post) and `AVL` (Tree) classes.
* `compiler.sh`: A shell script for easy compilation of the project.
* `README.md`: This file.
