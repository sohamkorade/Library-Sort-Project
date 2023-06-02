#include <bits/stdc++.h>
using namespace std;

#define epsilon 0
#define MAX 10
#define MAX2 MAX *(epsilon + 1)

#define IS_EMPTY(e) (e < 0)
#define NONE -1

void prepareLibrarySort(int n, int S[MAX2], int *init_len) {
  int i;
  *init_len = (1 + EPSILON) * n;
  for (i = 0; i < *init_len; i++) S[i] = NONE;
}

int searchFree(int e, int sorted[MAX2], int last) {
  int first = 0;
  int middle;

  while (last >= 0 && IS_EMPTY(sorted[last])) last--;
  while (first <= last && IS_EMPTY(sorted[first])) first++;
  while (first <= last) {
    middle = (first + last) / 2;
    if (IS_EMPTY(sorted[middle])) {
      int tmp = middle + 1;
      while (tmp < last && IS_EMPTY(sorted[tmp])) tmp++;
      if (sorted[tmp] > e) {
        tmp = middle - 1;
        while (middle > first && IS_EMPTY(sorted[middle])) middle--;
        if (sorted[middle] < e) return middle;
        last = middle - 1;
      } else
        first = tmp + 1;
    } else if (sorted[middle] < e)
      first = middle + 1;
    else
      last = middle - 1;
  }
  if (last >= 0 && IS_EMPTY(sorted[last])) last--;
  return last;
}

void libSort(int A[MAX], int N, int S[MAX2]) {
  if (N == 0) return;
  int j, k, step;
  int insert_no = 1;
  int inserted = 1;
  S[0] = A[0];
  int init_len = max((1 + EPSILON), insert_no + 1);
  while (inserted < N) {
    for (j = 0; j < insert_no; j++) {
      int inserted_pos = searchFree(A[inserted], S, init_len - 1);
      //   cout << "j = " << j << "\tinserted_pos = " << inserted_pos << endl;
      inserted_pos++;
      if (!IS_EMPTY(S[inserted_pos])) {
        int nextFree = inserted_pos + 1;
        while (!IS_EMPTY(S[nextFree])) nextFree++;

        if (nextFree >= init_len) {
          inserted_pos--;
          if (!IS_EMPTY(S[inserted_pos])) {
            nextFree = inserted_pos - 1;
            while (!IS_EMPTY(S[nextFree])) nextFree--;
            while (nextFree < inserted_pos) {
              S[nextFree] = S[nextFree + 1];
              nextFree++;
            }
          }
        } else {
          while (nextFree > inserted_pos) {
            S[nextFree] = S[nextFree - 1];
            nextFree--;
          }
        }
      } else if (inserted_pos >= init_len) {
        inserted_pos--;
        int nextFree = inserted_pos - 1;
        while (!IS_EMPTY(S[nextFree])) nextFree--;
        while (nextFree < inserted_pos) {
          S[nextFree] = S[nextFree + 1];
          nextFree++;
        }
      }

      //   cout << "inserted_pos = " << inserted_pos << "\tafter" << endl;
      S[inserted_pos] = A[inserted++];
      if (inserted >= N) return;
      //   for (int it = 0; it < init_len; it++)
      // cout << "S[" << it << "] = " << S[it] << " ";
      //   cout << endl << endl;
    }
    for (j = init_len - 1,
        k = min(insert_no * (2 + 2 * EPSILON), (1 + EPSILON) * N) - 1,
        step = (k + 1) / (j + 1);
         j >= 0; j--, k -= step) {
      S[k] = S[j];
      S[j] = NONE;
    }
    init_len = min(insert_no * (2 + 2 * EPSILON), N * (1 + EPSILON));
    insert_no <<= 1;
  }
}

void lib_sort(int A[MAX], int n) {
  int S[MAX2];
  int init_len, i, j;
  prepareLibrarySort(n, S, &init_len);
  libSort(A, n, S);
  for (i = 0, j = 0; i < init_len && j < n; i++)
    if (!IS_EMPTY(S[i])) A[j++] = S[i];
}

int main() {
  int A[MAX];
  A[0] = 1;
  A[1] = 5;
  A[2] = 2;
  A[3] = 3;
  A[4] = 4;
  A[5] = 6;
  A[6] = 10;
  A[7] = 7;
  A[8] = 8;
  A[9] = 9;
  lib_sort(A, 10);
  for (int i = 0; i < 10; i++) cout << "A[" << i << "] = " << A[i] << " ";
  cout << endl;
  return 0;
}