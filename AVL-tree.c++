#include <iostream>
#include <stack>
using namespace std;
template <typename T>
class AVLTreeRecursive {
public:
    struct Node {
        int bf;
        T value;
        int height;
        Node* left;
        Node* right;

        Node(T val){ 
        bf=0;
        value=val;
        height=0;
        left=NULL;
        right=NULL;
        }
    };

    Node* root;
    int nodeCount;

    AVLTreeRecursive(){ 
    root=NULL;
    nodeCount=0;
    }

    int height() {
        if (root == NULL) return 0;
        return root->height;
    }

    int size() {
        return nodeCount;
    }

    bool isEmpty() {
        return size() == 0;
    }

    bool contains(T value) {
        return contains(root, value);
    }

    bool insert(T value) {
        if (!contains(root, value)) {
            root = insert(root, value);
            nodeCount++;
            return true;
        }
        return false;
    }

    bool remove(T elem) {
        if (contains(root, elem)) {
            root = remove(root, elem);
            nodeCount--;
            return true;
        }
        return false;
    }
    void update() {
    performUpdate(root);
    }
    
     void performRightRotation() {
        root = rightRotation(root);
    }

    void performLeftRotation() {
        root = leftRotation(root);
    }

    string toString() {
        return getTreeDisplay(root);
    }

private:
    bool contains(Node* node, T value) {
        if (node == NULL) return false;

        int cmp = value.compare(node->value);

        if (cmp < 0) return contains(node->left, value);
        if (cmp > 0) return contains(node->right, value);

        return true;
    }

    Node* insert(Node* node, T value) {
        if (node == NULL) return new Node(value);

        int cmp = value.compare(node->value);

        if (cmp < 0) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }

        performUpdate(node);

        return balance(node);
    }

    Node* remove(Node* node, T value) {
        if (node == nullptr) return nullptr;

        int cmp = value.compare(node->value);

        if (cmp < 0) {
            node->left = remove(node->left, value);
        } else if (cmp > 0) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left != nullptr) ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }

        if (node == NULL) {
            return NULL;
        }

        performUpdate(node);

        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    void performUpdate(Node* node) {
        if (node == NULL) return;

        performUpdate(node->left);
        performUpdate(node->right);

        int leftNodeHeight = (node->left == NULL) ? -1 : node->left->height;
        int rightNodeHeight = (node->right == NULL) ? -1 : node->right->height;

        node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);
        node->bf = rightNodeHeight - leftNodeHeight;
    }

    Node* balance(Node* node) {
        if (node->bf == -2) {
            if (node->left->bf <= 0) {
                return leftLeftCase(node);
            } else {
                return leftRightCase(node);
            }
        } else if (node->bf == +2) {
            if (node->right->bf >= 0) {
                return rightRightCase(node);
            } else {
                return rightLeftCase(node);
            }
        }
        return node;
    }

    Node* leftLeftCase(Node* node) {
        return rightRotation(node);
    }

    Node* leftRightCase(Node* node) {
        node->left = leftRotation(node->left);
        return leftLeftCase(node);
    }

    Node* rightRightCase(Node* node) {
        return leftRotation(node);
    }

    Node* rightLeftCase(Node* node) {
        node->right = rightRotation(node->right);
        return rightRightCase(node);
    }

    Node* leftRotation(Node* node) {
        Node* newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;
        performUpdate(node);
        performUpdate(newParent);
        return newParent;
    }

    Node* rightRotation(Node* node) {
        Node* newParent = node->left;
        node->left = newParent->right;
        newParent->right = node;
        performUpdate(node);
        performUpdate(newParent);
        return newParent;
    }

    string getTreeDisplay(Node* root) {
        if (root == NULL) {
            return "";
        }

        string display;

        stack<Node*> stack;
        Node* current = root;

        while (current != NULL || !stack.empty()) {
            while (current != NULL) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();

            display += current->value + " ";

            current = current->right;
        }

        return display;
    }
};

int main() {
    system("cls");
    AVLTreeRecursive<string> avlTree;
    while (true) {
        cout << "\nAVL Tree Menu\n";
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. Display Tree\n";
        cout << "4. Display Height\n";
        cout << "5. Perform Rotations\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                system("cls");
                string value;
                cout << "Enter value to insert: ";
                cin >> value;
                if (avlTree.insert(value)) {
                    cout << "Value inserted successfully.\n";
                } else {
                    cout << "Value already exists in the tree.\n";
                }
                break;
            }
            case 2: {
                system("cls");
                string value;
                cout << "Enter value to remove: ";
                cin >> value;
                if (avlTree.remove(value)) {
                    cout << "Value removed successfully.\n";
                } else {
                    cout << "Value not found in the tree.\n";
                }
                break;
            }
            case 3:
            system("cls");
                cout << "Tree Display: " << avlTree.toString() <<endl;
                break;
            case 4:
            system("cls");
                cout << "Tree Height: " << avlTree.height() <<endl;
                break;
            case 5: {
                system("cls");
                avlTree.update();
                cout << "Rotations performed and tree updated.\n";
                avlTree.performRightRotation();
                cout << "Right Rotation performed.\n";
                avlTree.performLeftRotation();
                cout << "Left Rotation performed.\n";
            break;
            }
            case 6:
            system("cls");
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
