#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

/*
 *  Since the numbers that can be used for creating a magic number are only
 * three I check if each digit complies with one of the allowed states: Only
 * digits of value 1 or 4 are allowed. If the value of digit is 4 the previously
 * consecutive encountered fours cannot be more than 2 in a row. The first digit
 * can only have the value 1. Time complexity θ(n)
 * */

int main() {
  size_t n;
  cin >> n;

  std::string s = to_string(n);
  if ((int)s[0] - 48 != 1) {
    cout << "NO" << endl;
    return 0;
  }

  int fourCounter = 0;
  for (size_t i = 1; i < s.size(); i++) {
    int digit = s[i] - 48;
    if (digit != 1 && digit != 4) {
      cout << "NO" << endl;
      return 0;
    }
    if (digit == 1) {
      fourCounter = 0;
      continue;
    }
    if (++fourCounter < 3) {
      continue;
    }
    cout << "NO" << endl;
    return 0;
  }

  cout << "YES" << endl;

  return 0;
}
