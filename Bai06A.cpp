#include <iostream>
using namespace std;

struct Mang{
    int n;
    int arr[1000];
};

void Input(Mang &a, Mang &b){
    cout << "Nhap so phan tu cua mang A va B: ";
    cin >> a.n >> b.n;

    cout << "Nhap cac phan tu cua mang A: ";
    for(int i = 0; i < a.n; i++){
        cin >> a.arr[i];
    }
    cout << "Nhap cac phan tu cua mang B: ";
    for(int i = 0; i < b.n; i++){
        cin >> b.arr[i];
    }
}

void Output(const int& result, const int pos[1000]){
    cout << "So lan xuat hien mang A trong B: " << result << endl;
    if(result){
        cout << "Cac vi tri xuat hien: ";
        for(int i = 0; i < result; i++){
            cout << pos[i] << " ";
        }
    }
}

int Search(const Mang &a, const Mang &b, int pos[]){
    int c = 0;
    for(int i = 0; i <= b.n - a.n; i++){
        bool found = true;
        for(int j = 0; j < a.n; j++){
            if(a.arr[j] != b.arr[i+j]){
                found = false;
                break;
            }
        }
        if(found){
            pos[c] = i;
            c++;
        }
    }
    return c;
}

int main()
{
    Mang A, B;
    Input(A, B);
    int pos[1000];
    int result = Search(A, B, pos);
    Output(result, pos);
    return 0;
}
