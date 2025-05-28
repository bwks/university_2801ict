#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int partition(vector<int>& list, int low, int high) {
  int pivot = list[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (list[j] <= pivot) {
      i++;
      swap(list[i], list[j]);
    }
  }
  swap(list[i + 1], list[high]);
  return i + 1;
}

void quick_sort(vector<int>& list, int low, int high) {
  if (low < high) {
    int pi = partition(list, low, high);
    quick_sort(list, low, pi - 1);
    quick_sort(list, pi + 1, high);
  }
}

int main() {
  vector<int> test = { 10, 7, 8, 9, 1, 5 };
  quick_sort(test, 0, test.size() - 1);
  cout << "Quick_sort Result: ";
  for (int num : test) cout << num << " ";
  return 0;
}
