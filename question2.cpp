// Reference: http://rosettacode.org/wiki/Dijkstra%27s_algorithm
// 1. Implement a version of Dijkstra's algorithm that computes a shortest path from a start vertex to an end vertex in a directed graph.
// 2. Run your program with the following directed graph to find the shortest path from vertex "a" to vertex "e."
// 3. Show the output of your program.

// Vertices
//	Number	Name
//	0		a
//	1		b
//	2		c
//	3		d
//	4		e
//	5		f

// Edges
//	Start	End		Cost
//	a		b		7
//	a		c		9
//	a		f		14
//	b		c		10
//	b		d		15
//	c		d		11
//	c		f		2
//	d		e		6
//	e		f		9

// Adjacency list
//	a -> (b,7)-> (c,9) -> (f,14)
//	b -> (c,10) -> (d,15)
//	c -> (d,11) -> (f,2)
//	d -> (e,6)
//	e -> (f,9)
//	f

#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

enum vertex_t {x=-1, 0, 1, 2, 3, 4, 5,6,7,8,};
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

class neighbor
{
public:
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight): target(arg_target), weight(arg_weight)
	{
	}
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(vertex_t source, const adjacency_list_t &adjacency_list, std::vector<weight_t> &min_distance, std::vector<vertex_t> &previous)
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
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++)
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


std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous)
{
	std::list<vertex_t> path;
	for ( ; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


void dft(int v, adjacency_list_t visited)
{
   visited[v] = true;
  std::cout << " " << v << " ";
   std::vector<int>::iterator it;
//linkedListIterator<int> graphIt;
   for (it = visited[v].begin(); it != visited[v].end();++it)
   {
    int w = *it;
     if (!visited[w])
     dft(w, visited);
    }
}

int main()
{
	// remember to insert edges both ways for an undirected graph
	adjacency_list_t adjacency_list_undirected(9), adjacency_list_directed(9);

	// Directed
	// 0 = a
	adjacency_list_directed[0].push_back(neighbor(4));
	// 1 = b
	adjacency_list_directed[1].push_back(neighbor(0));
        adjacency_list_directed[1].push_back(neighbor(3));
	// 2 = c
	adjacency_list_directed[2].push_back(neighbor(1));
	// 3 = d
	adjacency_list_directed[3].push_back(neighbor(2));
        adjacency_list_directed[3].push_back(neighbor(4));
	// 4 = e
        adjacency_list_directed[4].push_back(neighbor(1));
	adjacency_list_directed[4].push_back(neighbor(9));

         adjacency_list_directed[5].push_back(neighbor(0));
	adjacency_list_directed[5].push_back(neighbor(8));
       adjacency_list_directed[5].push_back(neighbor(6));

       adjacency_list_directed[6].push_back(neighbor(7));
       adjacency_list_directed[6].push_back(neighbor(8));


       adjacency_list_directed[7].push_back(neighbor(8));
       adjacency_list_directed[7].push_back(neighbor(9));

         adjacency_list_directed[8].push_back(neighbor(0));
       adjacency_list_directed[8].push_back(neighbor(4));
        adjacency_list_directed[8].push_back(neighbor(9));

        dft(0,adjacency_list_directed[0]);


	//DijkstraComputePaths(a, adjacency_list_directed, min_distance, previous);
	//std::cout << "Directed Distance from a to e: " << min_distance[e] << std::endl;
	//path = DijkstraGetShortestPathTo(e, previous);
	//std::cout << "Directed Path : ";
	//std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	//std::cout << std::endl;

	return 0;
}