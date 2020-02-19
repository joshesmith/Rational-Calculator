#include <iostream>
#include "classes/My_expression.h"
int main() {
    using std::cout;
    using std::cin;

    My_expression calculator{};
    std::string user_input{};
    bool going{true};
    while (going){
        cout << "Enter your rational expression:\n";
        std::getline(cin,user_input);
        calculator.parse_string(user_input);
        cout << "simplifying...\n";
        calculator.simplify();

        do {
            cout << "Try another expression? (y/n): ";
            std::getline(cin,user_input);
            if (user_input == "y" || user_input == "Y") {
                calculator.clear();
            } else if (user_input == "n" || user_input == "N"){
                cout << "closing...";
                going = false;
            }
        } while (user_input != "y" && user_input != "Y" && user_input != "n" && user_input != "N");
    }
    return 0;
}
