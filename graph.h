#ifndef GRAPH__H__
#define GRAPH__H__

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;

#include "extra.h"
//u can write variable struct names in caps or smalls based on your comfort

//creates graph from vertices, n starts from 0 and iterates till maxn 
//and maxn: total number of vertices
typedef struct graph {
	int n, maxn;
	Vertex** vertices;
}Graph;
// each vertex will contain- 1. Station Name
//2.ID 		3.Safety value from danger value
//and it goes from edge to edge based on our code
typedef struct vertex {
	char* label;
	int id;
	int safetyval;
	Edge* first_edge;
}Vertex;
//u and v are vertices where the edge is made
//weight = road length essentially in this case
typedef struct edge {
	int u, v;
	int weight;
	Edge* next_edge;
}Edge;
//here this stores all paths from 1 vertex to another and their-
//road length and safety value so that we can sort safety values and then road length
typedef struct path{
	float safety_val;
	int road_len;
    int size;//size of the array which stores the stations which come in the path
	int* arr; // this prints all stations it passes through in order to reach destination station
}Path;

//INIT PATH
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
//we essentially use the directed edges to make the undirected edges
void graph_add_d_edge(Graph* graph, int u, int v, int w);


//TRAVERSALS
//in detail explanation is given in the graph.c file
void value_store(Path *paths,Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]);
void value_get(Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]) ;
void stack_print(List* stack, Graph* graph, bool print_dist,
                 int total_distance);
void store(int i,Path* paths,List* stack, Graph* graph,bool accept,int total_dist);
int distance_sum(List* curr_distance);
void all_paths(Graph* graph,int source_id,int destination_id);
float safety_value(int n,int arr[n]);
int cmpfunc(const void *a, const void *b);

#endif