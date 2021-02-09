#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * We sort the teams in decreasing order of power. Then we proccess each team in
 * that order and if none of the team members has already a team we form the
 * team and save it. Time complexity is O(nlog(2n))->O(nlogn) for sorting the
 * teams. Space complexity is θ(n)
 * */

int main() {
  size_t N;
  cin >> N;

  const size_t numberOfPossibleTeams = N * (2 * N - 1);

  using TeamPower = size_t;
  using PlayerIndex = size_t;
  using Team = tuple<TeamPower, PlayerIndex, PlayerIndex>;
  // Read the input
  std::vector<Team> teams(numberOfPossibleTeams, Team(0, 0, 0));
  size_t i = 1, j = 0, maxCol = 0;
  for (size_t teamIndex = 0; teamIndex < numberOfPossibleTeams; teamIndex++) {
    TeamPower teamPower;
    cin >> teamPower;
    teams[teamIndex] = make_tuple(teamPower, i, j);

    if (maxCol == j) {
      i++;
      maxCol++;
      j = 0;
    } else {
      j++;
    }
  }

  // O(nlogn)
  std::sort(teams.begin(), teams.end(), [&](const Team &tp0, const Team &tp1) {
    return std::get<0>(tp0) > std::get<0>(tp1);
  });

  // O(n) 2n size
  std::vector<bool> hasTeam(2 * N, false);
  std::vector<size_t> result(2 * N, 0);
  for (const auto team : teams) {
    TeamPower tp;
    PlayerIndex pi0, pi1;
    std::tie(tp, pi0, pi1) = team;
    if (hasTeam[pi0] || hasTeam[pi1]) {
      continue;
    }

    result[pi0] = pi1;
    hasTeam[pi0] = true;
    result[pi1] = pi0;
    hasTeam[pi1] = true;
  }

  for (auto teammate : result) {
    cout << teammate + 1 << " ";
  }
  return 0;
}
