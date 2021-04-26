#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graph.h"
//#include "personll.c"

int itr;

// create a new vertex with a specific label
Vertex* new_vertex(const char* label,int id) {
	assert(label);

	Vertex* vertex = malloc(sizeof (*vertex));
	assert(vertex);

	// make sure to copy the label across
	vertex->label = malloc((1 + strlen(label)) * sizeof (char));
	assert(vertex->label);
	strcpy(vertex->label, label);
    vertex->id = id;

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
        //free the edges
		while (vertex->first_edge) {
			Edge* edge = vertex->first_edge;
			vertex->first_edge = vertex->first_edge->next_edge;
			free(edge);
		}
        //free the values in the vertex
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
Path* total_paths(int n){
    Path* paths = (struct path*)malloc(n*sizeof(struct path));
    assert(paths);
    paths->size=0;

    return paths;
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
		graph->vertices[graph->n] = new_vertex(name,graph->n);
		graph->n++;
	} else {
		printf("adding new vertex to full graph\n");
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
		printf("adding edge between non-existant vertices,check pls\n");
	}
    
}


/**************************************************/
/**************************************************/
//                   TRAVERSE                     //
/**************************************************/
/**************************************************/

//used to set all values to false
void false_array(Graph* graph, bool array[]) {
    int i;
    for (i=0; i < graph->n; i++)
        array[i] = false;
}
//returns array with all paths and required values

void all_paths(Graph* graph,int source_id,int destination_id){
    // Creates zeroed visited array and initializes it
    itr =0;
    bool visited[graph->n];
    false_array(graph, visited);
    //global variable now has a stack to accept values
    // Create a stack
    List* stack=new_stack();
    List* curr_dist=new_stack();
    List* distances=new_queue();
    //we get total number of paths from this function
    value_get(graph, destination_id, source_id, true, stack,curr_dist,distances, visited);
    int m = queue_size(distances);
    Path *paths = total_paths(m);
    value_store(paths, graph, destination_id, source_id, true, stack,curr_dist,distances, visited);
    for(int i =0;i<m;i++){
        printf("%d ",(paths+i)->road_len);
        printf("\n");
        for(int j =0;j<(paths+i)->size;j++){
            printf("%d ",(paths+i)->arr[j]);
        }
    }
    free_stack(stack);
    free_stack(curr_dist);
    free_queue(distances);
}

// Finds a simple path from id to destination_id using depth first search
void value_get(Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]) {
    
    int total_dist=0;
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
            stack_push(curr_dist,curredge->weight);

            // Destination is reached
            if (destination_id == id) {
                total_dist=distance_sum(curr_dist);
                //stack_print(stack, graph, true, total_dist);
                stack_pop(stack);
                stack_pop(curr_dist);
                queue_enqueue(distances, total_dist);
            }
            // Destination is not reached
            else
                value_get(graph, destination_id, id, false, stack,curr_dist,distances,visited);
            
            visited[id] = false;
        }
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            if (!stack_is_empty(curr_dist))
                stack_pop(curr_dist);
            break;
        }
    }
}
void value_store(Path *paths, Graph* graph, int destination_id, int id, bool is_source,
              List* stack,List* curr_dist,List* distances,bool visited[]) {
    
    int total_dist=0;
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
            stack_push(curr_dist,curredge->weight);

            // Destination is reached
            if (destination_id == id) {
                total_dist=distance_sum(curr_dist);
                store(itr,paths,stack,graph,true,total_dist);
                //printf("%d %d ",total_dist,itr);
                stack_pop(stack);
                stack_pop(curr_dist);
                queue_enqueue(distances, total_dist);
                itr++;
            }
            // Destination is not reached
            else
                value_store(paths,graph, destination_id, id, false, stack,curr_dist,distances,visited);
            
            visited[id] = false;
        }
        curredge = curredge->next_edge;
        if (curredge == NULL) {
            stack_pop(stack);
            if (!stack_is_empty(curr_dist))
                stack_pop(curr_dist);
            break;
        }
    }
}

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

void store(int i,Path *paths,List* stack, Graph* graph,bool accept,int total_dist){
    
    int j=0;
    (paths+i)->road_len = total_dist;
    (paths+i)->size=stack_size(stack);
    (paths+i)->arr = malloc(sizeof(int)*stack_size(stack));
    int x;
    List* tempst=new_stack();
    while (!stack_is_empty(stack))
        stack_push(tempst, stack_pop(stack));
    while(stack_size(tempst)>0){
        x = stack_pop(tempst);
        (paths+i)->arr[j]=x;
        stack_push(stack,x);
        j++;
    }
    free_stack(tempst);
}

//no use for now

// Prints the path stored in the stack
// void stack_print(List* stack, Graph* graph, bool print_dist,
//                  int total_distance) {
//     int x;
//     List* tempstack=new_stack();
//     while (!stack_is_empty(stack))
//         stack_push(tempstack, stack_pop(stack));
    
//     while (stack_size(tempstack)>0) {
//         x = stack_pop(tempstack);
//         stack_push(stack, x);
//         printf("%d ", x);
//     }
//     free_stack(tempstack);
// }
// void stack_print(List* stack, Graph* graph, bool print_dist,
//                  int total_distance) {
//     int x;
//     List* tempstack=new_stack();
//     while (!stack_is_empty(stack))
//         stack_push(tempstack, stack_pop(stack));
    
//     while (stack_size(tempstack)>1) {
//         x = stack_pop(tempstack);
//         stack_push(stack, x);
//         printf("%s, ", graph->vertices[x]->label);
//     }
    
//     x = stack_pop(tempstack);
//     if (print_dist)
//         printf("%s (%dkm)\n", graph->vertices[x]->label, total_distance);
//     else
//         printf("%s\n", graph->vertices[x]->label);
//     stack_push(stack, x);
    
//     free_stack(tempstack);
// }


// int** tall_paths(Graph* graph, int source_id, int destination_id) {
    
//     // Create zeroed visited array
//     bool visited[graph->n];
//     false_array(graph, visited);
//     //global variable now has a stack to accept values
//     global=new_stack();
//     // Create a stack
//     List* stack=new_stack();
//     List* curr_dist=new_stack();
//     List* distances=new_queue();
//     value_get(graph, destination_id, source_id, true, stack,curr_dist,distances, visited);

//     int m = queue_size(distances);
//     int n = ((graph->maxn)+3);
//     row = m;
//     column = n;
//     int **arr;
//     arr = malloc(sizeof(int*) *m);
//     for(int i = 0;i<m;i++){
//         arr[i] = malloc(sizeof(int*) *n);
//     }
//     for(int i = 0;i<m;i++){
//         for(int j =0;j<n;j++){
//             arr[i][j] = -1;
//         }
//     }
//     //value_store(paths,graph, destination_id, source_id, true, stack,curr_dist,distances, visited);

//     //NOTE: GLOBAL STACK HAS FORMAT: (-2,dist,path)*m (m->paths)
    
//     //assert((stack_pop(global))==-2);
//     //To ensure that top of stack has element -2
//     int x =0,p=0,q=1;
//     List* tempstack=new_stack();
//     while (!stack_is_empty(global))
//         stack_push(tempstack, stack_pop(global));
//     while(stack_size(tempstack)>0){
//         if(x==-2){
//             p++;
//             q=1;
//         }
//         x = stack_pop(tempstack);
//         arr[p][q]=x;
//         q++;
//     }
//     float valarr[2][m];
//     float dangerval=0;
//     for(int i = 0;i<m;i++){
//         for(int j = 2;j<n;j++ ){
//             //dangerval = stations[arr[i][j]].positive+(stations[arr[i][j]].primary)/5+(stations[arr[i][j]].secondary)/10;
//         }
//     }
//     free_stack(tempstack);
//     free_stack(global);
//     free_stack(stack);
//     free_stack(curr_dist);
//     free_queue(distances);
//     return arr;
// }
