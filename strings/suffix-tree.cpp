#include <bits/stdc++.h>
using namespace std;
struct SuffixTree {
    struct Node {
        int ch[26], link, start, end, cnt;
        // end = INF for leaves (extends with each new char)
        Node(int s, int e) : link(0), start(s), end(e), cnt(0) {
            fill(ch, ch + 26, -1);
        }
        int len(int phase) { return min(end, phase + 1) - start; }
    };

    string s;
    vector<Node> t;
    int last, n;
    int activeNode, activeEdge, activeLen, remaining;
    int need;

    SuffixTree() {}

    void setSuffixLink(int v) {
        if (need != -1) t[need].link = v;
        need = v;
    }

    bool walkDown(int v) {
        if (activeLen >= t[v].len(n - 1)) {
            activeEdge += t[v].len(n - 1);
            activeLen  -= t[v].len(n - 1);
            activeNode  = v;
            return true;
        }
        return false;
    }

    void extend(int pos) {
        t[0].end = pos + 1;  // implicit: all leaves extend
        remaining++;
        need = -1;

        while (remaining > 0) {
            if (activeLen == 0) activeEdge = pos;
            int ae = s[activeEdge] - 'a';

            if (t[activeNode].ch[ae] == -1) {
                // Rule 2: create new leaf
                t[activeNode].ch[ae] = t.size();
                t.emplace_back(pos, INT_MAX);
                setSuffixLink(activeNode);
            } else {
                int nxt = t[activeNode].ch[ae];
                if (walkDown(nxt)) continue;

                if (s[t[nxt].start + activeLen] == s[pos]) {
                    // Rule 3: already exists — just extend active len
                    activeLen++;
                    setSuffixLink(activeNode);
                    break;
                }

                // Rule 2: split
                int split = t.size();
                t.emplace_back(t[nxt].start, t[nxt].start + activeLen);
                t[activeNode].ch[ae] = split;

                t[split].ch[s[pos] - 'a'] = t.size();
                t.emplace_back(pos, INT_MAX);
                t[nxt].start += activeLen;
                t[split].ch[s[t[nxt].start] - 'a'] = nxt;
                setSuffixLink(split);
            }

            remaining--;
            if (activeNode == 0 && activeLen > 0) {
                activeLen--;
                activeEdge = pos - remaining + 1;
            } else {
                activeNode = t[activeNode].link ? t[activeNode].link : 0;
            }
        }
        n = pos + 1;
    }

    void build(const string& str) {
        s = str + "$";
        n = 0;
        t.clear();
        t.emplace_back(0, 0);  // root
        last = activeNode = activeLen = activeEdge = remaining = 0;
        need = -1;
        for (int i = 0; i < (int)s.size(); i++) extend(i);
    }

    // DFS to collect suffix indices at leaves
    void dfs(int v, int depth, vector<int>& res) {
        bool leaf = true;
        for (int c = 0; c < 26; c++) {
            if (t[v].ch[c] == -1) continue;
            leaf = false;
            dfs(t[v].ch[c], depth + t[t[v].ch[c]].len(n - 1), res);
        }
        if (leaf) {
            // leaf: suffix index = n - 1 - depth  (n includes '$')
            res.push_back(n - 1 - depth);
        }
    }

    // Find all occurrences of pattern P in O(|P| + occ)
    vector<int> search(const string& p) {
        int v = 0, i = 0;
        while (i < (int)p.size()) {
            int c = p[i] - 'a';
            if (t[v].ch[c] == -1) return {};
            int nxt = t[v].ch[c];
            for (int j = t[nxt].start; j < t[nxt].end && i < (int)p.size(); j++, i++)
                if (s[j] != p[i]) return {};
            v = nxt;
        }
        vector<int> res;
        dfs(v, 0, res);
        sort(res.begin(), res.end());
        return res;
    }
};

// --- Longest Repeated Substring ---
// DFS: track string depth (total chars from root).
// Deepest internal node (>= 2 children) gives LRS.
string longestRepeated(SuffixTree& st) {
    string best = "";
    function<void(int, int)> dfs = [&](int v, int depth) {
        int childCount = 0;
        for (int c = 0; c < 26; c++) {
            if (st.t[v].ch[c] == -1) continue;
            childCount++;
            int nxt = st.t[v].ch[c];
            dfs(nxt, depth + st.t[nxt].len(st.n - 1));
        }
        // internal node with depth > best
        if (childCount > 0 && depth > (int)best.size()) {
            // walk back up to find the string — simplified via start pointer
            int start = st.t[v].start - (depth - st.t[v].len(st.n - 1));
            best = st.s.substr(max(0, start), depth);
        }
    };
    dfs(0, 0);
    return best;  // removes trailing '$' if present
}

// --- Count distinct substrings ---
// Each edge contributes (edgeLen) new distinct substrings.
// Total = sum of all edge lengths in the tree.
long long countDistinct(SuffixTree& st) {
    long long total = 0;
    // node 0 is root (no parent edge), skip
    for (int v = 1; v < (int)st.t.size(); v++)
        total += st.t[v].len(st.n - 1);
    return total - 1;  // subtract 1 for the empty string
}

// --- Longest Common Substring of two strings ---
// Build suffix tree of S1 + '#' + S2 + '$'
// Find deepest internal node whose subtree has leaves from both S1 and S2.
string longestCommon(const string& s1, const string& s2) {
    SuffixTree st;
    string combined = s1 + "#" + s2 + "$";
    st.build(combined);
    int n1 = s1.size();
    string best = "";

    // DFS: returns {has_s1_leaf, has_s2_leaf}
    function<pair<bool,bool>(int, int)> dfs = [&](int v, int dep) -> pair<bool,bool> {
        bool has1 = false, has2 = false;
        bool leaf = true;

        for (int c = 0; c < 26; c++) {
            if (st.t[v].ch[c] == -1) continue;
            leaf = false;
            int nxt = st.t[v].ch[c];
            auto [h1, h2] = dfs(nxt, dep + st.t[nxt].len(st.n - 1));
            has1 |= h1;
            has2 |= h2;
        }

        if (leaf) {
            int sufIdx = st.n - 1 - dep;
            has1 = (sufIdx < (int)n1);
            has2 = (sufIdx > (int)n1);  // > n1 skips the '#'
        }

        // internal node with leaves from both strings
        if (!leaf && has1 && has2 && dep > (int)best.size()) {
            // recover substring: edge ends at t[v].end, go back 'dep' chars
            int endPos = st.t[v].end;
            int startPos = endPos - dep;
            if (startPos >= 0 && endPos <= (int)st.s.size())
                best = st.s.substr(startPos, dep);
        }
        return {has1, has2};
    };

    dfs(0, 0);
    return best;
}

// --- Pattern matching demo ---

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   SuffixTree st;
//   st.build("banana");
//   cout << longestRepeated(st) << "\n";
//   cout << countDistinct(st) << "\n";
//   cout << longestCommon("banana", "ananas") << "\n";
//   for (int pos : st.search("ana")) cout << pos << " ";
//   cout << "\n";
// }
