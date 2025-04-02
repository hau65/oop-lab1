#include <bits/stdc++.h>
using namespace std;

const int nganHan = 186, daiHan = 365;
const int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
const string loaiTK[3] = {"ngan han","dai han","khong ki han"};

bool IsLeapYear(const int& year){
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}
int GetDaysInMonth(const int& month, const int& year){
    return (month == 2 && IsLeapYear(year))? 29 : daysInMonth[month - 1];
}
bool isNum(const string& str){
    return all_of(str.begin(), str.end(), [](unsigned char c){return isdigit(c); });
}

bool isChar(const string& str){
    return all_of(str.begin(), str.end(), [](unsigned char c){return (islower(c) || isupper(c) || c == ' '); });
}
bool hasSpecialChar(const string& str){
    return any_of(str.begin(), str.end(), [](unsigned char c){return (!islower(c) && !isupper(c) && !isdigit(c)); });
}

bool hasNum(const string& str){
    return any_of(str.begin(), str.end(), [](unsigned char c){return isdigit(c); });
}

void InputNumber(int& n)
{
    while (!(cin >> n))
    {
        cout << "Thu lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

class Date
{
private:
    int day, month, year;

public:
    Date(){}
    Date(int _day, int _month, int _year):day(_day), month(_month), year(_year){}

    string info() const
    {
        ostringstream oss;
        oss << day << "/" << month << "/" << year;
        return oss.str();
    }

    static bool isRealDate(const Date& d)
    {
        if (d.month < 1 || d.month > 12) throw runtime_error("Thang khong hop le.");
        if (d.day < 1 || d.day > GetDaysInMonth(d.month, d.year)) throw runtime_error("Ngay khong hop le.");
        if (d.year < 1900) throw runtime_error("Nam khong hop le.");
        return true;
    }

    // Calculate days since the dawn of man
    int daysSinceEver() const
    {
        int days = 0;
        for (int i = 1; i < year; i++){
            days += (IsLeapYear(i))? 366 : 365;
        }
        for (int i = 1; i < month; i++){
            days += GetDaysInMonth(i, year);
        }
        days += day;
        return days;
    }

    // Check if a date is valid
    friend istream& operator >> (istream& is, Date& date)
    {
        string str;
        cin >> str;
        stringstream ss(str);
        string temp[3];
        try
        {
            if (getline(ss, temp[0], '/') && isNum(temp[0])
                && getline(ss, temp[1], '/')&& isNum(temp[1])
                && getline(ss, temp[2], '/')&& isNum(temp[2]))
            {
                date.day = stoi(temp[0]);
                date.month = stoi(temp[1]);
                date.year = stoi(temp[2]);
            }
            else throw runtime_error("Dinh dang sai.");
            if (!isRealDate(date)) throw runtime_error("Ngay khong co that.");
        }
        catch (const runtime_error& e)
        {
            cout << "Loi: " << e.what() << endl << "Thu lai: ";
            is >> date;
        }
        return is;
    }

    friend ostream& operator << (ostream& os, Date& date){
        return os << date.info();
    }
};

class SoTietKiem
{
private:
    string ma, loai, name, cmnd;
    double tienGui, tienRut, laiSuat, laiSuatTruocHan = 0.5, tienLai;
    bool hasRutTien;
    Date dob, ngayMoSo, ngayRut;
    int han;


public:
    string getCMND() const {return cmnd;}
    string getMASO() const {return ma;}
    string getName() const {return name;}
    string getLoai() const {return loai;}
    double getTienGui() const {return tienGui;}
    Date getNgayMoSo() const {return ngayMoSo;}

    static bool isDungLoaiTK(const string& str)
    {
        for (const auto& i : loaiTK)
            if (!str.compare(i)) return true;
        return false;
    }

    string info() const
    {
        ostringstream oss;
        oss << "Ma: " << ma << endl;
        oss << "Ten: " << name << endl;
        oss << "CMND: " << cmnd << endl;
        oss << "Ngay sinh:" << dob.info() << endl;
        oss << "Loai: " << loai << endl;
        oss << "Tien gui: " << tienGui << endl;
        oss << "Ngay gui: " << ngayMoSo.info() << endl;

        return oss.str();
    }

    void PhanLoaiHan()
    {
        if (loai == loaiTK[0]) han = nganHan;
        else if (loai == loaiTK[1]) han = daiHan;
        else han = 999999999;
    }

    void Input()
    {
        // Nhap ma
        cout << "Nhap ma: ";
        cin.ignore(1000, '\n');
        getline(cin, ma);
        while (ma.length() > 6 || hasSpecialChar(ma) || ma == ""){
            cout << "Thu lai: ";
            getline(cin, ma);
        }

        // Nhap loai gui ngan hang
        cout << "Loai(ngan han, dai han, khong ki han): ";
        getline(cin, loai);
        while (!isDungLoaiTK(loai)){
            cout << "Thu lai: ";
            getline(cin, loai);
        }

        //Nhap ten
        cout << "Ten: ";
        getline(cin, name);
        while (!isChar(name)){
            cout << "Thu lai: ";
            getline(cin, name);
        }

        // Nhap CMND
        cout << "CMND (9 hoac 12 so) : ";
        getline(cin, cmnd);
        while (!isNum(cmnd) || (cmnd.length() != 9 && cmnd.length() != 12)){
            cout << "Thu lai: ";
            getline(cin, cmnd);
        }

        // Nhap date of birth
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        cin >> dob;

        // Nhap tien gui
        cout << "Nhap tien gui: ";
        while (!(cin >> tienGui) || tienGui <= 0)
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        // Ngay hien tai
        time_t t = time(nullptr);
        tm *const p = localtime(&t);
        Date ngayHienTai = {p->tm_mday, p->tm_mon + 1, p->tm_year + 1900};

        // Nhap ngay gui
        cout << "Nhap ngay gui: ";
        do{cin >> ngayMoSo;}
        while (ngayHienTai.daysSinceEver() - ngayMoSo.daysSinceEver() <= 0);
    }

    friend ostream& operator << (ostream& os, const SoTietKiem& stk){
        return os << stk.info();
    }

    void UpdateRateNTakeOut()
    {
        // Lai suat
        cout << "Lai suat (%/nam) (Lai suat phai tren lai suat ko ki han(0.5%/nam): ";
        while (!(cin >> laiSuat) || laiSuat <= 0.5)
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Ngay hien tai
        time_t t = time(nullptr);
        tm *const p = localtime(&t);
        Date ngayHienTai = {p->tm_mday, p->tm_mon + 1, p->tm_year + 1900};

        // Tinh tien lai
        int ngayDif = ngayHienTai.daysSinceEver() - ngayMoSo.daysSinceEver();
        if (loai == loaiTK[0] || loai == loaiTK[1]) tienLai = tienGui * ((ngayDif/han) * (laiSuat/100) + (ngayDif%han) * (laiSuatTruocHan/100));
        else tienLai = tienGui * (ngayDif/365) * (laiSuatTruocHan/100);
        cout << "Tien lai: " << tienLai << " VND." << endl;
        tienGui += tienLai;
        tienLai = 0;

        // Rut tien
        cout << "Ban muon rut tien khong? (y/n): ";
        string temp; cin >> temp;
        while (temp != "y" && temp != "n"){
            cout << "Thu lai: "; cin >> temp;
        }
        if (temp == "y") hasRutTien = true;
        else hasRutTien = false;

        if ((loai == loaiTK[0] && ngayDif < nganHan) || (loai == loaiTK[1] && ngayDif < daiHan)){
            cout << "Chua du han rut tien, ban co muon rut? (y/n): ";
            cin >> temp;
            while (temp != "y" && temp != "n"){
                cout << "Thu lai: "; cin >> temp;
            }
            if (temp == "n"){
                hasRutTien = false;
                return;
            }
        }

        if (hasRutTien)
        {
            cout << "Ban muon rut bao nhieu? " << endl;
            int n;
            while (!(cin >> n) || n < 0 || n > tienGui)
            {
                cout << "Thu lai: " << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            tienGui -= n;
            cout << "Rut tien thanh cong! " << endl;
            cout << "So tien con lai: " << tienGui << endl;
        }

        return;
    }
};

class DSSTK
{
private:
    vector<SoTietKiem> l;

public:
    int getSize() const {return l.size();}
    SoTietKiem getSTK(const int& n) const {return l[n];}
    string info() const
    {
        ostringstream oss;
        for (int i = 0; i < l.size(); i++){
            oss << "STK thu " << i + 1 << endl << l[i].info() << endl;
        }
        return oss.str();
    }
    void Input()
    {
        int n;
        cout << "Nhap so luong stk: "; InputNumber(n);
        for (int i = 0; i < n; i++)
        {
            SoTietKiem temp;
            cout << "Nhap stk thu " << i + 1 << endl;
            temp.Input();
            l.push_back(temp);
        }
    }

    void FindViaCMND(const string& str)
    {
        for (const auto& i : l){
            if (i.getCMND() == str){
                cout << i.info() << endl;
                return;
            }
        }
        cout << "Khong tim thay. " << endl;
    }

    void FindViaMaSo(const string& str)
    {
        for (const auto& i : l){
            if (i.getMASO() == str){
                cout << i.info() << endl;
                return;
            }
        }
        cout << "Khong tim thay. " << endl;
    }

    void ListFromTo(const Date& d1, const Date& d2)
    {
        int from = d1.daysSinceEver();
        int to = d2.daysSinceEver();
        bool found = false;
        for (const auto& i : l)
        {
            int day = i.getNgayMoSo().daysSinceEver();
            if (from <= day && day <= to){
                cout << i.info() << endl;
                found = true;
            }
        }
        if (!found) cout << "Khong co so tiet kiem nao duoc tao tu ngay " << d1.info() << " den ngay " << d2.info() << "." << endl;
    }

    void SortDescendingMoney()
    {
        vector<SoTietKiem> temp = l;
        sort(temp.begin(), temp.end(), [](const SoTietKiem s1, const SoTietKiem s2){return s1.getTienGui() > s2.getTienGui();});
        for (const auto& i : temp){
            cout << i.info() << endl;
        }
    }

    void SortAscendingOpenDate()
    {
        vector<SoTietKiem> temp = l;
        sort(temp.begin(), temp.end(), [](const SoTietKiem s1, const SoTietKiem s2){return s1.getNgayMoSo().daysSinceEver() < s2.getNgayMoSo().daysSinceEver();});
        for (const auto& i : temp){
            cout << i.info() << endl;
        }
    }
};

void Menu()
{
    DSSTK l;
    while (true)
    {
        cout << "-------------------------------------Menu---------------------------" << endl;
        cout << "1. Nhap du lieu." << endl;
        cout << "2. Xuat du lieu." << endl;
        cout << "3. Nhap lai xuat va rut tien " << endl;
        cout << "4. Tim kiem. " << endl;
        cout << "5. Liet ke." << endl;
        cout << "6. Sap xep. "<< endl;
        cout << "7. Thoat. " << endl;

        int n;
        cout << "Lua chon: ";
        if (!(cin >> n) || n < 1 || n > 8)
        {
            cout << "Thu lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        system("cls"); // this spawns a shell process to clear the damn console but i aint assed enough to find a better solution.
        switch(n)
        {
        case 1:
            {
                l.Input();
                break;
            }
        case 2:
            {
                if (l.getSize() == 0){
                    cout << "Chua co tai khoan nao. " << endl;
                    break;
                }
                cout << l.info();
                break;
            }
        case 3:
            {
                if (l.getSize() == 0){
                    cout << "Chua co tai khoan nao. " << endl;
                    break;
                }
                int n;
                cout << "Cap nhat lai suat cho tai khoan: " << endl;
                for (int i = 0; i < l.getSize(); i++){
                    cout << i+1 << ". " << l.getSTK(i).getName() << ", " << l.getSTK(i).getLoai() << ", " << l.getSTK(i).getTienGui() << " VND" << endl;
                }
                while (!(cin >> n) || n < 0 || n > l.getSize())
                {
                    cout << "Thu lai: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                l.getSTK(n-1).UpdateRateNTakeOut();
                break;
            }
        case 4:
            {
                if (l.getSize() == 0){
                    cout << "Chua co tai khoan nao. " << endl;
                    break;
                }
                cout << "Tim kiem: " << endl;
                cout << "1. Theo CMND." << endl;
                cout << "2. Theo ma so." << endl;
                int n;

                cout << "Lua chon: ";
                while (!(cin >> n) || n < 0 || n > 2)
                {
                    cout << "Thu lai: " << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                string temp;
                if (n == 1)
                {
                    cout << "CMND (9 hoac 12 so) : ";
                    cin.ignore(1000, '\n');
                    getline(cin, temp);
                    while (!isNum(temp) || (temp.length() != 9 && temp.length() != 12)){
                        cout << "Thu lai: ";
                        getline(cin, temp);
                    }
                    l.FindViaCMND(temp);
                }
                if (n == 2)
                {
                    cout << "Nhap ma: ";
                    cin.ignore(1000, '\n');
                    getline(cin, temp);
                    while (temp.length() > 6 || hasSpecialChar(temp) || temp == ""){
                        cout << "Thu lai: ";
                        getline(cin, temp);
                    }
                    l.FindViaMaSo(temp);
                }

                break;
            }
        case 5:
            {
                if (l.getSize() == 0){
                    cout << "Chua co tai khoan nao. " << endl;
                    break;
                }
                Date fromD, toD;
                cout << "Liet ke tu ngay den ngay: " << endl;
                cout << "Tu ngay: "; cin >> fromD;
                cout << "Den ngay: "; cin >> toD;
                cout << "Danh sach: " << endl;
                l.ListFromTo(fromD, toD);
                break;
            }
        case 6:
            {
                if (l.getSize() == 0){
                    cout << "Chua co tai khoan nao. " << endl;
                    break;
                }
                cout << "Sap xep: " << endl;
                cout << "1. Theo so tien gui giam dan." << endl;
                cout << "2. Theo ngay mo so tang dan." << endl;
                int n;

                cout << "Lua chon: ";
                while (!(cin >> n) || n < 0 || n > 2)
                {
                    cout << "Thu lai: " << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                cout << "Danh sach: " << endl;
                if (n == 1)
                {
                    l.SortDescendingMoney();
                    break;
                }
                if (n == 2)
                {
                    l.SortAscendingOpenDate();
                    break;
                }
            }
        case 7:
            {
                return;
            }
        default:
            {
                break;
            }
        }
    }
}

int main(){
    Menu();
}

/*
3
abcde
dai han
Nguyen Trung Hau
123456789
04/07/2006
50000
1/1/2000
b1435
ngan han
Vu Hai Thien
213442142
29/02/2004
20000
26/3/2024
c54a
dai han
Do Quang Tien
093430435
13/07/2006
200000
29/2/2024
*/
