#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graph.h"

// create a new vertex with a specific label
Vertex* new_vertex(const char* label) {
	assert(label);

	Vertex* vertex = malloc(sizeof (*vertex));
	assert(vertex);

	// make sure to copy the label across
	vertex->label = malloc((1 + strlen(label)) * sizeof (char));
	assert(vertex->label);
	strcpy(vertex->label, label);

	vertex->first_edge = NULL;

	return vertex;
}
// create a new w-weighted edge from vertex id u to vertex id v
Edge* new_edge(int u, int v, int w) {
	Edge* edge = malloc(sizeof (*edge));
	assert(edge);

	edge->u = u;
	edge->v = v;
	edge->weight = w;

	edge->next_edge = NULL;

	return edge;
}
// destroy a vertex, including its label and all of its edges
void free_vertex(Vertex* vertex) {
	if (vertex) {
		while (vertex->first_edge) {
			Edge* edge = vertex->first_edge;
			vertex->first_edge = vertex->first_edge->next_edge;
			free(edge);
		}
		free(vertex->label);
		free(vertex);	
	}
}
/* function definitions */

// create a new, empty graph, with space for n vertices
Graph* new_graph(int n) {
	Graph* graph = malloc(sizeof (*graph));
	assert(graph);
	
	graph->n = 0;
	graph->maxn = n;
	
	graph->vertices = malloc(n * sizeof (Vertex*));
	assert(graph->vertices);
	
	return graph;
}
// destroy a graph, its vertices, and their edges
void free_graph(Graph* graph) {
	if (graph) {
		int i;
		for (i = 0; i < graph->n; i++) {
			free_vertex(graph->vertices[i]);
		}

		free(graph->vertices);
		free(graph);	
	}
}
// add a new vertex with label 'name' to a graph
void graph_add_vertex(Graph* graph, const char* name) {
	if (graph->n < graph->maxn) {
		graph->vertices[graph->n] = new_vertex(name);	
		graph->n++;
	} else {
		fprintf(stderr, "hey! adding new vertex to full graph\n");
	}
}
// add an undirected edge between u and v with weight w to graph
void graph_add_u_edge(Graph* graph, int u, int v, int w) {
	// an undirected edge is just two directed edges
	graph_add_d_edge(graph, u, v, w);
	graph_add_d_edge(graph, v, u, w);
}
// add a directed edge from u to v with weight w to a graph
void graph_add_d_edge(Graph* graph, int u, int v, int w) {
	if(u < graph->n && u >= 0 && v < graph->n && v >= 0) {
		Edge* edge = new_edge(u, v, w);
		edge->next_edge = graph->vertices[u]->first_edge;
		graph->vertices[u]->first_edge = edge;
	} else {
		printf("hey! adding edge between non-existant vertices\n");
	}
    
}

//TRAVERSE
void false_array(Graph* graph, bool array[]) {//used to set all values to false
    int i;
    for (i=0; i < graph->n; i++)
        array[i] = false;
}
void stack_print(List* stack, Graph* graph, int total_distance);
void dfs_path(Graph* graph, int destination_id, int id, bool is_source, List* stack, bool visited[]);
void short_path_search(Graph* graph, int destination_id, int id, bool is_source, List* distances, List* curr_distance, List* stack, bool visited[],int shortest_loc, int *count);
int distance_sum(List* curr_distance);
// Calculates the total distance by adding all distances in curr_distance list
int distance_sum(List* curr_distance) {
    int x, sum=0;
    List* tempstack=new_stack();
    while (!stack_is_empty(curr_distance)) {
        x = stack_pop(curr_distance);
        sum += x;
        stack_push(tempstack, x);
    }
    while (!stack_is_empty(tempstack))
        stack_push(curr_distance, stack_pop(tempstack));
    
    return sum;
    
    free_stack(tempstack);
}

/******************************************************************************/

// Prints the path stored in the stack
void stack_print(List* stack, Graph* graph, int total_distance) {
    int x;
    List* tempstack=new_stack();
    printf("%d",stack_size(stack));
    while (!stack_is_empty(stack))
        stack_push(tempstack, stack_pop(stack));
    
    while (stack_size(tempstack)>1) {
        x = stack_pop(tempstack);
        stack_push(stack, x);
        printf("%s, ", graph->vertices[x]->label);
    }
    
    x = stack_pop(tempstack);
    printf("%s (%dkm)\n", graph->vertices[x]->label, total_distance);
    
    stack_push(stack, x);
    
    free_stack(tempstack);
}
/* PART 3: print all paths */
void all_paths(Graph* graph, int source_id, int destination_id) {
    
    // Create zeroed visited array
    bool visited[graph->n];
    false_array(graph, visited);//sets all elements to false
    
    // Create a stack
    List* stack=new_stack(); //make a new stack
    dfs_path(graph, destination_id, source_id, true, stack, visited);
    free_stack(stack);
}

// Finds a simple path from id to destination_id using depth first search
void dfs_path(Graph* graph, int destination_id, int id, bool is_source, List* stack, bool visited[]) {
    Edge *curredge=graph->vertices[id]->first_edge; //calling the edge connected to the source_id
    if (is_source) {//we took true as above
        stack_push(stack, id);//id = source_id
        visited[id] = true;
    }
    
    // Iterate until the stack is empty
    while (!stack_is_empty(stack)) {
        id = curredge->v;
        
        // Vertex is unvisited
        if (!visited[id]) {
            visited[id] = true;
            stack_push(stack, id);
            
            // Destination is reached
            if (destination_id == id) {
                stack_print(stack, graph, 0);
                stack_pop(stack);
            }
            // Destination is not reached
            else
                dfs_path(graph, destination_id, id, false, stack, visited);
            
            visited[id] = false;
        }
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            break;
        }
    }
}

/******************************************************************************/
/* PART 4: print shortest path */

void shortest_path(Graph* graph, int source_id, int destination_id) {
	
    // Create false visited array
    bool visited[graph->n];
    false_array(graph, visited);
    
    // Create a stack and queue
    List* stack=new_stack();
    List* curr_distance=new_stack();
    List* distances=new_queue();
    
    short_path_search(graph, destination_id, source_id, true, distances,
                      curr_distance, stack, visited, 0, 0);
    
    int x, shortest=queue_dequeue(distances), shortest_loc=0, count=1;
    //printf("%d",queue_size(distances));
    char arr[queue_size(distances)];
    if(queue_size(distances)<3){

    }
    while (!queue_is_empty(distances)) {
        x = queue_dequeue(distances);
        if (x < shortest) {
            shortest = x;
            shortest_loc = count;
        }
        count++;
    }
    
    free_stack(stack);
    free_stack(curr_distance);
    free_queue(distances);
}

// Stores distances of all simple paths in distances list if find_shortest
// is false. Otherwise, if find_shortest is true, iterates until the shortest
// path is reached and then prints the path and its distance.
void short_path_search(Graph* graph, int destination_id, int id, bool is_source, List* distances, List* curr_distance,
                       List* stack, bool visited[], int shortest_loc, int *count) {
    int total_distance=0;
    
    Edge *curredge=graph->vertices[id]->first_edge;
    
    if (is_source) {
        stack_push(stack, id);
        visited[id] = true;
    }
    
    // Iterate until the stack is empty
    while (!stack_is_empty(stack)) {
        id = curredge->v;
        
        // Vertex is unvisited
        if (!visited[id]) {
            visited[id] = true;
            stack_push(stack, id);
            stack_push(curr_distance, curredge->weight);
            
            // Destination is reached
            if (destination_id == id) {
                total_distance = distance_sum(curr_distance);
                stack_print(stack, graph,total_distance);
                stack_pop(stack);
                stack_pop(curr_distance);
                queue_enqueue(distances, total_distance);
            }
            // Destination is not reached
            else
                short_path_search(graph, destination_id, id, false, distances,
                                  curr_distance, stack, visited,
                                  shortest_loc, count);
            
            visited[id] = false;
        }
        
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            if (!stack_is_empty(curr_distance))
                stack_pop(curr_distance);
            break;
        }
    }
}

