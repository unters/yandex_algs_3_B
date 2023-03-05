#include <iostream>


int main(void) {
    int n, m;
    std::cin >> n >> m;

    int ** field = new int*[n];
    for (int i = 0; i < n; ++i) {
        field[i] = new int[m];
        for (int j = 0; j < m; ++j)
            field[i][j] = 0;
    }

    field[0][0] = 1;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            if (i < n - 1 && j < m - 2)
                field[i + 1][j + 2] += field[i][j];
            
            if (i < n - 2 && j < m - 1)
                field[i + 2][j + 1] += field[i][j];
        }
    }

    std::cout << field[n - 1][m - 1] << std::endl;

    return 0;
}
