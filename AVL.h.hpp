#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

struct node{
        string key;
        int height;
        node* left;
        node* right;
        time_t creation;
        node(string data){
            key=data;
            height=0;
            creation=time(nullptr);
            left=right=nullptr;
        }
    };

class AVL{
public:
    node* root;
    AVL(){
        root=nullptr;
    }
    int height(node* n){
        if (n!=nullptr){
            return n->height;
        }
        else return -1;
    }
    int getbalance(node* n){
        if(n!=nullptr){
            return height(n->left)-height(n->right);
        }
        else return 0;

    }

    node* rightrotate(node*y){
        node*temp1=y->left;
        node*temp2=temp1->right;
        temp1->right=y;
        y->left=temp2;
        y->height=max(height(y->left),height(y->right))+1;
        temp1->height=max(height(temp1->left),height(temp1->right))+1;
        return temp1;
    }

    node* leftrotate(node*y){
        node*temp1=y->right;
        node*temp2=temp1->left;
        temp1->left=y;
        y->right=temp2;
        y->height=max(height(y->left),height(y->right))+1;
        temp1->height=max(height(temp1->left),height(temp1->right))+1;
        return temp1;
    }

    node* insert(node*initial, node* vip){

        if(initial==nullptr){
            return vip;
        }
        else if(vip->creation<initial->creation){
            initial->left=insert(initial->left,vip);
        }
        else if(vip->creation>initial->creation){
            initial->right=insert(initial->right,vip);
        }
        else return initial;
        initial->height=max(height(initial->left),height(initial->right))+1;
        int bf=getbalance(initial);

        if (bf>1 && vip->creation<initial->left->creation){
            return rightrotate(initial);
        }
        else if(bf>1 &&vip->creation>initial->left->creation){
            initial->left=leftrotate(initial->left);
            return rightrotate(initial);
        }
        else if (bf<-1 && vip->creation>initial->right->creation){
            return leftrotate(initial);
        }
        else if(bf<-1 &&vip->creation<initial->right->creation){
            initial->right=rightrotate(initial->right);
            return leftrotate(initial);
        }
        return initial;
    }

    node*minvaluenode(node*n){
        node*current=n;
        while(current->left!=nullptr){
            current=current->left;
        }
        return current;
    }

    // node* deletee(node*initial,node*vip){
    //     if(initial==nullptr){
    //         return initial;
    //     }
    //     else if(vip->creation>initial->creation){
    //         initial->right=deletee(initial->right,vip);
    //     }
    //     else if(vip->creation<initial->creation){
    //         initial->left=deletee(initial->left,vip);
    //     }
    //     else{
    //         if(initial->left==nullptr){
    //             node*temp=initial->right;
    //             delete(initial);
    //             return temp;
    //         }
    //         else if(initial->right==nullptr){
    //             node*temp=initial->left;
    //             delete(initial);
    //             return temp;
    //         }
    //         else{
    //             node* tempp=minvaluenode(initial->right);
    //             initial->key=tempp->key;
    //             initial->creation=tempp->creation;
    //             initial->right= deletee(initial->right,tempp);
    //         }
    //     }
    //     initial->height=max(height(initial->left),height(initial->right))+1;
    //     int bf=getbalance(initial);

    //     if(bf==2 && getbalance(initial->left)>=0){
    //         return rightrotate(initial);
    //     }
    //     else if(bf==2 && getbalance(initial->left)<0){
    //         initial->left=leftrotate(initial->left);
    //         return rightrotate(initial);
    //     }
    //     else if(bf==-2 && getbalance(initial->right)<=0){
    //         return leftrotate(initial);
    //     }
    //     else if(bf==-2 && getbalance(initial->right)>0){
    //         initial->right=rightrotate(initial->right);
    //         return leftrotate(initial);
    //     }
    //     return initial;
    // }
    
    void printReverseInOrder(node* n, int N, int& count) {
        if (n->right != nullptr) {
            printReverseInOrder(n->right, N, count);
        }

        if (N != -1 && count >= N) {
            return;
        }

        cout << n->key << endl;
        count++;

        if (n->left != nullptr) {
            printReverseInOrder(n->left, N, count);
        }
    }

    void output_posts_recursive(node* root, int N) {
        if (root == nullptr) {
            return;
        }
        int count = 0;
        printReverseInOrder(root, N, count);
    }
    void destroyTree(node* n) {
        if (n == nullptr) {
            return;
        }
        destroyTree(n->left);
        destroyTree(n->right);
        delete n;
    }
};


