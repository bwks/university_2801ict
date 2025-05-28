#include <iostream>
#include <vector>
using namespace std;

void selection_sort(vector<int>& list) {
  for (int i = 0; i < list.size() - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < list.size(); j++) {
      if (list[j] < list[min_index]) min_index = j;
    }
    swap(list[i], list[min_index]);
  }
}

int main() {
  vector<int> test = { 64, 25, 12, 22, 11 };
  selection_sort(test);
  cout << "Selection_sort Result: ";
  for (int num : test) cout << num << " ";
  return 0;
}
