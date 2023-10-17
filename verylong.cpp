#include "verylong.h"
#include <iostream>
#include <cctype>

VeryLong::VeryLong() {
    digits.push_back(0);
}

VeryLong::VeryLong(const string& numStr) {
    if (!numStr.empty() && numStr[0] == '-') {
        isNegative = true;
        for (int i = numStr.length() - 1; i >= 1; i--) {
            digits.push_back(numStr[i] - '0');
        }
    }
    else {
        isNegative = false;
        for (int i = numStr.length() - 1; i >= 0; i--) {
            digits.push_back(numStr[i] - '0');
        }
    }
}

string VeryLong::toString() const {
    string result;

    if (isNegative) {
        result += '-';
    }

    // Перевірка, чи всі розряди дорівнюють нулю


    for (int i = digits.size() - 1; i >= 0; i--) {
        result += to_string(digits[i]);
    }

    return result;
}



bool VeryLong::operator<(const VeryLong& other) const {
    int size1 = digits.size();
    int size2 = other.digits.size();

    // Порівнюємо розміри векторів
    if (size1 < size2) {
        return true;
    } if (size1 > size2) {
        return false;
    }

    // Розміри векторів однакові, порівнюємо поелементно зліва направо
    for (int i = size1 - 1; i >= 0; i--) {
        if (digits[i] < other.digits[i]) {
            return true;
        }
        else if (digits[i] > other.digits[i]) {
            return false;
        }
    }

    // Вектори рівні
    return false;
};

bool VeryLong::operator>(const VeryLong& other) const {
    int size1 = digits.size();
    int size2 = other.digits.size();
    int maxSize = max(digits.size(), other.digits.size());

    // Порівнюємо розміри векторів
    if (size1 > size2) {
        return true;
    }
    else if (size1 < size2) {
        return false;
    }

    // Розміри векторів однакові, порівнюємо поелементно зліва направо
    for (int i = maxSize - 1; i >= 0; i--) {
        if (digits[i] > other.digits[i]) {
            return true;
        }
        else if (digits[i] < other.digits[i]) {
            return false;
        }
    }

    // Вектори рівні
    return false;
};

bool VeryLong::operator==(const VeryLong& other) const {
    int size1 = digits.size();
    int size2 = other.digits.size();
    int counter = 0;
    if (size1 != size2) {
        return false;
    }

    // Розміри векторів однакові, порівнюємо поелементно зліва направо
    for (int i = size1 - 1; i >= 0; i--) {
        if (digits[i] == other.digits[i]) {
            counter += 1;
        }
    }

    if (counter == size1) {
        return true;
    }

    return false;
};

VeryLong VeryLong::operator+(const VeryLong& other) const {
    VeryLong result;
    VeryLong num1(*this);
    VeryLong num2(other);

    if (num1.isNegative) {
        if (!num2.isNegative) {
            if (num1 > num2) {
                result = num1.difference(num2);
                result.digits.back() = -result.digits.back();
            }
            else {
                result = num2.difference(num1);
            }
        }
        else {
            result = num1.summ(num2);
            result.digits.back() = -result.digits.back();
        }
    }
    else {
        if (num2.isNegative) {
            if (num1 < num2) {
                result = num2.difference(num1);
                result.digits.back() = -result.digits.back();
            }
            else {
                result = num1.difference(num2);
            }
        }
        else {
            result = num1.summ(num2);
        }
    }

    return result;
}

VeryLong VeryLong::operator-(const VeryLong& other) const {
    VeryLong result;
    VeryLong a(*this);
    VeryLong b(other);

    if (a.isNegative && b.isNegative) {
        if (a < b) {
            result = b.difference(a);
        }
        else {
            result = a.difference(b);
        }

        result.digits.back() = -result.digits.back();

    } else if (a.isNegative || b.isNegative) {
        result = a.summ(b);
        if (a.isNegative) {
            result.digits.back() = -result.digits.back();
        }
    } else {

        if (a < b) {
            result = b.difference(a);
            result.digits.back() = -result.digits.back();
        }
        else {
            result = a.difference(b);
        }
    }
    return result;
}

VeryLong VeryLong::operator/(const VeryLong& other) const {
    VeryLong result;
    VeryLong a(*this);
    VeryLong b(other);
    if (b == VeryLong("0")) {
        return VeryLong("0");
    }
    while (a > b || a == b) {
        a = a.difference(b);
        result = result.summ(VeryLong("1"));
    }
    if (a.isNegative && !b.isNegative) {
        return result;
    }
    else if(!a.isNegative && b.isNegative){
        return result;
    }
    else {
        result.digits.back() = -result.digits.back();
    }
    return result;
}

VeryLong VeryLong::operator*(const VeryLong& other) const {
    VeryLong num1(*this);
    VeryLong num2(other);
    VeryLong result;

    // Додаємо a до себе b разів
    for (VeryLong i = VeryLong("0"); i < num2; i = i + VeryLong("1")) {
        result = result.summ(num1);
    }

    if (num1.isNegative || num2.isNegative) {
        if(num1.isNegative && num2.isNegative){
            return result;
        }
        result.digits.back() = -result.digits.back();

    }

    return result;
};

VeryLong VeryLong::difference(const VeryLong& other) const {
    VeryLong result;
    VeryLong a(*this);
    VeryLong b(other);
    int carry = 0; // Перенос з попереднього розряду
    int maxSize = max(digits.size(), other.digits.size());
    for (int i = 0; i < maxSize; i++) {
        if (i == result.digits.size()) {
            result.digits.push_back(0);
        }

        int diff = 0;
        if (i < a.digits.size()) {
            diff += a.digits[i] - carry;
        }
        if (i < b.digits.size()) {
            if (diff - b.digits[i] < 0) {
                diff += 10 - b.digits[i];
                carry = 1;
            }
            else {
                diff -= b.digits[i];
                carry = 0;
            }
        }

        result.digits[i] = diff;
    }
    // Видалити нулі з найвищих розрядів (якщо є)
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }
    return result;
};

VeryLong VeryLong::summ(const VeryLong& other) const {
    VeryLong result;
    VeryLong num1(*this);
    VeryLong num2(other);
    int carry = 0;
    int maxSize = max(num1.digits.size(), num2.digits.size());

    for (int i = 0; i < maxSize; i++) {
        if (i == result.digits.size()) {
            result.digits.push_back(0);
        }

        int sum = carry;
        if (i < num1.digits.size()) {
            sum += num1.digits[i];
        }
        if (i < num2.digits.size()) {
            sum += num2.digits[i];
        }

        carry = sum / 10;
        result.digits[i] = sum % 10;
    }

    if (carry > 0) {
        result.digits.push_back(carry);
    }

    return result;
};
