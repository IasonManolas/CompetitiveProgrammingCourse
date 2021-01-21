#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
typedef vector<int> vi;
typedef pair<int, int> pi;

/*
 * In case all elements are negative the maxSum is the smallest absolute value.
 * In case all elements are positive the maxSum is the sum of all the elements
 * In case we have both positive and negative elements:
 * If we encounter a negative element we need to decide whether it should be
 * added to the sum or not. The only case in which we add it is if
 * sum_(i-1)>=A_i and there exists some j>i for which sum_(i,j)>0. Because of
 * that everytime sum<0 we reset it to 0. Time complexity: θ(n)
 * */
// Function to find subarray with maximum sum
// arr: input array
// n: size of array
int maxSubarraySum(int arr[], int n) {
#define REP(i, a, b) for (int i = a; i <= b; i++)
  int sum = arr[0];
  int maxSum = sum;
  REP(i, 1, n - 1) {
    if (sum < 0) {
      sum = 0;
    }
    sum += arr[i];
    maxSum = max(maxSum, sum);
  }
  return maxSum;
}

// { Driver Code Starts.

int main() {
  int t, n;

  cin >> t;   // input testcases
  while (t--) // while testcases exist
  {

    cin >> n; // input size of array

    int a[n];

    for (int i = 0; i < n; i++)
      cin >> a[i]; // inputting elements of array

    cout << maxSubarraySum(a, n) << endl;
  }
}
// } Driver Code Ends
