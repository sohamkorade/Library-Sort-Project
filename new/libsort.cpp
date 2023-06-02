#include <bits/stdc++.h>
using namespace std;

#define EPSILON 1
#define NONE -1

int two_power(int x) { return 1 << x; }

/**
 * Library Sort Binary Search with blanks
 * Input: Data to be sorted n and number to be searched k.
 * Output: Position to enter the element d.
 */
int binarySearch(vector<int>& S, int n, int k) {
  int low = 0;
  int high = n - 1;
  while (low < high) {
    int mid = (low + high) / 2;
    if (S[mid] == -1) {
      int m1 = mid;
      int m2 = mid;
      while (S[m1] == -1 && m1 >= low) {
        m1--;
      }
      while (S[m2] == -1 && m2 <= high) {
        m2++;
      }
      if (m1 < 0 && m2 >= high + 1) {
        low = high = m1 + 1;
      } else if (m1 == 0 && m2 >= high + 1) {
        if (k < S[m1]) {
          low = high = m1;
        } else {
          low = high = m1 + 1;
        }
      } else if (m1 > 0 && m2 >= high + 1) {
        if (k >= S[m1]) {
          high = m1 + 1;
        } else {
          high = m1 - 1;
        }
      } else if (m1 > 0 && m2 < high + 1) {
        if (k <= S[m1]) {
          if (k == S[mid]) {
            low = high = m1;
          } else {
            high = m1 - 1;
          }
        } else if (k > S[m1] && k < S[m2]) {
          low = m1 + 1;
          high = m2 - 1;
        } else if (k >= S[m2]) {
          if (m2 < high) {
            low = m2 + 1;
          } else {
            low = m2;
          }
        }
      }
    } else {
      if (S[mid] < k) {
        low = mid + 1;
      } else if (S[mid] > k) {
        high = mid - 1;
      } else {
        return mid;
      }
    }
  }
  if (low == high) {
    if (S[low] < k) {
      low++;
      high++;
    }
  }
  return low;
}

void librarySortInsertion(vector<int>& A, vector<int>& S, int i) {
  int n = A.size();
  int i1 = 0;
  int c1 = 0;
  if (i == 1) {
    i1 = i - 1;
    c1 = 0;
  }
  int S1 = two_power(i);
  if (S1 > n) {
    S1 = n;
  }
  for (int j = two_power(i1 - 1) - c1; j < S1; j++) {
    int k = binarySearch(S, two_power(i) + two_power(i + 1), A[j]);
    if (S[k] != -1) {
      // if there is an element in that particular position, we have to shift
      // the elements till we find the next gap
      int l = k;
      while (S[l] != -1) {
        l++;
      }
      while (l > k) {
        S[l] = S[l - 1];
        l--;
      }
    }
    S[k] = A[j];
  }
}

void librarySortRebalancing(vector<int>& S, int n, int e) {
  int l = 0;
  int i = 0;
  int j = 0;
  vector<int> reba(n, -1);
  while (l < n) {
    if (S[j] != -1) {
      reba[i] = S[j];
      i++;
      j++;
      l++;
      for (int k = 0; k < e; k++) {
        reba[i] = -1;
        i++;
      }
    } else {
      j++;
    }
  }
  for (int k = 0; k < i; k++) {
    S[k] = reba[k];
  }
}

void librarySort(vector<int>& A) {
  int n = A.size();
  if (n == 0) return;
  vector<int> S((1 + EPSILON) * n, NONE);
  int j, k, step;
  int goal = 1;
  int pos = 1;
  S[0] = A[0];
  int m = max((1 + EPSILON), goal + 1);
  while (pos < n) {
    for (j = 0; j < goal; j++) {
      int insert_pos = binarySearch(S, m, A[pos]);
      insert_pos++;
      if (S[insert_pos] != -1) {
        int nextFree = insert_pos + 1;
        while (S[nextFree] != -1) nextFree++;
        if (nextFree >= m) {
          librarySortRebalancing(S, m, EPSILON);
          m = (1 + EPSILON) * m;
        } else {
          for (k = nextFree; k > insert_pos; k--) S[k] = S[k - 1];
        }
      }
      S[insert_pos] = A[pos];
      pos++;
    }
    goal *= 2;
  }
  for (j = 0; j < n; j++) A[j] = S[j];
}

int main() {
  string a = "testcase_1e", b = "_random.txt";
  for (int i = 5; i < 6; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    vector<int> A;
    string index = to_string(i), line;
    string file = a + index + b;
    ifstream fin;
    fin.open(file);
    while (getline(fin, line)) {
      A.push_back(stol(line));
    }
    fin.close();
    librarySort(A);
    for (int j = 0; j < A.size(); j++) cout << A[j] << "\n";
    // cout << "\n";
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << "Time Taken = " << duration.count() << " microseconds" << endl;
  }
  return 0;
}