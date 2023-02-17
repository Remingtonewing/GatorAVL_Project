#include <iostream>
#include <string>
#include <iterator>
#include <vector>



class TreeNode {


public:
    struct Node {
        std::string name;
        std::string ID;
        Node *right;
        Node *left;

        Node(std::string ID, std::string name) {
            this->ID = ID;
            this->name = name;
            left = nullptr;
            right = nullptr;
        }

        Node() {
            name = "";
            ID = "";
            left = nullptr;
            right = nullptr;
        }

        std::string getId() {
            return ID;
        }

        std::string getName() {
            return name;
        }

    };


    Node *head = nullptr;

    int height(Node *root) //Stepik solution 5.1a
    {
        if (!root)
            return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }

    int balanceTreeFactor(Node *node) { //Mod 4 Pg. 33
        return height(node->left) - height(node->right);
    }

    int size(Node *node) {
        if (node == NULL)
            return 0;
        else
            return (size(node->left) + 1 + size(node->right));
    }


    Node *Remove(Node *root, std::string ID) {
        if (!root) {
            std::cout << "unsuccessful" << std::endl;
            return root;
        } else if (std::stoi(root->getId()) < std::stoi(ID)) {
            root->right = Remove(root->right, ID);
            return root;
        }
        else if (std::stoi(root->getId()) > std::stoi(ID)) {
            root->left = Remove(root->left, ID);
            return root;
        }
        else if (root->getId() == ID) {
            if (!root->left && !root->right) {
                if (root->getId() == head->getId()) {
                    head = nullptr;
                }
                delete root;
                std::cout << "successful" << std::endl;
                return nullptr;
            }
            if (root->right != nullptr && root->left == nullptr) {
                root->name = root->right->name;
                root->ID = root->right->ID;
                root->left = root->right->left;
                root->right = root->right->right;
                delete root->right;
                std::cout << "successful" << std::endl;
                return root;
            }

            if (root->left != nullptr && root->right == nullptr) {
                root->ID = root->left->getId();
                root->name = root->left->getName();
                root->right = root->left->right;
                root->left = root->left->left;
                delete root->left;
                std::cout << "successful" << std::endl;
                return root;
            }
            if (root->right && root->left) {
                Node *finder = root->right;
                while (finder->left) {
                    finder = finder->left;
                }
                root->ID = finder->ID;
                root->name = finder->name;
                root->right = Remove(root->right, finder->ID);
                return root;
            }
        }
    }

    Node *rotateRight(Node *node) { //Taken directly from slides :D
        Node *grandChild = node->left->right;
        Node *newParent = node->left;
        newParent->right = node;
        node->left = grandChild;
        return newParent;
    }

    Node *rotateLeft(Node *node) { //Also taken directly from Mod 4. Slides :D
        Node *grandChild = node->right->left;
        Node *newParent = node->right;
        newParent->left = node;
        node->right = grandChild;
        return newParent;
    }

    Node *Rotate(Node *root) {
        if (balanceTreeFactor(root) > 1) {
            if (balanceTreeFactor(root->left) > 0)
                root = rotateRight(root);
            else {
                root->left = rotateLeft(root->left);
                root = rotateRight(root);
            }
        } else if (balanceTreeFactor(root) < -1) {
            if (balanceTreeFactor(root->right) > 0) {
                root->right = rotateRight((root->right));
                root = rotateLeft(root);
            } else
                root = rotateLeft(root);
        }
        return root;
    }

    Node *IDSearch(Node *root, std::string ID) {
        if (!root) {
            return nullptr;
        }
        if (root->getId() != ID) {
            IDSearch(root->left, ID);
            IDSearch(root->right, ID);
        } else {
            std::cout << root->name << std::endl;
            return root;
        }
        return root;
    }

    Node *nameSearch(Node *root, std::string name) {
        if (!root) {
            return nullptr;
        }
        if (root->getName() == name) {
            std::cout << root->ID << std::endl;
            return root;
        } else {
            nameSearch(root->left, name);
            nameSearch(root->right, name);
        }
        return root;
    }


    TreeNode() {
        head = nullptr;
    }


    Node *Head() {
        return head;
    }

    Node *setHead(Node *node) {
        this->head = node;
    }

    Node *Insert(Node *root, Node node) {
        if (root == nullptr) {
            if (head == nullptr) {
                root = new Node(node.getId(), node.getName());
                setHead(root);
                std::cout << "successful" << std::endl;
                return root;
            } else {
                std::cout << "successful" << std::endl;
                return new Node(node.getId(), node.getName());
            }
        }
        int tempID = std::stoi(node.ID);
        int pastID = std::stoi(root->ID);
        if (pastID == tempID) {
            std::cout << "unsuccessful" << std::endl;
            return root;
        } else if (pastID < tempID) {
            root->right = Insert(root->right, node);
            root = Rotate(root);

        } else if (pastID > tempID) {
            root->left = Insert(root->left, node);
            root = Rotate(root);
        }
        if (height(root) > height(head)) {
            setHead(root);
        }
        return root;
    }

    void printPost(Node *node, std::vector<std::string> &printName) { //All three print algorithms present in slides
        if (node) {
            printPost(node->left, printName);
            printPost(node->right, printName);
            printName.push_back(node->name);
        } else {
            std::cout << "";
        }
    }

    void PrintPre(Node *node, std::vector<std::string> &printName) {
        if (node) {
            printName.push_back(node->name);
            PrintPre(node->left, printName);
            PrintPre(node->right, printName);
        } else {
            std::cout << "";
        }
    }

    void PrintInOrder(Node *node, std::vector<std::string> &printName) {
        if (node) {
            PrintInOrder(node->left, printName);
            printName.push_back(node->name);
            PrintInOrder(node->right, printName);
        } else {
            std::cout << "";
        }
    }

    void printLevelCount(Node *node) {
        std::cout << height(node) << std::endl;
    }

    void printVector(std::vector<std::string> printName) {
        for (int i = 0; i < printName.size(); i++) {
            if (i != printName.size() - 1)
                std::cout << printName[i] << ", ";
            else
                std::cout << printName[i] << std::endl;
        }
    }

    std::vector<std::string> deleteInOrder(Node *root, std::vector<std::string> &nodes) {

        if (nodes.size() != size(root)) {
            if (root) {
                deleteInOrder(root->left, nodes);
                nodes.push_back(root->ID);
                deleteInOrder(root->right, nodes);
            }
        }
        return nodes;
    }
    void searchHelper(Node *root, std::vector<std::string>& idStore) {
        if (root) {
            PrintInOrder(root->left, idStore);
            idStore.push_back(root->ID);
            PrintInOrder(root->right, idStore);
        } else {
            std::cout << "";
        }
    }
    bool checkTree(std::vector<std::string> vec, std::string val) {
        for (int i = 0; i < vec.size(); i++) {
            if (val == vec[i]) {
                return true;
            } else {
                std::cout<< "";
            }
        }
        return false;
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
        }if (input.substr(0, 12) != "removeInorder") {
            commandType = input.find("remove", 0);
            if (commandType != std::string::npos) {
                return "remove";
            }
        }
        commandType = input.find("removeInorder", 0);
        if (commandType != std::string::npos) {
            return "removeInorder";
        }
        commandType = input.find("printPreorder", 0);
        if (commandType != std::string::npos) {
            return "printPreorder";
        }
        commandType = input.find("printInorder", 0);
        if (commandType != std::string::npos) {
            return "printInorder";
        }
        commandType = input.find("printPostorder", 0);
        if (commandType != std::string::npos) {
            return "printPostorder";
        }
        commandType = input.find("printLevelCount", 0);
        if (commandType != std::string::npos) {
            return "printLevelCount";
        }
        commandType = input.find("search", 0);
        if (commandType != std::string::npos) {
            return "search";
        }
        return "unsuccessful";
    }





    int main() {
        std::vector<std::string> names;
        TreeNode root;
        std::string studentID = "";
        std::string studentName = " ";

        int numLines;
        std::string userInput = "";

        std::cin >> numLines; //Reads how many commands the user is going to input.
        std::cin.ignore();
        std::cin.clear();

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

                    TreeNode::Node test = TreeNode::Node(studentID, studentName);

                    root.Insert(root.Head(), test);

                }
                else if (findCommand(userInput) == "remove" && userInput.substr(0,13) != "removeInorder") {
                    userInput.erase(0, 7);
                    studentID = userInput;
                    root.Remove(root.Head(), studentID);
                }
                else if (findCommand(userInput) == "printInorder") {
                    if (root.Head() == nullptr) {
                        std::cout << " " << std::endl;
                    }
                    root.PrintInOrder(root.Head(), names);
                    root.printVector(names);
                    names.clear();
                } else if (findCommand(userInput) == "search") {
                    bool isInt;
                    std::vector<std::string> value;
                    TreeNode::Node* result;
                    userInput.erase(0, 7);
                    for (char c : userInput) {
                        if (isdigit(c)) {
                            isInt = true;
                        } else {
                            isInt = false;
                            break;
                        }
                    }
                    if (!isInt) {
                        userInput = getNameVal(userInput);
                        root.printPost(root.Head(), value);
                        if (!root.checkTree(value, userInput)) {
                            std::cout << "unsuccessful" << std::endl;
                        } else {
                            result = root.nameSearch(root.Head(), userInput);
                        }
                        value.clear();
                    }
                    else if (isInt){
                        root.searchHelper(root.Head(),value);
                        if (!root.checkTree(value, userInput)) {
                            std::cout << "unsuccessful" << std::endl;
                        }
                        else {
                            result = root.IDSearch(root.Head(), userInput);
                        }
                        value.clear();
                    }

                } else if (userInput.substr(0,13) == "removeInorder") {
                    userInput.erase(0,14);
                    std::vector<std::string> nodes;
                    int iter = 0;
                    nodes = root.deleteInOrder(root.Head(),nodes);
                    for (int i = 0; i < root.size(root.Head()); i++) {
                        iter++;
                        if (i == std::stoi(userInput)) {
                            std::string tempID = nodes[i];
                            root.Remove(root.Head(),tempID);
                            break;
                        }
                        if (iter == nodes.size())  {
                            std::cout << "unsuccessful" << std::endl;
                        }
                    }
                } else if (findCommand(userInput) == "printPostorder") {
                    if (root.Head() == nullptr) {
                        std::cout << " " << std::endl;
                    } else {
                        root.printPost(root.Head(), names);
                        root.printVector(names);
                        names.clear();
                    }
                }
                else if (findCommand(userInput) == "printPreorder") {
                    if (root.Head() == nullptr) {
                        std::cout << " " << std::endl;
                    } else {
                        root.PrintPre(root.Head(), names);
                        root.printVector(names);
                        names.clear();
                    }
                } else if (findCommand(userInput) == "printLevelCount") {
                    root.printLevelCount(root.Head());
                } else {
                    std::cout << "unsuccessful" << std::endl;
                }

            }

        return 0;
    };
