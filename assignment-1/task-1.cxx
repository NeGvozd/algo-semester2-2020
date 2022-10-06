/****************************************************************************
За молоком

Леон и Матильда собрались пойти в магазин за молоком. Их хочет поймать Стэнсфилд, поэтому нашим товарищам нужно сделать это как можно быстрее. Каково минимальное количество улиц, по которым пройдёт хотя бы один из ребят (либо Матильда, либо Леон, либо оба вместе)?

Граф связный и неориентированный. Вершины нумеруются с 1.

Ввод: 
Первая строка содержит количество вершин n (1 ≤ n ≤ 10^5), количество ребер m (0 ≤ m ≤ 10^5) и номера вершин графа leon, matilda, milk, в которых находятся соответственно Леон, Матильда и магазин с молоком.
Следующие m строк содержат ребра графа. В каждой строке два числа, разделенные пробелом, если между i и j существует ребро. Гарантируется, что в графе нет петель и мультиребер.

Вывод: Одно число – количество ребер.


  in       | out
 ----------|-----
 3 2 1 2 3 |  2
 1 3       |
 2 3       |

 
  in       | out
 ----------|-----
 3 2 1 2 3 |  2
 1 3       |
 1 2       |
 

****************************************************************************/

#include <iostream>
#include <vector>


std::vector<int> bfs(const std::vector<std::vector<int>>& graph, const int start) 
{
    std::vector<int> dist(graph.size(), -1);
    std::vector<int> queue;

    queue.push_back(start);
    dist[start] = 0;

    for (size_t i = 0; i < queue.size(); ++i) {
        int v = queue[i];

        for (size_t j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j];

            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                queue.push_back(to);
            }
        }
    }

    return dist;
}


int findMinPath(const std::vector<std::vector<int>>& graph, 
                const int leon, 
                const int matilda, 
                const int milk)
{
    std::vector<int> dist_leon = bfs(graph, leon);
    std::vector<int> dist_matilda = bfs(graph, matilda);
    std::vector<int> dist_milk = bfs(graph, milk);

    int min_path = dist_leon[milk] + dist_matilda[milk];

    for (size_t i = 0; i < graph.size(); ++i) {
        if (dist_leon[i] != -1 && dist_matilda[i] != -1 && 
                dist_milk[i] != -1) {
            int path = dist_leon[i] + dist_matilda[i] + dist_milk[i];
            if (path < min_path) {
                min_path = path;
            }
        }
    }

    return min_path;
}


int main()
{
    int vertex_count, edge_count, leon, matilda, milk;
    std::cin >> vertex_count >> edge_count >> leon >> matilda >> milk;

    std::vector<std::vector<int>> graph(vertex_count + 1);
    for (int i = 0; i < edge_count; ++i) {
        int from, to;

        std::cin >> from >> to;

        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    std::cout << findMinPath(graph, leon, matilda, milk) << std::endl;

    return 0;
}

