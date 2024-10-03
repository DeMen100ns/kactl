/**
 * Author: Ann
 * Description:
*/
template <class V = string, class C = char>
vector<int> getManacher(V _s, C dif0 = '$', C dif1 = '#', C dif2 = '&') {
    V s = [&]() -> V {
        int _n = _s.size();
        V s(2 * _n + 1, dif1);
        s[0] = dif0;
        for (int i = 0; i < _n; i++) {
            s[2 * i + 1] = _s[i];
        }
        s[2 * _n] = dif2;
        return s;
    }();
    int n = s.size();
    vector<int> z(n, 1);
    for (int i = 1, l = 0, r = 0; i < n - 1; i++) {
        if (i < r) {
            z[i] = min(r - i, z[l + r - i - 1]);
        }
        while (s[i - z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            r = i + z[i];
            l = i - z[i] + 1;
        }
        if (i & 1) {
            z[i] = (z[i] - 1) / 2 * 2 + 1;
        } else {
            z[i] = z[i] / 2 * 2;
        }
    }
    return vector<int>(z.begin() + 1, z.end() - 1);
}
