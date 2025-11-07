#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<
T,
  null_type,
  less<T>,                // use less_equal<T> if you want to allow duplicates (see note below)
  rb_tree_tag,
  tree_order_statistics_node_update>;

// --- Example usage ---
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ordered_set<int> s;

  s.insert(10);
  s.insert(20);
  s.insert(30);
  s.insert(40);

  // 1️⃣ Get element by index (0-based)
  cout << "Element at index 2: " << *s.find_by_order(2) << "\n"; // -> 30

  // 2️⃣ Get index of an element
  cout << "Index of 30: " << s.order_of_key(30) << "\n"; // -> 2

  // 3️⃣ Lower bound behavior
  cout << "Index where 25 would be inserted: " << s.order_of_key(25) << "\n"; // -> 2

  // 4️⃣ Iterate through all elements
  for (auto x : s) cout << x << " ";
  cout << "\n";

  // 5️⃣ Check if an element exists
  if (s.find(20) != s.end())
    cout << "20 exists in set\n";
}

