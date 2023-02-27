#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


int main(void) {
    int n, sticker;
    std::cin >> n;
    std::set<int> diego_stickers_set;
    for (int i = 0; i < n; ++i) {
        std::cin >> sticker;
        diego_stickers_set.insert(sticker);
    }

    int min = *diego_stickers_set.begin();
    int max = *diego_stickers_set.rbegin();

    /* As soon as std::set's iterator is bidirectional, it is less efficient
     * than random access iterator of std::vector e.g. when it goes about 
     * binary search algorithm implemented in std::lower_bound. Tests have
     * shown that using std::lower_bound with std::set's iterator takes 30+
     * times more time (3.717s) than std::vector's iterator (0.127s).  */
    std::vector<int> diego_stickers_vector;
    std::copy(diego_stickers_set.begin(), diego_stickers_set.end(),
        std::back_inserter(diego_stickers_vector));
    
    int k, p;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> p;

        if (p > max) {
            std::cout << diego_stickers_set.size() << std::endl;
            continue;
        }

        if (p <= min) {
            std::cout << 0 << std::endl;
            continue;
        }

        auto pos = std::lower_bound(std::begin(diego_stickers_vector), 
            std::end(diego_stickers_vector), p);
        std::cout << std::distance(std::begin(diego_stickers_vector), pos) 
            << std::endl;
    }

    return 0;
}