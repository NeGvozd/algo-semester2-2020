/****************************************************************************
Сломанный мост
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>


enum class PlateStatus
{
    Whole = '.',
    Empty = '*'
};


int Bfs(std::vector<std::vector<int>>& graph,
        std::vector<int>& dist, int s, int u)
{
    std::fill(dist.begin(), dist.end()-2, std::numeric_limits<int>::max());
    dist[u] = std::numeric_limits<int>::max();

    std::queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int w : graph[v])
        {
            if (w == u)
            {
                dist[u] = dist[v] + 1;
                return 1;
            }
            if (dist[w] == std::numeric_limits<int>::max())
            {
                dist[w] = dist[v] + 1;
                q.push(w);
            }
        }
    }

    return 0;
}


int Dfs(std::vector<std::vector<int>>& graph, 
        std::vector<int>& dist, int s, int u)
{
    auto d = std::find(graph[s].begin(), graph[s].end(), u);
    if (d != graph[s].end() && dist[u] == dist[s] + 1)
    {
        graph[s].erase(d);
        return 1;
    }

    for (auto iterator = graph[s].begin(); iterator != graph[s].end(); ++iterator)
    {
        if (dist[*iterator] == dist[s] + 1 && Dfs(graph, dist, *iterator, u))
        {
            graph[*iterator].push_back(s);
            graph[s].erase(iterator);
            return 1;
        }
    }

    return 0;
}


int Dinic(std::vector<std::vector<int>>& graph, int s)
{
    int flux = 0;
    int u = s+1;
    std::vector<int> dist(graph.size());

    while(Bfs(graph, dist, s, u))
        while(Dfs(graph, dist, s, u))
            ++flux;

    return flux;
}


int main()
{
    int n, m, double_plate_time, single_plate_time;
    std::cin >> n >> m >> double_plate_time >> single_plate_time;

    std::vector<char> plates; 
    plates.reserve(n*m);
    std::vector<std::vector<int>> graph(n*m + 2);
    int empty_count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {            
            char c;
            std::cin >> c;
            
            if (c == (char)PlateStatus::Empty)
            {
                ++empty_count;

                int seq_number = (i - 1)*m + j,
                    var1 = i*m + j - 1;

                if ((i+j) % 2 != 0)
                {
                    graph[i*m + j].push_back(m*n + 1);

                    if (plates[seq_number] == (char)PlateStatus::Empty &&
                        i > 0)
                    {
                        graph[seq_number].push_back(i*m + j);
                    }
                    if (plates[var1] == (char)PlateStatus::Empty &&
                        j > 0)
                    {
                        graph[var1].push_back(i*m + j);
                    }
                }
                if ((i+j) % 2 == 0)
                {
                    graph[m*n].push_back(i*m + j);

                    if (plates[seq_number] == (char)PlateStatus::Empty &&
                        i > 0)
                    {
                        graph[i*m + j].push_back(seq_number);
                    }
                    if (plates[var1] == (char)PlateStatus::Empty &&
                        j > 0)
                    {
                        graph[i*m + j].push_back(var1);
                    }
                }
            }
            plates.push_back(c);
        }
    }

    if (single_plate_time*2 <= double_plate_time)
    {
        std::cout << single_plate_time*empty_count << std::endl;
        return 0;
    }
    if (m*n == empty_count)
    {
        std::cout << ((m*n) / 2)*double_plate_time + ((m*n) % 2)*single_plate_time
                  << std::endl;
        return 0;
    }
    
    int flux = Dinic(graph, n*m);
    std::cout << flux*double_plate_time + (empty_count - flux*2)*single_plate_time
              << std::endl;

    return 0;
}