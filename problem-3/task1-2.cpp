#include <iostream>
#include <cmath>
#include <limits>
#include <chrono>

class BinarySearchTree {
private:
  struct Node {
    double weight;
    Node* left;
    Node* right;
    Node(double w) : weight(w), left(nullptr), right(nullptr) {}
  };

  Node* root = nullptr;

  Node* insert_node(Node* node, double weight) {
    if (!node) return new Node(weight);
    if (weight < node->weight) {
      node->left = insert_node(node->left, weight);
    }
    else if (weight > node->weight) {
      node->right = insert_node(node->right, weight);
    }
    return node;
  }

  void find_closest_weight(Node* node, double target, double& closest) const {
    if (!node) return;
    // If exact match found, update closest and return immediately
    if (node->weight == target) {
      closest = target;
      return;
    }
    // If no exact match find the closes match
    if (std::abs(node->weight - target) < std::abs(closest - target)) {
      closest = node->weight;
    }
    // Left side is closer
    if (target < node->weight) {
      find_closest_weight(node->left, target, closest);
    }
    // Right side is closer
    else if (target > node->weight) {
      find_closest_weight(node->right, target, closest);
    }
  }

public:
  void insert(double weight) {
    root = insert_node(root, weight);
  }

  double find_closest(double target) const {
    if (!root) return -1;
    double closest = root->weight;
    find_closest_weight(root, target, closest);
    return closest;
  }
};

class AvlTree {
private:
  struct Node {
    double weight;
    Node* left;
    Node* right;
    int height;
    Node(double w) : weight(w), left(nullptr), right(nullptr), height(1) {}
  };

  Node* root = nullptr;

  // Helper functions
  int height(Node* node) { return node ? node->height : 0; }

  Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
  }

  Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
  }

  Node* insert_node(Node* node, double weight) {
    if (!node) return new Node(weight);

    if (weight < node->weight)
      node->left = insert_node(node->left, weight);
    else if (weight > node->weight)
      node->right = insert_node(node->right, weight);
    else
      return node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = height(node->left) - height(node->right);

    // Left Left
    if (balance > 1 && weight < node->left->weight)
      return rotate_right(node);
    // Right Right
    if (balance < -1 && weight > node->right->weight)
      return rotate_left(node);
    // Left Right
    if (balance > 1 && weight > node->left->weight) {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }
    // Right Left
    if (balance < -1 && weight < node->right->weight) {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    }
    return node;
  }

  void find_closest_weight(Node* node, double target, double& closest) const {
    if (!node) return;

    if (std::abs(node->weight - target) < std::abs(closest - target))
      closest = node->weight;

    if (target < node->weight)
      find_closest_weight(node->left, target, closest);
    else if (target > node->weight)
      find_closest_weight(node->right, target, closest);
  }

public:
  void insert(double weight) {
    root = insert_node(root, weight);
  }

  double find_closest(double target) const {
    if (!root) return -1;
    double closest = root->weight;
    find_closest_weight(root, target, closest);
    return closest;
  }
};

int main() {
  const int N = 10000;
  BinarySearchTree bst;
  AvlTree avl;

  // BST insertion timing
  auto start_bst = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= N; ++i) {
    bst.insert(i);
  }
  auto end_bst = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> bst_duration = end_bst - start_bst;

  std::cout << "BST insertion time for " << N << " sorted elements: "
    << bst_duration.count() << " seconds\n";

  // AVL insertion timing
  auto start_avl = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= N; ++i) {
    avl.insert(i);
  }
  auto end_avl = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> avl_duration = end_avl - start_avl;

  std::cout << "AVL insertion time for " << N << " sorted elements: "
    << avl_duration.count() << " seconds\n";

  return 0;
}