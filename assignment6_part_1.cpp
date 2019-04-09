#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
using namespace std;
enum vertex_t {x=-1, a=0, b=1, c=2, d=3, e=4, f=5, g=6,h=7};
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

class neighbor
{
public:
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight): target(arg_target), weight(arg_weight)
	{
	}
};

typedef vector<vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(vertex_t source, const adjacency_list_t &adjacency_list, vector<weight_t> &min_distance, vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, x);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v])
			{
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));
			}
		}
	}
}


list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous)
{
	list<vertex_t> path;
	for ( ; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


int main()
{
	// remember to insert edges both ways for an undirected graph
	adjacency_list_t adjacency_list_undirected(8), adjacency_list_directed(8);

	// Undirected
	// 0 = a
	adjacency_list_undirected[a].push_back(neighbor(b, 4));
	adjacency_list_undirected[a].push_back(neighbor(d, 6));
	adjacency_list_undirected[a].push_back(neighbor(e, 3));
	// 1 = b
	adjacency_list_undirected[b].push_back(neighbor(a, 4));
	adjacency_list_undirected[b].push_back(neighbor(d, 2));
	adjacency_list_undirected[b].push_back(neighbor(c, 8));
	// 2 = c
	adjacency_list_undirected[c].push_back(neighbor(b, 8));
	adjacency_list_undirected[c].push_back(neighbor(d, 3));
	adjacency_list_undirected[c].push_back(neighbor(g, 1));
	// 3 = d
	adjacency_list_undirected[d].push_back(neighbor(a, 6));
	adjacency_list_undirected[d].push_back(neighbor(b, 2));
	adjacency_list_undirected[d].push_back(neighbor(c, 3));
	adjacency_list_undirected[d].push_back(neighbor(h, 7));
	
	// 4 = e
	adjacency_list_undirected[e].push_back(neighbor(a, 3));
	adjacency_list_undirected[e].push_back(neighbor(h, 1));
	adjacency_list_undirected[e].push_back(neighbor(f, 5));
	// 5 = f
	adjacency_list_undirected[f].push_back(neighbor(e, 5));
	adjacency_list_undirected[f].push_back(neighbor(g, 10));
	adjacency_list_undirected[f].push_back(neighbor(h, 2));
	// 6 = g
	adjacency_list_undirected[g].push_back(neighbor(c, 1));
	adjacency_list_undirected[g].push_back(neighbor(h, 3));
	adjacency_list_undirected[g].push_back(neighbor(f, 10));
	
	// 7 = h
	adjacency_list_undirected[h].push_back(neighbor(d, 7));
	adjacency_list_undirected[h].push_back(neighbor(e, 1));
	adjacency_list_undirected[h].push_back(neighbor(g, 3));
	adjacency_list_undirected[h].push_back(neighbor(f, 2));

	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;
	cout<<"Undirected graph"<<endl;
	cout<<"   a      b       c      d     e     f    g        h"<<endl;
	cout<<endl;
	cout<<"a  ";
	DijkstraComputePaths(a, adjacency_list_undirected, min_distance, previous);
	std::list<vertex_t> path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	cout<<endl;
	cout<<"b  ";
	DijkstraComputePaths(b, adjacency_list_undirected, min_distance, previous);
	
	
	 path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"    ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	cout<<endl;


	cout<<"c  ";
	DijkstraComputePaths(c, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	
	cout<<endl;

	cout<<"d  ";
	DijkstraComputePaths(d, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	cout<<endl;


	cout<<"e  ";
	DijkstraComputePaths(e, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	

	cout<<endl;
	cout<<"f  ";
	DijkstraComputePaths(f, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"     ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	

	cout<<endl;
	cout<<"g  ";
	DijkstraComputePaths(g, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	

	cout<<endl;
	cout<<"h  ";
	DijkstraComputePaths(h, adjacency_list_undirected, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	cout<<endl;
	cout<<endl;


	cout<<"Directed graph"<<endl;
	// Directed
	// 0 = a
	adjacency_list_directed[a].push_back(neighbor(e, 3));
	// 1 = b
	adjacency_list_directed[b].push_back(neighbor(a, 4));
	adjacency_list_directed[b].push_back(neighbor(d, 2));
	// 2 = c
	adjacency_list_directed[c].push_back(neighbor(b, 8));
	adjacency_list_directed[c].push_back(neighbor(d, 3));
	// 3 = d
	adjacency_list_directed[d].push_back(neighbor(a, 6));
	adjacency_list_directed[d].push_back(neighbor(h, 7));
	
	// 4 = e
	adjacency_list_directed[e].push_back(neighbor(h, 1));
	adjacency_list_directed[e].push_back(neighbor(f, 5));
	// 5 = f
	adjacency_list_directed[f].push_back(neighbor(g, 10));
	adjacency_list_directed[f].push_back(neighbor(h, 2));
	// 6 = g
	adjacency_list_directed[g].push_back(neighbor(c, 1));
	// 7 = h
	adjacency_list_directed[h].push_back(neighbor(g, 3));

	cout<<"   a      b       c      d     e     f    g        h"<<endl;
	cout<<endl;
	cout<<"a  ";
	
	DijkstraComputePaths(a, adjacency_list_directed, min_distance, previous);
	
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	cout<<endl;
	cout<<"b  ";
	DijkstraComputePaths(b, adjacency_list_directed, min_distance, previous);
	
	
	 path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"    ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	cout<<endl;


	cout<<"c  ";
	DijkstraComputePaths(c, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	
	cout<<endl;

	cout<<"d  ";
	DijkstraComputePaths(d, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	cout<<endl;


	cout<<"e  ";
	DijkstraComputePaths(e, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	

	cout<<endl;
	cout<<"f  ";
	DijkstraComputePaths(f, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"     ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	

	cout<<endl;
	cout<<"g  ";
	DijkstraComputePaths(g, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);
	

	cout<<endl;
	cout<<"h  ";
	DijkstraComputePaths(h, adjacency_list_directed, min_distance, previous);
	path = DijkstraGetShortestPathTo(a, previous);
	cout <<  min_distance[a] <<"      ";
	cout <<  min_distance[b] <<"       ";
	path = DijkstraGetShortestPathTo(b, previous);
	cout <<  min_distance[c] <<"      ";
	path = DijkstraGetShortestPathTo(c, previous);
	cout << min_distance[d] <<"     ";
	path = DijkstraGetShortestPathTo(d, previous);
	cout <<  min_distance[e] <<"     ";
	path = DijkstraGetShortestPathTo(e, previous);
	cout <<min_distance[f] <<"    ";
	path = DijkstraGetShortestPathTo(f, previous);
    cout << min_distance[g] <<"        ";
	path = DijkstraGetShortestPathTo(g, previous);
	cout  << min_distance[h] << std::endl;
	path = DijkstraGetShortestPathTo(h, previous);

	cout<<endl;
	cout<<endl;

	return 0;
}