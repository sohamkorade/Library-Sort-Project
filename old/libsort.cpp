#include <bits/stdc++.h>
using namespace std;

void libsort(int arr[], const int low, const int high) {}

int main() {
  vector<int> arr;

  for (int x; cin >> x;) arr.push_back(x);

  libsort(arr.data(), 0, arr.size() - 1);

  for (auto& x : arr) cout << x << "\n";

  return 0;
}