//
// Created by j.smith on 11/02/2020.
//

#ifndef TUTORIAL_FILE_5_MATH_ELEMENT_H
#define TUTORIAL_FILE_5_MATH_ELEMENT_H
#include "Fraction.h"

class Math_element {
private:
    bool has_fraction;
    Fraction frac;
    char oper;

public:
    Math_element() = delete;
    Math_element(char operator_in);
    Math_element(Fraction fraction1);

    bool is_frac();
    char get_oper();
    Fraction get_frac();

    friend std::ostream& operator<<(std::ostream &out, const Math_element &element1);
};


#endif //TUTORIAL_FILE_5_MATH_ELEMENT_H
