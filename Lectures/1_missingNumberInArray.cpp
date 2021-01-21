#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, a, b) for (int i = a; i <= b; i++)
#define F first
#define S second
#define PB push_back
#define MP make_pair
typedef vector<int> vi;
typedef pair<int, int> pi;

int MissingNumber(vector<int> &array, int n);

// Position this line where user code will be pasted.

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> array(n - 1);
    for (int i = 0; i < n - 1; ++i)
      cin >> array[i];

    cout << MissingNumber(array, n) << "\n";
  }
  return 0;
} // } Driver Code Ends

// User function template for C++
/*
 * We know that sum_1^n=n(n+1)/2. Thus the missing number is the sum of the
 * given elements substracted from n(n+1)/2 Time complexity: θ(n)
 * */
int MissingNumber(vector<int> &array, int n) {
  const int64_t expectedSum = n * (n + 1) / 2;

  int64_t sum = std::accumulate(array.begin(), array.end(), 0);

  return expectedSum - sum;
}
