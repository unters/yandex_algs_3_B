#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>


int main(void) {
    int n, m;
    std::cin >> n >> m;

    /* flag[i] - vertex i status: 0 - not visited, 1 - belongs to group 1,
     * 2 - belongs to group 2.  */
    uint8_t * flags = new uint8_t[n];    
    for (int i = 0; i < n; ++i)
        flags[i] = 0;
    
    auto adj_list = new std::vector<uint8_t>[n];
    for (int i = 0; i < m; ++i) {
        /* Can't use uint8_t for v1 and v2 because it is typedef for unsigned
         * char and std::cin will treat them as chars - that is not what 
         * is needed.  */
        int v1, v2; 
        std::cin >> v1 >> v2;

        if (std::find(adj_list[v1 - 1].begin(), adj_list[v1 - 1].end(),
                v2 - 1) == adj_list[v1 - 1].end())
            adj_list[v1 - 1].push_back(v2 - 1);
        
        if (std::find(adj_list[v2 - 1].begin(), adj_list[v2 - 1].end(),
                v1 - 1) == adj_list[v2 - 1].end())
            adj_list[v2 - 1].push_back(v1 - 1);
    }

    std::stack<uint8_t> vertexes_to_visit;
    for (int i = 0; i < n; ++i)
        if (flags[i] == 0 && adj_list[i].empty() == false) {
            vertexes_to_visit.push(i);
            flags[i] = 1;         

            /* DFS.  */
            while (vertexes_to_visit.empty() == false) {
                uint8_t v = vertexes_to_visit.top();
                vertexes_to_visit.pop();

                uint8_t flag = flags[v] == 1 ? 2 : 1;
                for (auto it = adj_list[v].rbegin(); 
                        it != adj_list[v].rend(); ++it) {
                    if (flags[*it] == 0) {
                        vertexes_to_visit.push(*it);
                        flags[*it] = flag;
                    }

                    else if (flags[*it] == flags[v]) {
                        std::cout << "NO" << std::endl;
                        return 0;
                    }
                }
            }
        }

    std::cout << "YES" << std::endl;
    return 0;
}
