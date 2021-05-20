#include "bits/stdc++.h"
using namespace std;

#define int long long
#define ld long double
#define vi vector<int>
#define cd complex<ld>
const ld PI = acos(-1);

class FFT
{
    void fft(vector<cd> &a, bool invert)
    {
        int n = a.size();
        if (n <= 1)
            return;
        vector<cd> even, odd;

        for (int i = 0; i < n; i += 2)
        {
            even.push_back(a[i]);
        }

        for (int i = 1; i < n; i += 2)
        {
            odd.push_back(a[i]);
        }

        fft(even, invert);
        fft(odd, invert);

        for (int k = 0; k < n / 2; ++k)
        {
            cd t = polar((ld)1.0, 2 * PI * k * (invert ? -1 : 1) / n) * odd[k];

            a[k] = even[k] + t;
            a[k + n / 2] = even[k] - t;
            if (invert)
            {
                // We have to divide by n so we divide by 2 for each level of recursion depth
                a[k] /= 2;
                a[k + n / 2] /= 2;
            }
        }
    }

public:
    vi multiply(vi &a, vi &b)
    {
        int n = 1;
        while (n < a.size() + b.size())
            n *= 2;

        vector<cd> fa(n), fb(n);
        for (int i = 0; i < a.size(); i++)
        {
            fa[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++)
        {
            fb[i] = b[i];
        }

        fft(fa, 0);
        fft(fb, 0);

        for (int i = 0; i < n; i++)
        {
            fa[i] *= fb[i];
        }

        // Inverse fft
        fft(fa, 1);

        vi res(n);
        for (int i = 0; i < n; i++)
        {
            res[i] = round(fa[i].real());
        }

        return res;
    }
};

void printvec(vi &a)
{
    for (int x : a)
        cout << x << ' ';
    cout << '\n';
}

vi sum(vi &a, vi &b, int n)
{
    vi res(n);
    for (int i = 0; i < n; i++)
    {
        res[i] = a[i] + b[i];
    }
    return res;
}

vi subtract(vi &a, vi &b, int n)
{
    vi res(n);
    for (int i = 0; i < n; i++)
    {
        res[i] = a[i] - b[i];
    }
    return res;
}

vi multiply(vi &a, vi &b, int n)
{
    if (n == 1)
        return {a[0] * b[0], 0};
    vi al(n / 2), ar(n / 2), bl(n / 2), br(n / 2);

    for (int i = 0; i < n / 2; i++)
    {
        al[i] = a[i + n / 2];
        bl[i] = b[i + n / 2];
        ar[i] = a[i];
        br[i] = b[i];
    }

    vi s1 = sum(al, ar, n / 2), s2 = sum(bl, br, n / 2);

    vi A = multiply(al, bl, n / 2), B = multiply(s1, s2, n / 2), C = multiply(ar, br, n / 2);
    assert(A.size() == n);
    assert(B.size() == n);
    assert(C.size() == n);

    vi temp = sum(A, C, n);
    B = subtract(B, temp, n);
    vi res(2 * n);

    for (int i = 0; i < n; i++)
    {
        res[i + n] += A[i];
        res[i] += C[i];
        res[i + n / 2] += B[i];
    }
    return res;
}

vi preprocess(vi a, vi b)
{
    int n1 = a.size(), n2 = b.size(), n = 1;
    while (n < n1 + n2)
        n *= 2;
    a.resize(n);
    b.resize(n);
    reverse(a.begin(), a.end());
    vi res;

    FFT fft;

    res = fft.multiply(a, b);

    return res;
}

signed main()
{
    string text, pattern;
    cout << "Enter text\n";
    getline(cin, text);
    cout << "Enter pattern\n";
    cin >> pattern;
    vi T, P;
    for (char c : text)
    {
        if (c == '?')
            T.push_back(0);
        else
            T.push_back(c);
    }

    for (char c : pattern)
    {
        if (c == '?')
            P.push_back(0);
        else
            P.push_back(c);
    }

    vi P3 = P, P2 = P;

    for (int &x : P3)
    {
        x = x * x * x;
    }
    for (int &x : P2)
    {
        x = x * x;
    }

    vi T2 = T, T3 = T;

    for (int &x : T3)
    {
        x = x * x * x;
    }
    for (int &x : T2)
    {
        x = x * x;
    }

    vi p3t = preprocess(P3, T), pt3 = preprocess(P, T3), p2t2 = preprocess(P2, T2);
    int n = p3t.size();
    n /= 2;

    int tsz = T.size(), psz = P.size();
    for (int i = 0; i + psz - 1 < tsz; i++)
    {
        int ans = p3t[n + i - 1] + pt3[n + i - 1] - 2 * p2t2[n + i - 1];
        if (ans == 0)
        {
            cout << "Index: " << i << " -> '" << text.substr(i, pattern.size()) << "'\n";
        }
    }
}
