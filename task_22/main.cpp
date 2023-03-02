#include <iostream>


int main(void) {
    int n, k;
    std::cin >> n >> k;

    int * a = new int[n];
    a[0] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= k; ++j) {
            if (i - j < 0)
                break;
            
            a[i] += a[i - j];
        }

    std::cout << a[n - 1] << std::endl;
    return 0;
}
