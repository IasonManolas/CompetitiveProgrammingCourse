#include <cmath>
#include <iostream>
#include <vector>

/*
 * We use merge sort for counting the number of inversions. During the merge
 * step if we find that an element l in the left subarray is bigger than the
 * element in the right subarray r we increase the number of inversions by the
 * number of elements in the left subarray that come after the element we are
 * currently examining. We do that because since the two subarrays are sorted
 * all elements that come after element l will be greater than r and thus in the
 * merged array will come after r and thus will require inversions.
 *
 * Time complexity is the same as for merge sort O(nlogn) since we have logn
 * levels of d&c and each level processes n elements. Space complexity is θ(n)
 * */

std::vector<size_t> merge(const std::vector<size_t> &v, const size_t &p,
                          const size_t &q, const size_t &r,
                          size_t &numOfInversions) {
  const size_t mergedSize = r - p + 1;
  std::vector<size_t> mergedV(mergedSize);
  size_t li = p;
  size_t ri = q + 1;
  for (size_t k = 0; k < mergedSize; k++) {
    if (ri > r || (li <= q && v[li] <= v[ri])) {
      mergedV[k] = v[li++];
    } else {
      if (li <= q) {
        numOfInversions += q - li + 1;
      }
      mergedV[k] = v[ri++];
    }
  }

  return mergedV;
}

void mergeSort(std::vector<size_t> &v, const size_t &p, const size_t &r,
               size_t &numberOfInversions) {
  if (p < r) {
    const size_t q = std::floor(static_cast<double>(p + r) / 2.0);
    mergeSort(v, p, q, numberOfInversions);
    mergeSort(v, q + 1, r, numberOfInversions);

    std::vector<size_t> mergedV = merge(v, p, q, r, numberOfInversions);
    for (size_t i = 0; i < mergedV.size(); i++) {
      v[i + p] = mergedV[i];
    }
  }
}

int main() {
  size_t t;
  std::cin >> t;
  for (size_t testCase = 0; testCase < t; testCase++) {
    size_t N;
    std::cin >> N;
    std::vector<size_t> v;
    for (size_t integer = 0; integer < N; integer++) {
      size_t number;
      std::cin >> number;
      v.push_back(number);
    }
    size_t numberOfInversions = 0;
    mergeSort(v, 0, v.size() - 1, numberOfInversions);
    std::cout << numberOfInversions << std::endl;
  }
}
