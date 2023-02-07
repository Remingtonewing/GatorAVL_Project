#include <iostream>
#include <string>
#include "TreeNode.h"



int getIdVal(std::string userInput) {
    int quoteCount = 0;
    while (quoteCount < 2) {
        if (userInput[0] == '"') {
            userInput.erase(0, 1);
            quoteCount++;
        } else {
            userInput.erase(0, 1);
        }
    }
    return stoi(userInput);
}

std::string getNameVal(std::string userInput) {
    int iter = 0;
    int quoteCount = 0;
    while (quoteCount < 2) {
        if (userInput[iter] == '"') {
            quoteCount++;
            userInput.erase(iter, 1);
        }else {
            iter++;
        }
        if (quoteCount == 2) {
            break;
        }
    }
    return userInput.substr(0, iter);
}


TreeNode *Insert(TreeNode *root, TreeNode::Student s) {
    if (root == nullptr)
        return new TreeNode(s);
    if (root->s.ID < s.ID)
        root->right = Insert(root->right, s);
    else
        root->left = Insert(root->left, s);
    return root;
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


int main() {
    TreeNode *root = nullptr;
    int studentID = 0;
    std::string studentName = " ";
    int numLines;
    std::string userInput = "";
    std::cin >> numLines; //Reads how many commands the user is going to input.
    std::cin.ignore();
    for (int i = 0; i < numLines; i++) {
        std::getline(std::cin, userInput);
        if (findCommand(userInput) == "insert") {
            userInput.erase(0,7);
            //Insert userInput;
        }if (findCommand(userInput) == "remove") {
            userInput.erase(0,6);
            //Remove userInput
        }

        studentID = getIdVal(userInput);
        studentName = getNameVal(userInput);
        TreeNode::Student s = {studentID,studentName};
        root = Insert(root,s);
        std::cout << s.getId() << std::endl;
        std::cout << s.getName() << std::endl;
        std::cout << root->s.getId();

    }


}
