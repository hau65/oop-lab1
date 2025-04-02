#include <iostream>
#include <string>
using namespace std;
const int MAX = 100;

struct ChuyenBay{
    string codeChuyen;
    string date;
    string Time;
    string NoiDi;
    string NoiDen;
};

//hàm nhập
void InputChuyenBay(ChuyenBay &cb){
    cout << "code chuyen bay: ";
    getline(cin, cb.codeChuyen);
    cout << "Ngay bay (dd/mm/yyyy): ";
    cin >> date;
    cout << "Gio bay (hh:mm): ";
    getline(cin, cb.Time);
    cout << "Noi di: ";
    getline(cin, cb.NoiDi);
    cout << "Noi den: ";
    getline(cin, cb.NoiDen);
}

//hàm xuất
void OutputChuyenBay(const ChuyenBay &cb){
    cout << cb.codeChuyen << " - " << cb.Date << " - " << cb.Time;
    cout << " - " << cb.NoiDi << " -> " << cb.NoiDen << endl;
}

//hàm nhập danh sách chuyến bay
void InputDanhSach(ChuyenBay ds[], int &n){
    cout << "Nhap so luong chuyen bay: ";
    cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++){
        cout << "\nNhap thong tin chuyen bay thu " << i + 1 << ":\n";
        InputChuyenBay(ds[i]);
    }
}

//hàm xuất danh sách chuyến bay
void OutputDanhSach(ChuyenBay ds[], int n){
    for(int i = 0; i < n; i++){
        OutputChuyenBay(ds[i]);
    }
}

//hàm tìm chuyên bay theo mã
void CodeSearch(ChuyenBay ds[], int n, const string &code){
    bool k = false;
    for(int i = 0; i < n; i++){
        if(ds[i].codeChuyen == code){
            OutputChuyenBay(ds[i]);
            k = true;
        }
    }
    if(!k) cout << "Khong tim thay chuyen bay co ma " << code << endl;
}

//hàm tìm kiếm theo nơi đi nơi đến
void PlaceSearch(ChuyenBay ds[], int n, const string &NoiDi, const string &NoiDen){
    bool k = false;
    for(int i = 0; i < n; i++){
        if(ds[i].NoiDi == NoiDi && ds[i].NoiDen == NoiDen){
            OutputChuyenBay(ds[i]);
            k = true;
        }
    }
    if (!k) cout << "Khong tim thay chuyen bay tu " << NoiDi << " den " << NoiDen << endl;
}

//hàm đếm chuyến bay
int CountChuyenBay(ChuyenBay ds[], int n, const string &NoiDi, const string &NoiDen){
    int k = 0;
    for(int i = 0; i < n; i++){
        if(ds[i].NoiDi == NoiDi && ds[i].NoiDen == NoiDen){
            k++;
        }
    }
    return k;
}

//hàm sắp xếp chuyến bay
void SortChuyenBay(ChuyenBay ds[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if (ds[i].Date > ds[j].Date || (ds[i].Date == ds[j].Date && ds[i].Time > ds[j].Time)){
                swap(ds[i], ds[j]);
            }
        }
    }
}

//hàm hiển thị chuyến bay theo nơi đi vào ngày
void DisplayPlaceDate(ChuyenBay ds[], int n, const string &NoiDi, const string &Date){
    bool k = false;
    for(int i = 0; i < n; i++){
        if(ds[i].NoiDi == NoiDi && ds[i].Date == Date){
            OutputChuyenBay(ds[i]);
            k = true;
        }
    }
    if (!k) cout << "Khong co chuyen bay nao tu " << NoiDi << " vao ngay " << Date << endl;
}

int main(){
    ChuyenBay ds[MAX];
    int n;
    string codeTimKiem, NoiDi, NoiDen, Date;
    InputDanhSach(ds, n);
    cout << "\nDanh sach cac chuyen bay da nhap:\n";
    OutputDanhSach(ds, n);
        (ds, n);
    cout << "\nDanh sach chuyen bay sau khi sap xep:\n";
    OutputDanhSach(ds, n);
    cout << "\nNhap code chuyen bay can tim: ";
    getline(cin, codeTimKiem);
    CodeSearch(ds, n, codeTimKiem);
    cout << "\nNhap noi di va noi den de tim kiem (cach nhau boi dau cach): ";
    cin >> NoiDi >> NoiDen;
    PlaceSearch(ds, n, NoiDi, NoiDen);
    cout << "\nSo luong chuyen bay tu " << NoiDi << " den " << NoiDen << ": " << CountChuyenBay(ds, n, NoiDi, NoiDen) << endl;
    cout << "\nNhap noi di va ngay bay de hien thi (cach nhau boi dau cach): ";
    cin >> NoiDi >> Date;
    DisplayPlaceDate(ds, n, NoiDi, Date);
    return 0;
}
