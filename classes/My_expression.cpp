//
// Created by j.smith on 11/02/2020.
//

#include "My_expression.h"
#include "ctype.h"
#include <string>
#include <cassert>

My_expression::My_expression()
    :expression{}
{};

void My_expression::parse_string(std::string &text_input){
    int i{0};
    while (i < text_input.length()){
        if (isdigit(text_input[i])){
            //cycle forward as long as you see numbers
            int length = 1;
            while (((i+length)<text_input.length()) && isdigit(text_input[i+length])){
                length++;
            }
            int integer1{std::stoi(text_input.substr(i,length))};
            expression.push_back(Math_element(Fraction(integer1)));
            i += length;
        } else if (text_input[i] == ' ' || text_input[i] == '\\' || text_input[i] == 'n'){
            i++;
        } else {
            expression.push_back(Math_element(text_input[i]));
            i++;
        }
    }
    parenthesis_match();
}

void My_expression::clear(){
    expression.clear();
}

int My_expression::remove_bracket(int left, int right){
    if (right-left == 2) {
        expression.erase(expression.begin() + right);
        expression.erase(expression.begin() + left);
        right = right - 2;
    }
    return right;
}
void My_expression::brackets() {
    bool going{!expression.empty()};

    std::vector<int> bracket_indexes{};
    int i{0};
    while (i < expression.size()){
        if (!expression[i].is_frac()) {
            if (expression[i].get_oper() == '(') {
                bracket_indexes.push_back(i);
                i++;
            } else if (expression[i].get_oper() == ')') {
                //hit a local lowest level
                //pass the bracketed range to idmas
                i = idmas(bracket_indexes.back(), i);
                //remove brackets if possible.
                i = remove_bracket(bracket_indexes.back(),i);
                bracket_indexes.pop_back();
                i++;

                std::cout << *this << " remove brackets\n";
            } else {
                i++;
            }
            //cycle through taking note of ( indexes, until you see a ), then evaluate the expression within those brackets.
            //attempt to remove those brackets
            //if not flag to ignore going into them next run.
        } else {
            i++;
        }

    }
    //run one final idmas over the whole expression
    idmas(-1,expression.size());
}

int My_expression::idmas(int start, int end){
    int oldEnd(end);
    end = unary_pos_neg(start,end);
    if (oldEnd != end){
        std::cout << *this << " unary operator\n";
        oldEnd = end;
    }

    end = indices(start,end);
    if (oldEnd != end){
        std::cout << *this << " indices \n";
        oldEnd = end;
    }

    end = multiply_divide(start,end);
    if (oldEnd != end){
        std::cout << *this << " multiply and divide\n";
        oldEnd = end;
    }

    end = add_subtract(start,end);
    if (oldEnd != end){
        std::cout << *this << " add and subtract \n";
        oldEnd = end;
    }

    return end;
}

int My_expression::unary_pos_neg(int start, int end){
    int j{start+1};
    while (j<end){
        if (!expression[j].is_frac()){
            if (expression[j].get_oper() == '+'){
                //check the thing to the left is not a ) or frac or nothing
                if (j-1 == -1 || !expression[j-1].is_frac()){
                    if(j-1 == -1 || expression[j-1].get_oper() != ')'){
                        assert(expression[j+1].is_frac());
                        //plus is redundant, delete it
                        expression.erase(expression.begin()+j,expression.begin()+j+1);
                        end = end -1;
                    }
                }
            } else if (expression[j].get_oper() == '-'){
                //check the thing to the left is not a ) or frac or nothing
                if (j-1 == -1 || !expression[j-1].is_frac()){
                    if(j-1 == -1 || expression[j-1].get_oper() != ')'){
                        assert(expression[j+1].is_frac());
                        //apply negative, then delete it
                        expression[j+1] = Math_element(expression[j+1].get_frac()* -1);
                        expression.erase(expression.begin()+j,expression.begin()+j+1);
                        end = end -1;
                    }
                }
            }
        }
        j++;
    }
    return end;
}

int My_expression::indices(int start, int end){
    int j{start+1};
    while (j<end){
        if (!expression[j].is_frac()){
            if (expression[j].get_oper() == '^'){
                //identify the fraction on either side,
                assert(expression[j-1].is_frac() && expression[j+1].is_frac());
                //make sure the fraction on the left is not a power
                expression[j-1] = Math_element(expression[j-1].get_frac().int_power(expression[j+1].get_frac()));
                //delete two right elements
                expression.erase(expression.begin()+j,expression.begin()+j+2);
                end = end -2;
                j--;
            }
        }
        j++;
    }
    return end;
}

int My_expression::multiply_divide(int start, int end){
    int j{start+1};
    while (j<end){
        if (!expression[j].is_frac()){
            if (expression[j].get_oper() == '*'){
                //identify the fraction on either side,
                assert(expression[j-1].is_frac() && expression[j+1].is_frac());
                //make sure the fraction on the left is not a power
                expression[j-1] = Math_element(expression[j-1].get_frac() * expression[j+1].get_frac());
                //delete two right elements
                expression.erase(expression.begin()+j,expression.begin()+j+2);
                end = end -2;
                j--;
            } else if (expression[j].get_oper() == '/'){
                //identify the fraction on either side,
                assert(expression[j-1].is_frac() && expression[j+1].is_frac());
                //combine them
                expression[j-1] = Math_element(expression[j-1].get_frac() / expression[j+1].get_frac());
                expression.erase(expression.begin()+j,expression.begin()+j+2);
                end = end -2;
                j--;
            }
        }
        j++;
    }
    return end;
}
int My_expression::add_subtract(int start, int end) {
    int j{start+1};
    while (j<end){
        if (!expression[j].is_frac()){
            if (expression[j].get_oper() == '+'){
                //identify the fraction on either side,
                assert(expression[j-1].is_frac() && expression[j+1].is_frac());
                //make sure the fraction on the left is not a power
                expression[j-1] = Math_element(expression[j-1].get_frac() + expression[j+1].get_frac());
                //delete two right elements
                expression.erase(expression.begin()+j,expression.begin()+j+2);
                end = end -2;
                j--;
            } else if (expression[j].get_oper() == '-'){
                //identify the fraction on either side,
                assert(expression[j-1].is_frac() && expression[j+1].is_frac());
                //combine them
                expression[j-1] = Math_element(expression[j-1].get_frac() - expression[j+1].get_frac());
                expression.erase(expression.begin()+j,expression.begin()+j+2);
                end = end -2;
                j--;
            }
        }
        j++;
    }
    return end;
}

bool My_expression::parenthesis_match(){
    std::vector<char> stack1{};
    for (auto element : expression){
        if (!element.is_frac()){
            if (element.get_oper() == '(') {
                stack1.push_back('(');
            } else if (element.get_oper() == ')'){
                bool test = stack1.empty();
                assert(!stack1.empty() && stack1.back() == '(' && "incorrect parenthesis");
                stack1.pop_back();
            }

        }
    }
    assert(stack1.empty() && "incorrect parenthesis matching");
    return true;
}

void My_expression::simplify(){
    brackets();
}
std::ostream& operator<<(std::ostream &out, const My_expression &myexpr1){
    for (auto element : myexpr1.expression){
        out << element;
    }
    return out;
}

