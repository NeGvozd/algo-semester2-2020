/****************************************************************************
Look What You Made Rick Do
****************************************************************************/

#include <iostream>
#include <vector>
#include <string>


class SquareMatrix{
public:
    SquareMatrix(int n)
    {
        _data.reserve(n);
        for (int i = 0; i < n; i++)
        {
            _data.push_back(std::vector<int>(n));
        }
    }

    size_t Size() const { return _data.size(); }

    int& operator()(size_t i, size_t j) { return _data[i][j]; }

    int operator()(size_t i, size_t j) const { return _data[i][j]; }

private:
    std::vector<std::vector<int>> _data;
    friend std::ostream& operator<<(std::ostream& o, const SquareMatrix& matrix);
};


void dfs(const SquareMatrix& matrix, std::vector<bool>& visited,
         int current)
{
    visited[current] = true;

    for (int i = 0; i < matrix.Size(); i++)
    {
        if (matrix(current, i) && !visited[i]) {
            dfs(matrix, visited, i);
        }
    }
}


std::ostream& operator<<(std::ostream& o, const SquareMatrix& matrix)
{
    for (size_t i = 0; i < matrix.Size(); i++)
    {
        for (size_t j = 0; j < matrix.Size(); j++)
        {
            o << matrix(i, j);
        }
        o << std::endl;
    }
    return o;
}


void ReadLine(std::istream& i, SquareMatrix& matrix, int number)
{
    std::string line;
    i >> line;

    for (size_t i = 0; i < matrix.Size(); i++)
    {
        matrix(number, i) = line[i] - '0';
    }
}


int main()
{
    int vertex_count;
    std::cin >> vertex_count;

    SquareMatrix matrix(vertex_count);

    for (int i = 0; i < vertex_count; ++i)
    {
        ReadLine(std::cin, matrix, i);
    }

    std::vector<bool> visited(vertex_count, false);
    std::vector<int> path;

    for (int i = 0; i < vertex_count; i++)
    {
        dfs(matrix, visited, i);

        for (int v = 0; v < vertex_count; v++)
        {
            matrix(i,v) = ((v == i && !matrix(v,v)) ? 0 : visited[v]);
        }
        visited.assign(vertex_count, false);
    }

    std::cout << matrix;

    return 0;
}