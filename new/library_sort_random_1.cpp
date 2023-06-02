#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef long long int ll;

#define epsilon 1

ll convert_string(string &str) {
  ll sum = 0;
  for (ll i = 0; i < str.length(); i++) sum = 10 * sum + str[i] - 48;
  return sum;
}

ll search(ll x, vector<ll> S,
          ll end_index)  // last -> end_index, sorted->S, e->x, first ->
                         // start_index, middle -> mid
{
  ll start_index = 0, mid;

  while (end_index >= 0 && S[end_index] < 0) end_index--;

  while (start_index <= end_index && S[start_index] < 0) start_index++;

  while (start_index <= end_index) {
    mid = (start_index + end_index) / 2;
    if (S[mid] < 0) {
      ll temp = mid + 1;
      // search in the right direction
      while (temp < end_index && S[temp] < 0) temp++;
      if (S[temp] > x) {
        temp = mid - 1;
        while (mid > start_index && S[mid] < 0) mid--;
        // search in the left direction
        if (S[mid] < x) return mid;
        end_index = mid - 1;
      } else
        start_index = temp + 1;
    } else if (S[mid] < x)
      start_index = mid + 1;
    else
      end_index = mid - 1;
  }
  if (end_index >= 0 && S[end_index] < 0) end_index--;
  return end_index;
}

void Sort(vector<ll> &A, int n, vector<ll> &S) {
  if (n == 0)  // Size of Array is 0, return
    return;
  ll j, k, step;
  ll insert_no = 1;
  ll inserted = 1;
  S[0] = A[0];  // Element 0 at Position 0
  ll init_len = max((ll)1 + EPSILON, 1 + insert_no);
  while (inserted < n) {
    for (ll j = 0; j < insert_no; j++) {
      ll insert_pos = search(A[inserted], S, init_len - 1);
      cout << "j = " << j << "\tinserted_pos = " << insert_pos << endl;
      insert_pos++;
      if (S[insert_pos] >= 0) {
        ll free_spot = insert_pos + 1;
        while (S[free_spot] >= 0) free_spot++;

        // At free_spot, free spot is found
        if (free_spot >= init_len) {
          insert_pos--;
          if (S[insert_pos] >= 0) {
            free_spot = insert_pos - 1;
            while (S[free_spot] >= 0) free_spot--;
            // translate all elements to left
            while (free_spot < insert_pos) {
              S[free_spot] = S[free_spot + 1];
              free_spot++;
            }
          }
        } else  // translate all elements to right
        {
          while (free_spot > insert_pos) {
            S[free_spot] = S[free_spot - 1];
            free_spot--;
          }
        }
      } else if (insert_pos >=
                 (1 + EPSILON) * n)  // Search a Free Space Backwards
      {
        insert_pos--;
        ll free_spot = insert_pos - 1;
        while (S[free_spot] >= 0) free_spot--;
        while (free_spot < insert_pos) {
          S[free_spot] = S[free_spot + 1];
          free_spot++;
        }
      }

      cout << "inserted_pos = " << insert_pos << "\tafter" << endl;
      S[insert_pos] = A[inserted++];
      if (inserted >= n)  // Last Element Inserted into the Array
        return;
      for (ll it = 0; it < init_len; it++)
        cout << "S[" << it << "] = " << S[it] << " ";
      cout << "after" << endl << endl;
    }

    // Rebalance - It takes linear time. Tries to spread the elements as much as
    // possible
    for (j = init_len - 1,
        k = min((ll)insert_no * (2 + 2 * EPSILON), (ll)n * (1 + EPSILON)) - 1,
        step = (k + 1) / (j + 1);
         j >= 0; j--, k -= step) {
      S[k] = S[j];
      S[j] = -1;
    }

    // In each round insert the double of elements to the sorted array because
    // there will be the double of free spaces after the rebalance
    init_len = min((ll)insert_no * (2 + 2 * EPSILON), (ll)n * (1 + EPSILON));
    insert_no *= 2;  // 2*i elements sorted after this round
  }
}

void library_Sort(vector<ll> &A, ll n) {
  vector<ll> S;
  for (ll i = 0; i < (1 + EPSILON) * n; i++) S.push_back(-1);
  Sort(A, n, S);
  for (ll i = 0, j = 0; i < (1 + EPSILON) * n && j < n; i++) {
    if (S[i] >= 0) A[j++] = S[i];
  }
  return;
}

int main() {
  string a = "testcase_1e", b = "_random.txt";
  for (ll i = 1; i < 2; i++) {
    auto start = high_resolution_clock::now();
    vector<ll> A;
    string index = to_string(i), line;
    string file = a + index + b;
    ifstream fin;
    fin.open(file);
    while (getline(fin, line)) {
      ll sum = convert_string(line);
      A.push_back(sum);
    }
    fin.close();
    library_Sort(A, A.size());
    for (ll j = 0; j < A.size(); j++)
      cout << "A[" << j << "] = " << A[j] << " ";
    cout << endl << endl;
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << "Time Taken = " << duration.count() << " microseconds" << endl;
  }
  return 0;
}