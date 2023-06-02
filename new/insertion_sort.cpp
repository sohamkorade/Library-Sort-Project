#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef long long int ll;

ll convert_string(string &str)
{
    ll sum = 0;
    for (ll i = 0; i < str.length(); i++)
        sum = 10*sum + str[i] - 48;
    return sum;
}

void insertion_sort(vector<ll> &A)
{
    ll n = A.size();
    for (ll i = 0; i < n; i++)
    {
        ll j = i;
        while (j > 0 && A[j - 1] > A[j])
        {
            swap(A[j], A[j - 1]);
            j--;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    string a = "testcase_1e", b = argv[1], c = "_", d = ".txt";
    for (ll i = 1; i < 7; i++)
    {
        vector <ll> A;
        string index = to_string(i), line;
        string file = a + index + c + b + d;
        ifstream fin;
        fin.open(file);
        while (getline(fin, line))
        {
            ll sum = convert_string(line);
            A.push_back(sum);
        }
        fin.close();
        auto start = high_resolution_clock::now();
        insertion_sort(A);
        // for (ll j = 0; j < A.size(); j++)
            // cout << "A[" << j << "] = " << A[j] << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout<<duration.count()<<endl;
    }
    return 0;
}