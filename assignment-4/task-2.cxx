/****************************************************************************
Система бронирования
****************************************************************************/


#include <iostream>
#include <vector>
#include <climits>

const int INF = INT_MAX;

class Tree {
public:
    explicit Tree(std::vector<int> t) : _tree(t) {}

    void Solve(int n, int p, int k)
    {
        for(int i = 0; i < n; ++i)
        {
            _tree[k - 1 + i] = p - _tree[k - 1 + i];
        }

        _tree[0] = get_min(0);

        int number_of_requests = 0;
        std::cin >> number_of_requests;

        std::vector<int> res;
        int l, r, w;

        for (int i = 0; i < number_of_requests; ++i)
        {
            std::cin >> l >> r >> w;

            if (RmqBuild(l, r, 0, 0, _tree.size() / 2 + 1) >= w)
            {
                for(int j = l; j < r; ++j)
                    Remove(j, w);
            } 
            else 
            {
                res.push_back(i);
            }
        }

        for(int i = 0; i < res.size(); ++i)
        {
            std::cout << res[i] << ' ';
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> _tree;

    void Update(unsigned long _ind) {
        if(_ind <= 0) {
            return;
        }
        unsigned long prev = (_ind - 1) / 2;
        _tree[prev] = std::min(_tree[prev * 2 + 1], _tree[prev * 2 + 2]);
        Update(prev);
    }

    void Remove(int _ind, int _value) {
        unsigned long k = _tree.size() / 2;
        _tree[k + _ind] -= _value;
        Update(k + _ind);
    }

    int RmqBuild(int left, int right, int x, int lx, int rx) {
        if(left <= lx && right >= rx) return _tree[x];
        if(left >= rx || right <= lx) return INF;

        int mx = (lx + rx) / 2;

        return std::min(RmqBuild(left, right, 2 * x + 1, lx, mx), 
                        RmqBuild(left, right, 2 * x + 2, mx, rx));
    }

    int get_min(int _ind)
    {
        if(_ind >= (_tree.size()/2)) return _tree[_ind];

        _tree[2 * _ind + 1] = get_min(2 * _ind + 1);
        _tree[2 * _ind + 2] = get_min(2 * _ind + 2);

        return std::min(_tree[2 * _ind + 1], (_tree[2 * _ind + 2]));
    }
};


int main() 
{
    int n;
    std::cin >> n;
    --n;

    int k = 1;
    while(k < n)
    {
        k *= 2;
    }

    int treeSize = 2 * k - 1;
    std::vector<int> t(treeSize, INF);

    for(int i = 0; i < n; ++i)
    {
        std::cin >> t[k - 1 + i];
    }

    Tree tree(t);

    int p;
    std::cin >> p;

    tree.Solve(n+2, p, k);
}
