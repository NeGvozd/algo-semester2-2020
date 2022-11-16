/****************************************************************************
Rick for the Weekend
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>


class Vertex
{
public:
    int vertex;
    int distance;
    int cost;

    Vertex(int vertex, int distance, int cost=0)
    {
        this->vertex = vertex;
        this->distance = distance;
        this->cost = cost;
    }

    bool operator>(const Vertex& V) const
    {
        return this->distance > V.distance;
    }
};


int Dijkstra(const std::vector<std::vector<Vertex>>& graph,
             int from, int to, int cost)
{
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> heap;
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    heap.push({from, 0});

    while(!heap.empty())
    {
        Vertex current = heap.top();
        heap.pop();

        if (distances[current.vertex] == std::numeric_limits<int>::max()) {
            distances[current.vertex] = current.distance;
        }

        if (current.cost < cost) {
            for (auto& v : graph[current.vertex]) {
                if (distances[v.vertex] == std::numeric_limits<int>::max()) {
                    heap.push({v.vertex, current.distance + v.distance, current.cost+1});
                }
            }
        }
    }
    return distances[to] == std::numeric_limits<int>::max() ? -1 : distances[to];
}


int main()
{
    int vertex_count, edge_count, from, to, cost;
    std::cin >> vertex_count >> edge_count >> cost >> from >> to;

    std::vector<std::vector<Vertex>> graph(vertex_count);

    for (int i = 0; i < edge_count; ++i)
    {
        int from, to, distance;
        std::cin >> from >> to >> distance;
        graph[--from].push_back({--to, distance});
    }

    std::cout << Dijkstra(graph, --from, --to, cost) << std::endl;
    return 0;
}