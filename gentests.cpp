#include <bits/stdc++.h>
using namespace std;

#define ll long long

auto rng = default_random_engine{};

vector<ll> shuffled(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n; i++) v.push_back(i);
  shuffle(v.begin(), v.end(), rng);
  return v;
}

vector<ll> all_equal(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n; i++) v.push_back(0);
  return v;
}

vector<ll> ascending(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n; i++) v.push_back(i);
  return v;
}

vector<ll> descending(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = n - 1; i >= 0; i--) v.push_back(i);
  return v;
}

vector<ll> pipe_organ(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n / 2; i++) v.push_back(i);
  for (ll i = n / 2; i < n; i++) v.push_back(n - i);
  return v;
}

vector<ll> push_front(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 1; i < n; i++) v.push_back(i);
  v.push_back(0);
  return v;
}

vector<ll> push_middle(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n; i++)
    if (i != n / 2) v.push_back(i);
  v.push_back(n / 2);
  return v;
}

vector<ll> nearly_sorted(ll n) {
  vector<ll> v;
  v.reserve(n);
  for (ll i = 0; i < n; i++) v.push_back(i);
  // swap 10% of the elements
  for (ll i = 0; i < n / 10; i++) {
    ll x = uniform_int_distribution<ll>{0, n - 1}(rng);
    ll y = uniform_int_distribution<ll>{0, n - 1}(rng);
    swap(v[x], v[y]);
  }
  return v;
}

vector<ll> sawtooth(ll n) {
  vector<ll> v;
  v.reserve(n);
  ll period = n / 10;
  for (ll i = 0; i < n; i++) v.push_back(i % period);
  return v;
}

int main(int argc, char* argv[]) {
  if (argc < 2) return 1;
  ll n = atol(argv[1]);

  map<string, vector<ll> (*)(ll)> generators = {
      {"shuffled", shuffled},       {"all_equal", all_equal},
      {"ascending", ascending},     {"descending", descending},
      {"pipe_organ", pipe_organ},   {"push_front", push_front},
      {"push_middle", push_middle}, {"nearly_sorted", nearly_sorted},
      {"sawtooth", sawtooth},
  };

  // create test cases
  ofstream fout;
  for (int i = 1; i < n; i++) {
    for (auto& [name, gen] : generators) {
      vector<ll> v = gen(pow(10, i));
      string file = "testcases/1e" + to_string(i) + "_" + name + ".txt";
      fout.open(file);
      for (auto& x : v) fout << x << "\n";
      fout.close();
    }
  }

  return 0;
}