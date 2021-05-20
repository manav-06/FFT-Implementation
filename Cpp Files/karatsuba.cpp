#include "bits/stdc++.h"
using namespace std;

#define vi vector<int>

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

vi karatsuba(vi a, vi b)
{
    int n1 = a.size(), n2 = b.size(), n = 1;
    while (n < n1 + n2)
        n *= 2;
    a.resize(n);
    b.resize(n);
    vi res = multiply(a, b, n);
    return res;
}

int main()
{
    int n, m;
    cout << "Enter the polymonial degrees\n";
    cin >> n >> m;
    vi a(n + 1), b(m + 1);
    cout << "Enter the first polynomial\n";
    for (int i = 0; i <= n; i++)
    {
        cin >> a[i];
    }
    cout << "Enter the second polynomial\n";
    for (int i = 0; i <= m; i++)
    {
        cin >> b[i];
    }
    // vi a = {1, 2, 1}, b = {1, -2, 1};
    vi res = karatsuba(a, b);
    cout << "The product polynomial is:\n";
    for (int i = 0; i < a.size() + b.size() - 1; i++)
    {
        cout << res[i] << ' ';
    }
}
