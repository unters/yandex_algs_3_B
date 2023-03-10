/* There must be more elegant way to code the solution. TODO: refactor.  */

#include <iostream>
#include <vector>
#include <stack>


int main(void) {
    int n;
    std::cin >> n;

    /* If path[i] is -1, than i'th vertex has not been visited yet. If
     * path[i] is i, than DFS has started at path[i]. If path[i] is neither
     * -1 nor i than the path[i] was the vertex visited just before 
     * vertex[i]. */
    int * path = new int[n];
    for (int i = 0; i < n; ++i)
        path[i] = -1;

    auto adj_list = new std::vector<int>[n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int v;
            std::cin >> v;
            if (v == 1)
                adj_list[i].push_back(j);
        }

    /* DFS.  */
    std::stack<int> vertexes_to_visit;
    for (int i = 0; i < n; ++i)
        if (path[i] == -1) {
            vertexes_to_visit.push(i);

            while (vertexes_to_visit.empty() == false) {
                int v = vertexes_to_visit.top();
                vertexes_to_visit.pop();

                if (path[v] == -1)
                    path[v] = v;

                for (auto it = adj_list[v].rbegin();
                        it != adj_list[v].rend(); ++it) {
                    /* Loop.  */
                    if (*it == v) {
                        std::cout << "YES\n1\n" << v + 1 << std::endl;
                        return 0;
                    }

                    /* In this case *it is the vertex that preceeds vertex v
                     * in dfs.  */
                    if (*it == path[v])
                        continue;
                    
                    /* Cycle. */
                    if (path[*it] != -1) {
                        std::vector<int> cycle{path[*it], *it};
                        while (v != path[*it]) {
                            cycle.push_back(v);
                            v = path[v];
                        }

                        std::cout << "YES\n" << cycle.size() << std::endl;
                        for (auto cit = cycle.rbegin();
                                cit != cycle.rend(); ++cit)
                            std::cout << *cit + 1 << " ";
                        std::cout << std::endl;

                        return 0;
                    }                    

                    path[*it] = v;
                    vertexes_to_visit.push(*it);
                }
            }
        }

    std::cout << "NO\n";
    return 0;
}
