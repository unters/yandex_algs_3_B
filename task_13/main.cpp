#include <iostream>
#include <stack>
#include <string>
#include <sstream>


int main() {
    std::string s;
    getline(std::cin, s);

    /* Stack to store expression' operators.  */
    std::stack<int> operands;

    char c;
    int result;
    std::istringstream input(s);
    while(input >> c) {
        if (c == '+') {
            result = operands.top();
            operands.pop();
            result += operands.top();
            operands.pop();
            operands.push(result);
        }

        else if (c == '-') {
            result = operands.top() * (-1);
            operands.pop();
            result += operands.top();
            operands.pop();
            operands.push(result);
        }

        else if (c == '*') {
            result = operands.top();
            operands.pop();
            result *= operands.top();
            operands.pop();
            operands.push(result);
        }

        else
            operands.push((int)c - '0');
    }
    
    std::cout << operands.top() << std::endl;
    return 0;
}
