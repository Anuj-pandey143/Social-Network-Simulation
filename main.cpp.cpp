#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm> // For transform
#include <cctype>    // For tolower
#include "Graph.hpp"

using namespace std;

// Helper function to handle case-insensitivity for arguments
string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    net social_net;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string command;
        ss >> command; // Read the command AS-IS

        string extra_arg; 

        try {
            if (command == "ADD_USER") { // Check for exact uppercase
                string username;
                if (!(ss >> username)) {
                    cout << "Error: Missing username for ADD_USER" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for ADD_USER" << endl;
                    continue;
                }

                username = to_lower(username); // Convert ARGUMENT to lower
                if (social_net.user_map.find(username) != social_net.user_map.end()) {
                    cout << "Error: User '" << username << "' already exists." << endl;
                    continue;
                }
                social_net.add_user(username);
                cout << "User '" << username << "' added." << endl;

            } else if (command == "ADD_FRIEND") { // Check for exact uppercase
                string user1, user2;
                if (!(ss >> user1 >> user2)) {
                    cout << "Error: Missing one or two usernames for ADD_FRIEND" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for ADD_FRIEND" << endl;
                    continue;
                }

                user1 = to_lower(user1); // Convert ARGUMENTS to lower
                user2 = to_lower(user2);

                if (user1 == user2) {
                    cout << "Error: Cannot add yourself as a friend." << endl;
                    continue;
                }
                if (social_net.user_map.find(user1) == social_net.user_map.end()) {
                    cout << "Error: User '" << user1 << "' not found." << endl;
                    continue;
                }
                if (social_net.user_map.find(user2) == social_net.user_map.end()) {
                    cout << "Error: User '" << user2 << "' not found." << endl;
                    continue;
                }

                social_net.add_friend(user1, user2);
                cout << "Friendship added between '" << user1 << "' and '" << user2 << "'." << endl;

            } else if (command == "LIST_FRIENDS") { // Check for exact uppercase
                string username;
                if (!(ss >> username)) {
                    cout << "Error: Missing username for LIST_FRIENDS" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for LIST_FRIENDS" << endl;
                    continue;
                }

                username = to_lower(username); // Convert ARGUMENT to lower
                if (social_net.user_map.find(username) == social_net.user_map.end()) {
                    cout << "Error: User '" << username << "' not found." << endl;
                    continue;
                }

                set<string> friends = social_net.list_friend(username);
                for (const string& name : friends) {
                    cout << name << endl;
                }

            } else if (command == "SUGGEST_FRIENDS") { // Check for exact uppercase
                string username, n_str;
                if (!(ss >> username >> n_str)) {
                    cout << "Error: Missing arguments for SUGGEST_FRIENDS" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for SUGGEST_FRIENDS" << endl;
                    continue;
                }
                
                int n;
                try {
                    n = stoi(n_str);
                } catch (const exception& e) {
                    cout << "Error: <N> must be a valid number." << endl;
                    continue;
                }

                if (n < 0) {
                    cout << "Error: N must be 0 or greater." << endl;
                    continue;
                }
                
                username = to_lower(username); // Convert ARGUMENT to lower
                if (social_net.user_map.find(username) == social_net.user_map.end()) {
                    cout << "Error: User '" << username << "' not found." << endl;
                    continue;
                }

                vector<string> suggestions = social_net.suggest_friends(username, n);
                int count = 0;
                for (const string& name : suggestions) {
                    if (count >= n) break;
                    cout << name << endl;
                    count++;
                }

            } else if (command == "DEGREES_OF_SEPARATION") { // Check for exact uppercase
                string user1, user2;
                if (!(ss >> user1 >> user2)) {
                    cout << "Error: Missing one or two usernames for DEGREES_OF_SEPARATION" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for DEGREES_OF_SEPARATION" << endl;
                    continue;
                }

                user1 = to_lower(user1); // Convert ARGUMENTS to lower
                user2 = to_lower(user2);
                
                if (social_net.user_map.find(user1) == social_net.user_map.end()) {
                    cout << "Error: User '" << user1 << "' not found." << endl;
                    continue;
                }
                if (social_net.user_map.find(user2) == social_net.user_map.end()) {
                    cout << "Error: User '" << user2 << "' not found." << endl;
                    continue;
                }
                
                cout << social_net.degrees_of_separation(user1, user2) << endl;

            } else if (command == "ADD_POST") { // Check for exact uppercase
                string username;
                if (!(ss >> username)) {
                    cout << "Error: Missing username for ADD_POST" << endl;
                    continue;
                }
                
                string rest_of_line;
                getline(ss, rest_of_line); 

                size_t first_quote = rest_of_line.find('"');
                size_t last_quote = rest_of_line.rfind('"');

                if (first_quote == string::npos || last_quote == first_quote) {
                    cout << "Error: Malformed post content. Must be enclosed in \"quotes\"." << endl;
                    continue;
                }

                string content = rest_of_line.substr(first_quote + 1, last_quote - first_quote - 1);
                
                username = to_lower(username); // Convert ARGUMENTS to lower
                content = to_lower(content);
                

                if (social_net.user_map.find(username) == social_net.user_map.end()) {
                    cout << "Error: User '" << username << "' not found." << endl;
                    continue;
                }

                social_net.add_post(username, content);
                cout << "Post added." << endl;

            } else if (command == "OUTPUT_POSTS") { // Check for exact uppercase
                string username, n_str;
                if (!(ss >> username >> n_str)) {
                    cout << "Error: Missing arguments for OUTPUT_POSTS" << endl;
                    continue;
                }
                if (ss >> extra_arg) {
                    cout << "Error: Too many arguments for OUTPUT_POSTS" << endl;
                    continue;
                }

                int n;
                try {
                    n = stoi(n_str);
                } catch (const exception& e) {
                    cout << "Error: <N> must be a valid number." << endl;
                    continue;
                }
                
                username = to_lower(username); // Convert ARGUMENT to lower
                if (social_net.user_map.find(username) == social_net.user_map.end()) {
                    cout << "Error: User '" << username << "' not found." << endl;
                    continue;
                }
                
                social_net.output_posts(username, n);

            } else {
                cout << "Error: Invalid command '" << command << "'" << endl;
            }
        } catch (const exception& e) {
            cout << "An unexpected error occurred: " << e.what() << endl;
        }
    }
    return 0;
}
