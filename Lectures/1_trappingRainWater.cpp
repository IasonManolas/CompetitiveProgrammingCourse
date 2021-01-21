#include <bits/stdc++.h>
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
 * Given a set of blocks we first find the positions for which the blocks are
 * not under water and essentially split one "lake" from the other. We call
 * these blocks "towers". Time complexity θ(n) Then having the "towers" we
 * compute the water collected between two consecutive towers by computing the
 * area between the two towers. The area is essentialy the width(how far apart
 * the towers are to each other)x the size of the smallest tower minus the
 * blocks in between the towers. θ(n) For computing the result we sum the water
 * collected by all the consecutive tower pairs. overall time complexity: θ(n)
 * */
int main() {
  int64_t t;
  cin >> t;
  while (t--) {
    int64_t n;
    cin >> n;
    if (n < 3) {
      cout << 0 << endl;
      continue;
    }
    vi a(n);
    REP(i, 0, n - 1) { cin >> a[i]; }

    // create the vector of towers
    vi towersToTheRight;

    int64_t firstMaximaIndex = 0;
    REP(i, 0, n - 2) {
      if (a[i] > a[i + 1]) {
        firstMaximaIndex = i;
        break;
      }
    }
    if (firstMaximaIndex == n - 2) {
      cout << 0 << endl;
      continue;
    }
    towersToTheRight.push_back(firstMaximaIndex);

    int64_t maximaIndex = firstMaximaIndex;
    REP(i, firstMaximaIndex + 1, n - 1) {
      if (a[i] >= a[maximaIndex]) {
        towersToTheRight.push_back(i);
        maximaIndex = i;
        while (maximaIndex < n - 1 && a[maximaIndex + 1] >= a[maximaIndex]) {
          maximaIndex++;
        }
        i = maximaIndex;
        if (maximaIndex != towersToTheRight.back()) {
          towersToTheRight.push_back(i);
        }
      }
    }

    vi maxToTheRight(n, -1);
    int64_t maxIndex = n - 1;
    REP_R(i, n - 2, towersToTheRight.back()) {
      maxToTheRight[i] = maxIndex;
      if (a[i] >= a[maxIndex]) {
        maxIndex = i;
      }
    }

    int64_t lastMaxima = towersToTheRight.back();
    REP(i, towersToTheRight.back(), n - 1) {
      if (maxToTheRight[lastMaxima] == i) {
        if (i - lastMaxima == 1) {
          lastMaxima++;
        } else {
          towersToTheRight.push_back(i);
          lastMaxima = i;
          while (lastMaxima < n - 1 && a[lastMaxima + 1] >= a[lastMaxima]) {
            lastMaxima++;
          }
          i = lastMaxima;
          if (lastMaxima != towersToTheRight.back()) {
            towersToTheRight.push_back(i);
          }
        }
      }
    }

    if (towersToTheRight.size() < 2) {
      cout << 0 << endl;
      continue;
    }
    // compute collected water between towers
    int64_t cw = 0; // collected water
    REP(towerIndex, 0, towersToTheRight.size() - 2) {
      int64_t tower = towersToTheRight[towerIndex];
      int64_t nextTower = towersToTheRight[towerIndex + 1];
      int64_t buw = 0;
      int64_t width = 0;
      REP(i, tower + 1, nextTower - 1) {
        if (std::min(a[tower], a[nextTower]) > a[i]) {
          buw += a[i];
          width++;
        }
      }
      cw += std::min(a[tower], a[nextTower]) * width - buw;
    }
    cout << cw << endl;
  }

  return 0;
}
