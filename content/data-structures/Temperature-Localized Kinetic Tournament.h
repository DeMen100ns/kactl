/**
 * Author: DeMen100ns
 * Date: 2024-01-01
 * Description: 
 * n functions y=0x+0 by default, modifiable at any time, queries for maximum y, queries must be non-decreasing by x
 * node localizes temperature, x = 0 for each node by default, laziable
 */

const long long INF = (long long)4e18;

int sgn(long long x) {
    if (x == 0) return 0;
    return x > 0 ? +1 : -1;
}

long long rationalFloor(long long a, long long b) {
    return a / b - (a % b != 0 && sgn(a) != sgn(b));
}

struct Tournament {
    struct Node {
        long long a, b;
        int t, dt;
        long long melting_dt;
        Node() {}
        Node(long long a, long long b, int t) : a(a), b(b), t(t), dt(0), melting_dt(INF) {}
        long long operator*() { return a * t + b; }
        Node operator+(Node y) {
            Node x = *this;
            if (*x < *y) swap(x, y);
            long long xy_melting_dt = x.a == y.a ? INF : rationalFloor(-(x.a * x.t + x.b - y.a * y.t - y.b), x.a - y.a);
            xy_melting_dt = xy_melting_dt < 0 ? INF : xy_melting_dt + 1;
            Node res = x;
            res.melting_dt = min({xy_melting_dt, x.melting_dt, y.melting_dt});
            res.dt = 0;
            return res;
        }
    };

    int n;
    vector<Node> nodes;

    Tournament(int n) : n(n), nodes(4 * n, Node(0, 0, 0)) {}

    void apply(int idx, int dt) {
        nodes[idx].t += dt;
        nodes[idx].dt += dt;
        nodes[idx].melting_dt -= dt;
        if (nodes[idx].melting_dt <= 0) {
            down(idx);
            nodes[idx] = nodes[2 * idx + 1] + nodes[2 * idx + 2];
        }
    }

    void down(int idx) {
        apply(2 * idx + 1, nodes[idx].dt);
        apply(2 * idx + 2, nodes[idx].dt);
        nodes[idx].dt = 0;
    }

    void modify(int i, long long a, long long b, int t, int idx, int l, int r) {
        if (l + 1 == r) {
            nodes[idx] = Node(a, b, t);
        } else {
            down(idx);
            int m = (l + r) >> 1;
            if (i < m) modify(i, a, b, t, 2 * idx + 1, l, m);
            else modify(i, a, b, t, 2 * idx + 2, m, r);
            nodes[idx] = nodes[2 * idx + 1] + nodes[2 * idx + 2];
        }
    }

    void modify(int i, long long a, long long b, int t) { modify(i, a, b, t, 0, 0, n); }
    void heaten(int dt) { apply(0, dt); }
    Node winner() { return nodes[0]; }
};
