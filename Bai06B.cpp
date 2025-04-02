#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
using namespace std;

bool HasNumber(const string& str){
    return any_of(str.begin(), str.end(), [](const char c){return isdigit(c); });
}

bool IsNumber(const string& str)
{
    if (count_if(str.begin(), str.end(),[](const char c){return c == '.';}) > 1) return false;
    if (any_of(str.begin(), str.end(), [](const char c){return !isdigit(c) && c != '.'; })) return false;
    if (stod(str) < 0 || stod(str) > 10) return false;
    return true;
}

void InputPoint(double& n)
{
    string temp;
    while (!(cin >> temp) || !IsNumber(temp))
    {
        cout << "Thu lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    n = stod(temp);
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

class Student
{
private:
    string name;
    double toan, van, anh;
public:
    string getName() const {return name;}
    int getToan() const {return toan;}
    string info() const
    {
        ostringstream oss;
        oss << "Ten: " << name << endl;
        oss << "Diem toan: " << toan << endl;
        oss << "Diem van: " << van << endl;
        oss << "Diem anh: " << anh << endl;
        oss << "Diem TB: " << GetAverage() << endl;
        oss << "Phan loai: " << GetHonor();
        return oss.str();
    }

    void Input()
    {
        cout << "Nhap ten: ";
        cin.ignore(1000, '\n');
        while (!(getline(cin, name)) || HasNumber(name) || name.length() > 30){
            cout << "Thu lai: ";
        }
        cout << "Nhap diem toan: "; InputPoint(toan);
        cout << "Nhap diem van: "; InputPoint(van);
        cout << "Nhap diem anh: "; InputPoint(anh);
    }

    double GetAverage() const {
        return (toan*2 + van + anh) / 4;
    }

    string GetHonor() const
    {
        double av = GetAverage();
        if (av >= 9) return "Xuat sac";
        if (av >= 8) return "Gioi";
        if (av >= 6.5) return "Kha";
        if (av >= 5) return "Trung binh";
        return "Yeu";
    }
};

class StuList
{
private:
    vector<Student> l;

public:
    int GetSize() const {return l.size();}
    string info()
    {
        ostringstream oss;
        for (int i = 0; i < l.size(); i++){
            oss << "Hoc sinh thu " << i + 1 << endl << l[i].info() << endl << endl;
        }
        return oss.str();
    }

    void Input()
    {
        int n;
        cout << "Nhap so hoc sinh: "; InputNumber(n);
        for (int i = 0; i < n; i++)
        {
            cout << "Hoc sinh thu " << i + 1 << endl;
            Student temp;
            temp.Input();
            l.push_back(temp);
        }
    }

    Student Get1stAverage() const
    {
        Student temp = l[0];
        for (int i = 1; i < l.size(); i++){
            if (temp.GetAverage() < l[i].GetAverage())
                temp = l[i];
        }
        return temp;
    }
    vector<Student> GetStudentsWith(string& str) const
    {
        vector<Student> temp;
        for (auto& i : str){
            i = tolower(i);
        }
        for (auto& i : l)
        {
            string name = i.getName();
            for (auto& j : name) {
                j = tolower(j);
            }
            if (name.find(str) != string::npos){
                temp.push_back(i);
            }
        }
        return temp;
    }

    string GetToanListAscending()
    {
        vector <Student> temp = l;
        sort(temp.begin(), temp.end(), [](const Student& s1, const Student& s2){return s1.getToan() < s2.getToan(); });
        ostringstream oss;
        for (const auto& i : temp){
            oss << i.getName() << ": " << i.getToan() << endl;
        }
        return oss.str();
    }
};

void Menu()
{
    StuList l;
    while (true)
    {
        cout << "-------------------------------------Menu---------------------------" << endl;
        cout << "1. Nhap du lieu." << endl;
        cout << "2. Tim kiem hoc sinh co diem trung binh cao nhat." << endl;
        cout << "3. Tim kiem hoc sinh theo ten." << endl;
        cout << "4. Xuat danh sach hoc sinh co diem toan thap nhat." << endl;

        int n;
        cout << "Lua chon: ";
        if (!(cin >> n) || n < 1 || n > 4)
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
                if (l.GetSize() == 0) cout << "Khong co hoc sinh nao." << endl;
                else cout << "Hoc sinh co DTB cao nhat: " << endl << l.Get1stAverage().info() << endl;
                break;
            }
        case 3:
            {
                if (l.GetSize() == 0)
                {
                    cout << "Khong co hoc sinh nao." << endl;
                    break;
                }

                cout << "Nhap tu khoa: ";
                string temp;
                cin.ignore(1000, '\n');
                while (!(getline(cin, temp)) || HasNumber(temp) || temp.length() > 30){
                    cout << "Thu lai: ";
                }
                vector<Student> tempL = l.GetStudentsWith(temp);
                if (tempL.size() == 0)
                {
                    cout << "Khong co hoc sinh nao voi tu khoa " << temp << endl;
                    break;
                }
                for (const auto& i : tempL)
                {
                    cout << "Danh sach hoc sinh voi tu khoa " << temp << endl;
                    for (const auto& i : tempL) {
                        cout << i.info() << endl;
                    }
                }
                break;
            }
        case 4:
            {
                if (l.GetSize() == 0)
                {
                    cout << "Khong co hoc sinh nao." << endl;
                    break;
                }

                cout << "Danh sach hoc sinh co diem toan thap nhat: " << endl << l.GetToanListAscending() << endl;
                break;
            }
        default:
            {
                break;
            }
        }
    }
}

int main()
{
    Menu();
}
