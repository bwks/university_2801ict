#include <iostream>
#include <vector>
using namespace std;

void heaper(vector<int>& list, int n, int i) {
  int largest = i, left = 2 * i + 1, right = 2 * i + 2;
  if (left < n && list[left] > list[largest]) largest = left;
  if (right < n && list[right] > list[largest]) largest = right;
  if (largest != i) {
    swap(list[i], list[largest]);
    heaper(list, n, largest);
  }
}

void heap_sort(vector<int>& list) {
  for (int i = list.size() / 2 - 1; i >= 0; i--) heaper(list, list.size(), i);
  for (int i = list.size() - 1; i > 0; i--) {
    swap(list[0], list[i]);
    heaper(list, i, 0);
  }
}

int main() {
  vector<int> test = { 12, 11, 13, 5, 6, 7 };
  heap_sort(test);
  cout << "Heap_sort Result: ";
  for (int num : test) cout << num << " ";
  return 0;
}
