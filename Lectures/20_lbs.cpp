// { Driver Code Starts

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

std::vector<int> longestIncreasingSubsequence(int n, int a[]) {
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

  return lis;
}

class Solution {
public:
  /*
   * I use the solution which was described in the lis problem that computes the
   * lis of an array of elements in θ(nlogn). For both the normal and reversed
   * vector I compute a vector which holds the lis and lds respectively that
   * ends at index i. For computing the lds I simply reverse the vector and use
   * the lis algorithm. Finally to compute the lbs I compute for each index i
   * the sum: lis[i]+lds[i]-1 and keep the maximum (-1 because the index of the
   * peak is used in both the lds and lis). The total time complexity is
   * Θ(nlogn+nlogn+n)=θ(nlogn). space complexity:θ(n)
   * */
  int LongestBitonicSequence(vector<int> nums) {
    vector<int> reversed_nums(nums.rbegin(), nums.rend());
    int maxBS = 0;

    const vector<int> LISVector =
        longestIncreasingSubsequence(nums.size(), nums.data());
    vector<int> LDSVector =
        longestIncreasingSubsequence(nums.size(), reversed_nums.data());
    LDSVector = std::vector<int>(LDSVector.rbegin(), LDSVector.rend());

    for (int i = 0; i < nums.size(); i++) {
      maxBS = std::max(maxBS, LISVector[i] + LDSVector[i] - 1);
    }

    return maxBS;
  }
};

// { Driver Code Starts.
int main() {
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
      cin >> nums[i];
    Solution ob;
    int ans = ob.LongestBitonicSequence(nums);
    cout << ans << "\n";
  }
  return 0;
} // } Driver Code Ends
