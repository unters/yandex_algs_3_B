#include <iostream>
#include <algorithm>


int main(void) {
    int n, m, next_weight;
    std::cin >> n >> m;

    int ** weight_sums  = new int*[n];
    for (int i = 0; i < n; ++i) {
        weight_sums[i]  = new int[m];
        
        for (int j = 0; j < m; ++j) {
            std::cin >> next_weight;

            if (i == 0 && j == 0)
                weight_sums[0][0] = next_weight;

            else if (i == 0)
                weight_sums[i][j] = weight_sums[i][j - 1] + next_weight;

            else if (j == 0)
                weight_sums[i][j] = weight_sums[i - 1][j] + next_weight;

            else
                weight_sums[i][j] = std::min(
                    weight_sums[i - 1][j] + next_weight,
                    weight_sums[i][j - 1] + next_weight
                );
        }
    }

    std::cout << weight_sums[n - 1][m - 1] << std::endl;

    return 0;
}
