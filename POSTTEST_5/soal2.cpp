#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

int findMinValue(Node* root) {
    // Kalau tree kosong
    if (root == nullptr)
        return -1;

    // Selama masih punya anak kiri, lanjut ke kiri
    while (root->left != nullptr) {
        root = root->left;
    }

    // Node paling kiri adalah nilai terkecil
    return root->data;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);

    cout << "Nilai terkecil dalam tree adalah: " << findMinValue(root) << endl; 
    // Output: 20
    return 0;
}
