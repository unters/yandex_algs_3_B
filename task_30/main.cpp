
#include <iostream>
#include <vector>
#include <algorithm>


class substr_info {
public:
    bool current_is_a_match;
    int length;

    /* Coords of previous element in a longest subsequence until
     * current point. If there is no previous element - both coords
     * are negative.  */
    int prev_x, prev_y;

    substr_info() {}

    substr_info(bool b, int l, int x, int y)
        : current_is_a_match(b), length(l)
        , prev_x(x), prev_y(y) {}
};


int main(void) {
    int n, m;

    std::cin >> n;
    int * a = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cin >> m;
    int * b = new int[m];
    for (int i = 0; i < m; ++i)
        std::cin >> b[i];

    /* lcs stands for longest common subsequence.  */
    substr_info ** lcs = new substr_info*[n];
    for (int i = 0; i < n; ++i) {
        lcs[i] = new substr_info[m];

        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                if (i != 0 && j != 0) {
                    int prev_x, prev_y;
                    if (lcs[i - 1][j - 1].length == 0)
                        prev_x = -1, prev_y = -1;

                    else {
                        if (lcs[i - 1][j - 1].current_is_a_match)
                            prev_x = i - 1, prev_y = j - 1;

                        else {
                            prev_x = lcs[i - 1][j - 1].prev_x;
                            prev_y = lcs[i - 1][j - 1].prev_y;
                        }
                    }

                    lcs[i][j] = substr_info(true,
                        lcs[i - 1][j - 1].length + 1, prev_x, prev_y);
                }

                else
                    lcs[i][j] = substr_info(true, 1, -1, -1);
            }

            else {
                int row, col;

                if (i == 0 && j == 0) {
                    lcs[i][j] = substr_info(false, 0, -1, -1);
                    continue;
                }

                else if (i != 0 && j == 0)
                    row = i - 1, col = j;

                else if (i == 0 && j != 0)
                    row = i, col = j - 1;

                else {
                    if (lcs[i - 1][j].length >= lcs[i][j - 1].length) 
                        row = i - 1, col = j;
                    
                    else
                        row = i, col = j - 1;
                }

                int prev_x, prev_y;

                if (lcs[row][col].current_is_a_match)
                    prev_x = row, prev_y = col;

                else {
                    prev_x = lcs[row][col].prev_x;
                    prev_y = lcs[row][col].prev_y;
                }

                lcs[i][j] = substr_info(false, lcs[row][col].length,
                    prev_x, prev_y);
            }
        }
    }

    std::vector<int> v;
    int row = n - 1, col = m - 1;
    while(row != -1 && col != -1) {
        if (lcs[row][col].current_is_a_match)
            v.push_back(a[row]);

        int r = lcs[row][col].prev_x;
        int c = lcs[row][col].prev_y;

        row = r;
        col = c;
    }

    for (auto i = v.rbegin(); i != v.rend(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;
    
    return 0;
}
