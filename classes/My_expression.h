//
// Created by j.smith on 11/02/2020.
//

#ifndef TUTORIAL_FILE_5_MY_EXPRESSION_H
#define TUTORIAL_FILE_5_MY_EXPRESSION_H

#include <string>
#include <vector>
#include "Math_element.h"

class My_expression {
private:
    std::vector<Math_element> expression;
    bool parenthesis_match();
    int remove_bracket(int right, int left);
    void brackets();
    int idmas(int start, int end);
    int unary_pos_neg(int start, int end);
    int indices(int start, int end);
    int multiply_divide(int start, int end);
    int add_subtract(int start, int end);
public:
    My_expression();

    void parse_string(std::string &text_input);
    void simplify();
    void clear();

    friend std::ostream& operator<<(std::ostream &out, const My_expression &myexpr1);
};


#endif //TUTORIAL_FILE_5_MY_EXPRESSION_H
