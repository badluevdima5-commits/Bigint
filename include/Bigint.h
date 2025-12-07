#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <cstddef>
#include <stdexcept>
#include <iostream>

class Bigint {
public:
    // конструкторы
    Bigint();
    Bigint(int num);
    Bigint(long num);
    Bigint(const Bigint& arr);
    Bigint(const char* str);
    ~Bigint();
    //оператор присваивания
    Bigint& operator=(const Bigint& other);
    //операторы сравнения
    bool operator==(const Bigint& other) const;
    bool operator>(const Bigint& other) const;
    bool operator<(const Bigint& other) const;
    bool operator>=(const Bigint& other) const;
    bool operator<=(const Bigint& other) const;
    bool operator!=(const Bigint& other) const;
    //арифметические опреаторы
    Bigint operator-() const;
    Bigint& operator-=(const Bigint& other);
    Bigint& operator+=(const Bigint& other);
    Bigint& operator*=(const Bigint& other);
    Bigint& operator/=(const Bigint& other);
    Bigint operator+(const Bigint& other) const;
    Bigint operator-(const Bigint& other) const;
    Bigint operator*(const Bigint& other) const;
    Bigint operator/(const Bigint& divisor) const;
    //перегрузка для int & long
    Bigint& operator-=(int num);
    Bigint& operator+=(int num);
    Bigint& operator*=(int num);
    Bigint& operator/=(int num);
    Bigint& operator-=(long num);
    Bigint& operator+=(long num);
    Bigint& operator*=(long num);
    Bigint& operator/=(long num);
    Bigint operator+(int num) const;
    Bigint operator+(long num) const;
    Bigint operator-(int num) const;
    Bigint operator-(long num) const;
    Bigint operator*(int num) const;
    Bigint operator*(long num) const;
    Bigint operator/(int num) const;
    Bigint operator/(long num) const;
    //перегрузка операторов сравнения
    bool operator==(int num) const;
    bool operator==(long num) const;
    bool operator!=(int num) const;
    bool operator!=(long num) const;
    bool operator>(int num) const;
    bool operator>(long num) const;
    bool operator<(int num) const;
    bool operator<(long num) const;
    bool operator>=(int num) const;
    bool operator>=(long num) const;
    bool operator<=(int num) const;
    bool operator<=(long num) const;

    friend bool operator==(int left, const Bigint& right) {
        return Bigint(left) == right;
    }
    friend bool operator!=(int left, const Bigint& right) {
        return Bigint(left) != right;
    }
    friend bool operator>(int left, const Bigint& right) {
        return Bigint(left) > right;
    }
    friend bool operator<(int left, const Bigint& right) {
        return Bigint(left) < right;
    }
    friend bool operator>=(int left, const Bigint& right) {
        return Bigint(left) >= right;
    }
    friend bool operator<=(int left, const Bigint& right) {
        return Bigint(left) <= right;
    }
    friend bool operator==(long left, const Bigint& right) {
        return Bigint(left) == right;
    }
    friend bool operator!=(long left, const Bigint& right) {
        return Bigint(left) != right;
    }
    friend bool operator>(long left, const Bigint& right) {
        return Bigint(left) > right;
    }
    friend bool operator<(long left, const Bigint& right) {
        return Bigint(left) < right;
    }
    friend bool operator>=(long left, const Bigint& right) {
        return Bigint(left) >= right;
    }
    friend bool operator<=(long left, const Bigint& right) {
        return Bigint(left) <= right;
    }

     // Арифметические с int и long
    friend Bigint operator+(int left, const Bigint& right) {
        return Bigint(left) + right;
    }
    friend Bigint operator-(int left, const Bigint& right) {
        return Bigint(left) - right;
    }
    friend Bigint operator*(int left, const Bigint& right) {
        return Bigint(left) * right;
    }
    friend Bigint operator/(int left, const Bigint& right) {
        return Bigint(left) / right;
    }
    friend Bigint operator+(long left, const Bigint& right) {
        return Bigint(left) + right;
    }
    friend Bigint operator-(long left, const Bigint& right) {
        return Bigint(left) - right;
    }
    friend Bigint operator*(long left, const Bigint& right) {
        return Bigint(left) * right;
    }
    friend Bigint operator/(long left, const Bigint& right) {
        return Bigint(left) / right;
    }

    std::size_t size() const;
    friend std::ostream& operator<<(std::ostream& os, const Bigint& num);
private:
    char* digits_;
    std::size_t size_;
    bool negative_;
};
#endif