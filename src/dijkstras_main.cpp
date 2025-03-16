#include "dijkstras.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cerr << "Usage: " << argv[0] << "large.txt";
        return 1;
    }

    Graph G;
    try
    {
        file_to_graph(argv[1], G);
    }
    catch(const runtime_error &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> dis = dijkstra_shortest_path(G, 0, previous);

    for(int i = 0; i < G.numVertices; i++)
    {
        vector<int> path = extract_shortest_path(dis, previous, i);

        if(dis[i] == INF)
        {
            cout << 0 << " " << i << endl;
            cout << "Total cost is INF\n";
        }
        else
        {
            print_path(path, dis[i]);
        }
    }

    return 0;
}