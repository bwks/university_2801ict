#include <iostream>
#include <string>
#include <vector>

struct Order {
  int id;
  std::string details;
};

class ArrayQueue {
private:
  std::vector<Order> orders;
  size_t front_idx = 0; // Index of the front element in the queue

public:
  // Add order to queue
  void enqueue(const Order& order) {
    orders.push_back(order);
  }

  // Remove the order from the queue
  Order dequeue() {
    if (!empty()) {
      Order front_order = orders[front_idx];
      front_idx++;
      // Prevent vector from growing indefinitely
      if (front_idx > orders.size() / 2) {
        orders.erase(orders.begin(), orders.begin() + front_idx);
        front_idx = 0;
      }
      return front_order;
    }
    exit(0);
  }

  // View the next order without removing it
  Order peek() const {
    if (!empty()) {
      return orders[front_idx];
    }
    exit(0);
  }

  // Cancel order and remove it from the queue
  bool cancel(int order_id) {
    for (size_t i = front_idx; i < orders.size(); ++i) {
      if (orders[i].id == order_id) {
        orders.erase(orders.begin() + i);
        return true;
      }
    }
    return false;
  }

  // Check if the queue is empty
  bool empty() const {
    bool nada = front_idx >= orders.size();
    if (nada) {
      std::cout << "Queue is empty" << std::endl;
    }
    return nada;
  }
};

int main() {
  ArrayQueue queue;

  // Add to queue
  queue.enqueue({ 1, "Pizza" });
  queue.enqueue({ 2, "Burger" });
  queue.enqueue({ 3, "Sushi" });

  // Temporary copy of the queue to iterate through all orders
  ArrayQueue tempQueue1 = queue;
  std::cout << "Current orders in queue:" << std::endl;
  int position = 1;
  while (!tempQueue1.empty()) {
    Order currentOrder = tempQueue1.peek();
    std::cout << position << ". Order #" << currentOrder.id << ": " << currentOrder.details << std::endl;
    tempQueue1.dequeue();
    position++;
  }
  std::cout << std::endl;

  // Remove from queue
  queue.cancel(2); // Remove Burger

  // Temporary copy of the queue to iterate through all orders
  ArrayQueue tempQueue = queue;
  std::cout << "Current orders in queue:" << std::endl;
  int position1 = 1;
  while (!tempQueue.empty()) {
    Order currentOrder = tempQueue.peek();
    std::cout << position1 << ". Order #" << currentOrder.id << ": " << currentOrder.details << std::endl;
    tempQueue.dequeue();
    position1++;
  }
  std::cout << std::endl;

  while (!queue.empty()) {
    std::cout << "Next order: " << queue.peek().details << std::endl;
    auto order = queue.dequeue();
    std::cout << "Processing: " << order.details << std::endl;
  }
  // Output: Processing: Pizza, then Sushi
}
