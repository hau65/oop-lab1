 #include <bits/stdc++.h>
using namespace std;
double lowerbound = 0.00001;
int64_t x;
int64_t metro = 1;

double MaOwnSin(int n)
{
    metro *= (2*n) * (2*n+1);
    double value = (((n&1)? -1:1) * double(pow(x, 2*n + 1))) / metro;
    if (abs(value) > lowerbound){
        return value + MaOwnSin(n+1);
    }
    return value;
}

int main()
{
    cout << "Nhap x: ";
    while(!(cin >> x) || x > 4){
        cout << "Thu lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << x + MaOwnSin(1) << " | sin(x): " << sin(x);
}
