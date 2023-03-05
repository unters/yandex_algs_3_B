#include <iostream>
#include <algorithm>


int main(void) {
    int n, m, next_cost;
    std::cin >> n >> m;

    int ** cost_sums    = new int*[n];
    char ** steps       = new char*[n];
    for (int i = 0; i < n; ++i) {
        cost_sums[i]    = new int[m];
        steps[i]        = new char[m];
        
        for (int j = 0; j < m; ++j) {
            std::cin >> next_cost;

            if (i == 0 && j == 0) {
                cost_sums[0][0] = next_cost;
                steps[0][0]     = 'S';
            }

            else if (i == 0) {
                cost_sums[i][j] = cost_sums[i][j - 1] + next_cost;
                steps[i][j]     = 'R';
            }

            else if (j == 0) {
                cost_sums[i][j] = cost_sums[i - 1][j] + next_cost;
                steps[i][j]     = 'D';
            }

            else {
                if (cost_sums[i - 1][j] + next_cost < 
                        cost_sums[i][j - 1] + next_cost) {
                    cost_sums[i][j] = cost_sums[i][j - 1] + next_cost;
                    steps[i][j] = 'R';
                }

                else {
                    cost_sums[i][j] = cost_sums[i - 1][j] + next_cost;
                    steps[i][j] = 'D';
                }
            }
        }
    }

    int row = n - 1, column = m - 1, index = n + m - 3;
    char * path = new char[n + m - 2];
    while (row != 0 || column != 0) {
        path[index] = steps[row][column];

        if (path[index--] == 'R')
            --column;     

        else
            --row;
    }

    std::cout << cost_sums[n - 1][m - 1] << std::endl;
    for (int i = 0; i < n + m - 2; ++i)
        std::cout << path[i] << " ";
    std::cout << std::endl;

    return 0;
}
