struct BitTrie {
  static const int B = 30; // bits (use 62 with ll values)
  struct Node {
    int nxt[2] = {-1, -1}, cnt = 0;
  };
  vector<Node> t;
  BitTrie() : t(1) {}
  void insert(int v, int d = 1) { // d = 1 insert, d = -1 erase (the value must exist)
    int x = 0;
    for (int b = B-1; b >= 0; b--) {
      int k = v>>b & 1;
      if (t[x].nxt[k] < 0) { t[x].nxt[k] = t.size(); t.emplace_back(); }
      x = t[x].nxt[k];
      t[x].cnt += d;
    }
  }
  int maxXor(int v) { // max of v ^ u over u in the set (set must be non-empty)
    int x = 0, res = 0;
    for (int b = B-1; b >= 0; b--) {
      int k = v>>b & 1;
      int y = t[x].nxt[k^1];
      if (y >= 0 && t[y].cnt > 0) { res |= 1<<b; x = y; }
      else x = t[x].nxt[k];
    }
    return res;
  }
  int countLess(int v, int lim) { // number of u in the set with (v ^ u) < lim
    int x = 0, res = 0;
    for (int b = B-1; b >= 0 && x >= 0; b--) {
      int k = v>>b & 1, l = lim>>b & 1;
      if (l) {
        int y = t[x].nxt[k];
        if (y >= 0) res += t[y].cnt; // xor bit 0 < 1, whole subtree counts
        x = t[x].nxt[k^1];
      } else x = t[x].nxt[k];
    }
    return res;
  }
};
