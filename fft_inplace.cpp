#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long double ld;
typedef complex<ld> cd;
const ld PI = acos(-1);

void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        ld ang = 2 * PI / len * (invert ? -1 : 1);
        cd rt(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = w * a[i + j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= rt;
            }
        }
    }
    if (invert)
        for (cd &x : a)
            x /= n;
}

vi mult(vi &a, vi &b)
{
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    vector<cd> fa(n), fb(n);
    for (int i = 0; i < a.size(); i++)
        fa[i] = a[i];
    for (int i = 0; i < b.size(); i++)
        fb[i] = b[i];
    fft(fa, 0);
    fft(fb, 0);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, 1);

    vi r(n);
    for (int i = 0; i < n; i++)
        r[i] = round(fa[i].real());
    return r;
}

int main()
{
    int i, n, m;
    vector<int> a, b, c;
    cin >> n >> m;
    for (i = 0; i <= n; i++)
    {
        int k;
        cin >> k;
        a.push_back(k);
    }
    for (i = 0; i <= m; i++)
    {
        int k;
        cin >> k;
        b.push_back(k);
    }
    c = mult(a, b);
    for (int k : c)
        cout << k << " ";
    return 0;
}