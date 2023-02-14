#include <iostream>
#include <string>
#include "TreeNode.h"
#include <iterator>
#include <vector>




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

    int levelCount;
    int treeSize;
    Node node;
    Node *head;


    TreeNode *Remove(Node *root, std::string ID);

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

    TreeNode *Rotate(Node *root) {

    }

    TreeNode *findSuccessor(Node *root);

    TreeNode *IDSearch(Node *root, std::string ID);

    TreeNode *nameSearch(Node *root, std::string name);

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
        else if (root->ID.compare(root->getId()) > 0) {
            root->left = Insert(root->left, node);
            root = rotate()
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
        }
        return "unsuccessful";
    } //Needs finishing

    void printVector(std::vector<std::string> printName) {
        for (int i = 0; i < printName.size(); i++) {
            if (i != printName.size() - 1)
            std::cout << printName[i] << ",";
            else
                std::cout << printName[i];
            std::cout << std::endl;
        }
    }


    int main() {
        TreeNode root;
        std::string studentID = "";
        std::string studentName = " ";
        int numLines;
        std::string userInput = "";
        std::cin >> numLines; //Reads how many commands the user is going to input.
        std::cin.ignore();
        for (int i = 0; i < numLines; i++) {
            std::getline(std::cin, userInput);
            if (getIdVal(userInput) == "unsuccessful" || getNameVal(userInput) == "unsuccessful") {
                std::cout << "unsuccessful" << std::endl;
            } else {
                if (findCommand(userInput) == "insert") {
                    userInput.erase(0, 7);

                    studentID = getIdVal(userInput);
                    studentName = getNameVal(userInput);
                    Node node(studentID, studentName);


                    root.Insert(root.Head(), node);


                }
                if (findCommand(userInput) == "remove") {
                    userInput.erase(0, 6);
                }
                std::cout << studentID << " " << studentName << std::endl;
            }
        }

        return 0;
    };