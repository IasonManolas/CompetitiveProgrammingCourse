// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

/*
 * For solving this problem we use dp and a bottom up approach. We fill matrix M
 * of which each element [i][j] contains the answer to the subproblem: does the
 * subarray [1,i] of input vector arr contain a set of elements of which the sum
 * is j? The answer to that depends on whether sum j could be built with the
 * subarray [1,i-1] or whether having the surray [1,i-1] we could have created a
 * sum of value j-arr[i]. If the answer to one of the previous is yes then the
 * value M[i][j] is also yes. Otherwise the answer is no.
 *
 * Time complexity:
 * θ(arraySum*N) for filling the matrix M
 * */
class Solution {
public:
  int equalPartition(int N, int arr[]) {
    int arraySum = 0;
    for (int i = 0; i < N; i++) {
      arraySum += arr[i];
    }
    if (arraySum % 2 != 0) {
      return 0;
    }

    vector<vector<int>> M(N + 1, vector<int>(arraySum / 2 + 1, false));
    for (int i = 0; i <= N; i++)
      M[i][0] = true;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= arraySum / 2; j++) {
        if (arr[i - 1] <= j) {
          M[i][j] = M[i - 1][j] || M[i - 1][j - arr[i - 1]];
        }
      }
    }

    return M[N][arraySum / 2];
  }
};

// { Driver Code Starts.

int main() {
  int t;
  cin >> t;
  while (t--) {
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
      cin >> arr[i];

    Solution ob;
    if (ob.equalPartition(N, arr))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
} // } Driver Code Ends
