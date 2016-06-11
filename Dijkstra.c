#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

// Number of vertices in the graph
#define Vertices 9

// Function Prototypes
void dijkstra(char *colors[Vertices][Vertices], int graph[Vertices][Vertices], int src);
int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j, char *colors[Vertices][Vertices], int graph[Vertices][Vertices]);
void printSolution(int dist[], int n, int parent[], int src, int dest, char *colors[Vertices][Vertices], int graph[Vertices][Vertices]);

//const char* parseColors()
//{
//  const char *colors[Vertices][Vertices];
//
//
//
//  return colors;
//}

struct Stations
{
    int id;
    char name[50];
};

int main()
{
    int graph[Vertices][Vertices];

    //   \/\/  Make Function Somehow \/\/
    char buffer[1024];  
    char *record, *line;
    int i = 0;
    int j = 0;
    FILE *fstream = fopen("Weights.dat", "r");

    // Check for successful opening of file
    if (fstream == NULL)
    {
        printf("\n file opening failed\n");
        return -1;
    }
        
    // Get a single line from the file and parse it into tokens
    // and place the contents in a 2d array of strings.
    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)
    {
        //  Get the first token
        record = strtok(line, ",");

        while(record != NULL)
        {
            graph[i][j] = atoi(record);
            //printf("%d|", graph[i][j]);       
            // Walk through other tokens using NULL somehow?
            record = strtok(NULL, ",");
            j++;
        }
        //printf("\n");
        j = 0;
        i++;
    }
    fclose(fstream);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    char *colors[Vertices][Vertices];

    //   \/\/  Make Function Somehow \/\/
    //char buffer[1024];    
    //char *record, *line;
    i = 0;
    j = 0;
    fstream = fopen("Colors.dat", "r");

    // Check for successful opening of file
    if (fstream == NULL)
    {
        printf("\n file opening failed\n");
        return -1;
    }
    
    // Get a single line from the file and parse it into tokens
    // and place the contents in a 2d array of strings.
    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)
    {
        //  Get the first token
        record = strtok(line, ",");

        while(record != NULL)
        {
            colors[i][j] = strdup(record);
            //printf("%s|", colors[i][j]);      
            // Walk through other tokens using NULL somehow?
            record = strtok(NULL, ",");
            j++;
        }
        j = 0;
        i++;
    }
    fclose(fstream);
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    dijkstra(colors, graph, 0);
    
    //printf("\nnum = %d\n", graph[0][2]); // Down 0 and over 2.
 
    return 0;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using an adjacency matrix
void dijkstra(char *colors[Vertices][Vertices], int graph[Vertices][Vertices], int src)
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

void printPath(int parent[], int j, char *colors[Vertices][Vertices], int graph[Vertices][Vertices])
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
 
    printPath(parent, parent[j], colors, graph);
 
    printf("Colors are %d %s\n", graph[j][parent[j]], colors[j][parent[j]]);
}
 
void printSolution(int dist[], int n, int parent[], int src, int dest, char *colors[Vertices][Vertices], int graph[Vertices][Vertices])
{
    int i;
    
    printf("Vertex   Distance from Source   Path\n");
    printf("The total distance from station %d to station %d is %d", src, dest, dist[dest]);
    //printPath(parent, dest, colors);

//    for (i = 0; i < Vertices; i++)
//    {
//        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
//        //printPath(parent, i);
//    }
    printf("\n\n");
    printPath(parent, dest, colors, graph);
    
    return;
}

 
