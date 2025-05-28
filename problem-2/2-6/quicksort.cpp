// #include <iostream>
// #include <algorithm>
// #include <random>
// #include <chrono>
// #include <iomanip>
#include <vector>
#include <functional>

// Use median-of-three for pivot selection
int median_of_three(std::vector<int>& list, int low, int high) {
  int mid = low + (high - low) / 2;
  if (list[mid] < list[low])
    std::swap(list[low], list[mid]);
  if (list[high] < list[low])
    std::swap(list[low], list[high]);
  if (list[high] < list[mid])
    std::swap(list[mid], list[high]);
  // Place the median at the end for partitioning
  std::swap(list[mid], list[high]);
  return list[high];
}

int partition(std::vector<int>& list, int low, int high) {
  int pivot = median_of_three(list, low, high);
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (list[j] <= pivot) {
      ++i;
      std::swap(list[i], list[j]);
    }
  }
  std::swap(list[i + 1], list[high]);
  return i + 1;
}

// Recursive QuickSort with median-of-three
void quick_sort_medium_of_three(std::vector<int>& list, int low, int high) {
  if (low < high) {
    int pi = partition(list, low, high);
    quick_sort_medium_of_three(list, low, pi - 1);
    quick_sort_medium_of_three(list, pi + 1, high);
  }
}

// Public interface
void quick_sort(std::vector<int>& list) {
  if (list.size() <= 1) return;
  quick_sort_medium_of_three(list, 0, list.size() - 1);
}

// // Utility functions for testing
// std::vector<int> generateRandomData(int size, int seed = 42) {
//   std::vector<int> data(size);
//   std::mt19937 gen(seed);
//   std::uniform_int_distribution<> dis(1, size * 10);
//   for (int i = 0; i < size; ++i)
//     data[i] = dis(gen);
//   return data;
// }

// std::vector<int> generateReverseSortedData(int size) {
//   std::vector<int> data(size);
//   for (int i = 0; i < size; ++i)
//     data[i] = size - i;
//   return data;
// }

// std::vector<int> generateDuplicateData(int size) {
//   std::vector<int> data(size);
//   std::mt19937 gen(42);
//   std::uniform_int_distribution<> dis(1, 5);
//   for (int i = 0; i < size; ++i)
//     data[i] = dis(gen);
//   return data;
// }

// std::vector<int> generateExtremeData(int size) {
//   std::vector<int> data(size);
//   std::mt19937 gen(42);
//   for (int i = 0; i < size; ++i)
//     data[i] = (gen() % 100 < 95) ? 1 : 10000;
//   return data;
// }

// bool isSorted(const std::vector<int>& list) {
//   for (size_t i = 1; i < list.size(); ++i)
//     if (list[i] < list[i - 1]) return false;
//   return true;
// }

// void printlistay(const std::vector<int>& list, const std::string& label) {
//   std::cout << label << ": ";
//   for (size_t i = 0; i < std::min(list.size(), size_t(20)); ++i)
//     std::cout << list[i] << " ";
//   if (list.size() > 20) std::cout << "...";
//   std::cout << std::endl;
// }

// double measureTime(std::function<void()> func) {
//   auto start = std::chrono::high_resolution_clock::now();
//   func();
//   auto end = std::chrono::high_resolution_clock::now();
//   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//   return duration.count() / 1000.0; // ms
// }

// int main() {
//   std::cout << "=== QuickSort with Median-of-Three Pivot Selection (Function Only) ===\n\n";
//   std::vector<int> sizes = { 1000, 5000, 10000, 20000 };

//   for (int size : sizes) {
//     std::cout << "Testing with " << size << " elements:\n";
//     std::cout << std::string(50, '-') << std::endl;

//     // Random data
//     {
//       auto data = generateRandomData(size);
//       double time = measureTime([&]() { quick_sort(data); });
//       std::cout << "Random data:        " << std::fixed << std::setprecision(3)
//         << time << " ms - " << (isSorted(data) ? "✓ Sorted" : "✗ Not sorted") << std::endl;
//     }

//     // Reverse sorted data
//     {
//       auto data = generateReverseSortedData(size);
//       double time = measureTime([&]() { quick_sort(data); });
//       std::cout << "Reverse sorted:     " << std::fixed << std::setprecision(3)
//         << time << " ms - " << (isSorted(data) ? "✓ Sorted" : "✗ Not sorted") << std::endl;
//     }

//     // Many duplicates
//     {
//       auto data = generateDuplicateData(size);
//       double time = measureTime([&]() { quick_sort(data); });
//       std::cout << "Many duplicates:    " << std::fixed << std::setprecision(3)
//         << time << " ms - " << (isSorted(data) ? "✓ Sorted" : "✗ Not sorted") << std::endl;
//     }

//     // Extreme distribution
//     {
//       auto data = generateExtremeData(size);
//       double time = measureTime([&]() { quick_sort(data); });
//       std::cout << "Extreme distribution: " << std::fixed << std::setprecision(3)
//         << time << " ms - " << (isSorted(data) ? "✓ Sorted" : "✗ Not sorted") << std::endl;
//     }

//     std::cout << std::endl;
//   }

//   // Demonstration with a small listay
//   std::cout << "=== Small listay Demonstration ===\n";
//   std::vector<int> demo = { 64, 34, 25, 12, 22, 11, 90, 5 };
//   printlistay(demo, "Before sorting");
//   quick_sort(demo);
//   printlistay(demo, "After sorting");
//   std::cout << "\nMedian-of-three pivot selection helps avoid worst-case O(n^2) performance\n"
//     << "by choosing better pivots, especially on sorted or nearly sorted data.\n";
//   return 0;
// }
