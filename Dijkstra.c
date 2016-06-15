#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define VERTICES 36       // Number of VERTICES in the graph
#define SOURCE 1          // Source station id
#define DESTINATION 28    // Destination station id

// Structure to hold station names and id's
struct Stations
{
    int id;
    char name[50];
};

// Function Prototypes
void dijkstra(char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], int source, int dist[VERTICES], int shortest[VERTICES], int path[VERTICES]);
int minDistance(int dist[], int shortest[]);
void printPath(int path[], int j, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], struct Stations stations[VERTICES]);
void printSolution(int dist[], int path[], int source, int destination, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], struct Stations stations[VERTICES]);
void parseWeights(int graph[VERTICES][VERTICES]);
void parseColors(char *colors[VERTICES][VERTICES]);
void parseStations(struct Stations stations[VERTICES]);
void clearScreen();

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
    
    // dist[i] will hold the shortest distance from the source vertice to i'th vertice
    int dist[VERTICES];   
    
    // shortest[i] will be true if the i'th vertice is found to be the current shortest distance to the source vertice
    int shortest[VERTICES]; 
    
    // Array to store vertices that used to print the shortest path 
    int path[VERTICES]; 
    
    int i, choice, stop, source, destination;
    do
    {
        clearScreen();
        printf("                         TICKET TO RIDE PATH FINDER\n\n\n\n");
        printf("      ====        ________                ___________\n");
        printf("  _D _|  |_______/        \\__I_I_____===__|_________|\n");
        printf("   |(_)---  |   H\\________/ |   |        =|___ ___|      _________________ \n");
        printf("   /     |  |   H  |  |     |   |         ||_| |_||     _|                \\_____A\n");
        printf("  |      |  |   H  |__--------------------| [___] |   =|                        |\n");
        printf("  | ________|___H__/__|_____/[][]~\\_______|       |   -|                        |\n");
        printf("  |/ |   |-----------I_____I [][] []  D   |=======|____|________________________|_\n");
        printf("__/ =| o |=-~~\\  /~~\\  /~~\\  /~~\\ ____Y___________|__|__________________________|_\n");
        printf(" |/-=|___||    ||    ||    ||    |_____/~\\___/          |_D__D__D_|  |_D__D__D_|\n");
        printf("  \\_/      \\__/  \\__/  \\__/  \\__/      \\_/               \\_/   \\_/    \\_/   \\_/\n\n\n\n");
        printf("1) Print stations\n\n");
        printf("2) Find route between stations\n\n");
        printf("3) Exit\n\n\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                clearScreen();
                printf("Station ID's and name's are separated like this [ ID - NAME ]\n\n");
                for (i = 0; i < VERTICES; i += 2) // Print two stations per line
                {
                    printf("      %2d - %-25s  %2d - %s\n", stations[i].id, stations[i].name, stations[i+1].id, stations[i+1].name);
                }
                printf("\n\nPress ENTER to continue.");
                scanf("%c", &stop);
                scanf("%c", &stop);
                break;
            case 2:
                clearScreen();
                
                printf("Station ID's and name's are separated like this [ ID - NAME ]\n\n");
                for (i = 0; i < VERTICES; i += 2) // Print two stations per line
                {
                    printf("      %2d - %-25s  %2d - %s\n", stations[i].id, stations[i].name, stations[i+1].id, stations[i+1].name);
                }
                
                printf("\n\nEnter the source station's ID: ");
                scanf("%d", &source);
                printf("Enter the destination station's ID: ");
                scanf("%d", &destination);
                
                dijkstra(colors, graph, source, dist, shortest, path);
                printSolution(dist, path, source, destination, colors, graph, stations);
                
                printf("Press ENTER to continue.");
                scanf("%c", &stop);
                scanf("%c", &stop);
                break;
            case 3:
            
                break;
        }
    } while (choice != 3);
    
    //printf("\nnum = %d\n", graph[0][2]); // Down 0 and over 2.
 
    return 0;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using an adjacency matrix
void dijkstra(char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], int source, int dist[VERTICES], int shortest[VERTICES], int path[VERTICES])
{
    int count, v;
 
    for (v = 0; v < VERTICES; v++)
    {
        dist[v] = INT_MAX; // Initialize all disctances as infinite
        shortest[v] = 0;   // Initialize all of stpSet[] as false 
        path[v] = -1;      // Initialize all of path[] as the source
    }
 
    // Distance of source vertex from itself is always 0
    dist[source] = 0;
 
    // Find shortest path for all vertices
    for (count = 0; count < VERTICES-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        // u is always equal to source in first iteration
        int u = minDistance(dist, shortest);
 
        // Mark the picked vertex as processed
        shortest[u] = 1;
 
        // Update dist value of the adjacent vertices of the picked vertex
        for (v = 0; v < VERTICES; v++)
 
        // Update dist[v] only if is not in shortest, there is an edge from 
        // u to v, and total weight of path from source to  v through u is 
        // smaller than current value of dist[v]
        if (!shortest[v] && graph[u][v] && dist[u] != INT_MAX && ((dist[u] + graph[u][v]) < dist[v]))
        {
            dist[v] = dist[u] + graph[u][v];
            path[v] = u;
        }
    }
}

// A utility function to find the vertex with the smallest distance value from
// the set of vertices not yet included in shortest[]
int minDistance(int dist[], int shortest[])
{
    int min = INT_MAX; // Initialize min value
    int min_index;
    int v;
    
    for (v = 0; v < VERTICES; v++)
        if (shortest[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
 
    return min_index;
}

// Recursive function that prints off the path taken
void printPath(int path[], int j, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], struct Stations stations[VERTICES])
{
    // Base Case : If j is source
    if (path[j] == -1)
        return;
 
    printPath(path, path[j], colors, graph, stations);
 
    printf("%s to %s using %d %s\n", stations[path[j]].name, stations[j].name, graph[j][path[j]], colors[j][path[j]]);
}
 
// Starter function for printing the path taken
void printSolution(int dist[], int path[], int source, int destination, char* colors[VERTICES][VERTICES], int graph[VERTICES][VERTICES], struct Stations stations[VERTICES])
{
    printf("\n\n\n        -- TOTAL DISTANCE --\n");
    printf("From %s(%d) to %s(%d) is %d.\n\n\n", stations[source].name, stations[source].id, stations[destination].name, stations[destination].id, dist[destination]);
    printf("        -- COLORS NEEDED --\n");
    
    printPath(path, destination, colors, graph, stations);
    
    printf("\n");
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
    int j;
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
        
        // Remove new line and carriage return from station name
        for (j = 0; j < sizeof(stations[0].name); j++)
        {
            if (stations[i].name[j] == 10)
                stations[i].name[j] = 0;
            if (stations[i].name[j] == 13)
                stations[i].name[j] = 0;
        }
        
        i++;
    }
    fclose(fstream);
    return;
}

// Utility function to clear the screen
void clearScreen()
{
    int i;
    for (i = 0; i < 100; i++)
        printf("\n");
    return;
}