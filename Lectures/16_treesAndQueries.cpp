#include <algorithm>
#include <cmath>
// #include <cstdio>
#include <iostream>
#include <list>
#include <vector>
// #include <unordered_set>
using namespace std;

/*
 * I did not solve this on my own. After trying to solve it I looked at the
 * solution provided on https://www.codeleading.com/article/12342982075/
 * which I describe below:
 * The main idea is to map the queries to a range and based on that to apply
 * Mo's algorithm for sorting the queries. The queries are mapped to ranges by
 * using a depth first search. The add and remove functions for adjusting the
 * active range use a num array that contains the number of instances of a
 * specific color in the active range and the array sum of which the kth element
 * is the number of colors with k instances in the active range. Time
 * complexity: θ(n*sqrt(n))
 * */

const int N = 1e5 + 10;
struct Query {
  int l, r, k, id;
};

int n, m, sum[N], cl = 1, cr, c[N], df_start[N], df_end[N], dfn[N], cnt, nSqrt,
                  num[N], nodes[N];

vector<vector<int>> adjacentNodes;
vector<int> colors;
vector<Query> q;

void add(int nodeIndex) { sum[++num[colors[nodeIndex]]]++; }

void remove(int nodeIndex) { sum[num[colors[nodeIndex]]--]--; }

void dfs(int nodeIndex, int parrent) {
  df_start[nodeIndex] = ++cnt;
  dfn[cnt] = nodeIndex;
  for (auto neighbor : adjacentNodes[nodeIndex])
    if (neighbor != parrent) {
      dfs(neighbor, nodeIndex);
    }
  df_end[nodeIndex] = cnt;
}

int mosCmp(Query a, Query b) {
  return a.l / nSqrt == b.l / nSqrt ? a.r < b.r : a.l < b.l;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  nSqrt = sqrt(n);
  colors.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> colors[i];
  }
  adjacentNodes.resize(n + 1);
  for (int ei = 0; ei < n - 1; ei++) {
    int a, b;
    cin >> a >> b;
    adjacentNodes[a].push_back(b);
    adjacentNodes[b].push_back(a);
  }
  dfs(1, 1);

  q.resize(m + 1);
  // read queries
  for (int i = 1, v, k; i <= m; i++) {
    cin >> v >> k;
    q[i] = Query{df_start[v], df_end[v], k, i};
  }
  // sort queries acording to their range
  std::sort(q.begin() + 1, q.begin() + 1 + m, mosCmp);

  // process the queries
  vector<int> res(m + 1, 0);
  for (int i = 1, L, R; i <= m; i++) {
    L = q[i].l, R = q[i].r;
    while (L < cl)
      add(dfn[--cl]);
    while (R > cr)
      add(dfn[++cr]);
    while (L > cl)
      remove(dfn[cl++]);
    while (R < cr)
      remove(dfn[cr--]);
    res[q[i].id] = sum[q[i].k];
  }

  for (int i = 1; i <= m; i++)
    printf("%d\n", res[i]);

  return 0;
}
