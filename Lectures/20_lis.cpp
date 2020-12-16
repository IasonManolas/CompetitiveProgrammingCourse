// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#include <set>
#include <vector>
int longestSubsequence(int, int[]);

int main() {
  // taking total testcases
  int t, n;
  cin >> t;
  while (t--) {
    // taking size of array
    cin >> n;
    int a[n];

    // inserting elements to the array
    for (int i = 0; i < n; i++)
      cin >> a[i];

    // calling method longestSubsequence()
    cout << longestSubsequence(n, a) << endl;
  }
}
// } Driver Code Ends

struct ValueIndex {
  int value;
  int index;
};

struct ValueIndexComp {
  bool operator()(const ValueIndex &vi0, const ValueIndex &vi1) {
    return vi0.value < vi1.value;
  }
};

// We keep a bst of dominating positions which keeps all the elements i of the
// array for which a[j]>=a[i] and lis[j]<=lis[i]. This is because such elements
// are always a better choice for extending the increasing subsequence over
// element j. Since an element can be added and removed once from that bst
// its construction costs θ(n). For each element of the array we execute a
// predecessor query for finding which previous element the ith element of the
// array
// can extend. This costs θ(logn) for each element. Thus the overall complexity
// of the solution is θ(nlogn).
int longestSubsequence(int n, int a[]) {
  std::vector<int> lis(n);
  using Index = int;
  using Value = int;
  map<Value, Index> dominatingPositions;
  int lisSize = 1;

  for (int i = 0; i < n; i++) {
    auto insertionResult = dominatingPositions.insert(make_pair(a[i], i));
    if (!insertionResult.second) {
      dominatingPositions[a[i]] = i;
    }
    if (dominatingPositions.lower_bound(a[i]) == dominatingPositions.begin()) {
      lis[i] = 1;
    } else {
      auto itPredecessor = std::prev(dominatingPositions.lower_bound(a[i]));
      lis[i] = lis[itPredecessor->second] + 1;
    }

    auto itSuccesor = std::next(insertionResult.first);
    while (itSuccesor != dominatingPositions.end()) {
      if (itSuccesor->first >= a[i] && lis[itSuccesor->second] <= lis[i]) {
        itSuccesor = dominatingPositions.erase(itSuccesor);
      } else {
        itSuccesor++;
      }
    }
  }

  return dominatingPositions.size();
}
