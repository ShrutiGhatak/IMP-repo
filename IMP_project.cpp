#include <stdio.h>
#include <stdlib.h>
// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    //int degree;
    struct AdjListNode* next;
};
// A structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head; // pointer to head node of list
	int V_no,degree,state,visited,random;
};
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph {
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(
            sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    //newNode->degree=0;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i <V; ++i)
	{
		graph->array[i].head = NULL;
		graph->array[i].degree = 0;
		graph->array[i].V_no = 0;
		graph->array[i].state = 0;
		graph->array[i].visited = 0;
		graph->array[i].random = 0;
	}
  return graph;
}
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    graph->array[src].V_no=src;
    graph->array[dest].V_no=dest;
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
//A utility function to sort the vertices.
 void sort(struct Graph* graph)
 {
 	int v,i;
        struct AdjListNode* f;
        //struct AdjListNode* m;
        int t;
	for(i=0;i<graph->V;i++)
	{
		for(v=0;v<graph->V;v++)
		{
			//t=graph->array[v].head;
			//f=graph->array[v+1].head;
			if(graph->array[v].degree<graph->array[v+1].degree)
			{
				t=graph->array[v].V_no;
				graph->array[v].V_no = graph->array[v+1].V_no;
				graph->array[v+1].V_no = t;
				
				t=graph->array[v].degree;
				graph->array[v].degree = graph->array[v+1].degree;
				graph->array[v+1].degree = t;
				
				f=graph->array[v].head;
				graph->array[v].head = graph->array[v+1].head;
				graph->array[v+1].head = f;
			}
		}
	}
 }
// A utility function to calculate degree of each vertices.
void degcal(struct Graph* graph) {
    int v,d;
    //struct AdjListNode* temp;
    for (v = 0; v < graph->V; v++) {
    	//graph->array[v].V_no=v;
    	//temp=graph->array[v].head;
        struct AdjListNode* p = graph->array[v].head;
        //printf("\n Adjacency list of vertex %d\n head ", v);
        d=0;
        while (p) {
            //printf("-> %d", p->dest);
            p = p->next;
	    	d++;
        }
        graph->array[v].degree = d;
	//printf("\nThe degree of the vertex %d is:%d \n",v,temp->degree);
        //printf("\n");
    }
}
//A utility function to print the graph.
void printgraph(struct Graph* graph) {
    int v;
    //struct AdjListNode* temp;
    for (v = 0; v < graph->V; v++) {
        struct AdjListNode* p = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", graph->array[v].V_no);
        while (p) {
            printf("-> %d", p->dest);
            p = p->next;
        }
	printf("\nThe degree of the vertex %d is:%d \n",graph->array[v].V_no,graph->array[v].degree);
        printf("\n");
    }
}
void printSeedset(int*,int);
//A utility function to find seed set.
int* findSeedset(struct Graph* graph)
{
	int u,i,j,k=5,size=0,c,v;
	float w=0.5,th;
	static int S[5]={0};
	int *n_array;
	for(u=0;u<graph->V;u++)
	{
		if(size<k)
		{
			if(graph->array[u].state==0)
			{
					
				S[size]=graph->array[u].V_no;
				graph->array[u].state=1;
				graph->array[u].visited=1;
				size++;
		    }
			else
		    	continue;
		struct AdjListNode* p = graph->array[u].head;
		c=0;
		while(p!=NULL)
		{
				p=p->next;
				c++;
		}
		n_array = (int *)calloc(sizeof(int),c);
		struct AdjListNode* q = graph->array[u].head;
		i=0;
		while(q!=NULL)
		{
		 n_array[i] = q->dest;
		 q = q->next;
		 i++;
	    }
	    th = graph->array[u].degree*w;
	    i=0;
	while(i<c)
	{
	for(v=0;v<graph->V;v++)
	{
		if(graph->array[v].V_no == n_array[i])
		{
			if(graph->array[v].degree>=th && graph->array[v].state==0)
			{
			if(size<k)
			{
				S[size]=n_array[i];
				graph->array[v].state=1;
				graph->array[v].visited=1;
				size++;
			}
			else
			break;
		    }  
		}	
	}
	if(size>=k)
	    break;
	i++;
	}
	}
	//else
	//printSeedset(S);
	}
	printSeedset(S,5);
	return S;
}
void printSeedset(int S[],int k)
{
   int i;
   printf("\nThe seed set is:\n");
   for(i=0;i<k;i++)
   {
   printf("%d  ",S[i]);
   }
}
void influention(struct Graph* graph,int *S)
{
	int k,i,v,c,count=0;
	int *n_array,front=0,rear=4;
	float P=0.5,number;
	while(front!=-1)
	{
		for(i=front;i<=rear;i++)
		  printf("\n%d  ",S[i]);
		k=S[front];
		printf("\n%d",k);
		//count++;
		if(front >= rear)
		  front=rear=-1;
		else
		  front++;
		for(v=0;v<graph->V;v++)
		{
			if(graph->array[v].V_no == k)
			{
				printf("\n\nThe vertex %d is already visited and trying to influence its neighbours",graph->array[v].V_no);
				//count++;
				struct AdjListNode* p = graph->array[v].head;
				c=0;
	            while(p!=NULL)
	            {
	            	p=p->next;
	            	c++;
				}
				n_array = (int *)calloc(sizeof(int),c);
				struct AdjListNode* q = graph->array[v].head;
				i=0;
				while(q!=NULL)
				{
					n_array[i] = q->dest;
					q = q->next;
					i++;
				}
				i=0;
				while(i<c)
				{
					for(v=0;v<graph->V;v++)
					{
						if(graph->array[v].V_no == n_array[i] && graph->array[v].visited == 0)
						{
						  number = (float)rand()/RAND_MAX;
						  graph->array[v].random = 1;
						  printf("\n\nThe random no. of the vertex %d is:%f\n",graph->array[v].V_no,number);
						if(number < P)
						{
							printf("\nThe vertex %d is influenced",graph->array[v].V_no);
							if(rear == -1)
							 front=rear=0;
							else
							 rear++;
							S[rear] = graph->array[v].V_no;
							graph->array[v].visited = 1;
							graph->array[v].random = 2;
							//count++;
						}
						else
						{
						  printf("\nThe vertex %d is not influenced",graph->array[v].V_no);
						  graph->array[v].visited = 1;
						}
					    }
						else if(graph->array[v].V_no == n_array[i])
						{
							if(graph->array[v].visited == 1 && graph->array[v].state == 1)
							 printf("\n\nThe vertex %d is already influenced as it is seed",graph->array[v].V_no);
							else if(graph->array[v].visited == 1 && graph->array[v].random == 1)
							{
								printf("\n\nThe vertex %d is already visited but not influenced,again try to get influenced",graph->array[v].V_no);
								number = (float)rand()/RAND_MAX;
								printf("\n\nThe random no. of the vertex %d is:%f\n",graph->array[v].V_no,number);
						        if(number < P)
						        {
							      printf("\nThe vertex %d is influenced now",graph->array[v].V_no);
							      if(rear == -1)
							       front=rear=0;
							      else
							       rear++;
							     S[rear] = graph->array[v].V_no;
							     graph->array[v].random = 2;
							      //count++;
						        }
						        else
						         printf("\nThe vertex %d is again not influenced",graph->array[v].V_no);
							}
							else if(graph->array[v].visited == 1 && graph->array[v].random == 2)
							  printf("\n\nThe vertex %d is already influenced",graph->array[v].V_no);
						}
					
					}
					i++;
				}
				break;
			}
		}
		count++;
	}
	printf("\n\n\nTotal no. of influenced nodes is:%d",count);
}
int main() {
    // create the graph given in above figure
    int V = 115;
    int *r;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 7);
    addEdge(graph, 2, 8);
    addEdge(graph, 7, 8);
    addEdge(graph, 7, 10);
    addEdge(graph, 7, 108);
    addEdge(graph, 90, 108);
    addEdge(graph, 100, 108);
    addEdge(graph, 98, 100);
    addEdge(graph, 96, 100);
    addEdge(graph, 64, 100);
    addEdge(graph, 99, 100);
    addEdge(graph, 91, 100);
    addEdge(graph, 3, 100);
    addEdge(graph, 3, 75);
    addEdge(graph, 3, 83);
    addEdge(graph, 1, 90);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 5, 89);
    addEdge(graph, 4, 103);
    addEdge(graph, 102, 103);
    addEdge(graph, 93, 101);
    addEdge(graph, 101, 103);
    addEdge(graph, 103, 106);
    addEdge(graph, 103, 107);
    addEdge(graph, 103, 105);
    addEdge(graph, 104, 105);
    addEdge(graph, 65, 105);
    addEdge(graph, 30, 83);
    addEdge(graph, 24, 30);
    addEdge(graph, 24, 32);
    addEdge(graph, 23, 32);
    addEdge(graph, 32, 88);
    addEdge(graph, 32, 86);
    addEdge(graph, 29, 85);
    addEdge(graph, 29, 32);
    addEdge(graph, 32, 87);
    addEdge(graph, 53, 87);
    addEdge(graph, 55, 87);
    addEdge(graph, 55, 56);
    addEdge(graph, 52, 55);
    addEdge(graph, 52, 54);
    addEdge(graph, 47, 52);
    addEdge(graph, 52, 58);
    addEdge(graph, 58, 59);
    addEdge(graph, 34, 52);
    addEdge(graph, 34, 57);
    addEdge(graph, 57, 60);
    addEdge(graph, 60, 62);
    addEdge(graph, 61, 63);
    addEdge(graph, 61, 84);
    addEdge(graph, 63, 109);
    addEdge(graph, 41, 108);
    addEdge(graph, 41, 79);
    addEdge(graph, 41, 92);
    addEdge(graph, 51, 79);
    addEdge(graph, 79, 81);
    addEdge(graph, 27, 80);
    addEdge(graph, 74, 80);
    addEdge(graph, 45, 80);
    addEdge(graph, 45, 82);
    addEdge(graph, 76, 82);
    addEdge(graph, 82, 97);
    addEdge(graph, 28, 97);
    addEdge(graph, 28, 96);
    addEdge(graph, 28, 78);
    addEdge(graph, 81, 77);
    addEdge(graph, 81, 112);
    addEdge(graph, 112, 113);
    addEdge(graph, 11, 113);
    addEdge(graph, 111, 113);
    addEdge(graph, 111, 114);
    addEdge(graph, 94, 114);
    addEdge(graph, 33, 37);
    addEdge(graph, 25, 37);
    addEdge(graph, 9, 37);
    addEdge(graph, 17, 37);
    addEdge(graph, 17, 22);
    addEdge(graph, 17, 36);
    addEdge(graph, 35, 36);
    addEdge(graph, 50, 97);
    addEdge(graph, 49, 50);
    addEdge(graph, 44, 49);
    addEdge(graph, 39, 50);
    addEdge(graph, 39, 46);
    addEdge(graph, 43, 46);
    addEdge(graph, 42, 46);
    addEdge(graph, 26, 42);
    addEdge(graph, 26, 31);
    addEdge(graph, 26, 50);
    addEdge(graph, 31, 40);
    addEdge(graph, 15, 17);
    addEdge(graph, 14, 15);
    addEdge(graph, 14, 111);
    addEdge(graph, 14, 21);
    addEdge(graph, 19, 21);
    addEdge(graph, 14, 20);
    addEdge(graph, 14, 18);
    addEdge(graph, 15, 110);
    addEdge(graph, 12, 15);
    addEdge(graph, 12, 16);
    addEdge(graph, 13, 16);
    addEdge(graph, 9, 38);
    addEdge(graph, 38, 69);
    addEdge(graph, 69, 72);
    addEdge(graph, 67, 70);
    addEdge(graph, 67, 71);
    addEdge(graph, 68, 71);
    addEdge(graph, 68, 69);
    addEdge(graph, 69, 73);
    addEdge(graph, 66, 69);
    // print the adjacency list representation of the above graph
    //printgraph(graph);
    degcal(graph);
    //printgraph(graph);
	sort(graph);
    printgraph(graph);
    r=findSeedset(graph);
    influention(graph,r);
    return 0;
}




