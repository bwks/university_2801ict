#include <iostream>
#include <string>

struct Order {
  int id;
  std::string details;
};

class SllQueue {
private:
  struct Node {
    Order order;
    Node* next;
    Node(const Order& o) : order(o), next(nullptr) {}
  };

  Node* front;
  Node* rear;
  int size;

public:
  SllQueue() : front(nullptr), rear(nullptr), size(0) {}

  ~SllQueue() {
    while (!empty()) {
      dequeue();
    }
  }

  void enqueue(const Order& order) {
    Node* new_node = new Node(order);
    if (empty()) {
      front = rear = new_node;
    }
    else {
      rear->next = new_node;
      rear = new_node;
    }
    size++;
  }

  Order dequeue() {
    if (!empty()) {
      Node* temp = front;
      Order item = front->order;
      front = front->next;

      if (front == nullptr) {
        rear = nullptr;
      }

      delete temp;
      size--;
      return item;
    }
    // Return default Order when queue is empty
    return { -1, "" };
  }

  Order peek() const {
    if (!empty()) {
      return front->order;
    }
    exit(0);
  }

  bool cancel(int order_id) {
    if (empty()) return false;

    // Check front node first
    if (front->order.id == order_id) {
      dequeue();
      return true;
    }

    Node* current = front;
    while (current->next && current->next->order.id != order_id) {
      current = current->next;
    }

    if (current->next) {
      Node* toDelete = current->next;
      current->next = toDelete->next;

      if (toDelete == rear) {
        rear = current;
      }

      delete toDelete;
      size--;
      return true;
    }

    return false;
  }

  bool empty() const {
    bool nada = front == nullptr;
    if (nada) {
      std::cout << "Queue is empty" << std::endl;
    }
    return nada;
  }
};

// Example usage
int main() {
  SllQueue queue;

  queue.enqueue({ 1, "Cheeseburger" });
  queue.enqueue({ 2, "Fries" });
  queue.enqueue({ 3, "Milkshake" });

  queue.cancel(2); // Cancel Fries

  while (!queue.empty()) {
    std::cout << "Next order: " << queue.peek().details << "\n"; // Cheeseburger
    auto order = queue.dequeue();
    std::cout << "Processing: " << order.details << "\n";
  }
  // Output: Processing: Cheeseburger, then Milkshake

  return 0;
}
