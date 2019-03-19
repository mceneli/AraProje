/*
    Analysis of Algorithms - Semester Project
    GPS System with Breadth-First Search

    Student:
    Name: Osman Araz
    No: 16011020
    Delivery Date: 05.01.19
*/

/*
    ATTENTION: "graph.h", "queue.h" and "fundamentals.h" files are necessary to execute this program.
    These files should be in the same directory of this program.
*/

#include "graph.h"

Vertex **readGraph(int *N, int *M, int *src, int *dst);
void printBanner();
void printGraph(Vertex **V, int N, int M, int src, int dst);
void printPaths(Path **paths, int src, int dst, int numOfPaths);
void printMostFriendlyVertex(Vertex **V, int N);
void printLongestPath(Vertex **V, int N);
int main()
{
    // N: # of vertexes, M: # of edges, src: source vertex, dst: destination vertex:
    int N, M, src, dst;
    Vertex **V = readGraph(&N, &M, &src, &dst); // reading graph as adjacency list

    // getting all paths from the source vertex to the destination vertex:
    int numOfPaths;
    Path **paths = findPaths(V, N, src, dst, &numOfPaths);

    sortPaths(paths, numOfPaths); // sorting the paths according to their costs

    printBanner();
    printGraph(V, N, M, src, dst);
    printf("\n\t#########################\n\n");
    printPaths(paths, src, dst, numOfPaths);
    printf("\n\t#########################\n\n");
    printMostFriendlyVertex(V, N);
    printf("\n\t#########################\n\n");
    printLongestPath(V, N);
    printf("\n\t#########################\n\n");

    freePaths(paths, numOfPaths);
    paths = NULL;

    return 0;
}

/*
    A function which reads adjacency list of a graph from a given file.
    @param *N: pointer of the number of vertexes
    @param *M: pointer of the number of edges
    @param *src: pointer of the source vertex index
    @param *dst: pointer of the destination vertex index
    @return V: array of adjacency lists of the graph
*/
Vertex **readGraph(int *N, int *M, int *src, int *dst)
{
    char fileName[50];

    printBanner();
    printf("\tEnter the input file path: ");
    scanf("%s", fileName);

    FILE *fi = fopen(fileName, "r");

    if (!fi)
        fileAccessProblem();

    fscanf(fi, "%d %d", N, M);  // getting the numbers of vertices and edges
    fscanf(fi, "%d %d", src, dst); // getting the beginning and ending vertices

    Vertex **V = (Vertex **)malloc((*N)*sizeof(Vertex *));
    initializeVertexes(V, *N);

    if (!V)
        memoryAllocationProblem();

    int i;

    // constructing the adjacency list:
    for (i = 0; i < *M; ++i)
    {
        int vertex, adjacent, weight;
        fscanf(fi, "%d %d %d", &vertex, &adjacent, &weight);
        addAdjacency(V[vertex], createNode(adjacent, weight));
    }

    fclose(fi);

    return V;
}

/*
    A function which prints adjacency list of the graph.
    @param **V: array of adjacency lists of the graph
    @param N: number of vertexes
    @param M: number of edges
    @param src: source vertex index
    @param dst: destination vertex index
*/
void printGraph(Vertex **V, int N, int M, int src, int dst)
{
    printf("\tThe graph consists of %d vertexes and %d edges.\n", N, M);
    printf("\n\t#########################\n\n");
    printf("\tVertex adjacencies:\n\n");

    int i;

    for (i = 0; i < N; ++i)
    {
        Node *temp = V[i]->head;

        while (temp)
        {
            printf("\t%d -> %d   (cost: %d)\n", i, temp->name, temp->weight);
            temp = temp->next;
        }
    }

    printf("\n\t#########################\n\n");
    printf("\tThe beginning vertex is vertex #%d.\n", src);
    printf("\tThe ending vertex is vertex #%d.\n", dst);
}

/*
    A function which prints the vertex which has the maximum number of adjacents.
    @param **V: array of adjacency lists of the graph
    @param N: number of vertexes
*/
void printMostFriendlyVertex(Vertex **V, int N)
{
    int i, maxAdjacentIndex = 0;

    for (i = 1; i < N; ++i)
        if (V[i]->numOfAdjacents > V[maxAdjacentIndex]->numOfAdjacents)
            maxAdjacentIndex = i;

    printf("\tVertex #%d has the maximum number of adjacents (%d adjacents).\n", maxAdjacentIndex, V[maxAdjacentIndex]->numOfAdjacents);
}

/*
    A function which prints all possible paths from a vertex to another.
    @param **paths: array of all possible paths from a vertex to another
    @param src: source vertex index
    @param dst: destination vertex index
    @param numOfPaths: the number of paths
*/
void printPath(Path *path);
void printPaths(Path **paths, int src, int dst, int numOfPaths)
{
    int i;

    if (numOfPaths == 0)
        printf("\tThere is no path between vertex #%d to vertex #%d.\n", src, dst);
    else
    {
        printf("\tShortest path from vertex #%d to vertex #%d:\n\n", src, dst);
        printPath(paths[0]);
        printf("\n\t#########################\n\n");

        if (numOfPaths > 1)
        {
            printf("\tAlternative paths from vertex #%d to vertex #%d (sorted according to their costs):\n\n", src, dst);

            for (i = 1; i < numOfPaths; ++i)
                printPath(paths[i]);
        }
        else
            printf("\tThere is no alternative path between vertex #%d to vertex #%d.\n", src, dst);
    }
}

/*
    A function which prints a specific path from a vertex to another.
*/
void printPath(Path *path)
{
    int i;

    printf("\t");

    // printing the vertexes of the path:
    for (i = 0; i < path->numOfVertices-1; ++i)
        printf("%d -> ", path->vertices[i]);

    printf("%d   (total cost: ", path->vertices[path->numOfVertices-1]);

    // printing the distances of the path:
    for (i = 0; i < path->numOfVertices-2; ++i)
        printf("%d + ", path->distances[i]);

    printf("%d = %d)\n", path->distances[path->numOfVertices-2], path->cost);
}

/*
    A function which prints the furthest vertex tuple of the graph.
    @param **V: array of adjacency lists of the graph
    @param N: number of vertexes
*/
void printLongestPath(Vertex **V, int N)
{
    Path *longestPath = findLongestPathOfGraph(V, N);

    if (longestPath->numOfVertices == 0)
        printf("\tThere is no path in the map.\n");
    else
    {
        printf("\tLongest path in the map is from vertex #%d to vertex #%d:\n\n", longestPath->vertices[0], longestPath->vertices[longestPath->numOfVertices-1]);
        printPath(longestPath);
    }   
}

/*
    A function which prints the banner of the program.
*/
void printBanner()
{
    clearScreen();
    printf("\n\t##########################################\n");
    printf("\t################# BFS-GPS ################\n");
    printf("\t##########################################\n\n");
}