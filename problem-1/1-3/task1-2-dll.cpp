#include <iostream>
#include <stdexcept>
#include <string>

struct Order {
  int id;
  std::string details;
};

class Queue {
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
  Queue() : front(nullptr), rear(nullptr), size(0) {}

  ~Queue() {
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
    if (empty()) {
      throw std::runtime_error("Queue is empty");
    }

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

  Order peek() const {
    if (empty()) {
      throw std::runtime_error("Queue is empty");
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
    return front == nullptr;
  }
};

// Example usage with direct references
int main() {
  Queue queue;

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
