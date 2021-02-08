#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, a, b) for (int i = a; i <= b; i++)
#define REP_R(i, a, b) for (int i = a; i >= b; i--)
#define F first
#define S second
#define PB push_back
#define MP make_pair
typedef vector<int> vi;
typedef pair<int, int> pi;

template <class T> struct fenwick_tree {
  std::vector<T> x;
  fenwick_tree(size_t n) : x(n + 1) {}

  // initialize by a constant
  fenwick_tree(size_t n, T a) : x(n + 1, a) {
    x[0] = 0;
    for (int k = 1; k + (k & -k) <= n; ++k)
      x[k + (k & -k)] += x[k];
  }

  // initialize by a std::vector
  fenwick_tree(std::vector<T> y) : x(y.size() + 1) {
    for (int k = 0; k < y.size(); ++k)
      x[k + 1] = y[k];
    for (int k = 1; k + (k & -k) < x.size(); ++k)
      x[k + (k & -k)] += x[k];
  }

  // b[k] += a
  void add(int k, T a) {
    for (++k; k < x.size(); k += k & -k)
      x[k] += a;
  }

  // sum b[0,k)
  T sum(int k) {
    T s = 0;
    for (++k; k > 0; k &= k - 1)
      s += x[k];
    return s;
  }

  // sum b[k,j)
  T sum(int k, int j) { return sum(j) - sum(k); }

  // min { k : sum(k) >= a }; it requires b[k] >= 0
  int lower_bound(T a) {
    if (a <= 0)
      return 0;
    int k = x.size() - 1;
    for (int s : {1, 2, 4, 8, 16})
      k |= (k >> s);
    for (int p = ++k; p > 0; p >>= 1, k |= p)
      if (k < x.size() && x[k] < a)
        a -= x[k];
      else
        k ^= p;
    return k + 1;
  }

  // max { k : sum(k) <= a }; it requires b[k] >= 0
  int upper_bound(T a) {
    int k = x.size() - 1;
    for (int s : {1, 2, 4, 8, 16})
      k |= (k >> s);
    for (int p = ++k; p > 0; p >>= 1, k |= p)
      if (k < x.size() && x[k] <= a)
        a -= x[k];
      else
        k ^= p;
    return k;
  }
};

/*
 *  We remap the given array in order to use a vector and in order to avoid
 * using an unordered_multiset for counting the frequencies and since the actual
 * values of the array elements don't matter but rather their relationship to
 * each other and their position in the array.
 *
 * We compute the f(1,i,a_i)
 * and f(i,n,a_i) values for every i in [1,n]
 * (forwardFunction,backwardFunction). Then we use a fenwick tree which we fill
 * using the values of f(i,n,a_i) for every i. Then simply we check for each i
 * how many elements with j>i in the f(j,n,a_j) array are smaller than
 * f(1,i.a_i) and add those to the result. The last step is done fast thanks to
 * the fenwick tree we are using.
 *
 * Complexities:
 * Time complexity: We need θ(n) for computing the f(1,i,a_i) and f(i,n,a_i)
 * values. Adding and summing on a fenwick tree cost Ο(logn) thus the overall
 * time complexity of this solution is O(nlogn). Space complexity: We used Θ(n)
 * for saving f(1,i,a_i),f(i,n,a_i),frequencies and the fenwick tree. Overall
 * the space complexity is Θ(n) for computing the solution.
 * */

void remap(vector<int> &a) {
  vector<int> tmp(a.size());
  copy(a.begin(), a.end(), tmp.begin());
  sort(tmp.begin(), tmp.end());
  size_t sz = distance(tmp.begin(), unique(tmp.begin(), tmp.end()));
  tmp.resize(sz);

  for (auto &x : a)
    x = distance(tmp.begin(), lower_bound(tmp.begin(), tmp.end(), x));
}

int main() {
  int n;
  cin >> n;
  vi v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  remap(v); //Ο(nlogn)
  vi frequencies(n, 0);
  vi forwardFunction(n);        // 1..i
  for (int i = 0; i < n; i++) { //θ(n)
    frequencies[v[i]]++;
    forwardFunction[i] = frequencies[v[i]];
  }

  vi backwardFunction(n); // j..n
  fenwick_tree<int> tree(n);
  for (int i = 0; i < n; i++) {
    backwardFunction[i] = frequencies[v[i]]; //θ(n)
    frequencies[v[i]]--;                     //θ(n)
    tree.add(backwardFunction[i], 1);        // O(nlogn)
  }

  int64_t numberOfPairs = 0;
  for (int i = 0; i < n; i++) {
    tree.add(backwardFunction[i], -1);                 // O(nlogn)
    numberOfPairs += tree.sum(forwardFunction[i] - 1); // O(nlogn)
  }

  std::cout << numberOfPairs << endl;
  return 0;
}
