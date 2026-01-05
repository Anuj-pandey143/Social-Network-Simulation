#include "AVL.hpp"
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

class user{
public:
    node* user_post;
    string name;
    user(string uname){
        name=uname;
        user_post=nullptr;
    }
};

class net{
private:
    struct QNode {
        user* u;
        int dist;
        QNode* next;
        QNode(user* usr, int d) : u(usr), dist(d), next(nullptr) {}
    };

    class BFSQueue {
        QNode *front, *rear;
    public:
        BFSQueue() : front(nullptr), rear(nullptr) {}
        
        ~BFSQueue() {
            while (front != nullptr) {
                QNode* temp = front;
                front = front->next;
                delete temp;
            }
        }

        bool isEmpty() {
            return front == nullptr;
        }

        void enqueue(user* usr, int d) {
            QNode* temp = new QNode(usr, d);
            if (rear == nullptr) {
                front = rear = temp;
                return;
            }
            rear->next = temp;
            rear = temp;
        }

        bool dequeue(user* &outUser, int &outDist) {
            if (isEmpty()) {
                return false;
            }
            QNode* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }

            outUser = temp->u;
            outDist = temp->dist;
            
            delete temp;
            return true;
        }
    };
public:
    string net_name;
    vector<vector<user>> adjlist;
    unordered_map<string,pair<user*,vector<user*>>> user_map;
    AVL avl_tree_manager;
    net(){
        net_name="system";
    }
    ~net() {
        for (auto& pair : user_map) {
            user* u = pair.second.first;
            avl_tree_manager.destroyTree(u->user_post);
            delete u;
        }
    }
    bool add_user(string name){
        user* new_user = new user(name);
        vector<user*> user_friends={};
        user_map[name].first=new_user;
        user_map[name].second=user_friends;
        return true;
    }
    bool add_friend(string name1, string name2){
        user_map[name1].second.push_back(user_map[name2].first);
        user_map[name2].second.push_back(user_map[name1].first);
        return true;
    }

    set<string> list_friend(string name){
        vector<user*> friends=user_map[name].second;
        set<string> sorted_name;
        for(size_t i=0;i<friends.size();i++){
            sorted_name.insert(friends[i]->name);
        }
        return sorted_name;
    }
    
    vector<string> suggest_friends(string name, int N) {
        vector<user*>& friends = user_map[name].second;
        unordered_map<user*, int> mapper;

        for (user* f : friends) {
            vector<user*>& friendof = user_map[f->name].second;
            for (user* fof : friendof) {
                mapper[fof]++;
            }
        }

        auto cmp = [&mapper](user* a, user* b) {
            int countA = mapper.at(a);
            int countB = mapper.at(b);
            if (countA > countB) {
                return true;
            } else if (countA < countB) {
                return false;
            } else {
                return a->name < b->name;
            }
        };

        vector<user*> final_candidates;
        user* self = user_map[name].first;

        for (auto const& [user_ptr, count] : mapper) {
            if (user_ptr == self) {
                continue;
            }

            bool isFriend = false;
            for (user* f : friends) {
                if (f == user_ptr) {
                    isFriend = true;
                    break;
                }
            }

            if (!isFriend) {
                final_candidates.push_back(user_ptr);
            }
        }

        sort(final_candidates.begin(), final_candidates.end(), cmp);

        vector<string> result;
        for (size_t i = 0; i < final_candidates.size(); i++) {
            result.push_back(final_candidates[i]->name);
        }
        return result;
    }

    int degrees_of_separation(string name1, string name2) {
        if (name1 == name2) {
            return 0;
        }

        if (user_map.find(name1) == user_map.end() || user_map.find(name2) == user_map.end()) {
            return -1; 
        }
        user* startUser = user_map[name1].first;
        user* endUser = user_map[name2].first;

        BFSQueue q;
        unordered_map<user*, bool> visited; 

        q.enqueue(startUser, 0);
        visited[startUser] = true;

        user* currentUser = nullptr;
        int currentDist = 0;

        while (q.dequeue(currentUser, currentDist)) {
            if (currentUser == endUser) {
                return currentDist;
            }

            vector<user*>& friends = user_map[currentUser->name].second; 

            for (size_t i = 0; i < friends.size(); ++i) {
                user* neighbor = friends[i];
                
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = true;
                    q.enqueue(neighbor, currentDist + 1);
                }
            }
        }
        return -1;
    }

    void add_post(string name, string content) {
        if (user_map.find(name) == user_map.end()) {
            return;
        }

        user* main = user_map[name].first;
        node* new_post = new node(content);

        main->user_post = avl_tree_manager.insert(main->user_post, new_post);
    }

    void output_posts(string username, int N) {
        if (user_map.find(username) == user_map.end()) {
            return;
        }
        
        user* target_user = user_map[username].first;
        node* root = target_user->user_post;
        
        avl_tree_manager.output_posts_recursive(root, N);
    }

};