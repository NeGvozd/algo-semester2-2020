/****************************************************************************
Глупая ссора
****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <string>
#include <queue>


bool FindPath(std::vector<std::unordered_map<int, int>>& graph, std::vector<int>& path, 
              int edge_num1, int edge_num2)
{
    std::queue<int> q;
    std::vector<bool> visited(graph.size());
    std::vector<int> parent(graph.size(), -1);
    q.push(edge_num1);
    visited[edge_num1] = true;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        if(u == edge_num2)
            break;

        for(auto [v, c] : graph[u])
        {
            if(!visited[v] && c)
            {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    while(parent[edge_num2] != -1)
    {
        path.push_back(edge_num2);
        edge_num2 = parent[edge_num2];
    }
    return !path.empty();
}


void PrintPath(std::vector<std::unordered_map<int, int>>& flux, 
               std::vector<int>& path, int edge_num1, int edge_num2)
{
    FindPath(flux, path, 0, edge_num2);

    for(int i = path.size() - 1; i > 0; --i)
    {
        --flux[path[i]][path[i - 1]];
    }

    --flux[0][edge_num1];

    for(auto iterator = path.rbegin(); iterator != path.rend(); ++iterator)
    {
        if(*iterator <= (flux.size() - 1)/2)
            std::cout << (*iterator) << ' ';
    }

    std::cout << std::endl;
}


int main()
{
    int vertex_count, edge_count, edge_num1, edge_num2;
    std::cin >> vertex_count >> edge_count >> edge_num1 >> edge_num2;

    std::vector<std::unordered_map<int, int>> graph(2*vertex_count + 1);
    std::vector<std::unordered_map<int, int>> flux(2*vertex_count + 1);
    
    for(int i = 0; i < edge_count; ++i)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        if(v1 == v2 || v2 == edge_num1 || v1 == edge_num2)
            continue;

        auto iterator = graph[v2].find(v1);
        if(iterator == graph[v2].end())
        {
            ++graph[v1][v2];
            flux[v1][v2] = 0;
        }
        else
        {
            ++graph[v1][vertex_count + v2];
            ++graph[vertex_count + v2][v2];
            flux[v1][vertex_count + v2] = 0;
            flux[vertex_count + v2][v2] = 0;
        }
    }
    
    graph[0][edge_num1] = 2;
    flux[0][edge_num1] = 0;

    std::vector<int> path;
    while(FindPath(graph, path, 0, edge_num2))
    {
        for(int i = 0; i < path.size() - 1; ++i)
        {
            auto [l, r] = std::pair<int, int>(path[i + 1], path[i]);
            if(flux[l].find(r) != flux[l].end())
            {
                ++flux[l][r];
            }
            else
            {
                --flux[r][l];
            }

        	--graph[l][r];
        	++graph[r][l];
        }

        ++flux[0][edge_num1];
        --graph[0][edge_num1];
        path.clear();
    }

    if(flux[0][edge_num1] == 2)
    {
        std::cout << "YES" << '\n';
        PrintPath(flux, path, 0, edge_num2);
        path.clear();
        PrintPath(flux, path, 0, edge_num2);
    }
    else 
    {
        std::cout << "NO" << '\n';
    }

    return 0;
}

