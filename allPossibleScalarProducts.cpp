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

signed main()
{

    vector<int> A;
    vector<int> B;
    int n, x;
    cout << "Enter the array size\n";
    cin >> n;

    cout << "Enter the first array\n";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        A.push_back(x);
    }
    cout << "Enter the second array\n";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        B.push_back(x);
    }
    reverse(A.begin(), A.end());

    for (int i = n; i < 2 * n; i++)
    {
        A.push_back(0);
    }

    for (int i = 0; i < n; i++)
    {
        B.push_back(B[i]);
    }

    FFT fft;
    vector<int> c = fft.multiply(A, B);

    for (int i = n - 1; i <= 2 * n - 2; i++)
    {
        cout << "Second array shifted by " << i - (n - 1) << ", product is: ";
        cout << c[i] << "\n";
    }
}