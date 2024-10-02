/**
 * Author: Ann
 * Description: Solve system of n equations with m variables
 */

template <class T>
int solveLinear(vector<vector<T>> &A, vector<T> &b, vector<T> &x) { // return rank, or -1 if no solution
    int n = A.size(), m = x.size(), rank = 0;
    if (n > 0) assert(A[0].size() == m);

    vector<int> order(m);
    iota(order.begin(), order.end(), 0);

    for (int i = 0; i < n; i++) {
        T bv = 0;
        int br, bc;
        for (int r = i; r < n; r++) {
            for (int c = i; c < m; c++) {
                if (A[r][c] != 0) { // if dealing with floating point, replace with "abs(A[r][c]) > bv" to alleviate precision issues
                    bv = A[r][c];
                    br = r;
                    bc = c;
                }
            }
        }
        if (bv == 0) { // if dealing with floating point, replace with "bv <= EPS" to alleviate precision issues
            for (int r = i; r < n; r++) {
                if (b[r] != 0) return -1; // if dealing with floating point, replace with "abs(b[r]) > EPS" to alleviate precision issues
            }
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(order[i], order[bc]);
        for (int r = 0; r < n; r++) {
            swap(A[r][i], A[r][bc]);
        }
        T coef0 = 1 / A[i][i];
        for (int r = i + 1; r < n; r++) {
            T coef = coef0 * A[r][i];
            for (int c = i; c < m; c++) { // to get the determined values of x, replace with "for (int c = 0; c < m; c++) if (c != i) {"
                A[r][c] -= coef * A[i][c];
            }
            b[r] -= coef * b[i];
        }
        rank++;
    }

    fill(x.begin(), x.end(), 0);
    for (int i = rank - 1; i >= 0; i--) {
        b[i] /= A[i][i];
        x[order[i]] = b[i];
        for (int r = 0; r < i; r++) {
            b[r] -= b[i] * A[r][i];
        }
    }

    // to get the determined values of x, replace the above block "fill; for { }" with the following
    /*
    fill(x.begin(), x.end(), undefined);
    for (int i = 0; i < rank; i++) {
        for (int j = rank; j < m; j++) {
            if (A[i][j] != 0) goto fail; // if dealing with floating point, replace with "abs(A[i][j]) > EPS" to alleviate precision issues
        }
        x[order[i]] = b[i] / A[i][i];
        fail:;
    }
    */

    return rank;
}
