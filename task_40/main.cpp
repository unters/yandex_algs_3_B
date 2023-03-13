#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>


int main(void) {
    int n, m;
    std::cin >> n >> m;

    auto lines = new std::set<int>[m];
    for (int station, i = 0; i < m; ++i) {
        int p;
        std::cin >> p;

        for (int j = 0; j < p; ++j) {
            std::cin >> station;
            lines[i].insert(station);
        }
    }

    int a, b;
    std::cin >> a >> b;

    /* distance[i] represents number of line transfers that must be made in
     * order to get from line containing station A to line containing 
     * station B.  */
    int * distances = new int[m];
    for (int i = 0; i < m; ++i)
        if (lines[i].find(a) != lines[i].end()) 
            distances[i] = 0;

        else
            distances[i] = 100;

    /* Building adjecency list for graph of lines. Vertex of that graph
     * represents a subway line. Edge between two vertexes represents a
     * possibility to transfer between corresponding lines.  */
    auto lines_adj_list = new std::vector<int>[m];
    std::vector<int> lines_intersection;
    for (int i = 0; i < m; ++i)
        for (int j = i + 1; j < m; ++j) {
            std::set_intersection(lines[i].begin(), lines[i].end(),
                lines[j].begin(), lines[j].end(),
                std::back_inserter(lines_intersection));
            
            if (lines_intersection.empty() == false) {
                lines_adj_list[i].push_back(j);
                lines_adj_list[j].push_back(i);
                lines_intersection.clear();
            }
        }

    /* BFS.  */
    for (int i = 0; i < m; ++i)
        if (distances[i] == 0) {
            std::queue<int> lines_to_visit({i});
            while (lines_to_visit.empty() == false) {
                int line = lines_to_visit.front();
                lines_to_visit.pop();

                for (auto adj_line : lines_adj_list[line]) 
                    if (distances[adj_line] > distances[line] + 1) {
                        distances[adj_line] = distances[line] + 1;
                        lines_to_visit.push(adj_line);
                    }
            }
        }

    int distance = 100;
    for (int i = 0; i < m; ++i) 
        if (lines[i].find(b) != lines[i].end())
            distance = std::min(distance, distances[i]);

    if (distance == 100)
        std::cout << -1 << std::endl;

    else
        std::cout << distance << std::endl;

    delete [] lines, distances, lines_adj_list;
    return 0;
}
