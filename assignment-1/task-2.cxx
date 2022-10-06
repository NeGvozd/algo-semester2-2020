/****************************************************************************
Секретные материалы

Джон Макклейн сообщает по рации новую информацию о террористах в отдел с n полицейскими. Он звонит нескольким сотрудникам и просит распространить информацию по отделу, зная, что у каждого полицейского есть связь с определёнными коллегами. Джон Макклейн хочет, чтобы операция прошла успешно. Но если полицейский позвонит коллеге, от которого(возможно, не напрямую) сам получил информацию, террористы смогут отследить этот звонок и помешать операции. Если же двое сотрудников оповестят одного, ничего плохого не произойдёт. Помогите Джону Макклейну. Выведите NO, если кто-то из полицейских ошибётся, делая звонок. Если всё пройдёт хорошо, выведите YES и порядок, в котором полицейские получат информацию, считая, что полицейские оповещают коллег по возрастанию их номеров, а в начале Джон даёт информацию тем, кому не может позвонить никто из коллег. 

Нумерация ведётся с 0. Петли допустимы.

Ввод:
Первая строка содержит пару целых чисел n и m (1 ≤ n, m ≤ 10^5) — количество вершин и рёбер заданного ориентированного графа.
Следующие m строк содержат описания рёбер, по одному в строке. Каждая из строк содержит по два целых числа a и b (0 ≤ a, b < n) — начало и конец ребра.

Вывод:
Если такого порядка не существует, то выведите «NO» (без кавычек).
В противном случае, выведите «YES» в первую из строк. Во вторую строку выведите перестановку индексов вершин (целые числа от 0 до n - 1), такую, что для каждого ребра его стартовая вершина находится строго левее его конечной вершины.


  in  | out
 -----|-----
  4 5 | YES
  0 2 | 0 2 1 3
  2 1 |
  1 3 |
  2 3 |
  0 3 |

  in  | out
 -----|-----
  3 3 | NO
  0 1 |
  1 2 |
  2 0 |


  in  | out
 -----|-----
  2 2 | NO
  0 1 |
  1 1 |
  

****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

enum class Color { White, Gray, Black };


bool isCycle(const std::vector<std::vector<int>>& graph, 
              std::vector<Color>& colors,
              int v) 
{
    colors[v] = Color::Gray;
    for (int u : graph[v]) 
    {
        if (colors[u] == Color::Gray) {
            return true;
        }
        if (colors[u] == Color::White && isCycle(graph, colors, u)) {
            return true;
        }
    }
    colors[v] = Color::Black;
    return false;
}


void topoSort(const std::vector<std::vector<int>>& graph, 
              std::vector<int>& order,
              std::vector<Color>& colors,
              int v) 
{
    colors[v] = Color::Gray;
    for (int u : graph[v]) 
    {
        if (colors[u] == Color::White) {
            topoSort(graph, order, colors, u);
        }
    }
    order.push_back(v);
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
    
    bool isCyclic = false;
    std::vector<Color> colors(n, Color::White);

    for (int i = 0; i < n; ++i) 
    {
        if (colors[i] == Color::White) {
            isCyclic = isCycle(graph, colors, i);
        }
        if (isCyclic) {
            break;
        }
    }

    if (isCyclic) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES" << std::endl;
        std::vector<int> order;
        colors.assign(n, Color::White);
        for (int i = 0; i < n; ++i) 
        {
            if (colors[i] == Color::White) {
                topoSort(graph, order, colors, i);
            }
        }
        std::reverse(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            std::cout << order[i] << " ";
        }
    }

    return 0;
}

