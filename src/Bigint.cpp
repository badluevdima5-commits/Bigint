#include "../include/Bigint.h"
#include <cstring>
#include <cstdlib>
using namespace std;
Bigint::Bigint() {
    digits_ = new char[2];
    digits_[0] = '0';
    digits_[1] = '\0';
    size_ = 1;
    negative_ = false;
}
Bigint::Bigint(int num) {
    if (num == 0) {
        digits_ = new char[2];
        digits_[0] = '0';
        digits_[1] = '\0';
        size_ = 1;
        negative_ = false;
        return;
    }
    negative_ = num < 0;
    int tmp = abs(num);
    size_ = 0;
    int tmp2 = tmp;
    while (tmp2 != 0) {
        tmp2 /= 10;
        size_++;
    }
    digits_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; i++) {
        digits_[size_ - 1 - i] = '0' + (tmp % 10);
        tmp /= 10;
    }
    digits_[size_] = '\0';
}
Bigint::Bigint(long num) {
    if (num == 0) {
        digits_ = new char[2];
        digits_[0] = '0';
        digits_[1] = '\0';
        size_ = 1;
        negative_ = false;
        return;
    }
    negative_ = num < 0;
    long tmp = abs(num);
    size_ = 0;
    long tmp2 = tmp;
    while (tmp2 != 0) {
        tmp2 /= 10;
        size_++;
    }
    digits_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; i++) {
        digits_[size_ - 1 - i] = '0' + (tmp % 10);
        tmp /= 10;
    }
    digits_[size_] = '\0';
}
Bigint::Bigint(const Bigint& other) {
    size_ = other.size_;
    digits_ = new char[size_ + 1];
    negative_ = other.negative_;
    for (size_t i = 0; i < size_; i++)
        digits_[i] = other.digits_[i];
    digits_[size_] = '\0';
}
Bigint::Bigint(const char* str) {
    size_t start = 0;
    negative_ = false;
    if (str == nullptr || str[0] == '\0') {
        digits_ = new char[2];
        digits_[0] = '0';
        digits_[1] = '\0';
        size_ = 1;
        negative_ = false;
        return;
    }
    if (str[0] == '-') {
        negative_ = true;
        start = 1;
    }
    else if (str[0] == '+')
        start = 1;
    while (str[start] == '0' && str[start + 1] != '\0')
        start++;

    size_t len = strlen(str);
    for (size_t i = start; i < len; i++)
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("Invalid char");
        }

    size_ = len - start;
    if (size_ == 0) {
        digits_ = new char[2];
        digits_[0] = '0';
        digits_[1] = '\0';
        size_ = 1;
        negative_ = false;
        return;
    }

    digits_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; i++)
        digits_[i] = str[i + start];
    digits_[size_] = '\0';

    if (size_ == 1 && digits_[0] == '0') negative_ = false;
    
}
Bigint::~Bigint() {
    delete[] digits_;
}
Bigint& Bigint::operator=(const Bigint& other) {
    if (this != &other) {
        delete[] digits_;
        size_ = other.size_;
        digits_ = new char[size_ + 1];
        negative_ = other.negative_;
        for (size_t i = 0; i < size_; i++)
            digits_[i] = other.digits_[i];
        digits_[size_] = '\0';
    }
    return *this;
}
bool Bigint::operator==(const Bigint& other) const {
    if (negative_ != other.negative_ || size_ != other.size_) return false;
    for (size_t i = 0; i < size_; i++)
        if (digits_[i] != other.digits_[i]) return false;

    return true;
}
bool Bigint::operator>(const Bigint& other) const {
    if (negative_ && !other.negative_) return false;
    if (!negative_ && other.negative_) return true;
    if (!negative_) {
        if (size_ > other.size_) return true;
        if (size_ < other.size_) return false;
        for (size_t i = 0; i < size_; i++) {
            if (digits_[i] > other.digits_[i]) return true;
            if (digits_[i] < other.digits_[i]) return false;
        }
        return false;
    }
    if (negative_) {
        if (size_ < other.size_) return true;
        if (size_ > other.size_) return false;
        for (size_t i = 0; i < size_; i++) {
            if (digits_[i] < other.digits_[i]) return true;
            if (digits_[i] > other.digits_[i]) return false;
        }
        return false;
    }
    return false;
}
bool Bigint::operator<(const Bigint& other) const {
    return (!(*this == other) && !(*this > other));
}
bool Bigint::operator>=(const Bigint& other) const {
    return (*this > other || *this == other);
}
bool Bigint::operator<=(const Bigint& other) const {
    return (*this < other || *this == other);
}
bool Bigint::operator!=(const Bigint& other) const {
    return !(*this == other);
}
Bigint Bigint::operator-() const {
    Bigint res(*this);
    if (!(res.size_ == 1 && res.digits_[0] == '0'))
        res.negative_ = !res.negative_;
    return res;
}
Bigint& Bigint::operator*=(const Bigint& other) {
    *this = *this * other;
    return *this;
}
Bigint& Bigint::operator/=(const Bigint& other) {
    *this = *this / other;
    return *this;
}
Bigint& Bigint::operator+=(const Bigint& other) {
    *this = *this + other;
    return *this;
}
Bigint& Bigint::operator-=(const Bigint& other) {
    *this = *this - other;
    return *this;
}
Bigint Bigint::operator+(const Bigint& other) const {
    if (negative_ != other.negative_) {
        if (negative_) return other - (-*this);
        else return *this - (-other);
    }
    Bigint result;
    result.size_ = max(size_, other.size_);
    result.digits_ = new char[result.size_ + 1];
    int shift = 0;
    for (size_t i = 0; i < result.size_ || shift > 0; i++) {
        int digit1;
        int digit2;
        if (i < size_) digit1 = digits_[size_ - 1 - i] - '0';
        else digit1 = 0;
        if (i < other.size_) digit2 = other.digits_[other.size_ - 1 - i] - '0';
        else digit2 = 0;

        int sum = digit1 + digit2 + shift;
        shift = sum / 10;
        int digit_sum = sum % 10;
        result.digits_[result.size_ - 1 - i] = '0' + digit_sum;
    }
    result.digits_[result.size_] = '\0';
    result.negative_ = negative_;
    return result;
}
Bigint Bigint::operator-(const Bigint& other) const {
    if (negative_ != other.negative_)
        return *this + (-other);

    bool result_negative = false;
    const Bigint* bigger = this;
    const Bigint* smaller = &other;

    bool this_bigger = true;
    if (size_ != other.size_)
        this_bigger = (size_ > other.size_);
    else
        for (size_t i = 0; i < size_; i++)
            if (digits_[i] != other.digits_[i]) {
                this_bigger = (digits_[i] > other.digits_[i]);
                break;
            }

    if (!this_bigger) {
        bigger = &other;
        smaller = this;
        result_negative = !negative_;
    }
    else result_negative = negative_;

    Bigint result;
    result.size_ = bigger->size_;
    result.digits_ = new char[result.size_ + 1];
    int dot = 0;

    for (size_t i = 0; i < result.size_; i++) {
        int digit1;
        if (i < bigger->size_) digit1 = bigger->digits_[bigger->size_ - 1 - i] - '0';
        else  digit1 = 0;
        int digit2;
        if (i < smaller->size_) digit2 = smaller->digits_[smaller->size_ - 1 - i] - '0';
        else digit2 = 0;

        int diff = digit1 - digit2 - dot;
        if (diff < 0) {
            diff += 10;
            dot = 1;
        }
        else dot = 0;
        result.digits_[result.size_ - 1 - i] = '0' + diff;
    }
    result.digits_[result.size_] = '\0';
    while (result.size_ > 1 && result.digits_[0] == '0') {
        for (size_t i = 0; i < result.size_ - 1; i++)
            result.digits_[i] = result.digits_[i + 1];
        result.size_--;
    }
    result.negative_ = result_negative;
    if (result.size_ == 1 && result.digits_[0] == '0') result.negative_ = false;
    return result;
}
Bigint Bigint::operator*(const Bigint& other) const {
    Bigint result;
    result.size_ = size_ + other.size_;
    result.digits_ = new char[result.size_ + 1];

    for (size_t i = 0; i < result.size_; i++)
        result.digits_[i] = '0';

    result.digits_[result.size_] = '\0';
    int mul;
    for (size_t i = 0; i < size_; i++) {
        int shift = 0;
        for (size_t j = 0; j < other.size_; j++) {
            mul = (digits_[size_ - 1 - i] - '0') * (other.digits_[other.size_ - 1 - j] - '0')
                + shift + (result.digits_[result.size_ - (i + j) - 1] - '0');

            result.digits_[result.size_ - (i + j) - 1] = '0' + (mul % 10);
            shift = mul / 10;
        }
        if (shift != 0) result.digits_[result.size_ - 1 - (i + other.size_)] = '0' + shift;
    }
    while (result.size_ > 1 && result.digits_[0] == '0') {
        for (size_t i = 0; i < result.size_ - 1; i++)
            result.digits_[i] = result.digits_[i + 1];
        result.size_--;
    }
    result.negative_ = (negative_ != other.negative_);
    if (result.size_ == 1 && result.digits_[0] == '0') result.negative_ = false;
    return result;
}
Bigint Bigint::operator/(const Bigint& other) const {
    if (other == Bigint(0)) throw runtime_error("Division by zero");
    if (*this == Bigint(0))  return Bigint(0);

    Bigint dend_abs;
    if (negative_) dend_abs = -(*this);
    else dend_abs = *this;

    Bigint dsor_abs;
    if (other.negative_) dsor_abs = -other;
    else dsor_abs = other;

    if (dend_abs < dsor_abs) return Bigint(0);

    if (dend_abs == dsor_abs) {
        Bigint result(1);
        result.negative_ = (negative_ != other.negative_);
        return result;
    }
    if (dsor_abs == Bigint(1)) {
        Bigint result(*this);
        result.negative_ = (negative_ != other.negative_);
        return result;
    }
    Bigint result;
    Bigint current;

    result.size_ = size_;
    result.digits_ = new char[result.size_ + 1];
    for (size_t i = 0; i < result.size_; i++)
        result.digits_[i] = '0';
    result.digits_[result.size_] = '\0';
    Bigint temp = dsor_abs;
    for (size_t i = 0; i < size_; i++) {
        current = current * Bigint(10) + Bigint(digits_[i] - '0');
        int kent_digit = 0;

        while (current >= temp) {
            kent_digit++;
            temp = dsor_abs * Bigint(kent_digit + 1);
        }
        result.digits_[i] = '0' + kent_digit;
        current = current - dsor_abs * Bigint(kent_digit);
    }
    while (result.size_ > 1 && result.digits_[0] == '0') {
        for (size_t i = 0; i < result.size_ - 1; i++)
            result.digits_[i] = result.digits_[i + 1];
        result.size_--;
    }
    result.negative_ = (negative_ != other.negative_);

    if (result.size_ == 1 && result.digits_[0] == '0')
        result.negative_ = false;
    return result;
}
//перегрузка для int & long
Bigint Bigint::operator+(int num) const {
    return *this + Bigint(num);
}
Bigint Bigint::operator+(long num) const {
    return *this + Bigint(num);
}
Bigint Bigint::operator-(int num) const {
    return *this - Bigint(num);
}
Bigint Bigint::operator-(long num) const {
    return *this - Bigint(num);
}
Bigint Bigint::operator*(int num) const {
    return *this * Bigint(num);
}
Bigint Bigint::operator*(long num) const {
    return *this * Bigint(num);
}
Bigint Bigint::operator/(int num) const {
    return *this / Bigint(num);
}
Bigint Bigint::operator/(long num) const {
    return *this / Bigint(num);
}
Bigint& Bigint::operator-=(int num){
    return *this -= Bigint(num);
}
Bigint& Bigint::operator+=(int num){
    return *this += Bigint(num);
}
Bigint& Bigint::operator*=(int num){
    return *this *= Bigint(num);
}
Bigint& Bigint::operator/=(int num){
    return *this /= Bigint(num);
}
Bigint& Bigint::operator-=(long num){
    return *this -= Bigint(num);
}
Bigint& Bigint::operator+=(long num){
    return *this += Bigint(num);
}
Bigint& Bigint::operator*=(long num){
    return *this *= Bigint(num);
}
Bigint& Bigint::operator/=(long num){
    return *this /= Bigint(num);
}
// Операторы сравнения для int и long
bool Bigint::operator==(int num) const {
    return *this == Bigint(num);
}
bool Bigint::operator==(long num) const {
    return *this == Bigint(num);
}
bool Bigint::operator!=(int num) const {
    return *this != Bigint(num);
}
bool Bigint::operator!=(long num) const {
    return *this != Bigint(num);
}
bool Bigint::operator>(int num) const {
    return *this > Bigint(num);
}
bool Bigint::operator>(long num) const {
    return *this > Bigint(num);
}
bool Bigint::operator<(int num) const {
    return *this < Bigint(num);
}
bool Bigint::operator<(long num) const {
    return *this < Bigint(num);
}
bool Bigint::operator>=(int num) const {
    return *this >= Bigint(num);
}
bool Bigint::operator>=(long num) const {
    return *this >= Bigint(num);
}
bool Bigint::operator<=(int num) const {
    return *this <= Bigint(num);
}
bool Bigint::operator<=(long num) const {
    return *this <= Bigint(num);
}
size_t Bigint::size() const {
    return size_;
}
std::ostream& operator<<(std::ostream& os, const Bigint& num) {
    if (num.negative_) os << '-';
    for (size_t i = 0; i < num.size_; i++)
        os << num.digits_[i];
    return os;
}