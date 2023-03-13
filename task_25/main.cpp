#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


int main(void) {
    int n;
    std::cin >> n;

    std::set<int> nails_set;
    for (int nail, i = 0; i < n; ++i) {
        std::cin >> nail;
        nails_set.insert(nail);
    }
    
    std::vector<int> nails_vec;
    std::copy(nails_set.begin(), nails_set.end(),
        std::back_inserter(nails_vec));
    
    int * dp = new int[n];
    for (int i = 1; i < n; ++i) {
        int nails_distance = nails_vec[i] - nails_vec[i - 1];

        if (i == 1)
            dp[i] = nails_distance;

        else if (i == 2)
            dp[i] = dp[i - 1] + nails_distance;

        else
            dp[i] = std::min(dp[i - 1] + nails_distance, 
                dp[i - 2] + nails_distance);
    }

    std::cout << dp[n - 1] << std::endl;

    delete [] dp;
    return 0;
}
