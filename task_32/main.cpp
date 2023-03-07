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
    
    auto adj_list = new std::vector<uint32_t>[n];
    for (int i = 0; i < m; ++i) {
        /* TODO: Should I declare v1 and v2 outside of for loop?  */
        uint32_t v1, v2;
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

    std::vector<std::set<uint32_t>> components;
    std::stack<uint32_t> vertexes_to_visit;
    for (int i = 0; i < n; ++i) 
        if (visited[i] == false) {
            vertexes_to_visit.push(i);

            /* DFS.  */
            std::set<uint32_t> component;
            while (vertexes_to_visit.empty() == false) {
                uint32_t v = vertexes_to_visit.top();
                vertexes_to_visit.pop();

                component.insert(v + 1);
                visited[v] = true;
                for (auto it = adj_list[v].rbegin(); it != adj_list[v].rend(); ++it)
                    if (visited[*it] == false)
                        vertexes_to_visit.push(*it);
            }

            components.push_back(component);
        }

    std::cout << components.size() << std::endl;
    for (auto component : components) {
        std::cout << component.size() << std::endl;
        for (auto i = component.begin(); i != component.end(); ++i)
            std::cout << *i << " ";
        std::cout << std::endl;
    }

    return 0;
}
