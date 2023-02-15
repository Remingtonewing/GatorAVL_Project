#include <iostream>
#include <string>
#include "TreeNode.h"
#include <iterator>
#include <vector>

//.compare() taken from https://www.geeksforgeeks.org/stdstringcompare-in-c/ easiest method I used to compare ID values.



struct Node {
    std::string name;
    std::string ID;
    Node* right;
    Node* left;

    Node(std::string ID, std::string name) {
        this->ID = ID;
        this->name = name;
    }

    Node() {}

    std::string getId() {
        return ID;
    }

    std::string getName() {
        return name;
    }

};

class TreeNode {

public:

    Node *head;

    int findHeavy(Node* node) { //Finds which direction the tree "leans" (Mod 4 pg. 28)
        if (!node) {
            return 0;
        } else {
            int left = findHeavy(node->left) + 1;
            int right = findHeavy(node->right) + 1;
            if (left == right) {
                return right;
            }
            if (right < left) {
                return left;
            }
            if (left < right) {
                return right;
            }
        }
    }

    int balanceTreeFactor(Node* node) { //Mod 4 Pg. 33
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }


    Node *Remove(Node *root, std::string ID) {
        if (!root) {
            std::cout << "unsuccessful" << std::endl;
            return root;
        }
        if (head->getId() == ID) {
            head = nullptr;
            delete root;
            std::cout<< "successful" << std::endl;
            return head;
        }
        if (std::stoi(root->getId()) < std::stoi(ID))
            root->right = Remove(root,ID);
        if (std::stoi(root->getId()) > std::stoi(ID))
            root->left = Remove(root->left,ID);
        if (root->getId() == ID) {
            if (!root->left && !root->right) {
                delete root;
                std::cout<< "successful" << std::endl;
                return nullptr;
            } if (root->right == nullptr && root->left != nullptr) {
                root->ID = root->left->getId();
                root->name = root->left->getName();
                root->left = root->left->left;
                root->right = root->left->right;
                delete root->left;

                std::cout<< "successful" << std::endl;

                return root;
            } if (root->left == nullptr && root->right != nullptr) {
                root->ID = root->right->getId();
                root->name = root->right->getName();
                root->left = root->right->left;
                root->right = root->right->right;
                delete root->right;

                std::cout<< "successful" << std::endl;

                return root;
            } if (root->right && root->left) {
                Node* finder = root->right;
                while (finder->left) {
                    finder = finder->left;
                }
                root->ID = finder->ID;
                root->name = finder->name;
                root->right = Remove(root->right, root->ID);
                return root;
            }
        }
    }

    Node *rotateRight(Node* node) { //Taken directly from slides :D
        Node* grandChild = node->right->left;
        Node* newParent = node->left;
        newParent->right = node;
        node->right = grandChild;
        return newParent;
    }

    Node *rotateLeft(Node* node) { //Also taken directly from Mod 4. Slidees :D
        Node* grandChild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandChild;
        return newParent;
    }

    Node *Rotate(Node *root) {

    }

    Node *IDSearch(Node *root, std::string ID) {
        if (!root) {
            return nullptr;
        }
        if (root->ID != ID) {
            IDSearch(root->left, ID);
            IDSearch(root->right, ID);
        } else {
            std::cout << root->name << std::endl;
            return root;
        }
        return nullptr;
    }

    Node *nameSearch(Node *root, std::string name) {
        if (root->getName() == name) {
            std::cout << "successful" << std::endl;
            return root;
        } else {
            nameSearch(root->left, name);
            nameSearch(root->right, name);
        }
        std::cout << "unsuccessful" << std::endl;
        return root;
    }

    int height(Node* root) //Stepik solution 5.1a
    {
        if (!root)
            return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }


    TreeNode() {
        head = nullptr;
    }


    Node *Head() {
        return head;
    }


    Node *Insert(Node *root, Node node) {
        if (root == nullptr) {
            if (head == nullptr) {
                root = new Node(node.getId(), node.getName());
                head = root;
                std::cout << "successful" << std::endl;
                return head;
            } else {
                std::cout << "successful" << std::endl;
                return new Node(node.getId(), node.getName());
            }
        }
        if (root->getId() == node.getId()) {
            std::cout << "unsuccessful" << std::endl;
            return root;
        }
         if (std::stoi(root->getId()) < std::stoi(node.getId())) {
            root->right = Insert(root->right, node);
            //Incorporate rotate function
            return root;
        } if (std::stoi(root->getId()) > std::stoi(node.getId())) {
            root->left = Insert(root->left, node);
             //Incorporate rotate function
             return root;
         }
         std::cout << "unsuccessful" << std::endl;
         return root;
    }
    void printPost(Node* node, std::vector<std::string> &printName) { //All three print algorithms present in slides
        if (node) {
            printPost(node->left, printName);
            printPost(node->right, printName);
            printName.push_back(node->name);
        }else {
            std::cout << "";
        }
    }
    void PrintPre(Node* node, std::vector<std::string> &printName) {
        if (node) {
            printName.push_back(node->name);
            PrintPre(node->left, printName);
            PrintPre(node->right, printName);
        }else {
            std::cout << "";
        }
    }
    void PrintInOrder(Node* node, std::vector<std::string> &printName) {
        if (node) {
            PrintInOrder(node->left, printName);
            printName.push_back(node->name);
            PrintInOrder(node->right, printName);
        } else {
            std::cout << "";
        }
    }

    void printVector(std::vector<std::string> printName) {
        for (int i = 0; i < printName.size(); i++) {
            if (i != printName.size() - 1)
                std::cout << printName[i] << ",";
            else
                std::cout << printName[i];
        }
    }

};

    bool checkNum(std::string userInput) {
        if (userInput.length() != 8) {
            return false;
        }
        for (auto i: userInput) {
            if (std::isdigit(i) == false) {
                return false;
            }
        }
        return true;
    }

    bool checkString(std::string userInput) { //https://cplusplus.com/reference/cctype/isalpha/
        for (char i: userInput) {
            if (std::isalpha(i) == false && std::isblank(i) == false) {
                return false;
            }
        }
        return true;
    }


    std::string getIdVal(std::string userInput) {
        int quoteCount = 0;
        while (quoteCount < 2) {
            if (userInput[0] == '"') {
                userInput.erase(0, 1);
                quoteCount++;
            } else {
                userInput.erase(0, 1);
            }
        }
        userInput.erase(0, 1);
        if (!checkNum(userInput)) {
            return "unsuccessful";
        } else {
            return userInput;
        }
    }

    std::string getNameVal(std::string userInput) {
        int iter = 0;
        int quoteCount = 0;
        while (quoteCount < 2) {
            if (userInput[iter] == '"') {
                quoteCount++;
                userInput.erase(iter, 1);
            } else {
                iter++;
            }
            if (quoteCount == 2) {
                break;
            }
            if (quoteCount == 0 && iter == userInput.length()) {
                return "unsuccessful";
            }
            if (quoteCount == 1 && iter == userInput.length()) {
                return "unsuccessful";
            }
        }
        userInput = userInput.substr(0, iter);
        if (!checkString(userInput)) {
            return "unsuccessful";
        }
        return userInput.substr(0, iter);
    }

    std::string findCommand(std::string input) {
        std::string::size_type commandType = input.find("insert", 0);
        if (commandType != std::string::npos) {
            return "insert";
        }
        commandType = input.find("remove", 0);
        if (commandType != std::string::npos) {
            return "remove";
        }
        commandType = input.find("printInorder", 0);
        if (commandType != std::string::npos) {
            return "printInorder";
        }
        commandType = input.find("removeInorder", 0);
        if (commandType != std::string::npos) {
            return "removeInorder";
        }commandType = input.find("search", 0);
        if (commandType != std::string::npos) {
            return "search";
        }
        return "unsuccessful";
    } //Needs finishing





    int main() {
        std::vector<std::string> names;
        TreeNode root;
        std::string studentID = "";
        std::string studentName = " ";

        int numLines;
        std::string userInput = "";

        std::cin >> numLines; //Reads how many commands the user is going to input.
        std::cin.ignore();

        for (int i = 0; i < numLines; i++) {
            std::getline(std::cin, userInput);
                if (findCommand(userInput) == "insert") {
                    userInput.erase(0, 7);
                    if (getIdVal(userInput) == "unsuccessful" || getNameVal(userInput) == "unsuccessful") {
                        std::cout << "unsuccessful" << std::endl;
                        continue;
                    }

                    studentID = getIdVal(userInput);
                    studentName = getNameVal(userInput);

                    Node node(studentID, studentName);

                    root.Insert(root.Head(), node);

                }
                if (findCommand(userInput) == "remove") {
                    userInput.erase(0, 6);
                }
                if (findCommand(userInput) == "printInorder") {
                    root.PrintInOrder(root.Head(), names);
                    root.printVector(names);
                } if (findCommand(userInput) == "search") {
                    userInput.erase(0, 7);
                    Node* result = root.IDSearch(root.Head(), userInput);
                    if (result == nullptr) {
                        std::cout << "unsuccessful";
                    }
                }
            }

        return 0;
    };