//
// Created by j.smith on 6/02/2020.
//

#ifndef TUTORIAL_FILE_5_FRACTION_H
#define TUTORIAL_FILE_5_FRACTION_H
#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;
    int static gcd(int a, int b);
    void reduce();
    friend class Surd;
public:
    Fraction(int numer = 0, int denom = 1);

    //printing functions may want to check whether fraction is trivial without accessing private variables.
    bool is_zero() const;
    bool is_one() const;
    bool is_int() const;

    Fraction int_power(int power);
    Fraction int_power(Fraction power);

    friend std::ostream& operator<<(std::ostream &out, const Fraction &f1);
    friend std::istream& operator>>(std::istream &in, Fraction &f1);

    //conveniently friend function declarations count as forward declarations too.
    friend Fraction operator+(const Fraction &f1, const Fraction &f2);
    friend Fraction operator+(const Fraction &f1, int integer1);
    friend Fraction operator+(int integer1,const Fraction &f1);

    friend Fraction operator-(const Fraction &f1, const Fraction &f2);
    friend Fraction operator-(const Fraction &f1, int integer1);
    friend Fraction operator-(int integer1,const Fraction &f1);

    friend Fraction operator*(const Fraction &f1, const Fraction &f2);
    friend Fraction operator*(const Fraction &f1, int integer1);
    friend Fraction operator*(int integer1,const Fraction &f1);

    friend Fraction operator/(const Fraction &f1, const Fraction &f2);
    friend Fraction operator/(const Fraction &f1, int integer1);
    friend Fraction operator/(int integer1,const Fraction &f1);

    friend bool operator<(const Fraction &f1, const Fraction &f2);
    friend bool operator<(const Fraction &f1, int integer1);
    friend bool operator<(int integer1, const Fraction &f2);

    friend bool operator>(const Fraction &f1, const Fraction &f2);
    friend bool operator>(const Fraction &f1, int integer1);
    friend bool operator>(int integer1, const Fraction &f2);

    friend bool operator==(const Fraction &f1, const Fraction &f2);
    friend bool operator==(const Fraction &f1, int integer1);
    friend bool operator==(int integer1, const Fraction &f2);

    friend bool operator<=(const Fraction &f1, const Fraction &f2);
    friend bool operator<=(const Fraction &f1, int integer1);
    friend bool operator<=(int integer1, const Fraction &f2);

    friend bool operator>=(const Fraction &f1, const Fraction &f2);
    friend bool operator>=(const Fraction &f1, int integer1);
    friend bool operator>=(int integer1, const Fraction &f2);

    // overloading typecasts so you can use fractions as parameters to functions which don't know what a fraction is.
    explicit operator double();
    explicit operator int();
};

#endif //TUTORIAL_FILE_5_FRACTION_H
