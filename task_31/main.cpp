#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>


int main(void) {
    int n, m;
    std::cin >> n >> m;

    bool * visited = new bool[n];
    for (int i = 0; i < n; ++i)
        visited[i] = false;
    
    /* Note: at first I used std::set instead of std::vector to store
     * adjacent vertexes for i'th vertex (because in case of set there is no
     * need to check for multiple vertexes - set does it himself in O(logn)
     * time whereas using vector it is O(n)), but execution time in the first
     * case was longer than when using vector. TODO: why???  */
    auto adj_list = new std::vector<uint16_t>[n];
    for (int i = 0; i < m; ++i) {
        /* TODO: Should I declare v1 and v2 outside of for loop?  */
        uint16_t v1, v2;
        std::cin >> v1 >> v2;

        if (v1 != v2) {
            if (std::find(adj_list[v1 - 1].begin(), adj_list[v1 - 1].end(),
                    v2 - 1) == adj_list[v1 - 1].end())
                adj_list[v1 - 1].push_back(v2 - 1);
            
            if (std::find(adj_list[v2 - 1].begin(), adj_list[v2 - 1].end(),
                    v1 - 1) == adj_list[v2 - 1].end())
                adj_list[v2 - 1].push_back(v1 - 1);
        }
    }

    std::set<uint16_t> component;
    std::stack<uint16_t> vertexes_to_visit;
    vertexes_to_visit.push(0);

    /* DFS.  */
    while (vertexes_to_visit.empty() == false) {
        uint16_t v = vertexes_to_visit.top();
        vertexes_to_visit.pop();

        component.insert(v + 1);
        visited[v] = true;
        for (auto i = adj_list[v].rbegin(); i != adj_list[v].rend(); ++i)
            if (visited[*i] == false)
                vertexes_to_visit.push(*i);
    }

    std::cout << component.size() << std::endl;
    for (auto i = component.begin(); i != component.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    return 0;
}
