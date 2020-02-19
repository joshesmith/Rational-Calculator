//
// Created by j.smith on 11/02/2020.
//

#include "Math_element.h"
#include <cassert>

Math_element::Math_element(char operator_in)
    :oper{operator_in},has_fraction{false},frac{}
    {};

Math_element::Math_element(Fraction fraction1)
    :frac{fraction1},has_fraction{true},oper{}
    {};

bool Math_element::is_frac(){
    return has_fraction;
}

char Math_element::get_oper(){
    assert(!has_fraction);
    return  oper;
}

Fraction Math_element::get_frac() {
    assert(has_fraction);
    return  frac;
}

std::ostream& operator<<(std::ostream &out, const Math_element &element1){
    if (element1.has_fraction )
        if (element1.frac.is_int()){
            out << element1.frac;
        } else {
            out << '<' << element1.frac << '>';
        }
    else
        out << element1.oper;
    return out;
}