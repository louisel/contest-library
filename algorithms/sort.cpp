/*
 * Counting sort: O(n + max). Can be 3-5 times faster than std::sort
 * for n on the order of 1000 or so. Also stable.
 * f := a function mapping elements to integers in the range [0, max).
 */
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <typename Iterator, typename Mapping>
void counting_sort(Iterator begin, Iterator end, int max, Mapping f) {
    using T = typename Iterator::value_type;
    vector<int> pos(max+1);
    for (auto it = begin; it != end; ++it)
        ++pos[f(*it)+1];
    for (int i = 1; i < max; ++i)
        pos[i] += pos[i-1];
    vector<T> sorted(distance(begin, end));
    for (auto it = begin; it != end; ++it)
        sorted[pos[f(*it)]++] = move(*it);
    for (auto& val : sorted)
        *(begin++) = move(val);
}

int main() {
    int n = 1000, iter = 10000;
    vector<int> a(n), b(n);
    for (int t = 0; t < iter; ++t) {
        for (int i = 0; i < n; ++i)
            a[i] = b[i] = rand() % n;
        sort(a.begin(), a.end());
        counting_sort(b.begin(), b.end(), n, [] (int n) {
            return n;
        });
        assert(a == b);
    }
    cout << "All tests passed" << endl;
    return 0;
}
