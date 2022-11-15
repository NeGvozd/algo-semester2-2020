/****************************************************************************
Районы, кварталы, жилые массивы

Фрэнку опять прилетел новый заказ. Однако в этот раз город играет по очень странным правилам: все дороги в городе односторонние и связывают только офисы нанимателей перевозчика. Множество офисов, между любыми двумя из которых существует путь, образуют квартал, если нельзя добавить никакие другие, чтобы условие выполнялось. Фрэнку интересно, каково минимальное количество односторонних дорог нужно ещё построить, чтобы весь город стал квраталом. 

Нумерация ведётся с 1. Петли допустимы.

Ввод:
Первая строка содержит пару целых чисел n и m (1 ≤ n ≤ 10^5, 0 ≤ m ≤ 10^5) — количество вершин и рёбер заданного ориентированного графа.
Следующие m строк содержат описания рёбер, по одному в строке. Каждая из строк содержит по два целых числа a и b (1 ≤ a, b ≤ n) — начало и конец ребра.

Вывод: Выведите одно число — количество дорог, которые нужно добавить, чтобы весь город стал одним кварталом.

 | in  | out |
 |-----|-----|
 | 2 1 |  1  |
 | 1 2 |     |

 | in  | out |
 |-----|-----|
 | 4 3 |  2  |
 | 1 2 |     |
 | 3 2 |     |
 | 2 4 |     |
 
 | in  | out |
 |-----|-----|
 | 5 4 |  2  |
 | 1 2 |     |
 | 3 2 |     |
 | 2 4 |     |
 | 2 5 |     |

****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>


enum class Color { White, Gray, Black };


void dfs1(const std::vector<std::vector<int>>& graph, 
          std::vector<Color>& colors, 
          std::vector<int>& order, 
          int vertex) 
{
    colors[vertex] = Color::Gray;
    for (int v : graph[vertex])
    {
        if (colors[v] == Color::White) {
            dfs1(graph, colors, order, v);
        }
    }
    colors[vertex] = Color::Black;
    order.push_back(vertex);
}


void dfs2(const std::vector<std::vector<int>>& graph,
          std::vector<std::vector<int>>& components,
          std::vector<Color>& colors,
          int vertex,
          int component)
{
    colors[vertex] = Color::Gray;
    components[component].push_back(vertex);
    for (int v : graph[vertex])
    {
        if (colors[v] == Color::White) {
            dfs2(graph, components, colors, v, component);
        }
    }
    colors[vertex] = Color::Black;
}


void FindComponents(const std::vector<std::vector<int>>& graph,
                    std::vector<std::vector<int>>& components)
{
    std::vector<Color> colors(graph.size(), Color::White);
    std::vector<int> order;
    for (int i = 0; i < graph.size(); ++i)
    {
        if (colors[i] == Color::White) {
            dfs1(graph, colors, order, i);
        }
    }

    int component = 0;
    colors.assign(graph.size(), Color::White);

    for (int i = graph.size() - 1; i >= 0; --i)
    {
        if (colors[order[i]] == Color::White) {
            components.push_back(std::vector<int>());
            dfs2(graph, components, colors, order[i], component);
            ++component;
        }
    }
}


int AdditionalRoads(const std::vector<std::vector<int>>& graph)
{
    std::vector<std::vector<int>> components;
    FindComponents(graph, components);

    if (components.size() == 1) {
        return 0;
    }

    std::vector<bool> is_incoming(components.size(), false);
    std::vector<bool> is_outgoing(components.size(), false);

    for (int u = 0; u < graph.size(); ++u)
    {
        for (int v : graph[u])
        {
            if (v != u) {
                is_outgoing[u] = true;
                is_incoming[v] = true;
            }
        }
    }

    int incoming = 0;
    int outgoing = 0;

    for (int i = 0; i < components.size(); ++i)
    {
        if (is_incoming[i]) {
            ++incoming;
        }
        if (is_outgoing[i]) {
            ++outgoing;
        }
    }

    return std::max(incoming, outgoing);
}


int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);

    for (int i = 0; i < m; ++i) 
    {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    std::cout << AdditionalRoads(graph) << std::endl;
    return 0;
}