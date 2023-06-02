#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], const int low, const int high) {
  // random pivot
  swap(arr[high], arr[low + rand() % (high - low + 1)]);
  int& pivot = arr[high];

  // put all elements < pivot to left
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  // put pivot in the middle, return index
  swap(arr[i + 1], pivot);
  return i + 1;
}

void quicksort(int arr[], const int low, const int high) {
  if (low >= high) return;

  // pivot index
  const int pi = partition(arr, low, high);
  quicksort(arr, low, pi - 1);
  quicksort(arr, pi + 1, high);
}

int main() {
  vector<int> arr;

  for (int x; cin >> x;) arr.push_back(x);

  quicksort(arr.data(), 0, arr.size() - 1);

  for (auto& x : arr) cout << x << "\n";

  return 0;
}