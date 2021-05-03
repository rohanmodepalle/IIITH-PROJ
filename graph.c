#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graph.h"
#include "personll.c"

//GLOBAL VARIABLE ITERATORS TO REDUCE PARAMETERS IN FUNCTIONS
int itr;
int itr1, itr2;

// Create a new vertex with a specific name and id
//id essentially is 0,1,2,..n based on order of input
//the name is just to add uniqueness and avoid numerical confusion
Vertex* new_vertex(const char* label,int id) {
	assert(label);

	Vertex* vertex = malloc(sizeof (*vertex));
    //assert the existence of vertex else there is no point in the code progressing
	assert(vertex);

	// make sure to copy the name across
	vertex->label = malloc((1 + strlen(label)) * sizeof (char));
	assert(vertex->label);

	strcpy(vertex->label, label);
    vertex->id = id;

	vertex->first_edge = NULL;

	return vertex;
}
// create a new w-weighted edge from vertex id u to vertex id v
//the weight is road_length here
Edge* new_edge(int u, int v, int w) {
	Edge* edge = malloc(sizeof (*edge));
	assert(edge);

	edge->u = u;
	edge->v = v;
	edge->weight = w;
	edge->next_edge = NULL;

	return edge;
}
// destroy a vertex, including its name and all of its weighted-edges
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
// stores all paths generated and road lengths from source to destination
// every time a new path is called, new memory is allocated and size is initialized to zero 
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

//false_array creates a boolean array which checks if vertex is visited or not
//we need this function for DFS 
void false_array(Graph* graph, bool array[]) {
    int i;
    for (i=0; i < graph->n; i++)
        array[i] = false;
}

//IMPLEMENTATION OF PART 2 OF THE TASK GIVEN
//it prints and 3 or less than 3 paths sorted in order of their safety value and then road length
void all_paths(Graph* graph,int source_id,int destination_id){
    
    itr =0; //this is the global variable we declared, we init to 0 
    
    //now we declare boolean array to check and note which all vertices are visited 
    //it returns TRUE for those vertices iterated in the graph
    bool visited[graph->n];
    false_array(graph, visited);

    List* stack=new_stack(); //stack which stores the vertices visited from source to destination 
    List* curr_dist=new_stack(); //stack which stores all the total distances for all paths generated 
    List* distances=new_queue(); //queue to store the order of distances in suitable time complexity and access it

    //we get total number of paths from this function, this is needed in order to initialise the data type- 'struct paths'
    value_get(graph, destination_id, source_id, true, stack,curr_dist,distances, visited);
    // used to count all the paths from source to destination
    int m = queue_size(distances);
    //based on total number of paths found above, we make list of paths and INIT them
    Path *paths = total_paths(m);
    //this stores all the paths, the road lengths in a random arbitary order and returns it for futher processing
    value_store(paths, graph, destination_id, source_id, true, stack,curr_dist,distances, visited);
    //now the only thing missing is safety values
    //using data from personll.c and personll.h we access the data of people and stations
    for(int i = 0;i<m;i++){
        (paths+i)->safety_val = safety_value((paths+i)->size,(paths+i)->arr); //uses formula provided to find safety value
    }//the function safety_value is explained below

    //SORTER- THIS SORTS PATHS BASED ON-
    //1.SAFETY VALUE   2.ROAD LENGTH
    sorter(paths,m);

    //THIS PRINTS ALL PATHS AFTER PERFORMING ALL THE DESIRED OPERATIONS
    for(int i =0;i<m;i++){
        printf("%d ",(paths+i)->road_len);
        printf("%f ",(paths+i)->safety_val);
        for(int j =0;j<(paths+i)->size;j++){
            printf("%d ",(paths+i)->arr[j]);
        }
        printf("\n");
    }

    //free the stacks and queues after using them
    free_stack(stack);
    free_stack(curr_dist);
    free_queue(distances);
}

//This function uses BUBBLE SORT to sort based on safety value sand then road length
void sorter(Path *paths,int m){
    int outer, inner;
    Path temp; //we create temporary path of size 1 to enable swapping of structs based on priority order
    for(outer=0;outer<m;outer++)
    {
        for(inner=outer+1;inner<m;inner++)
        
            if(paths[outer].safety_val>paths[inner].safety_val)
            {
            temp=paths[outer];
            paths[outer]=paths[inner];
            paths[inner]=temp;
            }
            else if(paths[outer].safety_val==paths[inner].safety_val){
                if(paths[outer].road_len>paths[inner].road_len){ //safety values are equal, then equate road lengths
                    temp=paths[outer];
                    paths[outer]=paths[inner];
                    paths[inner]=temp;
                }
            }
        }
}

// Finds a simple path from id to destination_id using depth first search
// This stores the total number of paths so that we can store all values in the next function
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

// THIS STORES ROAD LENGTHS AND ALL VERTICES GENERATED WHILE ITERATING THROUGH THE EDGES
// hence this is need to insert values into struct paths
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


//This function is used to calculate total distance generated by the edges involved in reaching from source to destination
int distance_sum(List* curr_distance) {
    int x, sum=0;
    List* tempstack=new_stack(); //we use this due to the property of FILO or LIFO which reverses the values in opposite order
    while (!stack_is_empty(curr_distance)) {
        x = stack_pop(curr_distance);
        sum += x;
        stack_push(tempstack, x);
    }
    while (!stack_is_empty(tempstack))
        stack_push(curr_distance, stack_pop(tempstack));
    
    return sum; // total path length is returned
    
    free_stack(tempstack); //free the temporary value
}

//THIS FUNTCION STORES ROAD LENGTHS AND ALL VERTICES INVOLVED IN EVERY SINGLE PATH 
//THE DETAILS AND VALUES ARE STORED IN 'STRUCT PATHS'
void store(int i,Path *paths,List* stack, Graph* graph,bool accept,int total_dist){
    
    int j=0;
    (paths+i)->road_len = total_dist; //total road length
    (paths+i)->size=stack_size(stack); // size of array i.e. number of vertices needed to reach destination
    (paths+i)->arr = malloc(sizeof(int)*stack_size(stack)); // mallocs memory based on above number
    int x;

    List* tempst=new_stack(); // because of LIFO/FILO 
    
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

//THIS  CALCULATES SAFETY VALUE FROM DANGER VALUE   
float safety_value(int n,int arr[n]){
    float danger_val = 0;
    for(int i=0;i<n;i++){
        danger_val += (stations[arr[i]].positive)+(stations[arr[i]].primary/5)+(stations[arr[i]].secondary/10);
    }//we use the formula provided to calculate the danger value from stations structure since it contains required parameters
    //we generate afety values in range {0,1}
    if(danger_val==0){
        return 1; //no danger value means full safety :)
    }
    else{
        return (1/danger_val); //inversely proportional
    }
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

/////////////////////////////////////////////////////////////////
// add a new vertex with label 'name' to a graph
// void graph_add_vertex(Graph* graph, const char* name) {
// 	if (graph->n < graph->maxn) {
// 		graph->vertices[graph->n] = new_vertex(name,graph->n);
// 		graph->n++;
// 	} else {
// 		printf("adding new vertex to full graph\n");
// 	}
// }
////////////////////////////////////////////////////////////////