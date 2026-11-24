#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
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
    bool completed; //this is used to check if critical operations were completed
    EmployeeNode* insert(EmployeeNode* node, int empId, string n, string d, string t, string e){
        if(node == nullptr){
            completed = true;
            size += 1;
            return new EmployeeNode(empId, n, d, t, e);
        }

        if (empId < node->employeeID){ 
            node->left = insert(node->left, empId, n, d, t, e);
        }
        else if (empId > node->employeeID){ 
            node->right = insert(node->right, empId, n, d, t, e);
        }
        else{ 
            // If the ID already exists, we don't add the node and return the existing node
            cout << "Error: ID already exists.";
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
    // This function writes employee records in ID order.
    void saveNodes(EmployeeNode* node, ofstream& file){
        if (node == nullptr){
            return;
        }
        saveNodes(node->left, file);
        file << node->getID() << "," << csvField(node->getName()) << ","
             << csvField(node->getDepartment()) << ","
             << csvField(node->getTitle()) << ","
             << csvField(node->getEmail()) << "\n";
        saveNodes(node->right, file);
    }

    // This function puts quotes around CSV fields that contain commas or quotes.
    string csvField(string value){
        string result = "\"";
        for (char c : value){
            if (c == '"'){
                result += "\"\"";
            }
            else{
                result += c;
            }
        }
        result += "\"";
        return result;
    }

    // This function reads one CSV row, including fields enclosed in quotes.
    bool readCSVLine(string line, vector<string>& fields){
        fields.clear();
        string value = "";
        bool inQuotes = false;
        bool afterQuote = false;
        for (size_t i = 0; i < line.size(); i++){
            char c = line[i];
            if (inQuotes){
                if (c == '"'){
                    if (i + 1 < line.size() && line[i + 1] == '"'){
                        value += '"';
                        i++;
                    }
                    else{
                        inQuotes = false;
                        afterQuote = true;
                    }
                }
                else{
                    value += c;
                }
            }
            else if (afterQuote){
                if (c == ','){
                    fields.push_back(value);
                    value = "";
                    afterQuote = false;
                }
                else{
                    return false;
                }
            }
            else if (c == '"'){
                if (!value.empty()){
                    return false;
                }
                inQuotes = true;
            }
            else if (c == ','){
                fields.push_back(value);
                value = "";
            }
            else{
                value += c;
            }
        }
        if (inQuotes){
            return false;
        }
        fields.push_back(value);
        return fields.size() == 5;
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

    bool saveToFile(string filename){
        ofstream file(filename);
        if (!file.is_open()){
            return false;
        }
        saveNodes(root, file);
        file.close();
        return !file.fail();
    }

    bool loadFromFile(string filename){
        ifstream file(filename);
        if (!file.is_open()){
            return false;
        }
        string line;
        int skipped = 0;
        int added = 0;
        while (getline(file, line)){
            if (!line.empty() && line.back() == '\r'){
                line.pop_back();
            }
            vector<string> fields;
            if (!readCSVLine(line, fields)){
                skipped++;
                continue;
            }
            int id;
            char extra;
            stringstream idStream(fields[0]);
            if (!(idStream >> id) || id <= 0 || (idStream >> extra)){
                skipped++;
                continue;
            }
            bool missing = false;
            for (int i = 1; i < 5; i++){
                if (fields[i].find_first_not_of(" \t\r") == string::npos){
                    missing = true;
                }
            }
            if (missing || search(id) != nullptr){
                skipped++;
                continue;
            }
            if (insert(id, fields[1], fields[2], fields[3], fields[4])){
                added++;
            }
        }
        cout << added << " employees loaded. " << skipped << " rows skipped." << endl;
        return !file.bad();
    }
};

// This function reads an integer without crashing on letters or invalid numbers.
int readNumber(string message, int minimum, int maximum){
    string input;
    while (true){
        cout << message;
        if (!getline(cin, input)){
            return -1;
        }
        stringstream stream(input);
        int number;
        char extra;
        if ((stream >> number) && !(stream >> extra) &&
            number >= minimum && number <= maximum){
            return number;
        }
        cout << "Invalid number. Please try again." << endl;
    }
}

// This function reads a string from the user and ensures that it's not empty.
string readText(string message){
    string value;
    while (true){
        cout << message;
        if (!getline(cin, value)){
            return "";
        }
        if (value.find_first_not_of(" \t\r") != string::npos &&
            value.find('\n') == string::npos && value.find('\r') == string::npos){
            return value;
        }
        cout << "This field cannot be empty." << endl;
    }
}

void showEmployee(EmployeeNode* employee){
    if (employee == nullptr){
        cout << "Employee not found." << endl;
        return;
    }
    cout << "ID: " << employee->getID() << endl;
    cout << "Name: " << employee->getName() << endl;
    cout << "Department: " << employee->getDepartment() << endl;
    cout << "Title: " << employee->getTitle() << endl;
    cout << "Email: " << employee->getEmail() << endl;
}

int main(){
    AVLTree directory;
    const string filename = "employees.csv";
    bool unsaved = false;

    while (true){
        cout << "\n===== Company Employee Directory =====" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Find Employee" << endl;
        cout << "3. Update Employee" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "5. List All Employees" << endl;
        cout << "6. Save to CSV" << endl;
        cout << "7. Load from CSV" << endl;
        cout << "8. Exit" << endl;

        int choice = readNumber("Choose an option: ", 1, 8);
        if (choice == -1){
            break;
        }
        if (choice == 1){
            int id = readNumber("Employee ID: ", 1, numeric_limits<int>::max());
            if (id == -1) break;
            if (directory.search(id) != nullptr){
                cout << "Error: ID already exists." << endl;
                continue;
            }
            string name = readText("Name: ");
            string department = readText("Department: ");
            string title = readText("Job title: ");
            string email = readText("Email: ");
            if (!cin) break;
            if (directory.insert(id, name, department, title, email)){
                cout << "Employee added." << endl;
                unsaved = true;
            }
        }
        else if (choice == 2){
            int id = readNumber("Employee ID: ", 1, numeric_limits<int>::max());
            if (id == -1) break;
            showEmployee(directory.search(id));
        }
        else if (choice == 3){
            int id = readNumber("Employee ID: ", 1, numeric_limits<int>::max());
            if (id == -1) break;
            if (directory.search(id) == nullptr){
                cout << "Employee not found." << endl;
                continue;
            }
            string name = readText("New name: ");
            string department = readText("New department: ");
            string title = readText("New job title: ");
            string email = readText("New email: ");
            if (!cin) break;
            if (directory.update(id, name, department, title, email)){
                cout << "Employee updated." << endl;
                unsaved = true;
            }
        }
        else if (choice == 4){
            int id = readNumber("Employee ID: ", 1, numeric_limits<int>::max());
            if (id == -1) break;
            if (directory.remove(id)){
                cout << "Employee deleted." << endl;
                unsaved = true;
            }
            else{
                cout << "Employee not found." << endl;
            }
        }
        else if (choice == 5){
            cout << "\nEmployees (" << directory.getSize() << "):" << endl;
            directory.display();
        }
        else if (choice == 6){
            if (directory.saveToFile(filename)){
                cout << "Saved to " << filename << endl;
                unsaved = false;
            }
            else{
                cout << "Error saving file." << endl;
            }
        }
        else if (choice == 7){
            if (directory.loadFromFile(filename)){
                cout << "File loaded." << endl;
                unsaved = true; // Loading may add records to the current directory.
            }
            else{
                cout << "Could not open " << filename << endl;
            }
        }
        else if (choice == 8){
            if (unsaved){
                string answer;
                while (true){
                    cout << "Save changes before exiting? (y/n/c to cancel): ";
                    if (!getline(cin, answer)){
                        return 0;
                    }
                    if (answer == "y" || answer == "Y"){
                        if (directory.saveToFile(filename)){
                            cout << "Changes saved." << endl;
                            return 0;
                        }
                        cout << "Error saving file. Exit canceled." << endl;
                        break;
                    }
                    if (answer == "n" || answer == "N"){
                        return 0;
                    }
                    if (answer == "c" || answer == "C"){
                        break;
                    }
                    cout << "Enter y, n, or c." << endl;
                }
            }
            else{
                break;
            }
        }
    }
    return 0;
}
