#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;
// Note: I couldn't come up with the solution. I read the solution given on
// https://codeforces.com/blog/entry/81506

/*
 * For achieving the maximum damage we need the nl lighting spells to double the
 * biggest nl spells. In case the biggest nl spells are all lighting spells
 * there will be one lighting spell which will not double its next spell. This
 * is the greatest spell (which also is the greatest lighting spell in this
 * case). Because of that in this special case the maximum damage is achieved by
 * using the nl+1 greatest spell. Time complexity: θ(nlogn) since we use a tree
 * for storing the spells.
 * */

set<int64_t> spellPowers[2];
int64_t spellPowerSum[2];
set<int64_t> lightingSpells;
int64_t numOfLightingSpells[2];

void transferItem(int id) {
  assert(spellPowers[id].size() > 0);
  int x = *spellPowers[id].rbegin();
  if (id == 1)
    x = *spellPowers[id].begin();
  bool d = lightingSpells.count(x);

  spellPowerSum[id] -= x, spellPowerSum[!id] += x;
  spellPowers[id].erase(x), spellPowers[!id].insert(x);
  numOfLightingSpells[id] -= d, numOfLightingSpells[!id] += d;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t n;
  cin >> n;

  int64_t maximumDamage = 0;
  while (n--) {
    bool isLightingSpell;
    int64_t power;
    cin >> isLightingSpell >> power;
    const bool addSpell = power > 0;

    if (addSpell) {
      spellPowerSum[0] += power;
      spellPowers[0].insert(power);
      numOfLightingSpells[0] += isLightingSpell;
      if (isLightingSpell)
        lightingSpells.insert(power);
    } else {
      const bool isInSecondArray = spellPowers[1].count(-power) != 0;
      spellPowers[isInSecondArray].erase(-power);
      spellPowerSum[isInSecondArray] += power;
      if (isLightingSpell) {
        lightingSpells.erase(-power);
        numOfLightingSpells[isInSecondArray]--;
      }
    }

    const int64_t nmLS0 = numOfLightingSpells[0];
    const int64_t nmLS1 = numOfLightingSpells[1];
    const int64_t nmLS = lightingSpells.size();
    assert(lightingSpells.size() ==
           numOfLightingSpells[0] + numOfLightingSpells[1]);
    const int64_t numOfLS = lightingSpells.size();
    // Make second array have numOfLS items since that's how we get the max
    // damage
    while (spellPowers[1].size() < numOfLS)
      transferItem(0);
    while (spellPowers[1].size() > numOfLS)
      transferItem(1);
    // keep the largest numOfLS spells in the second array
    while (!spellPowers[0].empty() && !spellPowers[1].empty() &&
           *spellPowers[0].rbegin() > *spellPowers[1].begin()) {
      transferItem(0);
      transferItem(1);
    }

    maximumDamage = spellPowerSum[0] + 2 * spellPowerSum[1];

    // if there arent at least numOfLS in the second array (which keeps the
    // numOfLSlargest spells) the maximum sum is achieved by using numOfLS-1
    // largest spells and one spell from the first array

    if (numOfLS == numOfLightingSpells[1] && numOfLS != 0) {
      maximumDamage -= *spellPowers[1].begin();
      if (!spellPowers[0].empty()) {
        maximumDamage += *spellPowers[0].rbegin();
      }
    }

    cout << maximumDamage << "\n";
  }

  return 0;
}
