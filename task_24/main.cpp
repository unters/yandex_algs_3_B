#include <iostream>
#include <tuple>
#include <algorithm>


int main(void) {
    int n;
    std::cin >> n;

    /* min_time[i] represent minimal time to serve first i + i customers.  */
    int * min_time = new int[n];
    /* customers[i] stores time parameters for i + 1 'th customer.  */
    auto customers = new std::tuple<int, int, int>[n];
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        customers[i] = std::make_tuple(a, b, c);

        if (i == 0)
            min_time[i] = a;

        else if (i == 1)
            min_time[i] = std::min({min_time[0] + a,
                std::get<1>(customers[0])});

        else if (i == 2)
            min_time[i] = std::min({min_time[1] + a,
                min_time[0] + std::get<1>(customers[1]),
                std::get<2>(customers[0])});

        else
            min_time[i] = std::min({min_time[i - 1] + a, 
                min_time[i - 2] + std::get<1>(customers[i - 1]),
                min_time[i - 3] + std::get<2>(customers[i - 2])});    
    }

    std::cout << min_time[n - 1] << std::endl;

    delete [] min_time;
    delete [] customers;
    return 0;
}
