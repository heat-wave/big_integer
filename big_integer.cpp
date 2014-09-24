#include <big_integer.h>
#include <iostream>
#include <climits>
#include <algorithm>

big_integer::big_integer()
{
    v.push_back(0);
    sign = 0;
}

big_integer::big_integer(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
}

big_integer::big_integer(int a)
{
    this->v.push_back(std::abs(a));
    if (a)
        sign = (a < 0) ? -1 : 1;
    else
        sign = 0;
}

big_integer::~big_integer()
{
    v.clear();
    // ~sign; ???
    sign = 0;
}

big_integer& big_integer::operator=(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs) {
    long int d = 0;
    this->v.resize(std::max(this->v.size(), rhs.v.size()));
    if (this->sign == 0) {
        *this = rhs;
        return *this;
    }
    if (rhs.sign == 0)
        return *this;
    long int s;
    if (this->sign == rhs.sign) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i >= rhs.v.size())
                s = (long int) v[i] + d;
            else
                s = (long int) v[i] + (long int) rhs.v[i] + d;
            d = s / (UINT_MAX);
            v[i] = s % (UINT_MAX);
        }
        if (d != 0)
            v.push_back(d);
    }
    else {
        if (*this == -rhs)
            return *this = 0;

        if (sign == 1 && *this < -rhs || sign == -1 && -*this < rhs) {
            sign = -sign;
            std::swap(this->v, rhs.v);
        }

        for (size_t i = 0; i < v.size(); ++i) {
            if (i >= rhs.v.size())
                s = (long int) v[i] + d;
            else {
                if (v[i] >= rhs.v[i])
                    s = (long int) v[i] - (long int) rhs.v[i] + d;
                else {
                    s = (long int) v[i] + UINT_MAX - (long int) rhs.v[i] + d;
                    d = -1;
                }
            }
            if (s < 0) {
                v[i] = UINT_MAX - 1;
                d = -1;
            }
            else {
                v[i] = s % UINT_MAX;
                d = 0;
            }
        }
    }

    while (v[v.size() - 1] == 0)
        v.pop_back();

    return *this;
}