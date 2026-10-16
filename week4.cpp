#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
    public :
    int data;
    Node* left;
    Node* right;

    Node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
    }
};

class Tree {
public:
    Node* root;

    Tree() { root = nullptr; }
    ~Tree();

    Node* insert(Node* n, int v);
    bool search(Node* n, int v);
    Node* findMin(Node* n);
    Node* deleteNode(Node* n, int v);
    void inOrder(Node* n);
    void preOrder(Node* n);
    int height(Node* n);
    void levelOrder();

private:
    void clear(Node* n);
};

// Free all nodes
void Tree::clear(Node* n) {
    if (n == nullptr) return;

    clear(n->left);
    clear(n->right);
    delete n;
}

Tree::~Tree() {
    clear(root);
}


Node* Tree::insert(Node* n, int v) {
    if (n == nullptr)
        return new Node(v);

    if (v < n->data)
        n->left = insert(n->left, v);
    else if (v > n->data)
        n->right = insert(n->right, v);

    return n;
}


bool Tree::search(Node* n, int v) {
    if (n == nullptr)
        return false;

    if (n->data == v)
        return true;

    if (v < n->data)
        return search(n->left, v);

    return search(n->right, v);
}


Node* Tree::findMin(Node* n) {
    if (n == nullptr)
        return nullptr;

    while (n->left != nullptr)
        n = n->left;

    return n;
}


Node* Tree::deleteNode(Node* n, int v) {
    if (n == nullptr)
        return nullptr;

    if (v < n->data) {
        n->left = deleteNode(n->left, v);
    }
    else if (v > n->data) {
        n->right = deleteNode(n->right, v);
    }
    else {
        // No left child
        if (n->left == nullptr) {
            Node* temp = n->right;
            delete n;
            return temp;
        }

        // No right child
        if (n->right == nullptr) {
            Node* temp = n->left;
            delete n;
            return temp;
        }

        // Two children
        Node* temp = findMin(n->right);
        n->data = temp->data;
        n->right = deleteNode(n->right, temp->data);
    }

    return n;
}


void Tree::inOrder(Node* n) {
    if (n == nullptr)
        return;

    inOrder(n->left);
    cout << n->data << " ";
    inOrder(n->right);
}


void Tree::preOrder(Node* n) {
    if (n == nullptr)
        return;

    cout << n->data << " ";
    preOrder(n->left);
    preOrder(n->right);
}


int Tree::height(Node* n) {
    if (n == nullptr)
        return -1;

    return 1 + max(height(n->left), height(n->right));
}


void Tree::levelOrder() {
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }

    cout << endl;
}


int main() {
    Tree t;
    for(int v:{50,30,70,20,40,60,80,10,35})
        t.root=t.insert(t.root,v);

    cout<<"InOrder: ";
    t.inOrder(t.root);
    cout<<endl;

    cout<<"PreOrder: ";
    t.preOrder(t.root);
    cout<<endl;

    cout<<"Height: "<<t.height(t.root)<<endl;

    cout<<"Search 35: "<<t.search(t.root,35)<<endl;
    cout<<"Search 99: "<<t.search(t.root,99)<<endl;

    // Delete leaf
    t.root=t.deleteNode(t.root,10);
    cout<<"After del 10: ";
    t.inOrder(t.root);
    cout<<endl;

    // Delete 1-child node
    t.root=t.deleteNode(t.root,20);
    cout<<"After del 20: ";
    t.inOrder(t.root);
    cout<<endl;

    // Delete 2-child node
    t.root=t.deleteNode(t.root,30);
    cout<<"After del 30: ";
    t.inOrder(t.root);
    cout<<endl;

    cout<<"LevelOrder: ";
    t.levelOrder();

    return 0;
}
