#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

/*
 * We use a greedy approach and choose the meetings by the earliest ending time.
 * Time complexity is O(nlogn) for sorting the meetings
 * Space complexity Θ(n)
 * */

void maxMeetings(int *, int *, int);

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int start[n], end[n];
    for (int i = 0; i < n; i++)
      cin >> start[i];

    for (int i = 0; i < n; i++)
      cin >> end[i];

    maxMeetings(start, end, n);
    cout << endl;
  }
  return 0;
} // } Driver Code Ends

struct Meeting {
  int start;
  int end;
  int meetingIndex;
  bool operator<(const Meeting &m) const {
    return end != m.end ? end < m.end : meetingIndex < m.meetingIndex;
  }
};

void maxMeetings(int start[], int end[], int n) {
  vector<Meeting> meetings = vector<Meeting>(n);
  for (int i = 0; i < n; i++) {
    meetings[i] = Meeting{start[i], end[i], i + 1};
  }
  std::sort(meetings.begin(), meetings.end());

  int currentEndTime = meetings[0].end;
  int meetingsCounter = 1;
  cout << meetings[0].meetingIndex;
  for (int i = 1; i < n; i++) {
    if (meetings[i].start > currentEndTime) {
      meetingsCounter++;
      currentEndTime = meetings[i].end;
      cout << " " << meetings[i].meetingIndex;
    }
  }
}
