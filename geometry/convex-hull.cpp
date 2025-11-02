#include <bits/stdc++.h>

using namespace std;

struct point {
  double x, y;
  point() { x = y = 0; }
  point(double _x, double _y) : x(_x), y(_y) {}
  bool operator == (point const& t) const {
    return x == t.x && y == t.y;
  }
};

int orientation(point a, point b, point c) {
  double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
  if (v < 0) return -1; // clockwise
  if (v > 0) return +1; // counter-clockwise
  return 0;
}

bool cw(point a, point b, point c, bool include_collinear) {
  int o = orientation(a, b, c);
  return o < 0 || (include_collinear && o == 0);
}
bool collinear(point a, point b, point c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<point>& a, bool include_collinear = false) {
  point p0 = *min_element(a.begin(), a.end(), [](point a, point b) {
      return make_pair(a.y, a.x) < make_pair(b.y, b.x);
      });
  sort(a.begin(), a.end(), [&p0](const point& a, const point& b) {
      int o = orientation(p0, a, b);
      if (o == 0)
      return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
      < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
      return o < 0;
      });
  if (include_collinear) {
    int i = (int)a.size()-1;
    while (i >= 0 && collinear(p0, a[i], a.back())) i--;
    reverse(a.begin()+i+1, a.end());
  }

  vector<point> st;
  for (int i = 0; i < (int)a.size(); i++) {
    while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
      st.pop_back();
    st.push_back(a[i]);
  }

  if (include_collinear == false && st.size() == 2 && st[0] == st[1])
    st.pop_back();

  a = st;
}

double area(const vector<point>& fig) {
  double res = 0;
  for (unsigned i = 0; i < fig.size(); i++) {
    point p = i ? fig[i - 1] : fig.back();
    point q = fig[i];
    res += (p.x - q.x) * (p.y + q.y);
  }
  return fabs(res) / 2;
}


// example use case
void solve() {
  double n,r; 
  cin >> n >> r;

  vector<point> coords(n);
  for(int i = 0; i < n; i++) {
    cin >> coords[i].x >> coords[i].y;
  }

  auto dist = [](point &a, point&b) {
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
  };

  const double PI = 3.141516;
  double cir = 2 * PI * r;
  convex_hull(coords);

  double per = 0; 
  coords.push_back(coords[0]);
  for(int i = 1; i < coords.size(); i++) {
    per +=  dist(coords[i-1],coords[i]);
  }

  int ans = round(per+cir);
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
