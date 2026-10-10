struct Trie {

  static const int A = 26; // alphabet size
  struct Node {
    int nxt[A], cnt = 0, end = 0; // cnt: words passing here, end: words ending here
    Node() { memset(nxt, -1, sizeof nxt); }
  };
  vector<Node> t;
  Trie() : t(1) {}
  void insert(const string& s) {
    int x = 0;
    for (char c : s) {
      int k = c - 'a';
      if (t[x].nxt[k] < 0) { t[x].nxt[k] = t.size(); t.emplace_back(); }
      x = t[x].nxt[k];
      t[x].cnt++;
    }
    t[x].end++;
  }
  int find(const string& s) { // node of s, or -1
    int x = 0;
    for (char c : s) {
      x = t[x].nxt[c - 'a'];
      if (x < 0) return -1;
    }
    return x;
  }
  int count(const string& s) { int x = find(s); return x < 0 ? 0 : t[x].end; }  // exact matches
  int prefix(const string& s) { int x = find(s); return x < 0 ? 0 : t[x].cnt; } // words with prefix s
  bool erase(const string& s) { // removes one copy, false if absent
    if (!count(s)) return false;
    int x = 0;
    for (char c : s) { x = t[x].nxt[c - 'a']; t[x].cnt--; }
    t[x].end--;
    return true;
  }
};
