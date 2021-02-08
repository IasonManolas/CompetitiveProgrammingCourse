#include <algorithm>
#include <assert.h>
#include <iostream>
#include <set>
#include <vector>
/*
 * Initially we create a set of non-overlapping "frog segments" which are mapped
 * to a frog. Every mosquito that lands within this segment is eaten by the frog
 * of this segment. By creating this data structure we are able to determine
 * which frog eats a mosquito using a predecessor query. Before constructing
 * this non-overlapping set of frog segments we sort the segments in decreasing
 * order of beginning. That way we need to adjust the ending points of the frog
 * segments already in the set that overlap with the new segment. This
 * adjustment is done in the checkNextSegments function.The main idea is to keep
 * the invariant of non-overlapping segments.
 *
 * Having the non-overlapping frog segment set we start processing the mosquitos
 * that land. For every incoming mosquito we check whether there exists a frog
 * that is able to eat it.
 * If no frog can eat the landing mosquito then we store
 * the mosquito for the future in case the tongue of a frog gets elongated
 * allowing it to eat a previously landed mosquitoes.
 * If there exists a frog which can eat the landed mosquito we increase its
 * tongue accordingly and check whether the frog is able to eat additional
 * mosquitoes that landed previously but weren't eaten. After the frog eats all
 * the mosquitoes it can we need to resolve (possibly) new generated overlaps in
 * the frog segment set. Thus we need to adjust the segments that follow the
 * segment where the mosquito landed. For doing that we simply call the same
 * function we used to resolve the overlaps while constructing the segment set
 * (checkNextSegments).
 *
 * After all mosquitoes landed we output the result.
 *
 * Time complexity
 * Non overlapping segment construction costs O(nlogn) because we can remove at
 * most n segments.
 * Eating mosquitos costs O(mlogn) since each mosquito can be
 * added and removed at most once Overall time complexity is O((n+m)logn)
 * */

using namespace std;

struct Frog {
  int64_t c{0};
  int64_t t{0};
};

struct FrogSegment {
  int64_t begin;
  int64_t end;
  int64_t frogIndex;
};

struct Mosquito {
  int64_t p;
  int64_t b;
};

struct MosquitoComp {
  bool operator()(const Mosquito &m0, const Mosquito &m1) const {
    return m0.p < m1.p;
  }
};

struct FrogSegmentComp {
  bool operator()(const FrogSegment &fs0, const FrogSegment &fs1) const {
    return fs0.begin < fs1.begin;
  }
} frogSegmentComp;

using FrogSegmentSetIterator = set<FrogSegment, FrogSegmentComp>::iterator;
set<FrogSegment, FrogSegmentComp> frogSegments;

void checkNextSegments(const FrogSegment &newFrogSegment,
                       FrogSegmentSetIterator &nextSegmentIt) {
  // remove all segments that are fully contained in the new segment
  while (nextSegmentIt != frogSegments.end() &&
         nextSegmentIt->begin <= newFrogSegment.end &&
         nextSegmentIt->end <= newFrogSegment.end) {
    nextSegmentIt = frogSegments.erase(nextSegmentIt); // amortized O(1)
  }

  // If the new segment overlaps with the next adjust the begining of the next
  // segment so that they do not overlap
  if (nextSegmentIt != frogSegments.end() &&
      nextSegmentIt->begin <= newFrogSegment.end) {
    const FrogSegment updatedNextSegment{
        newFrogSegment.end + 1, nextSegmentIt->end, nextSegmentIt->frogIndex};
    frogSegments.insert(frogSegments.erase(nextSegmentIt), updatedNextSegment);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t fn, mn;
  cin >> fn;
  cin >> mn;

  std::vector<Frog> frogs(fn);
  std::vector<FrogSegment> inputFrogSegments(fn);
  // Read frog positions and tongues
  for (int64_t fi = 0; fi < fn; fi++) {
    int64_t x, t;
    cin >> x;
    cin >> t;
    frogs[fi].t = t;

    FrogSegment newFrogSegment{x, x + t, fi};
    inputFrogSegments[fi] = newFrogSegment;
  }

  // Construction of non-overlapping frog segments
  std::sort(inputFrogSegments.rbegin(), inputFrogSegments.rend(),
            frogSegmentComp);
  for (int64_t fi = 0; fi < fn; fi++) {
    frogSegments.insert(inputFrogSegments[fi]); // O(logn)
    FrogSegmentSetIterator nextSegmentIt =
        frogSegments.upper_bound(inputFrogSegments[fi]); // O(logn)
    checkNextSegments(inputFrogSegments[fi], nextSegmentIt);
  }

  // Read mosquitos and proccess them
  std::multiset<Mosquito, MosquitoComp> aliveMosquitoes;
  while (mn--) {
    Mosquito m;
    cin >> m.p;
    cin >> m.b;
    FrogSegmentSetIterator nextSegmentIt =
        frogSegments.upper_bound(FrogSegment{m.p, 0});
    FrogSegmentSetIterator previousSegmentIt = std::prev(nextSegmentIt);

    const bool isBeforeBegin = frogSegments.begin() == nextSegmentIt;
    const bool noTongueIsLongEnough = previousSegmentIt->end < m.p;
    const bool noFrogCanEatIt = isBeforeBegin || noTongueIsLongEnough;
    if (noFrogCanEatIt) {
      aliveMosquitoes.insert(m);
      continue;
    }

    int tongueAddition = m.b;
    frogs[previousSegmentIt->frogIndex].c++;
    // Check whether the frog can eat additional mosquitoes after the tongue
    // extension. We perform at most m successor queries because every mosquito
    // can be inserted and removed at most once.
    auto mosquitoIt =
        aliveMosquitoes.lower_bound(Mosquito{previousSegmentIt->begin, 0});
    while (mosquitoIt != aliveMosquitoes.end() &&
           (mosquitoIt->p <= (previousSegmentIt->end + tongueAddition) &&
            mosquitoIt->p >= previousSegmentIt->begin)) {
      tongueAddition += mosquitoIt->b;
      frogs[previousSegmentIt->frogIndex].c++;
      mosquitoIt = aliveMosquitoes.erase(mosquitoIt);
    }

    frogs[previousSegmentIt->frogIndex].t += tongueAddition;
    FrogSegment newFrogSegment{previousSegmentIt->begin,
                               previousSegmentIt->end + tongueAddition,
                               previousSegmentIt->frogIndex};
    frogSegments.insert(frogSegments.erase(previousSegmentIt), newFrogSegment);
    checkNextSegments(newFrogSegment, nextSegmentIt);
  }

  for (const Frog &f : frogs) {
    cout << f.c << " " << f.t << endl;
  }

  return 0;
}
