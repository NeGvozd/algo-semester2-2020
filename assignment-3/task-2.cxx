/****************************************************************************
MST-2
****************************************************************************/

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

class DisjointSetUnion{ //class for crascall
private:
  std::vector<int> parent;
  std::vector<int> rank;
public:
  DisjointSetUnion(int n):parent(n), rank(n, 1){ //calling vector constructor with parametrs n
    for(int i = 0; i<n; ++i) 
      parent[i] = i;
    
  }
  int get(int v){//finding representatives of set
    while(v!=parent[v])
      v=parent[v];
    return v;
  }
  int unite(int v, int u){
    v = get(v);
    u = get(u);
    if(v == u)//if it is one set, that do nothing 
      return v;
    if(rank[v] == rank[u])//else connect one set to another. If rangs are equal, add 1 to one of
      ++rank[v];
    if(rank[v] < rank[u]){
      parent[v] = u;
      return u;
    }
    else{ //if(rank[v] >= rank[u]) 
      parent[u] = v;
      return v;
    }
  }
};

std::pair<std::vector<std::pair<int,int>>, int> cruskall(const std::vector<std::pair<int, int>>& g, const std::vector<int>& w) {
  std::vector<int> index(g.size());//point at elements of first and second vectors
  int n = 0; //number of vertex
  for(int i = 0; i<g.size(); ++i){ //g.size - number of edges in not-oriented graph
    index[i] = i;
    n = std::max(std::max(n, g[i].first), g[i].second);
  }
  n++;
  std::sort(index.begin(), index.end(), [&w](int i, int j){
    return w[i]<w[j];  
  });
  DisjointSetUnion DSU(n);
  std::vector<std::pair<int,int>> tree;
  int treeWeight = 0;
  for(int i : index){
    int v = g[i].first;
    int u = g[i].second;
    int wvu = w[i];
    if(DSU.get(v) != DSU.get(u)){
      DSU.unite(v, u);
      treeWeight+=wvu;
      tree.push_back({v, u});
    }
  }
  return {tree, treeWeight};
}
std::pair<std::vector<std::pair<int,int>>, int> cruskall(const std::vector<std::vector<int>>& g, const std::vector<std::vector<int>>& w) {
  std::vector<std::pair<int, int>> g1;
  std::vector<int> w1;
  for(int v = 0; v<g.size(); ++v)
    for(int iu=0; iu<g[v].size(); ++iu){
      g1.push_back({v, g[v][iu]});
      w1.push_back(w[v][iu]);
    }
  return cruskall(g1, w1);
}


int main()
{
    // INPUT
    int N, M;
    int b,e,val;
    std::ifstream file("input.txt");
    file >> N >> M;
    std::vector<std::vector<int>> g(N);
    std::vector<std::vector<int>> w(N);

    for(int i = 0; i < M; ++i){
        file >> b >> e >> val;
        g[b-1].push_back(e-1);
        g[e-1].push_back(b-1);
        w[b-1].push_back(val);
        w[e-1].push_back(val);
    }

  std::cout<<cruskall(g,w).second;
}