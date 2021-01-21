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
typedef vector<int64_t> vi;
typedef pair<int64_t, int64_t> pi;

/*
 * We simply construct a difference array which holds in position i the
 * difference of the ith element with respect to the sum [0,i-1]. That way we
 * can apply the update operations on that array in O(1). We do that for update
 * op [l,r,v] by adding v to diffArray[l] and substracting v from
 * diffArray[r+1]. We then reconstruct the array from the diffArray in O(n)
 * time. Overall time complexity: θ(n) if n>q && n>u
 * */

int main() {
  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n, u;
    cin >> n >> u;
    vi diffArray(n, 0);
    while (u--) { //θ(u)
      int64_t l, r, v;
      cin >> l >> r >> v;
      diffArray[l] += v;
      if (r != n - 1) {
        diffArray[r + 1] -= v;
      }
    }
    vi res(n);
    int64_t sum = 0;
    for (int i = 0; i < n; i++) { //θ(n)
      sum += diffArray[i];
      res[i] = sum;
    }

    int64_t q;
    cin >> q;
    while (q--) { //θ(q)
      int64_t qi;
      cin >> qi;
      cout << res[qi] << "\n";
    }
  }
  return 0;
}
