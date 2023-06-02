#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], const int low, const int high) {
  const int pivot = high;
  int i = low - 1;

  // put elements < pivot to left
  for (int j = low; j < high; j++) {
    if (arr[j] < arr[pivot]) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  // put pivot in the middle, return index
  swap(arr[i + 1], arr[pivot]);
  return pivot;
}

void quicksort(int arr[], const int low, const int high) {
  if (low >= high) return;
  const int pivot = partition(arr, low, high);
  quicksort(arr, low, pivot - 1);
  quicksort(arr, pivot + 1, high);
}

int main() {
  // open input file
  ifstream in("input.txt");
  if (!in) {
    puts("Unable to open input file");
    return -1;
  }
  // parse input
  int n;
  in >> n;
  int arr[n];
  for (int i = 0; i < n; i++) {
    in >> arr[i];
  }
  in.close();

  // sort
  quicksort(arr, 0, n - 1);

  // save output to file
  ofstream out("output.txt");
  if (!out) {
    puts("Unable to create output file");
    return -1;
  }
  out << n << "\n";
  for (int i = 0; i < n; i++) {
    out << arr[i] << "\n";
  }
  out.close();

  return 0;
}