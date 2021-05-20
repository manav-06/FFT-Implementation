#include <bits/stdc++.h>
using namespace std;

#define maxn 50001
#define MOD 998244353
#define G 3
#define LL long long

LL rev[maxn], len = 1, n, m;
LL A[maxn], B[maxn], C[maxn];

struct OPT
{
    inline LL Pow(LL a, LL k)
    {
        LL base = 1;
        while (k)
        {
            if (k & 1)
                base = (base * a) % MOD;
            a = (a * a) % MOD;
            k >>= 1;
        }
        return base % MOD;
    }
    void NTT(LL *a, LL len, LL opt)
    {
        for (int i = 0; i < len; i++)
        {
            if (i < rev[i])
            {
                swap(a[i], a[rev[i]]);
            }
        }
        for (int i = 1; i < len; i <<= 1)
        {
            LL wn = Pow(G, (opt * ((MOD - 1) / (i << 1)) + MOD - 1) % (MOD - 1));
            LL step = i << 1;
            for (int j = 0; j < len; j += step)
            {
                LL w = 1;
                for (int k = 0; k < i; k++, w = (1ll * w * wn) % MOD)
                {
                    LL x = a[j + k];
                    LL y = 1ll * w * a[j + k + i] % MOD;
                    a[j + k] = (x + y) % MOD;
                    a[j + k + i] = (x - y + MOD) % MOD;
                }
            }
        }
        if (opt == -1)
        {
            LL r = Pow(len, MOD - 2);
            for (int i = 0; i < len; i++)
                a[i] = 1ll * a[i] * r % MOD;
        }
    }
} T;

void multiply()
{

    //n and m is size of both polynomials
    cin >> n >> m;
    // coefficient of 1st polynomial
    for (int i = 0; i <= n; i++)
        cin >> A[i];
    // coefficient of 2nd polynomial
    for (int i = 0; i <= m; i++)
        cin >> B[i];
    // highest possible power in resultant polynomial
    int tot = m + n;
    int l = 0;
    while (len <= tot)
    {
        len <<= 1;
        l++;
    }
    for (int i = 0; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    T.NTT(A, len, 1), T.NTT(B, len, 1);
    for (int i = 0; i < len; i++)
    {
        C[i] = (LL)(A[i] * B[i]) % MOD;
    }
    T.NTT(C, len, -1);
    for (int i = 0; i <= tot; i++)
        cout << C[i] << " ";
}

int main()
{
    multiply();
    return 0;
}