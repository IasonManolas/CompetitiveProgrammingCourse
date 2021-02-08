// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

/*
 * We simply go over the array by keeping track of the maximum index we can
 * reach from each cell (saved in maxReached). We keep track of how many steps
 * we have done from the previous maxReach (saved in steps) and update it every
 * time the number of steps is equal to the number of steps the last maxReach
 * allows us (steps==0). Time complexity: θ(n) since the function breaks early
 * as soon as a jump is found with which the last element can be reached.
 * */

// Function to return minimum number of jumps to end of array
int minJumps(int arr[], int n) {
  if (arr[0] == 0) {
    return -1;
  }

  int steps = arr[0];
  int maxReached = arr[0];
  int jumps = 1;
  if (maxReached >= n - 1) {
    return jumps;
  }
  for (int i = 1; i < n; i++) {
    maxReached = max(maxReached, i + arr[i]);
    steps--;

    if (maxReached >= n - 1) {
      jumps++;
      break;
    }

    if (steps == 0) {
      jumps++;
      steps = maxReached - i;
      if (steps == 0) {
        return -1;
      }
    }
  }

  return jumps;
}

// { Driver Code Starts.

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, i, j;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
      cin >> arr[i];

    cout << minJumps(arr, n) << endl;
  }
  return 0;
}
// } Driver Code Ends
