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
    EmployeeNode* searchNode(EmployeeNode* node, int empId){
        if (node == nullptr || node->employeeID == empId){
            return node;
        }
        if (empId < node->employeeID){
            return searchNode(node->left, empId);
        }
        return searchNode(node->right, empId);
    }

    EmployeeNode* deleteNode(EmployeeNode* node, int empId){
        if (node == nullptr){
            return nullptr;
        }

        if (empId < node->employeeID){
            node->left = deleteNode(node->left, empId);
        }
        else if (empId > node->employeeID){
            node->right = deleteNode(node->right, empId);
        }
        else{
            // 0 or 1 child
            if (node->left == nullptr || node->right == nullptr){
                EmployeeNode* child = (node->left != nullptr) ? node->left : node->right;
                delete node;
                return child;
            }
            // 2 children: copy the next-biggest employee here, then delete that one
            EmployeeNode* successor = node->right;
            while (successor->left != nullptr){
                successor = successor->left;
            }
            node->employeeID = successor->employeeID;
            node->name = successor->name;
            node->department = successor->department;
            node->title = successor->title;
            node->email = successor->email;
            node->right = deleteNode(node->right, successor->employeeID);
        }

        updateHeight(node);

        int balanceFactor = getBalance(node);
        //left-left
        if (balanceFactor > 1 && getBalance(node->left) >= 0){
            return rotateRight(node);
        }
        //left-right
        if (balanceFactor > 1 && getBalance(node->left) < 0){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        //right-right
        if (balanceFactor < -1 && getBalance(node->right) <= 0){
            return rotateLeft(node);
        }
        //right-left
        if (balanceFactor < -1 && getBalance(node->right) > 0){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void inOrderTraversal(EmployeeNode* node){
        if (node == nullptr){
            return;
        }
        inOrderTraversal(node->left);
        cout << node->employeeID << " | " << node->name << " | "
             << node->department << " | " << node->title << " | "
             << node->email << endl;
        inOrderTraversal(node->right);
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
    EmployeeNode* search(int empId){
        return searchNode(root, empId);
    }

    bool update(int empId, string n, string d, string t, string e){
        EmployeeNode* node = searchNode(root, empId);
        if (node == nullptr){
            return false;
        }
        node->setName(n);
        node->setDepartment(d);
        node->setTitle(t);
        node->setEmail(e);
        return true;
    }

    bool remove(int empId){
        if (searchNode(root, empId) == nullptr){
            return false;
        }
        root = deleteNode(root, empId);
        size -= 1;
        return true;
    }

    int getSize() const{
        return size;
    }

    void display(){
        if (root == nullptr){
            cout << "Directory is empty." << endl;
            return;
        }
        inOrderTraversal(root);
    }
};
