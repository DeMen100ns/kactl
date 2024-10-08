/**
 * Author: Ann
 * Date: 2024
 * Description: Palindrome Tree
 */

struct PalinTree {
    struct Node {
        int len;
        map<char, int> adj; // should replace this if alphabet size is small
        int link;
        int val; // number of endpos's of this palindrome
    };

    string s;
    int cur;
    vector<Node> pt;

    PalinTree(string s) : s(s), pt(2) {
        pt[0].len = -1;
        pt[0].link = 0;
        pt[0].val = 0;
        pt[1].len = 0;
        pt[1].link = 0;
        pt[1].val = 0;
        cur = 0;
    }

    void add(int i) {
        while (true) {
            if (i - 1 - pt[cur].len >= 0 && s[i - 1 - pt[cur].len] == s[i]) {
                break;
            }
            cur = pt[cur].link;
        }

        if (pt[cur].adj.count(s[i])) {
            cur = pt[cur].adj[s[i]];
            return;
        }

        int link = cur;
        cur = (int)pt.size();
        pt.push_back({});
        pt[cur].len = pt[link].len + 2;
        pt[link].adj[s[i]] = cur;

        if (pt[cur].len == 1) {
            pt[cur].link = 1;
            pt[cur].val = 1;
            return;
        }

        while (true) {
            link = pt[link].link;
            if (i - 1 - pt[link].len >= 0 && s[i - 1 - pt[link].len] == s[i]) {
                pt[cur].link = pt[link].adj[s[i]];
                pt[cur].val = pt[pt[cur].link].val + 1;
                return;
            }
        }

        assert(0);
    }
};
