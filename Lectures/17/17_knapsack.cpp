#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> vector<T> get_input_sequence(size_t n) {
  vector<T> sequence(n);

  for (size_t i = 0; i < n; ++i)
    cin >> sequence[i];
  return sequence;
}

template <> vector<std::pair<size_t, size_t>> get_input_sequence(size_t n) {
  vector<std::pair<size_t, size_t>> sequence(n);

  for (size_t i = 0; i < n; ++i) {
    cin >> sequence[i].first;
    cin >> sequence[i].second;
  }
  return sequence;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t s, n;
  cin >> s;
  cin >> n;
  auto v = get_input_sequence<std::pair<size_t, size_t>>(n);

  vector<vector<size_t>> K(n + 1, vector<size_t>(s + 1, 0));

//O(n*s)
  //We fill matrix K such that K[i][j] represents the maximum profit with maximum weight j and using
  //the first i items. Thus in the end the bottom right cell contains the maximum value that can
  //be achieved with a bag of capacity s
  for (size_t i = 0; i < n + 1; i++) {
    for (size_t j = 0; j < s + 1; j++) {
      if (i == 0 || j == 0) {
        K[i][j] = 0;
      } else if (j < v[i - 1].first) {
        K[i][j] = K[i - 1][j];
      } else {
        K[i][j] = std::max(K[i - 1][j],
                           K[i - 1][j - v[i - 1].first] + v[i - 1].second);
      }
    }
  }

  cout << K[n][s] << endl;
}
