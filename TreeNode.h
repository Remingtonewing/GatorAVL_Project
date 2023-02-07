#include <iostream>
#include <string>


class TreeNode {

public:
    std::string getName(std::string userInput);
    int getId(std::string userInput);
    TreeNode* Insert(TreeNode* root,std::string val);
    int val;
    std::string name;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};