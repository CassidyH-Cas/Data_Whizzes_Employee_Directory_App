#include <iostream>
#include <string>
using namespace std;

class EmployeeNode {
    friend class AVLTree;
private: 
    int employeeID;
    string name;
    string department;
    string title;
    string email;
    int height;
    EmployeeNode* left;
    EmployeeNode* right;
public:
    EmployeeNode(int empId, string n, string d, string t, string e) : employeeID(empId), name(n), department(d), title(t), email(e){
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    int getID() const{
        return employeeID;
    }
    string getName() const{
        return name;
    }
    string getDepartment() const{
        return department;
    }
    string getTitle() const{
        return title;
    }
    string getEmail() const{
        return email;
    }
    int getHeight() const{
        return height;
    }
    void setName(string n){
        name = n;
    }
    void setDepartment(string d){
        department = d;
    }
    void setTitle(string t){
        title = t;
    }
    void setEmail(string e){
        email = e;
    }
    void setHeight(int h){
        height = h;
    }
};

class AVLTree {
private: 
    EmployeeNode* root;
    int size;
    bool completed; //use to check if critical operations were completed
    EmployeeNode* insert(EmployeeNode* node, int empId, string n, string d, string t, string e){
        if(node == nullptr){
            completed = true;
            size += 1;
            return new EmployeeNode(empId, n, d, t, e);
        }

        if (empId < node->employeeID){ 
            node->left = insert(node->left, empId, n, d, t, e);
            completed = true;
        }
        else if (empId > node->employeeID){ 
            node->right = insert(node->right, empId, n, d, t, e);
            completed = true;
        }
        else{ 
            cout << "Error: ID already exists."; //not sure if this goes in main or not
            completed = false;
            return node;
        }

        updateHeight(node);
        
        int balanceFactor = getBalance(node);
        //right rotation
        if (balanceFactor > 1 && empId < node->left->employeeID){
            node = rotateRight(node);
        }
        //left rotation
        else if (balanceFactor < -1 && empId > node->right->employeeID){
            node = rotateLeft(node);
        }
        //left-right rotation
        else if (balanceFactor > 1 && empId > node->left->employeeID){
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        //right-left rotation
        else if (balanceFactor < -1 && empId < node->right->employeeID){
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        return node;
    }
    EmployeeNode* rotateLeft(EmployeeNode* node){
        if (node == nullptr || node->right == nullptr){
            return node;
        }

            EmployeeNode* rChild = node->right;
            node->right = rChild->left;
            rChild->left = node;

        updateHeight(node);
        updateHeight(rChild);

        return rChild;
    }
    EmployeeNode* rotateRight(EmployeeNode* node){
        if (node == nullptr || node->left == nullptr){
            return node;
        }

            EmployeeNode* lChild = node->left;
            node->left = lChild->right;
            lChild->right = node;

        updateHeight(node);
        updateHeight(lChild);

        return lChild;
    }
    int getBalance(EmployeeNode* node){
        return getHeight(node->left) - getHeight(node->right);
    }
    void updateHeight(EmployeeNode* node){
        if (node != nullptr){
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            node->height = max(leftHeight, rightHeight) + 1;
        }
    }
    int getHeight(EmployeeNode* node){
        if (node == nullptr){
            return 0;
        }
        else
            return node->height;
    }

public:
    AVLTree(){
        root = nullptr;
        size = 0;
        completed = false;
    }
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    ~AVLTree(){
        destruct(root);
        root = nullptr;
    }
    void destruct(EmployeeNode* r){
        if (r == nullptr)
        return;
        destruct(r->left);
        destruct(r->right);
        delete r;
    }
    bool insert(int empId, string n, string d, string t, string e){
        root = insert(root, empId, n, d, t, e);
        return completed;
    }
};
