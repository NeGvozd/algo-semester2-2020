/****************************************************************************
MST-1

****************************************************************************/

#include <iostream>
#include <vector>
#include <array>
#include <queue>


inline std::pair<std::vector<std::pair<int,int>>, int> prima(const std::vector<std::vector<int>>& g, const std::vector<std::vector<int>>& w) {
	std::vector<int> keys(g.size(), -1);
	std::vector<bool> visited(g.size(), 0);
	std::vector<int> parents(g.size(), -1);

	std::priority_queue<std::pair<int, int>> q;
	q.push({ 0, 0 });
	keys[0] = 0;
	while (!q.empty()) {
		int v = q.top().second;
		int key = -q.top().first;
		//std::cout << "Dj " << v << " " << d << std::endl;
		q.pop();
		if (key > keys[v])
			continue;
		visited[v] = true;
		for (int iu = 0; iu < g[v].size(); ++iu) {
			int u = g[v][iu];
			int wu = w[v][iu];
			if(visited[u])
				continue;
			if (keys[u] == -1 || keys[u] > wu) {
				keys[u] = wu;
				q.push({ -keys[u], u });
				parents[u] = v;
			}
		}
	}
	int treeWeight=0;
	std::vector<std::pair<int,int>> tree;
	for(int v=1;v<parents.size();v++)
	{
		tree.push_back({parents[v],v});
		treeWeight+=keys[v];
	}

	return {tree,treeWeight};
}

int main(){
    int N,M;
    int a,b,c;
    std::cin >> N >> M;
    std::vector<std::vector<int>> g(N);
    std::vector<std::vector<int>> W(N);

    for(int i = 0;i < M;i++)
    {
        std::cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
        W[a].push_back(c);
        W[b].push_back(c);
    }
    //std::cout<<"I am here";
    std::cout<<prima(g,W).second;
}