#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define NONE -1
#define EPSILON 5LL

auto isnt_none = [](ll i) { return i != NONE; };
auto is_none = [](ll i) { return i == NONE; };

ll search(ll e, vector<ll>& S, ll hi) {
  ll lo = 0;

  // find first non-NONE index
  while (hi >= 0 && is_none(S[hi])) hi--;
  // find last non-NONE index
  while (lo <= hi && is_none(S[lo])) lo++;

  while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;
    ll left = mid - 1;
    ll right = mid + 1;
    if (is_none(S[mid])) {
      // try forward scan
      while (right < hi && is_none(S[right])) right++;
      if (S[right] <= e) {
        lo = right + 1;
        continue;
      }
      // try backward scan
      while (left > lo && is_none(S[left])) left--;
      if (S[left] < e)  // found position
        return left;
      hi = left - 1;
      continue;
    }
    if (S[mid] < e) {
      lo = right;
    } else {
      hi = left;
    }
  }
  // return a lower position if no position found
  if (hi >= 0 && is_none(S[hi])) hi--;
  return hi;
}

ll search_free_pos(vector<ll>& A, vector<ll>& S, ll A_i, ll B_n) {
  // B_i is the position where we want to insert the element
  ll B_i = 1 + search(A[A_i], S, B_n - 1);

  if (isnt_none(S[B_i])) {
    // nextFree is the first free space after B_i
    ll nextFree = B_i + 1;
    // search a free space forward
    while (isnt_none(S[nextFree])) nextFree++;
    if (nextFree >= B_n) {
      if (isnt_none(S[B_i])) {
        // search a free space backward
        nextFree = --B_i;
        while (isnt_none(S[nextFree])) nextFree--;

        // shift elements to the left
        move(S.begin() + nextFree + 1, S.begin() + B_i + 1,
             S.begin() + nextFree);
      }
    } else {
      // shift elements to the right
      move_backward(S.begin() + B_i, S.begin() + nextFree,
                    S.begin() + nextFree + 1);
    }
  } else if (B_i >= B_n) {  // insPos is out of bounds
    // search a free space backward
    ll nextFree = --B_i;
    while (isnt_none(S[nextFree])) nextFree--;
    // shift elements to the left
    move(S.begin() + nextFree + 1, S.begin() + B_i + 1, S.begin() + nextFree);
  }
  return B_i;
}

void rebalance(vector<ll>& S, ll k, ll B_n) {
  // distance between elements to move
  ll step = (k + 1) / B_n;
  for (ll i = B_n - 1; i >= 0; i--) {
    if (is_none(S[i])) continue;
    S[k] = S[i];
    S[i] = NONE;
    k -= step;
  }
}

void lib_sort(vector<ll>& A) {
  ll A_n = A.size();
  if (A_n == 0) return;

  // sorted array
  vector<ll> S((1 + EPSILON) * A_n, NONE);

  // t elements to insert in each round
  ll t = 1;

  // A_i is the index of the next element to insert
  ll A_i = 0;

  // insert the first element into S
  S[0] = A[A_i++];

  // B_n is the size of the sorted array
  ll B_n = max(t + 1, 1 + EPSILON);

  while (A_i < A_n) {
    // insert `t` elements into S
    for (ll i = 0; i < t; i++) {
      ll B_i = search_free_pos(A, S, A_i, B_n);
      S[B_i] = A[A_i++];
      if (A_i >= A_n) break;
    }

    // double the number of elements to insert
    t *= 2;

    // k is the new size of S
    ll k = min(t, A_n) * (1 + EPSILON);
    rebalance(S, k - 1, B_n);
    B_n = k;
  }
  // copy S to A removing gaps
  copy_if(S.begin(), S.end(), A.begin(), isnt_none);
}

int main(int argc, char* argv[]) {
  ifstream fin(argv[1]);
  auto A = vector<ll>(istream_iterator<ll>(fin), {});
  fin.close();

  auto start = high_resolution_clock::now();
  lib_sort(A);
  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);

  cerr << "Time Taken: " << duration.count() << " microseconds" << endl;
  for (auto& x : A) cout << x << "\n";
  return 0;
}