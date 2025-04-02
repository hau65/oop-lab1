#include <bits/stdc++.h>
using namespace std;

int dayInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
bool IsLeapYear(const int& year) {
    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

int GetDayInMonth(const int& month, const int& year) {
    return (month == 2 && IsLeapYear(year))? 29 : dayInMonth[month - 1];
}

class Date
{
private:
    int day, month, year;

public:
    Date(){}
    Date (const int& _day,const int& _month,const int& _year) : day(_day), month(_month), year(_year){}

    bool isValid(const Date& date){
        return (!(date.day < 1 || date.month < 1 || date.year < 1 ||date.day > GetDayInMonth(date.month, date.year) || date.month > 12));
    }

    string info()
    {
        ostringstream oss;
        oss << setw(2) << setfill('0') << day << "/" << month << "/" << year;
        return oss.str();
    }

    int NoOfDay() const
    {
        int n = 0;
        for (int i = 1; i < month; i++)
            n += GetDayInMonth(i, year);
        n += day;

        return n;
    }

    friend istream& operator >> (istream& is, Date& date)
    {
        cout << "Nhap ngay (d/m/y): ";
        string str;
        cin >> str;

        stringstream ss(str);
        string temp;
        try
        {
            if (str.find('/') == string::npos)
                throw invalid_argument("Sai dinh dang.");
            if (getline(ss, temp, '/')) date.day = stoi(temp);
            if (getline(ss, temp, '/')) date.month = stoi(temp);
            if (getline(ss, temp, '/')) date.year = stoi(temp);

            if (date.day < 1 || date.month < 1 || date.year < 1
                ||date.day > GetDayInMonth(date.month, date.year) || date.month > 12)
                throw invalid_argument("Sai ngay.");

            return is;
        }
        catch (const exception& e)
        {
            cout << "Loi: " << e.what() << endl;
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            return is >> date;
        }
    }

    friend ostream& operator << (ostream& os, Date date){
        return os << date.info();
    }

    // Operators
    Date operator + (const int& n) const
    {
        Date d = *this;
        d.day += n;
        while (d.day > GetDayInMonth(d.month, d.year))
        {
            d.day -= GetDayInMonth(d.month, d.year);
            d.month++;
            if (d.month > 12)
            {
                d.month = 1;
                d.year++;
            }
        }
        return d;
    }

    Date operator - (const int& n) const
    {
        Date d = *this;
        d.day -= n;
        while (d.day <= 0)
        {
            d.month--;
            if (d.month == 0)
            {
                d.month = 12;
                d.year--;
            }
            if (d.year < 1)
                throw runtime_error("Ngay khong hop le.");
            d.day += GetDayInMonth(d.month, d.year);
        }

        return d;
    }
};

int main()
{
    Date d1;
    cin >> d1;
    cout << "Ngay ke tiep: " << d1 + 1 << endl;
    try { cout << "Ngay ngay truoc: " << d1 - 1 << endl; }
    catch (const runtime_error& e)
        {cout <<"Loi: " << e.what() << endl;};
    cout << "Ngay thu " << d1.NoOfDay() << " trong nam."<< endl;
}
