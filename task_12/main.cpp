#include <iostream>
#include <stack>


int main(void) {
    std::string braces_sequence;
    std::getline(std::cin, braces_sequence);

    std::stack<char> opened_braces;
    for(char const c : braces_sequence) {
        if (c == '{' || c == '[' || c == '(') {
            opened_braces.push(c);
            continue;
        }

        if (opened_braces.empty()) {
            std::cout << "no\n";
            return 0;
        }

        char b = opened_braces.top();

        if (c == '}' && b != '{') {
            std::cout << "no\n";
            return 0;
        }

        else if (c == ']' && b != '[') {
            std::cout << "no\n";
            return 0;
        }

        else if (c == ')' && b != '(') {
            std::cout << "no\n";
            return 0;
        }

        opened_braces.pop();
    }

    if (opened_braces.empty())
        std::cout << "yes\n";

    else
        std::cout << "no\n";

    return 0;
}
