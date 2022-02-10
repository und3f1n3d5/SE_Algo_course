#include <iostream>
#include <vector>
#include <string>


class Rational {
private:

    int64_t nominator = 0, denominator = 1;

    class DivideByZero: std::exception {};

    static void reduce(Rational &r);


    static void Check(Rational &r);

public:
    Rational() = default;

    Rational &operator=(const Rational &right);

    explicit Rational(const int64_t &p, const int64_t &q) {
        nominator = p;
        denominator = q;
        if (q == 0)
            throw DivideByZero();
        Check(*this);
    }

    Rational(const int64_t &i) {
        nominator = i;
        denominator = 1;
    }

    Rational(const int &i) {
        nominator = i;
        denominator = 1;
    }


    explicit operator bool () const;

    std::string toString() const;

    Rational &operator+=(const Rational &right);
    Rational &operator-=(const Rational &right);
    Rational &operator*=(const Rational &right);
    Rational &operator/=(const Rational &right);


    const Rational operator--(int);
    Rational& operator--();
    const Rational operator++(int);
    Rational& operator++();

    Rational operator-();
    Rational operator+() const;

    friend bool operator>(const Rational &left, const Rational &right);

    std::string asDecimal(size_t precision = 0) const;

    explicit operator double () const;
};

Rational operator+(const Rational &left, const Rational &right);
Rational operator-(const Rational &left, const Rational &right);
Rational operator*(const Rational &left, const Rational &right);
Rational operator/(const Rational &left, const Rational &right);

bool operator==(const Rational &left, const Rational &right);
bool operator>=(const Rational &left, const Rational &right);
bool operator<=(const Rational &left, const Rational &right);
bool operator<(const Rational &left, const Rational &right);
bool operator>(const Rational &left, const Rational &right);
bool operator!=(const Rational &left, const Rational &right);
