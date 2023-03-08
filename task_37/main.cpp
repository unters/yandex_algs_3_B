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

    /* path[i] value represents the vertex preceding vertex i on a shortest
     * path from vertex v1 to vertex i. path[i] value is valid only after BFS
     * and only if distance[i] is not equal to 100.  */
    int * path = new int[n];
    path[v1] = -1;

    /* Queue containing vertexses to visit.  */
    std::queue<int> q;
    q.push(v1);

    /* BFS.  */
    while (q.empty() == false) {
        int v = q.front();
        
        for (auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it) {
            if (distances[v] + 1 < distances[*it]) {
                distances[*it] = distances[v] + 1;
                path[*it] = v;
                q.push(*it);
            }
        }

        q.pop();
    }

    if (distances[v2] == 100)
        std::cout << -1 << std::endl;

    else if (path[v2] == -1)
        std::cout << 0 << std::endl;

    else {
        std::vector<int> path_to_v2;
        path_to_v2.push_back(v2);

        int previous_vertex = path[v2];
        while (previous_vertex != -1) {
            path_to_v2.push_back(previous_vertex);
            previous_vertex = path[previous_vertex];
        }

        std::cout << distances[v2] << std::endl;
        for (auto it = path_to_v2.rbegin(); it != path_to_v2.rend(); ++it)
            std::cout << *it + 1 << " ";
        std::cout << std::endl;
    }

    return 0;
}
