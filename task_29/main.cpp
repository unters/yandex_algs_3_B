#include <iostream>
#include <set>


int main(void) {
    int n;
    std::cin >> n;

    /* To prevent segmentation fault.  */
    if (n == 0) {
        std::cout << "0\n0 0\n";
        return 0;
    }

    int * prices = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> prices[i];

    
    /* Value of table[i][j] means that at i'th day (counting from 0) after
     * lunch Petya has spent table[i][j] rubles and has j coupons. */
    int     ** table        = new int*[n];
    /* Value of max_coupons[i][j] means that in range from 0'th to i'th day
     * according to optimal money spending strategy Petya had at most
     * max_coupons[i][j] coupons.  */
    int     ** max_coupons  = new int*[n];
    /* Value of steps[i][j] describes the most optimal step on i'th day 
     * Petya has to make to reach the situation described by corresponding
     * cells of table and max_coupons. '+' - buy a lunch with price > 100;
     * 'P' - buy a lunch with price <= 100; '-' - spend a coupon. */
    char    ** steps        = new char*[n];
    for (int i = 0; i < n; ++i) {
        table[i]        = new int[n + 1];
        max_coupons[i]  = new int[n + 1];
        steps[i]        = new char[n + 1];
        
        for (int j = 0; j <= n; ++j) {
            table[i][j]         = -1;
            max_coupons[i][j]   = 0;
            steps[i][j]         = '0';
        }
    }

    if (prices[0] > 100) {
        table[0][1]         = prices[0];
        max_coupons[0][1]   = 1;
        steps[0][1]         = 'B';
    }

    else {
        table[0][0] = prices[0];
        steps[0][0] = 'B';
    }

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j <= n; ++j) {
            if (table[i][j] == -1)
                continue;

            if (prices[i + 1] <= 100) {
                table[i + 1][j] = table[i][j] + prices[i + 1];
                max_coupons[i + 1][j] = max_coupons[i][j];
                steps[i + 1][j] = 'P';
            }

            else {
                table[i + 1][j + 1] = table[i][j] + prices[i + 1];
                /* max_coupons[i][j] + 1 can be changed for j.  */
                max_coupons[i + 1][j + 1] = max_coupons[i][j] + 1;
                steps[i + 1][j + 1] = '+';
            }

            if (j > 0) {
                if (table[i][j] < table[i + 1][j - 1] ||
                        table[i + 1][j - 1] == -1) {
                    table[i + 1][j - 1] = table[i][j];
                    max_coupons[i + 1][j - 1] = max_coupons[i][j];
                    steps[i + 1][j - 1] = '-';
                }
            }
        }

    // std::cout << std::endl;

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j <= n; ++j)
    //         std::cout << table[i][j] << "\t";
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j <= n; ++j)
    //         std::cout << max_coupons[i][j] << "\t";
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j <= n; ++j)
    //         std::cout << steps[i][j] << "\t";
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;

    /* min for price, max for coupons, left for "coupons left".  */
    int min = 300001, max = 0, left = 0;
    for (int j = 0; j <= n; ++j)
        if (table[n - 1][j] != -1 && table[n - 1][j] <= min) {
            min     = table[n - 1][j];
            max     = max_coupons[n - 1][j];
            left    = j;
        }

    std::set<int> days;
    int j = left;
    for (int i = n - 1; i > 0; --i) {
        if (steps[i][j] == '-') {
            days.insert(i + 1);
            ++j;
        }

        else if (steps[i][j] == '+')
            --j;
    }

    std::cout << min << std::endl << left << " " << max - left << std::endl;
    for (int day : days)
        std::cout << day << std::endl;

    return 0;
}
