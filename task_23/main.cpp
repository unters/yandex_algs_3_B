#include <iostream>
#include <algorithm>
#include <set>


int main(void) {
    int n;
    std::cin >> n;

    int * ops   = new int[n];
    int * paths = new int[n];
    ops[0] = 0;
    paths[0] = -1;

    for (int i = 1; i < n; ++i)
        ops[i] = 1000001;

    for (int i = 0; i < n; ++i) {
        if (i + 1 < n)
            if (ops[i] + 1 < ops[i + 1]) {
                ops[i + 1]      = ops[i] + 1;
                paths[i + 1]    = i;
            }

        if (i * 2 + 1 < n)
            if (ops[i] + 1 < ops[i * 2 + 1]) {
                    ops[i * 2 + 1]      = ops[i] + 1;
                    paths[i * 2 + 1]    = i;
            }

        if (i * 3 + 2 < n)
            if (ops[i] + 1 < ops[i * 3 + 2]) {
                    ops[i * 3 + 2]      = ops[i] + 1;
                    paths[i * 3 + 2]    = i;
            }
    }
    
    std::set<int> path = {1};
    for (int i = n - 1; i >= 0; i = paths[i])
        path.insert(i + 1);
    
    std::cout << ops[n - 1] << std::endl;
    for (int i : path)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
