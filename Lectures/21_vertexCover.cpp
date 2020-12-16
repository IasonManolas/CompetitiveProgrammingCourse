#include <algorithm>
//#include <cmath>
// #include <cstdio>
#include <iostream>
#include <vector>
// #include <unordered_set>
using namespace std;

vector<std::pair<int, int>> get_input_sequence(size_t n) {
  vector<std::pair<int, int>> sequence(n);

  for (size_t i = 0; i < n; ++i) {
    cin >> sequence[i].first >> sequence[i].second;
    sequence[i].first--;
    sequence[i].second--;
  }
  return sequence;
}

/*
 * Main idea:
 * 1)Compute the size of the largesst independent set of the tree lis
 * 2) The minimum vertex cover is computed as the number of nodes not in the
 * lis. This set of nodes covers all the edges since if it didnt there would
 * exist an edge that would not be covered by the lis and thus the lis would not
 * be the maximum set that can be constructed. The lis is constructed by
 * choosing to insert a node in case the sum of the number of nodes in the
 * independent set of the subtree rooted at each of its children of this node is
 * less or equal to the sum of number of nodes that comprise the lis of the
 * subtrees rooted at each of the gradchildren of this node. We make the tree
 * rooted by simply choosing as a root the first node.
 * */

vector<vector<int>> adjacentNodes;
vector<bool> visited;
vector<int> vc;
int vertexCover(int vi) {
  visited[vi] = true;
  if (adjacentNodes[vi].size() == 1 && visited[adjacentNodes[vi][0]]) { // leaf
    visited[vi] = false;
    return 1;
  }

  int childrenVertexCoverSum = 0;
  int grandchildrenVertexCoverSum = 0;
  for (int childIndex : adjacentNodes[vi]) {
    if (visited[childIndex]) { // adjacent node contains the parent as well
      continue;
    }

    if (vc[childIndex] == -1) {
      vc[childIndex] = vertexCover(childIndex);
    }
    childrenVertexCoverSum += vc[childIndex];
    // grandchildren
    for (int grandchildIndex : adjacentNodes[childIndex]) {
      if (visited[grandchildIndex]) {
        continue;
      }
      if (vc[grandchildIndex] == -1) {
        vc[grandchildIndex] = vertexCover(grandchildIndex);
      }
      grandchildrenVertexCoverSum += vc[grandchildIndex];
    }
  }

  vc[vi] = max(childrenVertexCoverSum, 1 + grandchildrenVertexCoverSum);
  visited[vi] = false;
  return vc[vi];
}

using Edge = pair<int, int>;
int main() {
  std::ios_base::sync_with_stdio(false);
  size_t n;
  cin >> n;
  adjacentNodes.resize(n);
  visited.resize(n, false);
  vc.resize(n, -1);
  auto E = get_input_sequence(n - 1);
  for (Edge e : E) {
    adjacentNodes[e.first].push_back(e.second);
    adjacentNodes[e.second].push_back(e.first);
  }

  std::cout << n - vertexCover(0) << std::endl;

  return 0;
}
