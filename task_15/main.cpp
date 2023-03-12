#include <iostream>
#include <stack>


int main(void) {
    int n;
    std::cin >> n;

    int * city_cost     = new int[n];
    int * target_city   = new int[n];
    for (int i = 0; i < n; ++i)
        target_city[i] = -1;

    std::stack<int> s;
    for (int i = 0; i < n; ++i) {
        std::cin >> city_cost[i];

        while(s.empty() == false) {
            if (city_cost[s.top()] > city_cost[i]) {
                target_city[s.top()] = i;
                s.pop();
            }
            
            else
                break;
        }

        s.push(i);
    }

    for (int i = 0; i < n; ++i)
        std::cout << target_city[i] << " ";
    std::cout << std::endl;

    return 0;
}
