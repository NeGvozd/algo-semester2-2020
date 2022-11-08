/****************************************************************************
Who let the Rick out?
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#define INT_MAX 2147483647


struct Vertex
{
    size_t vertex;
    size_t distance;

    bool operator>(const Vertex& V) const
    {
        return this->distance > V.distance;
    }
};


int Dijkstra(const size_t to, const size_t from, 
             const size_t f_cost, const size_t s_cost,
             const int vertex_count)
{
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> heap;
    std::vector<size_t> distances(vertex_count, INT_MAX);
    heap.push({from, 0});
    while(!heap.empty() && distances[to] == INT_MAX)
    {
        Vertex current = heap.top();
        size_t vertex = (current.vertex + 1) % vertex_count;
        size_t distance = f_cost;

        if(distances[vertex] == INT_MAX)
        {
            // distances[vertex] = current.distance + distance;
            heap.push({vertex, current.distance + distance});
        }

        vertex = (current.vertex*current.vertex + 1) % vertex_count;
        distance = s_cost;

        if(distances[vertex] == INT_MAX)
        {
            // distances[vertex] = current.distance + distance;
            heap.push({vertex, current.distance + distance});
        }

        if (distances[heap.top().vertex] == INT_MAX)
        {
            distances[heap.top().vertex] = heap.top().distance;
        }

        while (!heap.empty() && distances[heap.top().vertex] != INT_MAX)
        {
            heap.pop();
        }        
    }
    return distances[to];
}


int main()
{
    size_t f_travel, s_travel, n, from, to;

    std::cin >> f_travel >> s_travel >> n >> from >> to;
    std::cout << Dijkstra(to, from, f_travel, s_travel, n);

    return 0;
}