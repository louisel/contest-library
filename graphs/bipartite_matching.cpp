/*
 * Bipartite matching using Kuhn's algorithm.
 * Runs in O(VE), but often faster.
 * Nodes on both sides are 0-indexed.
 * a := number of left nodes
 * b := number of right nodes
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

struct graph {
    int a, b;
    vector<vector<int>> adj;
    vector<int> visit, match;

    graph(int a, int b)
        : a(a), b(b), adj(a+b), visit(a+b, -1), match(a+b, -1) {}

    void edge(int i, int j) {
        adj[i].push_back(a+j);
        adj[a+j].push_back(i);
    }

    bool augment(int n, int run) {
        if (visit[n] == run)
            return false;
        visit[n] = run;
        for (int c : adj[n]) {
            // Can optimize by splitting the conditions across two loops,
            // and by randomizing the order of neighbors visited.
            if (match[c] == -1 || augment(match[c], run)) {
                match[n] = c, match[c] = n;
                return true;
            }
        }
        return false;
    }

    int matching() {
        // Can optimize by greedily initializing with direct matches,
        // and randomizing the order of nodes visited.
        int ret = 0;
        for (int i = 0; i < a; ++i)
            ret += augment(i, i);
        return ret;
    }
};

int main() {
    graph g(4, 4);
    g.edge(0, 0);
    g.edge(0, 1);
    g.edge(1, 0);
    g.edge(1, 1);
    g.edge(2, 0);
    g.edge(2, 1);
    g.edge(3, 1);
    g.edge(3, 2);
    g.edge(3, 3);
    assert(g.matching() == 3);
    cout << "All tests passed" << endl;
    return 0;
}
