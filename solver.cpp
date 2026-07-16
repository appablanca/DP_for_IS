#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Vertex
{
public:
    int id;
    int degree;

    Vertex(int id) : id(id), degree(0) {}

    vector<int> get_neighbors(const vector<vector<int>> &adj_matrix) const
    {
        vector<int> neighbors;

        for (int j = 0; j < adj_matrix.size(); j++)
        {
            if (adj_matrix[id][j] == 1)
            {
                neighbors.push_back(j);
            }
        }

        return neighbors;
    }
};

class Edge
{
public:
    int u, v;

    Edge(int u, int v) : u(u), v(v) {}
};

class Graph
{
public:
    vector<Vertex> vertices;
    vector<Edge> edges;
    vector<vector<int>> adj_matrix;

    Graph(int n)
    {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            vertices.push_back(Vertex(i));
        }
    }

    void add_edge(int u, int v)
    {
        if (adj_matrix[u][v] == 1)
            return;

        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1;

        vertices[u].degree++;
        vertices[v].degree++;

        edges.push_back(Edge(u, v));
    }

    bool has_edges() const
    {
        return !edges.empty();
    }

    Edge get_any_edge() const
    {
        return edges[0];
    }

    void remove_vertex(int v)
    {
        int n = adj_matrix.size();

        for (int u = 0; u < n; u++)
        {
            if (adj_matrix[v][u] == 1)
            {
                adj_matrix[v][u] = 0;
                adj_matrix[u][v] = 0;

                vertices[v].degree--;
                vertices[u].degree--;
            }
        }

        vector<Edge> new_edges;

        for (const Edge &e : edges)
        {
            if (e.u != v && e.v != v)
            {
                new_edges.push_back(e);
            }
        }

        edges = new_edges;
    }

    void printGraph()
    {
        cout << vertices.size() << endl;
        cout << edges.size() << endl;
    }
};

class Bag
{
public:
    int id;
    int degree;
    vector<int> constitiuents;

    Bag(int id) : id(id), degree(0) {}

    void addToBag(int a)
    {
        constitiuents.push_back(a);
    }
};

enum NodeType
{
    LEAF,
    INTRODUCE,
    FORGET,
    JOIN
};

class NiceBag
{
public:
    int id;
    NodeType type;
    vector<int> bag;
    int vertex;
    int parent;
    vector<int> children;
    
};

class TD
{
public:
    vector<Bag> bags;
    vector<Edge> edges;
    vector<vector<int>> adj_matrix;
    int width;

    TD(int n)
    {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            bags.push_back(Bag(i));
        }
    }

    void add_edge(int u, int v)
    {
        if (adj_matrix[u][v] == 1)
            return;

        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1;

        bags[u].degree++;
        bags[v].degree++;

        edges.push_back(Edge(u, v));
    }

    void printTD()
    {
        cout << bags.size() << endl;
        for (auto &bag : bags)
        {
            cout << "Bag " << bag.id << ": ";

            for (int v : bag.constitiuents)
                cout << v << " ";
            cout << bag.degree;
            cout << endl;
        }
        for (const auto &row : adj_matrix)
        {
            for (int x : row)
                cout << x << " ";

            cout << '\n';
        }
    }
};

Graph getGraphFromFile(const string &filename)
{
    ifstream f(filename);

    string p, tw;

    int n, m;

    f >> p >> tw >> n >> m;

    Graph g(n);

    int u, v;

    while (f >> u >> v)

    {

        g.add_edge(u - 1, v - 1);
    }

    return g;
}
TD getTDFromFile(const string &filename)
{
    ifstream f(filename);

    string s, tds;

    int N, W, n;

    f >> s >> tds >> N >> W >> n;

    TD td(N);
    char b;
    int bagID;
    int c;
    for (int i = 0; i < N; i++)
    {
        f >> b >> bagID;
        while (true)
        {
            f >> c;
            td.bags[bagID - 1].addToBag(c);
            while (isspace(f.peek()) && f.peek() != '\n')
                f.get();

            if (f.peek() == '\n')
            {
                f.get();
                break;
            }
        }
    }
    int u, v;
    while (f >> u >> v)
    {
        td.add_edge(u - 1, v - 1);
    }
    return td;
}

int main()
{
    string filename = "./inputs/DBLP-v1";
    Graph g = getGraphFromFile(filename + ".gr");
    TD td = getTDFromFile(filename + ".td");

    return 0;
}