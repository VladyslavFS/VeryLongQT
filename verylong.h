#pragma once
#ifndef VERYLONG_H
#define VERYLONG_H

#include <vector>
#include <string>

using namespace std;

class VeryLong {
private:
    vector<int> digits;
    bool isNegative = false;


    VeryLong difference(const VeryLong& other) const;
    VeryLong summ(const VeryLong& other) const;



public:
    VeryLong();
    VeryLong(const string& numStr);
    VeryLong operator+(const VeryLong& other) const;
    VeryLong operator-(const VeryLong& other) const;
    VeryLong operator/(const VeryLong& other) const;
    VeryLong operator*(const VeryLong& other) const;
    bool operator<(const VeryLong& other) const;
    bool operator>(const VeryLong& other) const;
    bool operator==(const VeryLong& other) const;
    string toString() const;
    void input();
    void print() const;
};

#endif // VERYLONG_H

