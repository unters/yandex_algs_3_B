#include <iostream>
#include <string>


int main(void) {
    int n, m, k;
    std::cin >> n >> m >> k;

    int ** prefix_sums = new int*[n];
    for (int i = 0; i < n; ++i)
        prefix_sums[i] = new int[m];

    /* Calculating prefix sums.  */
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j) {
            std::cin >> prefix_sums[i][j];

            if (i > 0)
                prefix_sums[i][j] += prefix_sums[i - 1][j];
            if (j > 0)
                prefix_sums[i][j] += prefix_sums[i][j - 1];
            if (i > 0 && j > 0)
                prefix_sums[i][j] -= prefix_sums[i - 1][j - 1];
        }

    /* Calculating demanded sums.  */
    int x1, y1, x2, y2, sum;
    for (int i = 0; i < k; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        --x1; --y1; --x2; --y2;

        sum = prefix_sums[x2][y2];

        if (x1 > 0)
            sum -= prefix_sums[x1 - 1][y2]; 
        if (y1 > 0)
            sum -= prefix_sums[x2][y1 - 1];
        if (x1 > 0 && y1 > 0)
            sum += prefix_sums[x1 - 1][y1 - 1];

        std::cout << sum << std::endl;
    }
    
    return 0;
}
