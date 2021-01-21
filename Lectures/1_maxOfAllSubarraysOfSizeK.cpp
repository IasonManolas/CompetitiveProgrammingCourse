#include <bits/stdc++.h>
#include <deque>
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
 * For solving this problem we use a deque for saving possible maximum of next
 * shifted windows. We start by creating the first window of size k and then
 * iteratively remove the element from the deque that is outside of the window
 * and add the new element from the back. When adding the element we remove all
 * the elements that are smaller or equal than the new element. We do that
 * because those are not possible canditates for being a max element in future
 * windows. That way our deque has the minimal size and is sorted meaning that
 * the maximum element of each window is positioned at the top of the deque.
 * Time complexity analysis:
 * θ(1) for poping and adding an element
 * Since each element is added and removed at most once we get an overall
 * complexity of θ(n)=θ(pop_ops)+θ(add_ops)=θ(n)+θ(n)
 * */


vector<int> max_of_subarrays(int *arr, int n, int k) {
deque<pi> window;
  vector<int> max;
  REP(i, 0, k - 1) {
        while(!window.empty() && (window.back().first <=arr[i] )) {
          window.pop_back();
      }
      window.push_back({arr[i],i});
  }
  max.push_back(window.front().first);

  REP(i, k, n - 1) {
    while (!window.empty() && window.front().second <= i - k) {
      window.pop_front();
    }
    while(!window.empty() && (window.back().first <=arr[i] )) {
      window.pop_back();
    }
    window.push_back({arr[i],i});
    max.push_back(window.front().first);
  }
  return max;
}

int main() {

  int t;
  cin >> t;

  while (t--) {

    int n, k;
    cin >> n >> k;

    int arr[n];
    for (int i = 0; i < n; i++)
      cin >> arr[i];

    vector<int> res = max_of_subarrays(arr, n, k);
    for (int i = 0; i < res.size(); i++)
      cout << res[i] << " ";
    cout << endl;
  }

  return 0;
} // } Driver Code Ends
