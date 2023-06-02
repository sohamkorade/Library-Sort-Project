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

int partition(vector <ll> &A, ll low, ll high)
{
    ll pivot = A[high];
    ll i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return (i + 1);
}

void quickSort(vector <ll> &A, ll low, ll high)
{
    if (low < high)
    {
        ll pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
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
        quickSort(A, 0, A.size()-1);
        // for (ll j = 0; j < A.size(); j++)
            // cout << "A[" << j << "] = " << A[j] << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout<<duration.count()<<endl;
    }
    return 0;
}