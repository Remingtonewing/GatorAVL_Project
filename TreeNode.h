#include <iostream>
#include <string>


class TreeNode {

public:
    struct Student {
        std::string name;
        std::string ID;
        Student(int ID, std::string name);
        Student();
        int getId(TreeNode* root, std::string userInput);
        TreeNode* Insert(TreeNode* root,std::string val);
        std::string getName(std::string userInput);
    };
    int levelCount = 0;
    Student s;
    TreeNode *left;
    TreeNode *right;
    TreeNode(Student s) :  left(NULL), right(NULL) {}



};
