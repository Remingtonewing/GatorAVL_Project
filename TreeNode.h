#include <iostream>
#include <string>


class TreeNode {

public:
    struct Student {
        std::string name;
        int ID;
        Student(int ID, std::string name);
        Student();
        int getId();
        std::string getName();
    };
    TreeNode* Insert(TreeNode* root,Student s);
    int levelCount = 0;
    Student s;
    TreeNode *left;
    TreeNode *right;
    TreeNode(Student s) :  left(nullptr), right(nullptr) {
        this->s.name = s.getName();
        this->s.ID = s.getId();
    }

};
TreeNode::Student::Student(int ID, std::string name) {
    this->ID = ID;
    this->name = name;
}
TreeNode::Student::Student() {}

int TreeNode::Student::getId() {
    return ID;
}
std::string TreeNode::Student::getName() {
    return name;
}