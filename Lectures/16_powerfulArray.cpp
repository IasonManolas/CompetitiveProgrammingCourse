#include <algorithm>
//#include <cmath>
// #include <cstdio>
#include <iostream>
#include <vector>
// #include <unordered_set>
#include <cmath>
#include <unordered_map>
using namespace std;

/*
 * I simply sort the queries following mo's algorithm and expand the active
 * range accordingly. I faced some difficulties regarding the int type to use
 * for solving that I read other solutions online. Overall time complexity:
 * θ(q*logq)+θ(n*sqrt(n))
 * */

template <typename T> vector<T> get_input_sequence(size_t n) {
  vector<T> sequence(n);

  for (size_t i = 0; i < n; ++i)
    cin >> sequence[i];
  return sequence;
}

struct Query {
  int l{0};
  int r{0};
  int inputIndex{0};
};

template <> vector<Query> get_input_sequence(size_t n) {
  vector<Query> sequence(n);

  for (size_t i = 0; i < n; ++i) {
    cin >> sequence[i].l;
    sequence[i].l--;
    cin >> sequence[i].r;
    sequence[i].r--;
    sequence[i].inputIndex = i;
  }
  return sequence;
}

int cnt[1000006];
int64_t answer = 0;
int64_t an[200005];
std::vector<int> v(200005);
void add(const int &pos) {
  answer -= (long long)v[pos] * (long long)cnt[v[pos]] * (long long)cnt[v[pos]];
  cnt[v[pos]]++;
  answer += (long long)v[pos] * (long long)cnt[v[pos]] * (long long)cnt[v[pos]];
}

void remove(const int &pos) {
  answer -= (long long)v[pos] * (long long)cnt[v[pos]] * (long long)cnt[v[pos]];
  cnt[v[pos]]--;
  answer += (long long)v[pos] * (long long)cnt[v[pos]] * (long long)cnt[v[pos]];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, q;
  cin >> n;
  cin >> q;
  v = get_input_sequence<int>(n);
  auto Q = get_input_sequence<Query>(q);
  const int nSqrt = sqrt(n);
  sort(Q.begin(), Q.end(), [&](const Query &a, const Query &b) { //θ(qlogq)
    if (a.l / nSqrt != b.l / nSqrt)
      return a.l < b.l;
    return a.r < b.r;
  });

  answer = v[0];
  cnt[v[0]] = 1;
  int currentL = 0;
  int currentR = 0;
  for (int qi = 0; qi < q; qi++) { //θ(n*sqrt(n))
    const int l = Q[qi].l;
    const int r = Q[qi].r;
    while (currentL < l) {
      remove(currentL++);
    }
    while (currentL > l) {
      add(--currentL);
    }
    while (currentR < r) {
      add(++currentR);
    }
    while (currentR > r) {
      remove(currentR--);
    }
    an[Q[qi].inputIndex] = answer;
  }

  for (size_t qi = 0; qi < q; qi++) {
    cout << an[qi] << "\n";
  }
  return 0;
}
