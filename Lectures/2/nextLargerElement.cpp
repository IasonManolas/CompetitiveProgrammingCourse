#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    size_t tcs;
   cin>>tcs;
   for(size_t tc=0;tc<tcs;tc++){
 size_t N;
 std::cin >> N;
 vector<size_t> A(N);
 for (size_t i = 0; i < N; i++) {
   cin >> A[i];
 }

 deque<size_t> Q;
 vector<size_t> results(N);
 results[N - 1] = -1;
 Q.push_front(N - 1);
 for (int i = N - 2; i >= 0; i--) {
   while (!Q.empty() && A[i] >= A[Q.front()]) {
     Q.pop_front();
   }
   if (Q.empty()) {
     results[i] = -1;
   } else {
     results[i] = A[Q.front()];
   }
   Q.push_front(i);
 }
 for (size_t res : results) {
   if (res == size_t(0) - 1)
     cout << -1 << " ";
   else
     std::cout << res << " ";
 }
 cout<<"\n";

}

 return 0;
}
