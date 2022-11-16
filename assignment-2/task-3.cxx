/****************************************************************************
Wake Me Up When Rickember Ends
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>


class Vertex
{
public:
    int vertex;
    double distance;

    Vertex(int vertex, double distance)
    {
        this->vertex = vertex;
        this->distance = distance;
    }

    bool operator>(const Vertex& V) const
    {
        return this->distance > V.distance;
    }
};


double Dijkstra(const std::vector<std::vector<Vertex>>& graph,
             int from, int to)
{
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> heap;
    std::vector<double> distances(graph.size(), std::numeric_limits<int>::max());
    heap.push({from, 0});

    while(!heap.empty())
    {
        Vertex current = heap.top();

        if (distances[current.vertex] == std::numeric_limits<int>::max()) {
            distances[current.vertex] = current.distance;
        }

        while(distances[current.vertex] != std::numeric_limits<int>::max())
        {
            heap.pop();
            for (auto& v : graph[current.vertex])
            {
                if (distances[v.vertex] == std::numeric_limits<int>::max()) {
                    heap.push({v.vertex, v.distance + (1 - v.distance) * current.distance});
                }
            }

            if (heap.empty()) {
                break;
            }
            current = heap.top();
        }
    }
    return distances[to];
}


int main()
{
    int n, m, from, to;
    std::cin >> n >> m >> from >> to;

    std::vector<std::vector<Vertex>> graph(n);
    int variant = 0;

    for(int i = 0; i < m; i++)
    {
        int from, to;
        double distance;
        std::cin >> from >> to >> distance;
        graph[--from].push_back({--to, distance/100});
        graph[to].push_back({from, distance/100});
    }

    std::cout << Dijkstra(graph, --from, --to) << std::endl;
    return 0;
}