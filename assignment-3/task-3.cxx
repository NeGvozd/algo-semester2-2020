/****************************************************************************
Сделай связным
****************************************************************************/

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

class DisjointSetUnion{ //class for crascall
private:
  std::vector<long long> parent;
  std::vector<long long> rank;
public:
  DisjointSetUnion(long long n):parent(n), rank(n, 1){ //calling vector constructor with parametrs n
    for(long long i = 0; i<n; ++i) 
      parent[i] = i;
    
  }
  long long get(long long v){//finding representatives of set
    while(v!=parent[v])
      v=parent[v];
    return v;
  }
  long long unite(long long v, long long u){
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

std::pair<std::vector<std::pair<long long,long long>>, long long> cruskall(const std::vector<std::pair<long long, long long>>& g, const std::vector<long long>& w) {
  std::vector<long long> index(g.size());//point at elements of first and second vectors
  long long n = 0; //number of vertex
  for(long long i = 0; i<g.size(); ++i){ //g.size - number of edges in not-oriented graph
    index[i] = i;
    n = std::max(std::max(n, g[i].first), g[i].second);
  }
  n++;
  std::sort(index.begin(), index.end(), [&w](long long i, long long j){
    return w[i]<w[j];  
  });
  DisjointSetUnion DSU(n);
  std::vector<std::pair<long long,long long>> tree;
  long long treeWeight = 0;
  for(long long i : index){
    long long v = g[i].first;
    long long u = g[i].second;
    long long wvu = w[i];
    if(DSU.get(v) != DSU.get(u)){
      DSU.unite(v, u);
      treeWeight+=wvu;
      tree.push_back({v, u});
    }
  }
  return {tree, treeWeight};
}
std::pair<std::vector<std::pair<long long,long long>>, long long> cruskall(const std::vector<std::vector<long long>>& g, const std::vector<std::vector<long long>>& w) {
  std::vector<std::pair<long long, long long>> g1;
  std::vector<long long> w1;
  for(long long v = 0; v<g.size(); ++v)
    for(long long iu=0; iu<g[v].size(); ++iu){
      g1.push_back({v, g[v][iu]});
      w1.push_back(w[v][iu]);
    }
  return cruskall(g1, w1);
}


int main()
{
    // INPUT
    long long N, M;
    long long b,e,val;
  long long min_val = INT_FAST64_MAX;
  long long min_v;
    std::ifstream file("input.txt");
    file >> N >> M;
  std::vector<long long> A(N);
    std::vector<std::vector<long long>> g(N);
    std::vector<std::vector<long long>> w(N);
  for(long long i = 0; i < N; ++i){ 
    file >> val;
    A[i] = val;
    if (val < min_val){
      min_val = val;
      min_v = i;
    }
  }
  for(long long i = 0; i < N; ++i){ 
    g[i].push_back(min_v);
    w[i].push_back(min_val + A[i]);
    g[min_v].push_back(i);
    w[min_v].push_back(min_val + A[i]);
  }
    for(long long i = 0; i < M; ++i){
        file >> b >> e >> val;
        g[b-1].push_back(e-1);
        g[e-1].push_back(b-1);
        w[b-1].push_back(val);
        w[e-1].push_back(val);
    }
  

  std::cout<<cruskall(g,w).second;
}
