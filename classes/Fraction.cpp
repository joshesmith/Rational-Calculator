//
// Created by j.smith on 6/02/2020.
//

#include "Fraction.h"
#include <assert.h>
int Fraction::gcd(int a, int b) {
    return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
};

void Fraction::reduce(){
    int current_gcd = gcd(numerator,denominator);
    numerator = numerator/current_gcd;
    denominator = denominator/current_gcd;
};

Fraction::Fraction(int numer, int denom)
        :numerator{numer},denominator{denom}{
    reduce();
};

bool Fraction::is_zero() const {
    return numerator == 0;
};

bool Fraction::is_one() const {
    return (numerator == 1) && (denominator == 1);
};

bool Fraction::is_int() const {
    return (denominator == 1);
}

Fraction Fraction::int_power(int power){
    if (power==0){
        return Fraction(1);
    } else {
        int new_numer{numerator};
        int new_denom{denominator};

        for (int i{1}; i < abs(power); i++) {
            new_numer *= numerator;
            new_denom *= denominator;
        }
        if (power < 0) {
            std::swap(new_numer,new_denom);
        }
        return Fraction(new_numer,new_denom);
    }
}

Fraction Fraction::int_power(Fraction power){
    assert(power.denominator == 1);
    return int_power(power.numerator);
}




std::ostream& operator<<(std::ostream &out, const Fraction &f1){
    if (f1.denominator == 1)
        out << f1.numerator;
    else
        out << f1.numerator << '/' << f1.denominator;
    return out;
}

std::istream& operator>>(std::istream &in, Fraction &f1){
    in >> f1.numerator;
    in >> f1.denominator;
    f1.reduce();

    return in;
};

Fraction operator+(const Fraction &f1, const Fraction &f2){
    int new_numer = f1.numerator*f2.denominator+f2.numerator*f1.denominator;
    int new_denom = f1.denominator*f2.denominator;
    return Fraction(new_numer,new_denom);
};

Fraction operator+(const Fraction &f1, int integer1){
    int new_numer = f1.numerator+integer1*f1.denominator;
    return Fraction(new_numer,f1.denominator);
};

Fraction operator+(int integer1, const Fraction &f1){
    return f1 + integer1; //calls the opposite order function
}

Fraction operator-(const Fraction &f1, const Fraction &f2){
    int new_numer = f1.numerator*f2.denominator-f2.numerator*f1.denominator;
    int new_denom = f1.denominator*f2.denominator;
    return Fraction(new_numer,new_denom);
};

Fraction operator-(const Fraction &f1, int integer1){
    int new_numer = f1.numerator-integer1*f1.denominator;
    return Fraction(new_numer,f1.denominator);
};

Fraction operator-(int integer1, const Fraction &f1){
    return f1 - integer1; //calls the opposite order function
}

Fraction operator*(const Fraction &f1, const Fraction &f2){
    int new_numer = f1.numerator*f2.numerator;
    int new_denom = f1.denominator*f2.denominator;
    return Fraction(new_numer,new_denom);
};
Fraction operator*(const Fraction &f1, int integer1){
    int new_numer = f1.numerator*integer1;
    return Fraction(new_numer,f1.denominator);
};
Fraction operator*(int integer1, const Fraction &f1){
    return f1 * integer1;
};

Fraction operator/(const Fraction &f1, const Fraction &f2){
    int new_numer = f1.numerator*f2.denominator;
    int new_denom = f1.denominator*f2.numerator;
    return Fraction(new_numer,new_denom);
};

Fraction operator/(const Fraction &f1, int integer1){
    int new_denom = f1.denominator*integer1;
    return Fraction(f1.numerator,new_denom);
};
Fraction operator/(int integer1,const Fraction &f1){
    return f1 / integer1;
};

bool operator<(const Fraction &f1, const Fraction &f2){
  return f1.numerator*f2.denominator < f2.numerator*f1.denominator;
};
bool operator<(const Fraction &f1, int integer1){
    return f1.numerator < integer1*f1.denominator;
};
bool operator<(int integer1, const Fraction &f2){
    return integer1*f2.denominator < f2.numerator;
};

bool operator>(const Fraction &f1, const Fraction &f2){
    return f1.numerator*f2.denominator > f2.numerator*f1.denominator;
};
bool operator>(const Fraction &f1, int integer1){
    return f1.numerator > integer1*f1.denominator;
};
bool operator>(int integer1, const Fraction &f2){
    return integer1*f2.denominator > f2.numerator;
};

bool operator==(const Fraction &f1, const Fraction &f2){
    return f1.numerator*f2.denominator == f2.numerator*f1.denominator;
};
bool operator==(const Fraction &f1, int integer1){
    return f1.numerator == integer1*f1.denominator;
};
bool operator==(int integer1, const Fraction &f2){
    return integer1*f2.denominator == f2.numerator;
};

bool operator<=(const Fraction &f1, const Fraction &f2){
    return f1.numerator*f2.denominator <= f2.numerator*f1.denominator;
};
bool operator<=(const Fraction &f1, int integer1){
    return f1.numerator <= integer1*f1.denominator;
};
bool operator<=(int integer1, const Fraction &f2){
    return integer1*f2.denominator <= f2.numerator;
};

bool operator>=(const Fraction &f1, const Fraction &f2){
    return f1.numerator*f2.denominator >= f2.numerator*f1.denominator;
};
bool operator>=(const Fraction &f1, int integer1){
    return f1.numerator >= integer1*f1.denominator;
};
bool operator>=(int integer1, const Fraction &f2){
    return integer1*f2.denominator >= f2.numerator;
};

Fraction::operator double(){
    return static_cast<double>(numerator)/ static_cast<double >(denominator);
};

Fraction::operator int(){
    return numerator/denominator;
};