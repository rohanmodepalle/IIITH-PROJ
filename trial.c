#include <trial.h>

// V vertices graph
struct Graph* InitGraph(int V){
    int i;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph-> array = (struct AdjList*)malloc(V*sizeof(struct AdjList));
    //init adj lists as empty by making head = NULL
    for(i = 0; i<V; ++i){
        graph->array[i].head = NULL;
    }
    return graph;
}

//create new adj list node
struct ListNode* NAL(int dest, int weight){
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//adding new edge to an undirected graph
void addEdge(struct Graph* graph,int src, int dest, int weight){
    //new node is added to the adjacency list of source.  The node is added at the beginning.
    struct ListNode* newNode = NAL(dest,weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    //NOTE: UNIDRECTED GRAPH SO VICE-VERSA IT
    newNode = NAL(src,weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

int main(){
    int vertices = 4;
    struct ListNode* h ;
    struct Graph* g = InitGraph(vertices);
    addEdge(g,1,2,10);
    addEdge(g,1,3,20);
    addEdge(g,2,4,30);
    addEdge(g,3,2,40);

    for (int i = 1; i <= vertices; i++) {
		printf("HeadNode[%d] >>  ", i) ;
		h  = g->array[i].head ;	
		while (h != NULL) {
			printf("%d (%d) " , h->dest, h->weight) ;
			h = h->next ;
		}
		printf("\n");
    }
}