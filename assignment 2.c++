// question 1 


#include <iostream>
using namespace std;

void concessionByValue(long long fee, int percent) {
    fee -= fee * percent / 100;   // only the local copy changes
}
void concessionByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;   // changes caller's fee
}
void concessionByPointer(long long* fee, int percent) {
    if (fee != nullptr)
        *fee -= (*fee) * percent / 100;
}
int main() {
    long long a = 45000, b = 45000, c = 45000;
    concessionByValue(a, 10);
    concessionByReference(b, 10);
    concessionByPointer(&c, 10);
    cout << a << '\\n' << b << '\\n' << c << '\\n';
}


// question 2


#include <iostream>
using namespace std;

int& highestMark(int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}

int main() {
    int marks[] = {76, 91, 84, 88};
    highestMark(marks, 4) += 2;
    cout << highestMark(marks, 4) << '\\n';
}


// question 3


#include <iostream>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false,
              bool insured = false) {
    double amount = 40.0 + 12.0 * weightKg;
    if (express) amount += 30.0;
    if (insured) amount += 15.0;
    return amount;
}

// Integer input is explicitly interpreted as grams.
double charge(int weightGrams) {
    return 40.0 + 12.0 * (weightGrams / 1000.0);
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    cout << charge(2) << '\\n';
    cout << charge(2.0) << '\\n';
    cout << charge(2.0f, true) << '\\n';
    cout << charge(500) << '\\n';
    cout << charge(1.5, false, true) << '\\n';
    Parcel p{3.0, true, false};
    cout << charge(p) << '\\n';
}


// question 4 


#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    string accountNumber;
    long long balance;
    long long transactions[10];
    int count;

    void record(long long amount) {
        if (count < 10) {
            transactions[count++] = amount;
        } else {
            for (int i = 1; i < 10; ++i)
                transactions[i - 1] = transactions[i];
            transactions[9] = amount;
        }
    }

public:
    SavingsAccount(const string& number, long long opening)
        : accountNumber(number), balance(opening), count(0) {}

    void deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::deposit(long long amount) {
    if (amount <= 0) return;
    balance += amount;
    record(amount);
}

bool SavingsAccount::withdraw(long long amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    record(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber
         << " Balance: " << balance << '\\n';
    for (int i = 0; i < count; ++i)
        cout << (transactions[i] >= 0 ? "Deposit " : "Withdrawal ")
             << transactions[i] << '\\n';
}

int main() {
    SavingsAccount account("SB1024", 1000);
    account.deposit(200);
    account.withdraw(150);
    account.miniStatement();
}


// question 5


#include <iostream>
#include <string>
using namespace std;

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    string name;
public:
    explicit BusTicket(const string& n) : seat(0), name(n) {
        if (issued < CAPACITY) {
            ++issued;
            seat = issued;
        }
    }
    static int count() { return issued; }
    void print() const {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat) : string("Waiting"))
             << '\\n';
    }
};
int BusTicket::issued = 0;

int main() {
    BusTicket trip[4] = {
        BusTicket("Asha"), BusTicket("Bala"),
        BusTicket("Chitra"), BusTicket("Dev")
    };
    for (const BusTicket& t : trip) t.print();
    cout << "Issued: " << BusTicket::count() << '\\n';
}


// question 6

#include <iostream>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    int difference = first - second;
    return difference < 0 ? -difference : difference;
}

bool earlier(const Time& a, const Time& b) {
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\\n';
    Time noon(12, 0), beforeNoon(11, 59);
    cout << minutesBetween(noon, beforeNoon) << ' '
         << earlier(beforeNoon, noon) << '\\n';
    cout << minutesBetween(noon, noon) << ' '
         << earlier(noon, noon) << '\\n';
}

