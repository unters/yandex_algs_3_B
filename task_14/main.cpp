#include <iostream>
#include <stack>


int main(void) {
    uint n, next_car, last_car = 0;
    std::cin >> n;

    std::stack<uint> cars;
    for (uint i = 0; i < n; ++i) {
        while(cars.empty() == false) {
            if (cars.top() == last_car + 1) {
                cars.pop();
                ++last_car;
            }

            else
                break;
        }

        std::cin >> next_car;
        if (next_car == last_car + 1)
            ++last_car;

        else
            cars.push(next_car);        
    }

    while(cars.empty() == false) {
        if (cars.top() == last_car + 1) {
            cars.pop();
            ++last_car;
        }

        else
            break;
    }

    if (cars.empty())
        std::cout << "YES\n";

    else
        std::cout << "NO\n";

    return 0;
}
