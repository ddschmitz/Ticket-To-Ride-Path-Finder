#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

// Number of VERTICES in the graph
#define VERTICES 36

// Structure to hold station names and id's
struct Stations
{
    int id;
    char name[50];
};

// Function Prototypes
void dijkstra(char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], int src);
int minDistance(int dist[], int sptSet[]);
void printPath(int parent[], int j, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES]);
void printSolution(int dist[], int parent[], int src, int dest, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES]);
void parseWeights(int graph[VERTICES][VERTICES]);
void parseColors(char *colors[VERTICES][VERTICES]);
void parseStations(struct Stations stations[VERTICES]);

int main()
{
    // Parse the weights .csv file into a 2d array
    int graph[VERTICES][VERTICES];
    parseWeights(graph);
    
    // Parse the colors .csv file into a 2d array of strings
    char* colors[VERTICES][VERTICES];
    parseColors(colors);

    // Parse the stations.csv file into an array of structures
    struct Stations stations[VERTICES];
    parseStations(stations);
    
    dijkstra(colors, graph, 1);
    
    //printf("\nnum = %d\n", graph[0][2]); // Down 0 and over 2.
 
    return 0;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using an adjacency matrix
void dijkstra(char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], int src)
{
    int count, v;
    int dist[VERTICES];   // The output array.  dist[i] will hold the shortest
                          // distance from src to i
 
    int sptSet[VERTICES]; // sptSet[i] will be true if vertex i is included in shortest
                          // path tree or shortest distance from src to i is finalized
                     
    int parent[VERTICES]; // Parent array to store shortest path tree
 
    for (v = 0; v < VERTICES; v++)
    {
        dist[v] = INT_MAX; // Initialize all disctances as infinite
        sptSet[v] = 0;     // Initialize all of stpSet[] as false 
        parent[v] = -1;    // Initialize all of parent[] as the source
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (count = 0; count < VERTICES-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        // u is always equal to src in first iteration
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = 1;
 
        // Update dist value of the adjacent vertices of the picked vertex
        for (v = 0; v < VERTICES; v++)
 
        // Update dist[v] only if is not in sptSet, there is an edge from 
        // u to v, and total weight of path from src to  v through u is 
        // smaller than current value of dist[v]
        if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && ((dist[u] + graph[u][v]) < dist[v]))
        {
            dist[v] = dist[u] + graph[u][v];
            parent[v] = u;
        }
    }
 
    printSolution(dist, parent, src, 28, colors, graph);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[])
{
    int min = INT_MAX; // Initialize min value
    int min_index;
    int v;
   
 
    for (v = 0; v < VERTICES; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
 
    return min_index;
}

void printPath(int parent[], int j, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES])
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
 
    printPath(parent, parent[j], colors, graph);
 
    printf("\t%d %s\n", graph[j][parent[j]], colors[j][parent[j]]);
}
 
void printSolution(int dist[], int parent[], int src, int dest, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES])
{
    int i;
    
    printf("Vertex   Distance from Source   Path\n");
    printf("The total distance from station %d to station %d is %d.\n", src, dest, dist[dest]);
    printf("\nThe colors you will need are:\n");
    //printPath(parent, dest, colors);

//    for (i = 0; i < VERTICES; i++)
//    {
//        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
//        //printPath(parent, i);
//    }
    printPath(parent, dest, colors, graph);
    
    return;
}

// Utility function to parse the .csv file containing the weights of the edges
void parseWeights(int graph[VERTICES][VERTICES])
{
    char buffer[1024];  
    char *record, *line;
    int i = 0;
    int j = 0;
    FILE *fstream = fopen("US_Weights.csv", "r");

    // Check for successful opening of file
    if (fstream == NULL)
    {
        printf("\n Opening US_Weights.csv failed.\n");
        exit(1);
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
    return;
}

// Utility function to parse the .csv file containing the colors of the edges
void parseColors(char* colors[VERTICES][VERTICES])
{
    char buffer[1024];    
    char *record, *line;
    int i = 0;
    int j = 0;
    FILE *fstream = fopen("US_Colors.csv", "r");

    // Check for successful opening of file
    if (fstream == NULL)
    {
        printf("\n Opening US_Colors.csv failed.\n");
        exit(2);
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
    return;
}

// Utility function to parse the .csv file containing the station names and id's
void parseStations(struct Stations stations[VERTICES])
{
    char buffer[1024];    
    char *record, *line;
    int i = 0;
    FILE *fstream = fopen("US_Station_Names.csv", "r");

    // Check for successful opening of file
    if (fstream == NULL)
    {
        printf("\n Opening US_Station_Names.csv failed.\n");
        exit(3);
    }
    
    // Get a single line from the file and parse it into tokens
    // and place the contents in a 2d array of strings.
    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)
    {
        // Get the first token which is the id
        record = strtok(line, ",");
        stations[i].id = atoi(record);
        
        // Get the second token which is the name
        record = strtok(NULL, ",");
        strcpy(stations[i].name, record);
        
        i++;
    }
    fclose(fstream);
    return;
}