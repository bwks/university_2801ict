#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& list, int left, int mid, int right) {
  vector<int> L(list.begin() + left, list.begin() + mid + 1);
  vector<int> R(list.begin() + mid + 1, list.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < L.size() && j < R.size()) {
    list[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  }
  while (i < L.size()) list[k++] = L[i++];
  while (j < R.size()) list[k++] = R[j++];
}

void merge_sort(vector<int>& list, int left, int right) {
  if (left >= right) return;
  int mid = left + (right - left) / 2;
  merge_sort(list, left, mid);
  merge_sort(list, mid + 1, right);
  merge(list, left, mid, right);
}

int main() {
  vector<int> test = { 12, 11, 13, 5, 6, 7 };
  merge_sort(test, 0, test.size() - 1);
  cout << "Merge_sort Result: ";
  for (int num : test) cout << num << " ";
  return 0;
}
