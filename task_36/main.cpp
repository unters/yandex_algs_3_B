#include <iostream>
#include <vector>
#include <queue>


int main(void) {
    int n;
    std::cin >> n;

    auto adj_list = new std::vector<int>[n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int digit;
            std::cin >> digit;
            if (digit == 1)
                adj_list[i].push_back(j);
        }
    
    int v1, v2;
    std::cin >> v1 >> v2;
    --v1; --v2;

    int * distances = new int[n];
    for (int i = 0; i < n; ++i)
        distances[i] = 100;
    distances[v1] = 0;

    /* Queue containing vertexses to visit.  */
    std::queue<int> q;
    q.push(v1);

    /* BFS.  */
    while (q.empty() == false) {
        int v = q.front();
        
        for (auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it) {
            if (distances[v] + 1 < distances[*it]) {
                distances[*it] = distances[v] + 1;
                q.push(*it);
            }
        }

        q.pop();
    }

    if (distances[v2] == 100)
        std::cout << -1 << std::endl;        
    else
        std::cout << distances[v2] << std::endl;

    return 0;
}
