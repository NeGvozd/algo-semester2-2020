/****************************************************************************
LCA

Задано дерево с корнем, содержащее 𝑛 (1 ≤ 𝑛 ≤ 100 000) вершин, пронумерованных от 0 до 𝑛−1. Требуется ответить на 𝑚 (1 ≤ 𝑚 ≤ 10 000 000) запросов о наименьшем общем предке для пары вершин. Запросы генерируются следующим образом. Заданы числа 𝑎1, 𝑎2 и числа 𝑥, 𝑦 и 𝑧. Числа 𝑎3, . . . , 𝑎2𝑚 генерируются следующим образом: 𝑎𝑖 = (𝑥·𝑎𝑖−2+𝑦·𝑎𝑖−1+𝑧) mod 𝑛. Первый запрос имеет вид ⟨𝑎1, 𝑎2⟩. Если ответ на 𝑖−1-й запрос равен 𝑣, то 𝑖-й запрос имеет вид ⟨(𝑎2𝑖−1 + 𝑣) mod 𝑛, 𝑎2𝑖⟩.
Для решения задачи можно использовать метод двоичного подъёма.

*Формат входных данных*
Первая строка содержит два числа: 𝑛 и 𝑚. Корень дерева имеет номер 0.
Вторая строка содержит 𝑛 − 1 целых чисел, 𝑖-е из этих чисел равно номеру родителя вершины 𝑖.
Третья строка содержит два целых числа в диапазоне от 0 до 𝑛−1: 𝑎1 и 𝑎2.
Четвертая строка содержит три целых числа: 𝑥, 𝑦 и 𝑧, эти числа неотрицательны и не превосходят 10^9.

*Формат выходных данных*
Выведите в выходной файл сумму номеров вершин — ответов на все запросы.

 | in   | out |
 |------|-----|
 |3 2   |2    |
 |0 1   |     |
 |2 1   |     |
 |1 1 0 |     |

****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
#include <climits>


struct Element {
    int num;
    int depth;

    Element(int _num = 0, int _depth = -1) : num(_num), depth(_depth) {}

    Element(const Element& elem) : num(elem.num), depth(elem.depth) {}

    Element& operator= (const Element& right)
    {
        num = right.num; depth = right.depth;

        return *this;
    }
    bool operator<(const Element& right) const
    {
        return depth < right.depth;
    }
};


class SparceTable {
private:
    int N;
    int logN;

    std::vector<std::vector<Element>> buffer;

    int Log(const int val) const
    {
        if (val == 1) return 0;
        return Log(val / 2) + 1;
    }
public:
    SparceTable(std::vector<Element>& data) : N(data.size())
    {
        logN = Log(N);
        buffer.assign(N, std::vector<Element>());

        for (int i = 0; i < N; ++i)
        {
            buffer[i].push_back(data[i]);
        }

        for (int j = 1; j < logN + 1; ++j)
        {  
            for (int i = 0; i < N; ++i)
            {    
                int right_border_id = i + (1 << j) - 1;  
                if (right_border_id + 1 > N) break;
                int middle_id = i + (1 << (j - 1));

                buffer[i].push_back(std::min(buffer[i][j - 1], 
                                    buffer[middle_id][j - 1]));
            }
        }
    }

    const std::vector<std::vector<Element>>& GetBuffer() const { return buffer; }
};


class RMQ {
private:
    const std::vector<std::vector<Element>>& ST;

    int Log(const int val) const
    {
        if (val == 1) return 0;

        return Log(val / 2) + 1;
    }

public:
    RMQ(int M, const SparceTable& _Table) : ST(_Table.GetBuffer()) {}
 
    Element find_min(const int L, const int R) const
    {
        assert(R >= L);

        int j = Log(R - L + 1);
        return std::min(ST[L][j], ST[R - (1 << j) + 1][j]);
    }

    int size() const { return ST.size(); }
};


class Graph {
private:
    int v_num;
    std::vector<std::vector<int>> buffer;

    void AddEdge(const int from, const int to) { buffer[from].push_back(to); }

    friend void operator>>(std::istream& inp, Graph& G)
    {
        for (int i = 1; i < G.size(); i++)
        {
            int parent;
            inp >> parent;

            G.AddEdge(parent, i);
        }
    }
public:
    Graph(int _v_num) : v_num(_v_num)
    {
        buffer.resize(v_num);
        std::cin >> *this;
    }

    int size() const { return v_num; }

    void Dfs(std::vector<int>& pos, std::vector<Element>& way,
                const int cur_num, const int cur_depth) const
    {
        way.push_back(Element(cur_num, cur_depth));  
        pos[cur_num] = way.size() - 1;
 
        for (auto _next : buffer[cur_num])
        {
            Dfs(pos, way, _next, cur_depth + 1);
            way.push_back(Element(cur_num, cur_depth));
        }
    }
};


class LCA {
private:
    long long x, y, z;
    long long a1, a2;
    long long N;
    int M;

    friend void operator>>(std::istream& inp, LCA& lca)
    {
        inp >> lca.a1 >> lca.a2;
        inp >> lca.x >> lca.y >> lca.z;
    }

    int next_v() const { return (a1 * x + a2 * y + z) % N; }

    void next_request()
    { 
        a1 = next_v();
        std::swap(a1, a2);

        a1 = next_v();
        std::swap(a1, a2);
    }
public:
    LCA(int _M, const Graph& G): M(_M), N(G.size())
    {
        std::cin >> *this;

        std::vector<int> pos(N, -1);
        std::vector<Element> way;

        G.Dfs(pos, way, 0, 0);
        SparceTable table(way);
        RMQ rmq(M, table);

        Element ans(0, -1);
        int s = 0;

        for (int i = 0; i < M; ++i)
        {
            int first_pos = pos[(a1 + ans.num) % N];
            int second_pos = pos[a2];

            if (first_pos > second_pos)
            {
                std::swap(first_pos, second_pos);
            }

            ans = rmq.find_min(first_pos, second_pos);
            s += ans.num;
            next_request();
        }

        std::cout << s;
    }
};


int main()
{
    int N, M;
    std::cin >> N >> M;

    Graph G(N);
    LCA(M, G);
    
    return 0;
}