#ifndef GRAPH__H__
#define GRAPH__H__

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;
#include "extra.c"

//u can write variable struct names in caps or smalls based on your comfort
typedef struct graph {
	//int array_size;//for the path making
	int n, maxn;
	Vertex** vertices;
}Graph;
typedef struct vertex {
	char* label;
	int id;
	int safetyval;
	Edge* first_edge;
}Vertex;
typedef struct edge {
	int u, v;
	int weight;
	Edge* next_edge;
}Edge;
typedef struct path{
	float safety_val;
	int road_len;
    int size;
	int* arr;
}Path;
Path* total_paths(int n);
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
void value_store(Path *paths,Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]);
void value_get(Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]) ;
void stack_print(List* stack, Graph* graph, bool print_dist,
                 int total_distance);
void store(int i,Path* paths,List* stack, Graph* graph,bool accept,int total_dist);
int distance_sum(List* curr_distance);
void all_paths(Graph* graph,int source_id,int destination_id);

#endif