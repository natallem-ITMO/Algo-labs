#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <complex>
#include <cmath>
#include <iomanip>


using namespace std;
using cx = complex<double>;

const double PI = std::acos(-1);

vector<cx> fft(vector<cx> &a, cx w) {
    long long n = a.size();
    if (n == 1) return {a[0]};
    vector<cx> a0(n / 2);
    vector<cx> a1(n / 2);
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

string genLongNum() {
    long long l = 250000;
    string s;
    for (long long i = 0; i < l; i++) {
        s += '1';
    }
    s += "\n";
    return s;
}


typedef complex<double> base;

void fft2(vector<base> &a, bool invert) {
    long long n = (long long) a.size();
    if (n == 1) return;

    vector<base> a0(n / 2), a1(n / 2);
    for (long long i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft2(a0, invert);
    fft2(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    base w(1), wn(cos(ang), sin(ang));
    for (long long i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2, a[i + n / 2] /= 2;
        w *= wn;
    }
}

long long mulNumberString(string &s) {
    vector<long long> num1, num2;
    for (long long i = 0; i < s.size(); i++) {
        int num = s[i] - '0';
        num1.push_back(num);
        num2.push_back(num);
    }
    vector<long long> res = mul(num1, num2);
    long long sum = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0') continue;
        sum += (res[2 * i] - 1) / 2;
    }

    return sum;

}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#else
    std::ifstream cin("duel.in");
    std::ofstream cout("duel.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    cout << mulNumberString(s);


    return 0;
}
