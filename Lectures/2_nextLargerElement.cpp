#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

// Function to return Next larger elements
/*
 * We use a deque in which we add elements by iterating over the given array
 * from end to start. For each element we iteratively pop items until we find an
 * element that is greater then the current element or the deque is empty and
 * save the result. Time complexity: θ(n) since every item can be added and
 * removed from the deque at most once. Space complexity: θ(n)
 * */
vector<long long> nextLargerElement(vector<long long> arr, int n) {
  deque<long long> Q;
  vector<long long> results(n);
  results[n - 1] = -1;
  Q.push_front(n - 1);
  for (int i = n - 2; i >= 0; i--) {
    while (!Q.empty() && arr[i] >= arr[Q.front()]) {
      Q.pop_front();
    }
    if (Q.empty()) {
      results[i] = -1;
    } else {
      results[i] = arr[Q.front()];
    }
    Q.push_front(i);
  }
  return results;
}

// { Driver Code Starts.

int main() {
  int t;
  cin >> t;
  while (t--) {

    int n;
    cin >> n;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++)
      cin >> arr[i];

    vector<long long> res = nextLargerElement(arr, n);
    for (long long i : res)
      cout << i << " ";
    cout << endl;
  }
  return 0;
}
// } Driver Code Ends
