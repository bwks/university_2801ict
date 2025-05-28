#include <iostream>
#include <vector>
using namespace std;

void insertion_sort(vector<int>& list) {
  for (int i = 1; i < list.size(); i++) {
    int key = list[i], j = i - 1;
    while (j >= 0 && list[j] > key) {
      list[j + 1] = list[j];
      j--;
    }
    list[j + 1] = key;
  }
}

int main() {
  vector<int> test = { 12, 11, 13, 5, 6 };
  insertion_sort(test);
  cout << "Insertion_sort Result: ";
  for (int num : test) cout << num << " ";
  return 0;
}
