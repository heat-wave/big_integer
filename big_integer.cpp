#include <big_integer.h>
#include <iostream>

big_integer::big_integer()
{
    v.push_back(0);
    sign = false;
}

big_integer::big_integer(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
}

big_integer::big_integer(int a)
{
    v.push_back(a);
    sign = (a < 0);
}

big_integer::~big_integer()
{
    v.clear();
    sign = NULL;
}

big_integer& big_integer::operator=(big_integer const& other)
{
    this->v = other.v;
    this->sign = other.sign;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs)
{
    long int d = 0;
    value.resize(std::max(value.size(), rhs.value.size()));
    if (sign == 0)
    {
        *this = rhs;
        return *this;
    }
    if (rhs.sign == 0)
        return *this;
    if (sign == rhs.sign)
    {
        for(unsigned int i = 0; i < std::max(value.size(), rhs.value.size()); i++)
        {
            long long int s;
            if (i > rhs.value.size())
                s = (long long int)value[i] + d;
            else
                s = (long long int)value[i] + (long long int)rhs.value[i] + d;
            d = s / (4294967296);
            value[i] = s % (4294967296);
        }
        if (d != 0)
            value.push_back(d);
    }
    else if (sign == 1)
    {
        if (*this < -rhs)
            sign = -1;
        if (*this == -rhs)
            return *this = 0;

        for(unsigned int i = 0; i < std::max(value.size(), rhs.value.size()); i++)
        {
            long long int s;
            if (i > rhs.value.size())
                s = (long long int)value[i] + d;
            else
                s = (long long int)value[i] - (long long int)rhs.value[i] + d;
            d = (long int) s / (4294967296);
            value[i] = (long int) abs(s) % (4294967296);
        }
        if (d != 0)
        {
            value.push_back(abs(d));
            if (d < 0)
                sign = -1;
        }
    }
    else
    {
        if (-*this < rhs)
            sign = 1;
        if (-*this == rhs)
            return *this = 0;
        for(unsigned int i = 0; i < std::max(value.size(), rhs.value.size()); i++)
        {
            long long int s;
            if (i > rhs.value.size())
                s = (long long int)value[i] + d;
            else
                s = -(long long int)value[i] + (long long int)rhs.value[i] + d;
            d = s / (4294967296);
            value[i] = abs(s) % (4294967296);
        }
        if (d != 0)
        {
            value.push_back(abs(d));
            if (d < 0)
                sign = 1;
        }
    }
    return *this;
}

