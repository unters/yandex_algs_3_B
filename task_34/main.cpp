/* Looks too monstrostic. There must be more elegant way to code a valid
 * topological sort. TODO: refactor.  */

#include <iostream>
#include <vector>
#include <stack>


int main(void) {
    int n, m;
    std::cin >> n >> m;

    bool * visited = new bool[n];
    for (int i = 0; i < n; ++i)
        visited[i] = false; 

    /* reference[i] represents number of vertexes that reference vertex i.  */
    int * references = new int[n];
    for (int i = 0; i < n; ++i)
        references[i] = 0;

    bool there_is_a_loop = false;
    auto adj_list = new std::vector<int>[n];
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        /* I don't terminate the program during I/O because of 
         * potential PE.  */
        if (v1 == v2) 
            there_is_a_loop = true;

        adj_list[v1 - 1].push_back(v2 - 1);
        ++references[v2 - 1];
    }

    if (there_is_a_loop) {
        std::cout << -1 << std::endl;
        return 0;
    }

    /* ordered[i] shows if vertex i has taken its position in topologicaly 
     * ordered sequence.  */
    bool * ordered = new bool[n];
    for (int i = 0; i < n; ++i)
        visited[i] = false;

    /* Vector of vertexes in inverse topological order.  */
    std::vector<int> & v = *(new std::vector<int>);
    /* Stack of vertexes to visit.  */
    std::stack<int> & s = *(new std::stack<int>);
    for (int i = 0; i < n; ++i) 
        if (references[i] == 0) {
            s.push(i);
            
            while (s.empty() == false) {
                int vertex = s.top();
                if (ordered[vertex] == true) {
                    s.pop();
                    continue;
                }

                visited[vertex] = true;
                
                /* Variable flag shows if every vertex behind the current
                 * one has already been discovered.  */
                bool flag = true;
                /* If all vertexes after the current one are visited, current
                 * vertex can be added to vertexes vector. If not - visit all
                 * vertexes that are still unvisited.  */
                for (auto it = adj_list[vertex].begin();
                    it != adj_list[vertex].end(); ++it)
                {
                    if (visited[*it] == true && ordered[*it] == false) {
                        std::cout << -1 << std::endl;
                        return 0;
                    }
                    
                    if (visited[*it] == true)
                        continue;

                    flag = false;
                    break;
                }

                if (flag == true) {
                    v.push_back(vertex);
                    ordered[vertex] = true;
                    s.pop();
                }

                else
                    for (auto it = adj_list[vertex].rbegin();
                            it != adj_list[vertex].rend(); ++it) {
                        if (visited[*it] == false)
                            s.push(*it);

                        else if (ordered[*it] == false) {
                            std::cout << -1 << std::endl;
                            return 0;
                        }
                    }
            }
        }

    if (v.empty() == true)
        std::cout << -1 << std::endl;

    else {
        for (auto it = v.rbegin(); it != v.rend(); ++it)
            std::cout << *it + 1 << " ";
        std::cout << std::endl;
    }

    return 0;
}
