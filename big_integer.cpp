#include "big_integer.hpp"
#include <iostream>
#include <climits>
#include <algorithm>


big_integer::big_integer()
{
    v.push_back(0);
    sign = 0;
}

big_integer::big_integer(big_integer && other) {
    *this = other;
}

big_integer::big_integer(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
}

big_integer::big_integer(int a)
{
    this->v.push_back((unsigned int)abs(a));
    if (a)
        sign = (a < 0) ? -1 : 1;
    else
        sign = 0;
}

big_integer::~big_integer()
{
}

big_integer& big_integer::operator=(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs) {
    long long int d = 0;
    this->v.resize(std::max(this->v.size(), rhs.v.size()));
    if (this->sign == 0) {
        *this = rhs;
        return *this;
    }
    if (rhs.sign == 0)
        return *this;
    long long int s;
    if (this->sign == rhs.sign) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i >= rhs.v.size())
                s = (long long int) v[i] + d;
            else
                s = (long long int) v[i] + (long long int) rhs.v[i] + d;
            d = s / (UINT_MAX);
            v[i] = (unsigned  int) s % (UINT_MAX);
        }
        if (d != 0)
            v.push_back((unsigned int)d);
    }
    else {
        std::vector<unsigned int> temp = rhs.v;
        if (*this == -rhs)
            return *this = 0;

        if (sign == 1 && *this < -rhs || sign == -1 && -*this < rhs) {
            sign = -sign;
            std::swap(this->v, temp);
        }

        for (size_t i = 0; i < v.size(); ++i) {
            if (i >= rhs.v.size())
                s = (long long int) v[i] + d;
            else {
                if (v[i] >= temp[i])
                    s = (long long int) v[i] - (long long int) temp[i] + d;
                else {
                    s = (long long int) v[i] + UINT_MAX - (long long int) temp[i] + d;
                    d = -1;
                }
            }
            if (s < 0) {
                v[i] = UINT_MAX - 1;
                d = -1;
            }
            else {
                v[i] = (unsigned int) s % UINT_MAX;
                d = 0;
            }
        }
    }

    while (v[v.size() - 1] == 0)
        v.pop_back();

    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return *this += - rhs;
}

big_integer& big_integer::operator*=(unsigned int rhs) {

    uint64_t s, d = 0;
    if (!sign || !rhs) {
        return *this = 0;
    }
    for (size_t i = 0; i < v.size(); i++) {
        s = (uint64_t)v[i] * (uint64_t)rhs + d;
        v[i] = (unsigned int) s % UINT_MAX;
        d = s / UINT_MAX;
    }
    if (d)
        v.push_back((unsigned int) d);
    return *this;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    sign *= rhs.sign;
    if (!sign)
        return *this;
    big_integer temp1 = *this, temp2 = 0;
    for (size_t i = 0; i < rhs.v.size(); i++) {
        temp1 *= rhs.v[i];
        for (int j = 0; j < i; j++)
            temp1.v.insert(v.begin(), 0);
        temp2 += temp1;
        temp1 = *this;
    }
    return *this = temp2;
}

big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    big_integer temp(*this);
    temp.sign = -temp.sign;
    return temp;
}

big_integer& big_integer::operator++() {
    return *this += 1;
}

big_integer big_integer::operator++(int) {
    big_integer temp(*this);
    ++*this;
    return temp;
}

big_integer& big_integer::operator--() {
    return *this -= 1;
}

big_integer big_integer::operator--(int) {
    big_integer temp(*this);
    --*this;
    return temp;
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

bool big_integer::operator==(big_integer const& b) const {
    return (this->v == b.v && this->sign == b.sign);
}

bool big_integer::operator!=(big_integer const& b) const {
    return (!(*this == b));
}

bool big_integer::operator<(big_integer const& b) const {
    if (*this == b)
        return false;
    if (this->v < b.v)
        return (b.sign == 1);
    else //a.v >= b.v
        return (this->sign == -1);
}

bool big_integer::operator>(big_integer const& b) const {
    return (-*this < -b);
}

bool big_integer::operator<=(big_integer const& b) const {
    return (*this < b || *this == b);
}

bool big_integer::operator>=(big_integer const& b) const{
    return (*this > b || *this == b);
}


/*
std::ostream& operator<<(std::ostream& s, big_integer const& a) {

}*/
