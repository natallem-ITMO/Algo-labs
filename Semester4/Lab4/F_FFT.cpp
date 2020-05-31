#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <complex>
#include <cmath>


using namespace std;
using cx = complex<double>;

const double PI = std::acos(-1);

vector<cx> fft(vector<cx> &a, cx w) {
    long long n = a.size();
    if (n == 1) return {a[0]};
    vector<cx> a0(n/2);
    vector<cx> a1(n/2);
    for (long long i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    auto w2 = w * w;
    auto u0 = fft(a0, w2);
    auto u1 = fft(a1, w2);

    vector<cx> u(n);
    cx wi = 1;
    for (long long i = 0; i < n; i++) {
        u[i] = u0[i % (n / 2)] + wi * u1[i % (n / 2)];
        wi *= w;
    }
    return u;
}

long long find_min_pow_2(long long size) {
    long long cur_size = 1;
    while (cur_size < size) {
        cur_size <<= 1;
    }
    return cur_size;
}


void fillLast(vector<long long> &previous, long long new_size) {
    vector<long long> newEmptyVector(new_size, 0);
    for (long long i = 0; i < previous.size(); i++) {
        newEmptyVector[i] = previous[i];
    }
    previous = newEmptyVector;
}

void prepareVec(vector<long long> &a, vector<long long> &b) {
    long long new_size = find_min_pow_2(max(a.size(), b.size())) * 2;
    fillLast(a, new_size);
    fillLast(b, new_size);
}

void scalarMul(vector<cx> &u, vector<cx> &v) {
    for (long long i = 0; i < u.size(); i++) {
        u[i] *= v[i];
    }
}


vector<long long> reverseFFT(vector<cx> &vec, cx w) {
    auto reverse = fft(vec, w);
    long long n = vec.size();
    for (long long i = 1, j = vec.size() - 1; i < n / 2; i++, j--) {
        swap(reverse[i], reverse[j]);
    }
    vector<long long> res(n);
    for (long long i = 0; i < n; i++) {
        reverse[i] /= n;
        res[i] = (long long) (reverse[i].real() + 0.5);

    }
    return res;
}

vector<long long> mul(vector<long long> &a, vector<long long> &b) {
    prepareVec(a, b);
    vector<cx> aa(a.begin(), a.end());
    vector<cx> bb(b.begin(), b.end());
    double dd = 2 * PI / ((double) aa.size());
    cx w = exp(1i * dd);
    auto u = fft(aa, w);
    auto v = fft(bb, w);
    scalarMul(u, v);
    return reverseFFT(u, w);
}


void mulNumberString(string &s1, string &s2) {
    vector<long long> num1;
    vector<long long> num2;
    int sign = 1;

    for (long long i = 0; i < s1.size(); i++) {
        if (s1[i] == '-')
            sign *= -1;
        else
            num1.push_back(s1[i] - '0');
    }
    for (long long i = 0; i < s2.size(); i++) {
        if (s2[i] == '-')
            sign *= -1;
        else
            num2.push_back(s2[i] - '0');
    }
    vector<long long> res = mul(num1, num2);
    long long count = 0;
    long long start;
    for (start = res.size() - 1; start >= 0; start--) {
        if (res[start] == 0) continue;
        else break;
    }
    if (start == -1) {
        cout << 0;
        return;
    }

    for (long long i = start; i >= 0; i--) {
        long long &t = res[i];
        if (t == 0 && count == 0) continue;
        t += count;
        count = t / 10;
        t %= 10;
    }

    if (sign < 0) cout << "-";

    if (count != 0) cout << count;
    for (long long i = 0; i <= start; i++) {
        cout << res[i];
    }

}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s1, s2;
    cin >> s1 >> s2;
    mulNumberString(s1, s2);
    return 0;
}
