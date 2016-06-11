#include <stdio.h>
#include <limits.h>
#include <string.h>
 
// Number of vertices in the graph
#define Vertices 9

// Function Prototypes
void dijkstra(const char *colors[Vertices][Vertices], int graph[Vertices][Vertices], int src);
int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j, const char *colors[Vertices][Vertices], int graph[Vertices][Vertices]);
int printSolution(int dist[], int n, int parent[], int src, int dest, const char *colors[Vertices][Vertices], int graph[Vertices][Vertices]);

struct Stations
{
	int id;
	char name[50];
	char color[10];
	//char color2[10];
};

int main()
{
	//struct Stations Station0, Station1, Station2, Station3, Station4, Station5, Station6, Station7, Station8;


	//Station0.id = 0;
	//strcpy(Station0.name, "Station0");
	

	//printf("Train Station #%d is %s\n",Station0.id, Station0.name);








   /* Let us create the example graph discussed above */
    int graph[Vertices][Vertices] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                     {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                     {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                     {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                     {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                     {0, 0, 4, 0, 10, 0, 2, 0, 0},
                                     {0, 0, 0, 14, 0, 2, 0, 1, 6},
                                     {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                     {0, 0, 2, 0, 0, 0, 6, 7, 0}
                                    };
 
    const char *colors[Vertices][Vertices] = {{"", "Orange", "", "", "", "", "", "Red", ""},
                                              {"Orange", "", "Blue", "", "", "", "", "Black", ""},
                                              {"", "Blue", "", "Pink", "", "Any", "", "", "Any"},
                                              {"", "", "Pink", "", "Green", "Red", "", "", ""},
                                              {"", "", "", "Green", "", "Blue", "", "", ""},
                                              {"", "", "Any", "", "BLue", "", "Orange", "", ""},
                                              {"", "", "", "Red", "", "Orange", "", "Green", "Black"},
                                              {"Red", "Black", "", "", "", "", "Green", "", "Yellow"},
                                              {"", "", "Any", "", "", "", "Black", "Yellow", ""}
                                             };
    printf("Color from 0 to 1 is %s\n", colors[0][1]);
	dijkstra(colors, graph, 0);
    
    //printf("\nnum = %d\n", graph[0][2]); // Down 0 and over 2.
 
    return 0;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using an adjacency matrix
void dijkstra(const char *colors[Vertices][Vertices], int graph[Vertices][Vertices], int src)
{
    int count, v;
    int dist[Vertices];   // The output array.  dist[i] will hold the shortest
                          // distance from src to i
 
    int sptSet[Vertices]; // sptSet[i] will be true if vertex i is included in shortest
                          // path tree or shortest distance from src to i is finalized
                     
    int parent[Vertices]; // Parent array to store shortest path tree
 
    for (v = 0; v < Vertices; v++)
    {
        dist[v] = INT_MAX; // Initialize all disctances as INFINITE
        sptSet[v] = 0;     // Initialize all of stpSet[] as false 
        parent[v] = -1;    // Initialize all of parent[] as the source
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (count = 0; count < Vertices-1; count++)
    {
		// Pick the minimum distance vertex from the set of vertices not yet processed
        // u is always equal to src in first iteration
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = 1;
 
        // Update dist value of the adjacent vertices of the picked vertex
        for (v = 0; v < Vertices; v++)
 
        // Update dist[v] only if is not in sptSet, there is an edge from 
        // u to v, and total weight of path from src to  v through u is 
        // smaller than current value of dist[v]
        if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && ((dist[u] + graph[u][v]) < dist[v]))
        {
            dist[v] = dist[u] + graph[u][v];
            parent[v] = u;
		}
    }
 
    printSolution(dist, Vertices, parent, src, 4, colors, graph);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[])
{
    int min = INT_MAX; // Initialize min value
    int min_index;
    int v;
   
 
    for (v = 0; v < Vertices; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
 
    return min_index;
}

void printPath(int parent[], int j, const char *colors[Vertices][Vertices], int graph[Vertices][Vertices])
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
 
    printPath(parent, parent[j], colors, graph);
 
    printf("Colors are %d %s\n", graph[j][parent[j]], colors[j][parent[j]]);
}
 
int printSolution(int dist[], int n, int parent[], int src, int dest, const char *colors[Vertices][Vertices], int graph[Vertices][Vertices])
{
    int i;
    
    printf("Vertex   Distance from Source   Path\n");
    //printf("\n%d -> %d \t\t %d\t\t%d ", src, dest, dist[dest], src);
    //printPath(parent, dest, colors);

    for (i = 0; i < Vertices; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        //printPath(parent, i);
    }
    printf("\n\n");
	printPath(parent, dest, colors, graph);
}
 
