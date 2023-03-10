/* Instead of std::array<int, 3> it might be much better to use std::tuple.
 * To create a tuple (and pair in previous tasks) I should use (should have 
 * used) std::make_tuple() (std::make_pair()).  */

#include <iostream>
#include <vector>
#include <queue>
#include <array>


int8_t const steps[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1},
};


int main(void) {
    int n;
    std::cin >> n;

    int *** distances = new int**[n];
    for (int i = 0; i < n; ++i) {
        distances[i] = new int*[n];
        for (int j = 0; j < n; ++j) {
            distances[i][j] = new int[n];
            for (int k = 0; k < n; ++k)
                distances[i][j][k] = 27000;
        }
    }

    typedef std::array<int, 3> coords;
    std::queue<coords> vertexes_to_visit;

    char *** map = new char**[n];
    for (int i = 0; i < n; ++i) {
        map[i] = new char*[n];
        for (int j = 0; j < n; ++j) {
            map[i][j] = new char[n];
            for (int k = 0; k < n; ++k) {
                std::cin >> map[i][j][k];
                if (map[i][j][k] == 'S') {
                    vertexes_to_visit.push({i, j, k});
                    distances[i][j][k] = 0;
                }
            }
        }
    }

    /* BFS.  */
    int x, y, z, current_distance;
    while (vertexes_to_visit.empty() == false) {
        auto const & v = vertexes_to_visit.front();
        current_distance = distances[v[0]][v[1]][v[2]];

        for (int i = 0; i < 6; ++i) {
            x = v[0] + steps[i][0];
            y = v[1] + steps[i][1];
            z = v[2] + steps[i][2];

            if (x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n)
                continue;

            if (map[x][y][z] == '.')
                if (distances[x][y][z] > current_distance + 1) {
                    distances[x][y][z] = current_distance + 1;
                    vertexes_to_visit.push({x, y, z});
                }
        }

        vertexes_to_visit.pop();
    }

    int min = 27000;
    for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
            if (distances[0][j][k] < min)
                min = distances[0][j][k];

    std::cout << min << std::endl;

    return 0;
}
