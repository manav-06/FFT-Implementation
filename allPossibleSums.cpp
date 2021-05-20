#include "bits/stdc++.h"
using namespace std;

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
    vector<int> a;
    vector<int> b;
    int n, x;
    cout << "Enter the array size\n";
    cin >> n;

    cout << "Enter the first array\n";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        a.push_back(x);
    }
    cout << "Enter the second array\n";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        b.push_back(x);
    }
    int mxa = *max_element(a.begin(), a.end()), mxb = *max_element(b.begin(), b.end());

    vi A(mxa + 1), B(mxb + 1);

    for (int x : a)
    {
        A[x]++;
    }
    for (int x : b)
    {
        B[x]++;
    }
    FFT fft;
    vi res = fft.multiply(A, B);
    cout << "All possible sums are: \n";
    for (int i = 0; i <= mxa + mxb; i++)
    {
        if (res[i] > 0)
        {
            cout << i << " frequency: " << res[i] << '\n';
        }
    }
}
