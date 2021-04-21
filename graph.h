#ifndef GRAPH__H__
#define GRAPH__H__

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;

#include "extra.c"

struct graph {
	int n, maxn;
	Vertex** vertices;
};
struct vertex {
	char* label;
	Edge* first_edge;
};
struct edge {
	int u, v;
	int weight;
	Edge* next_edge;
};
// create a new, empty graph, with space for a maximum of n vertices
Graph* new_graph(int n);
// destroy a graph, its vertices, and their edges
void free_graph(Graph* graph);
// add a new vertex with label 'name' to a graph
void graph_add_vertex(Graph* graph, const char* name);
// add an undirected edge between u and v with weight w to graph
void graph_add_u_edge(Graph* graph, int u, int v, int w);
// add a directed edge from u to v with weight w to a graph
void graph_add_d_edge(Graph* graph, int u, int v, int w);


//TRAVERSALS
void print_dfs(Graph* graph, int source_id);
void print_bfs(Graph* graph, int source_id);
void detailed_path(Graph* graph, int source_id, int destination_id);
void all_paths(Graph* graph, int source_id, int destination_id);
void shortest_path(Graph* graph, int source_id, int destination_id);
#endif