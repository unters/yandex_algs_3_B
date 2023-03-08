/* TODO: there must be some way to avoid that "if hell" and "Mua-ha-ha" 
 * initialization that take place in bfs. TODO: refactor / fix / correct.  */

#include <iostream>
#include <vector>
#include <queue>


int main(void) {
    int n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;
    --s; --t;

    /* Special case.  */
    if (q == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    
    /* Vector v contains coordinates of flees.  */
    std::vector<std::pair<int, int>> flees;
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x; --y;
        flees.push_back(std::pair<int, int>(x, y));
    }

    int ** distances = new int*[n];
    for (int i = 0; i < n; ++i) {
        distances[i] = new int[m];
        for (int j = 0; j < m; ++j)
            distances[i][j] = INT32_MAX;
    }

    distances[s][t] = 0;
    std::queue<std::pair<int, int>> vertexes_to_visit;
    vertexes_to_visit.push(std::pair<int, int>(s, t));

    /* Mua-ha-ha-ha.  */
    int x, y, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
    
    /* BFS.  */
    while (vertexes_to_visit.empty() == false) {
        auto v = vertexes_to_visit.front();
        x = v.first, y = v.second;

        x1 = x + 1, y1 = y - 2;
        x2 = x + 2, y2 = y - 1;
        x3 = x + 2, y3 = y + 1;
        x4 = x + 1, y4 = y + 2;
        x5 = x - 1, y5 = y + 2;
        x6 = x - 2, y6 = y + 1;
        x7 = x - 2, y7 = y - 1;
        x8 = x - 1, y8 = y - 2;

        if (x1 < n && y1 >= 0)
            if (distances[x][y] + 1 < distances[x1][y1]) {
                distances[x1][y1] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x1, y1));
            }

        if (x2 < n && y2 >= 0)
            if (distances[x][y] + 1 < distances[x2][y2]) {
                distances[x2][y2] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x2, y2));
            }
            
        if (x3 < n && y3 < m)
            if (distances[x][y] + 1 < distances[x3][y3]) {
                distances[x3][y3] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x3, y3));
            }

        if (x4 < n && y4 < m)
            if (distances[x][y] + 1 < distances[x4][y4]) {
                distances[x4][y4] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x4, y4));
            }
        
        if (x5 >= 0 && y5 < m)
            if (distances[x][y] + 1 < distances[x5][y5]) {
                distances[x5][y5] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x5, y5));
            }

        if (x6 >= 0 && y6 < m)
            if (distances[x][y] + 1 < distances[x6][y6]) {
                distances[x6][y6] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x6, y6));
            }

        if (x7 >= 0 && y7 >= 0)
            if (distances[x][y] + 1 < distances[x7][y7]) {
                distances[x7][y7] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x7, y7));
            }

        if (x8 >= 0 && y8 >= 0)
            if (distances[x][y] + 1 < distances[x8][y8]) {
                distances[x8][y8] = distances[x][y] + 1;
                vertexes_to_visit.push(std::pair<int, int>(x8, y8));
            }

        vertexes_to_visit.pop();
    }

    long sum = 0;
    for (auto it = flees.begin(); it != flees.end(); ++it) {
        x = (*it).first, y = (*it).second;

        if (distances[x][y] == INT32_MAX) {
            std::cout << -1 << std::endl;
            return 0;
        }

        sum += distances[x][y];
    }

    std::cout << sum << std::endl;
    return 0;
}
