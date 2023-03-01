#include <iostream>
#include <algorithm>


int main(void) {
    int n;
    std::cin >> n;

    /* Element with index i - 1 stores number of sequnces of length i that 
     * satisfy demanded property.  */
    int * counter = new int[std::max(n, 4)];
    counter[0] = 2;
    counter[1] = 4;
    counter[2] = 7;
    counter[3] = 13;
    for (int i = 4; i < n; ++i)
        counter[i] = 2 * counter[i - 2] + 2 * counter[i - 3] + \
            counter[i - 4];

    std::cout << counter[n - 1] << std::endl;;
    return 0;
}
