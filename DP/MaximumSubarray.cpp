// Kadane's Algorithm - Maximum Subarray Sum O(N)
ll maximumSub(const vll& arr) {
    ll cur = 0, ans = -LINF;
    each(x, arr) {
        cur = max(x, cur + x);
        ckmax(ans, cur);
    }
    return ans;
}

