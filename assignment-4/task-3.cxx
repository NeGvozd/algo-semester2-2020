/****************************************************************************
Художник и фотограф
****************************************************************************/


#include <iostream>
#include <vector>
#include <climits>


class SegmentTree {
public:
    void Build(int, int, int);

    void CountBright();

    int FindMin(int v, int tl, int tr, int l, int r);

    void Update(int v, int tl, int tr, int l, int r, int new_val);
 
    void Push(int, int, int);

private:
    std::vector<int> tree;
    std::vector<int> tAdd;
    std::vector<int> sequence;
    int n;
};
 
void SegmentTree::Build(int v, int l, int r)
{
    if (l == r)
    {
        tree[v] = sequence[l];
    }
    else
    {
        int m = (l + r) / 2;

        Build(v * 2 + 1, l, m);
        Build(v * 2 + 2, m + 1, r);

        tree[v] = std::min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
}
 
int SegmentTree::FindMin(int v, int tl, int tr, int l, int r)
{
    Push(v, tl, tr);
 
    if (tl > r || tr < l) return INT_MAX;
 
    if (l <= tl && tr <= r) return tree[v];
 
    int tm = tl + (tr - tl) / 2;
    int child_1 = FindMin(v * 2 + 1, tl, tm, l, r);
    int child_2 = FindMin(v * 2 + 2, tm + 1, tr, l, r);

    return std::min(child_1, child_2);
}
 
void SegmentTree::Update(int v, int tl, int tr, int l, int r, int new_val)
{
    Push(v, tl, tr);

    if (r < tl || tr < l) return;

    if (l <= tl && tr <= r)
    {
        tAdd[v] = new_val;
        Push(v, tl, tr);
        return;
    }

    int tm = tl + (tr - tl) / 2;
    Update(v * 2 + 1, tl, tm, l, r, new_val);
    Update(v * 2 + 2, tm + 1, tr, l, r, new_val);
 
    tree[v] = std::min(tree[v * 2 + 1], tree[v * 2 + 2]);
}
 
void SegmentTree::Push(int v, int tl, int tr)
{
    if (tAdd[v] != INT_MAX)
    {
        tree[v] = tAdd[v];

        if (tl != tr)
        {
            tAdd[v * 2 + 1] = tAdd[v];
            tAdd[v * 2 + 2] = tAdd[v];
        }
        tAdd[v] = INT_MAX;
    }
}
 
 
void SegmentTree::CountBright()
{
    std::cin >> n;

    tree = std::vector<int>(4 * n, INT_MAX);
    tAdd = std::vector<int>(4 * n, INT_MAX);

    sequence = std::vector<int>(n);

    for (int i = 0; i < n; i++)
    {
        int r, g, b;
        std::cin >> r >> g >> b;
        sequence[i] = r + g + b;
    }
 
    Build(0, 0, n - 1);
 
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        int c, d, r, g, b, e, f;
        std::cin >> c >> d >> r >> g >> b >> e >> f;
        int a = r + g + b;
 
        Update(0, 0, n - 1, c, d, a);
 
        int k = FindMin(0, 0, n - 1, e, f);
        std::cout << k << ' ';
    }
 
}
 
int main()
{
    SegmentTree t;
    t.CountBright();

    return 0;
}