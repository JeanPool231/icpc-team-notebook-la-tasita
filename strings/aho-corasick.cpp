#include <bits/stdc++.h>
using namespace std;

// ALPHA is a compile-time constant: one contiguous allocation for all nodes.
// toIdx maps a character to [0, ALPHA) — swap freely for any alphabet.
template<int ALPHA>
struct AhoCorasick {
    function<int(char)> toIdx;
    vector<array<int, ALPHA>> go;
    vector<int> fail, dict, output;
    // output[v] = pattern index ending at v (-1 if none)

    AhoCorasick(function<int(char)> toIdx) : toIdx(toIdx) {
        go.emplace_back(); go.back().fill(-1);
        fail.push_back(0);
        dict.push_back(-1);
        output.push_back(-1);
    }

    int insert(const string& s, int patId) {
        int cur = 0;
        for (char c : s) {
            int ch = toIdx(c);
            if (go[cur][ch] == -1) {
                go[cur][ch] = go.size();
                go.emplace_back(); go.back().fill(-1);
                fail.push_back(0);
                dict.push_back(-1);
                output.push_back(-1);
            }
            cur = go[cur][ch];
        }
        output[cur] = patId;
        return cur;
    }

    // Build failure and dictionary links (call after all insertions)
    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            if (go[0][c] == -1) {
                go[0][c] = 0; // missing char at root loops back to root
            } else {
                fail[go[0][c]] = 0;
                q.push(go[0][c]);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            dict[u] = (output[fail[u]] != -1) ? fail[u] : dict[fail[u]];
            for (int c = 0; c < ALPHA; c++) {
                if (go[u][c] == -1) {
                    go[u][c] = go[fail[u]][c]; // compressed goto
                } else {
                    fail[go[u][c]] = go[fail[u]][c];
                    q.push(go[u][c]);
                }
            }
        }
    }

    void search(const string& text, const vector<string>& pats,
                function<void(int,int)> cb) {
        int cur = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            cur = go[cur][toIdx(text[i])];
            for (int v = cur; v > 0; v = dict[v])
                if (output[v] >= 0)
                    cb(i - (int)pats[output[v]].size() + 1, output[v]);
        }
    }

};

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   vector<string> patterns = {"he", "she", "his", "hers"};
//   AhoCorasick<26> ac([](char c) { return c - 'a'; });
//   for (int i = 0; i < (int)patterns.size(); ++i) ac.insert(patterns[i], i);
//   ac.build();
//   ac.search("ahishers", patterns, [&](int pos, int id) {
//     cout << patterns[id] << " at " << pos << "\n";
//   });
// }
