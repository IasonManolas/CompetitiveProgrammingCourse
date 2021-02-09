#include <bits/stdc++.h>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Flipping the bits of a substring of the initial marks cannot add more than
 * two to the length of the initially longest alternating sequence. This is
 * because in the best case we will introduce two alternating bits on the two
 * ends of the substring we are flipping (since the number of alternating bits
 * within the substring do not change by flipping them).
 *
 * Time and space complexity are θ(n).
 * */

int main() {
  int n;
  cin >> n;
  std::string s(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }

  // Compute the length of the longest alternating sequence of the initial marks
  int initialASlength = 1;
  char lastCharOfAS = s[0];
  for (int i = 0; i < n - 1; i++) {
    if (lastCharOfAS != s[i + 1]) {
      initialASlength++;
      lastCharOfAS = s[i + 1];
    }
  }

  cout << min(n, initialASlength + 2) << endl;

  return 0;
}
