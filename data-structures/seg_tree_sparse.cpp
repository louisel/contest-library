/*
 * Sparse segment tree supporting an arbitrary monoid.
 *   (See https://en.wikipedia.org/wiki/Monoid)
 * Represented as a perfect binary tree, identity-initialized.
 * Root is 1. Parent of node i is i/2. Children of node i are 2*i and 2*i+1.
 * s := size (number of leaves)
 * v := underlying array
 * id := monoid identity
 * op := monoid operation (not necessarily commutative)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;
using ll = long long;

template <typename Monoid>
struct seg_tree_sparse {
    using T = typename Monoid::T;
    Monoid m;
    ll s;
    unordered_map<ll,T> v;

    seg_tree_sparse(ll n, Monoid m = Monoid()): m(m) {
        for (s = 1; s < n; ) {
            s <<= 1;
        }
    }

    void update(ll i, T t) {
        i += s;
        v[i] = t;
        for (i /= 2; i > 0; i /= 2) {
            v[i] = m.op(v.count(2*i)   ? v[2*i]   : m.id,
                        v.count(2*i+1) ? v[2*i+1] : m.id);
        }
    }

    T query(ll i, ll j) {
        i += s, j += s;
        T l = m.id, r = m.id;
        for (; i <= j; i /= 2, j /= 2) {
            if (i % 2 == 1) l = m.op(l, v.count(i) ? v[i] : m.id), ++i;
            if (j % 2 == 0) r = m.op(v.count(j) ? v[j] : m.id, r), --j;
        }
        return m.op(l, r);
    }
};

struct monoid {
    using T = int;
    static constexpr T id = numeric_limits<T>::min();
    static T op(T a, T b) { return max(a, b); }
};

int main() {
    int n = 100;
    vector<int> v(n, numeric_limits<int>::min());
    seg_tree_sparse<monoid> s(n);
    for (int t = 0; t < 1000000; ++t) {
        if (rand() % 2) {
            int i = rand() % n, val = rand() % 100;
            v[i] = val;
            s.update(i, val);
        } else {
            int l = rand() % n, r = rand() % n;
            if (r < l)
                swap(l, r);
            int max_elem = *max_element(v.begin() + l, v.begin() + r + 1);
            assert(s.query(l, r) == max_elem);
        }
    }
    cout << "All tests passed" << endl;
    return 0;
}
