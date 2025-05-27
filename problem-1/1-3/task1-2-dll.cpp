#include <iostream>
#include <string>

struct Order {
  int id;
  std::string details;
};

class DllQueue {
private:
  struct Node {
    Order order;
    Node* prev;
    Node* next;
    Node(const Order& o) : order(o), prev(nullptr), next(nullptr) {}
  };

  Node* front;
  Node* rear;
  int size;

public:
  DllQueue() : front(nullptr), rear(nullptr), size(0) {}

  ~DllQueue() {
    Node* current = front;
    while (current) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }

  Node* enqueue(const Order& order) {
    Node* node = new Node(order);
    if (empty()) {
      front = rear = node;
    }
    else {
      rear->next = node;
      node->prev = rear;
      rear = node;
    }
    size++;
    return node;
  }

  Order dequeue() {
    if (!empty()) {
      Node* temp = front;
      Order item = front->order;

      if (front == rear) {
        front = rear = nullptr;
      }
      else {
        front = front->next;
        front->prev = nullptr;
      }

      delete temp;
      size--;
      return item;
    }
    throw std::runtime_error("Cannot dequeue from an empty queue");
  }

  Order peek() const {
    if (!empty()) {
      throw std::runtime_error("Cannot peek from an empty queue");
    }
    return front->order;
  }

  // O(1) cancellation with direct node reference
  void cancel(Node* target) {
    if (!target) return;

    if (target == front) {
      dequeue();
      return;
    }

    if (target == rear) {
      rear = rear->prev;
      rear->next = nullptr;
    }
    else {
      target->prev->next = target->next;
      target->next->prev = target->prev;
    }

    delete target;
    size--;
  }

  bool empty() const {
    bool nada = front == nullptr;
    if (nada) {
      std::cout << "Queue is empty" << std::endl;
    }
    return nada;
  }
};

// Example usage with direct references
int main() {
  DllQueue queue;

  // Enqueue orders and store their node references
  queue.enqueue({ 1, "Pizza" });
  auto burgerNode = queue.enqueue({ 2, "Burger" });
  queue.enqueue({ 3, "Sushi" });

  // Direct cancellation using stored node reference
  queue.cancel(burgerNode);

  // Process remaining orders
  while (!queue.empty()) {
    auto order = queue.dequeue();
    std::cout << "Processing: " << order.details << "\n";
  }
  // Output: Processing: Pizza, then Sushi
}
