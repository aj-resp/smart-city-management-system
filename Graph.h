#pragma once
#include <iostream>
using namespace std;

/*
Node which store the next node to from which it is connected and also the weight of the connection and all
*/
struct AdjNode
{
    int vertex;
    int weight;
    AdjNode* next;

    AdjNode(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};

/*
As we have multiple type of stores so we are using it to retrieve the type of the stops from it
*/
struct NodeInfo
{
    int originalIndex;
    char type[20];
};

/*
Simple graph array of pointers basically it store the nodes / vertices in the first col means col wise in first
row and the other nodes means all the edges it is connected too in the row for those
*/
class Graph
{
private:
    AdjNode** adjList;
    int vertices;
    int maxVertices;

    // Helper function for string comparison
    static bool strMatchHelper(const char* s1, const char* s2)
    {
        if (!s1 || !s2)
            return false;
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0')
        {
            if (s1[i] != s2[i])
                return false;
            i++;
        }
        return (s1[i] == '\0' && s2[i] == '\0');
    }

public:
    Graph() : adjList(nullptr), vertices(0), maxVertices(0) {}


    // COPY CONSTRUCTOR
    Graph(const Graph& other)
    {
        vertices = other.vertices;
        maxVertices = other.maxVertices;

        if (maxVertices > 0)
        {
            adjList = new AdjNode * [maxVertices];
            for (int i = 0; i < maxVertices; i++)
            {
                adjList[i] = nullptr;
            }
            for (int i = 0; i < vertices; i++)
            {
                AdjNode* curr = other.adjList[i];
                AdjNode* lastNode = nullptr;

                while (curr != nullptr) {

                    AdjNode* newNode = new AdjNode(curr->vertex, curr->weight);

                    if (adjList[i] == nullptr)
                    {
                        adjList[i] = newNode;
                    }
                    else
                    {
                        lastNode->next = newNode;
                    }
                    lastNode = newNode;
                    curr = curr->next;
                }
            }
        }
        else {
            adjList = nullptr;
        }
    }

    // ASSIGNMENT OPERATOR 
    Graph& operator=(const Graph& other)
    {
        if (this == &other)
            return *this;

        if (adjList != nullptr)
        {
            for (int i = 0; i < maxVertices; i++)
            {
                AdjNode* curr = adjList[i];
                while (curr != nullptr)
                {
                    AdjNode* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
            }
            delete[] adjList;
        }

        // Copy new data
        vertices = other.vertices;
        maxVertices = other.maxVertices;

        if (maxVertices > 0)
        {
            adjList = new AdjNode * [maxVertices];
            for (int i = 0; i < maxVertices; i++)
            {
                adjList[i] = nullptr;
            }

            for (int i = 0; i < vertices; i++)
            {
                AdjNode* curr = other.adjList[i];
                AdjNode* lastNode = nullptr;

                while (curr != nullptr)
                {
                    AdjNode* newNode = new AdjNode(curr->vertex, curr->weight);

                    if (adjList[i] == nullptr)
                    {
                        adjList[i] = newNode;
                    }
                    else
                    {
                        lastNode->next = newNode;
                    }
                    lastNode = newNode;
                    curr = curr->next;
                }
            }
        }
        else
        {
            adjList = nullptr;
        }

        return *this;
    }


    void initialize(int v)
    {
        maxVertices = v;
        vertices = v;
        adjList = new AdjNode * [v];
        for (int i = 0; i < v; i++)
        {
            adjList[i] = nullptr;
        }
    }

    /*
    Basically taking the stop numbers in the parameters so that we can add its connection there and also
    add the weight between them and weight is basically calculated as the distance between both of the
    nodes coordinates as it was said in the comments we can use any of the approach
    */
    void addEdge(int u, int v, int weight)
    {
        if (u >= maxVertices || v >= maxVertices || u < 0 || v < 0)
        {
            cout << "WARNING: Invalid edge (" << u << " -> " << v << ")\n";
            return;
        }

        if (weight <= 0)
        {
            cout << "WARNING: Invalid weight " << weight << " for edge (" << u << " -> " << v << "), setting to 1\n";
            weight = 1;
        }

        /*
         Adding weights and edge between the nodes by first creating the nodes basically adding the
         node at heas of the adjlist means adding one more neighbour u is connected to
        */
        AdjNode* newNode = new AdjNode(v, weight);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        //Adding edge from v to u
        newNode = new AdjNode(u, weight);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    int getVertices() const
    {
        return vertices;
    }

    AdjNode* getAdjList(int v) const
    {
        if (v < 0 || v >= maxVertices)
            return nullptr;
        return adjList[v];
    }


    void dijkstra(int start, int dist[], int parent[])
    {
        // Basic validation
        if (start < 0 || start >= vertices)
            return;
        if (vertices <= 0)
            return;
        if (adjList == nullptr)
            return;

        //Basically assigning the large value to all distances as we do in dijkstra and all and recording visiting too
        const int INF = 1000000000;
        bool visited[500] = { false };

        // Initializing
        for (int i = 0; i < vertices; i++)
        {
            dist[i] = INF;
            parent[i] = -1;
        }

        //Now Setting start distance as 0 so now we start doing dijkstra to find path and all
        dist[start] = 0;

        for (int count = 0; count < vertices; count++)
        {
            int minDist = INF;
            int u = -1;

            // Finding minimum distance
            for (int v = 0; v < vertices; v++)
            {
                if (!visited[v] && dist[v] < minDist)
                {
                    minDist = dist[v];
                    u = v;
                }
            }

            if (u == -1 || minDist == INF)
                break;

            visited[u] = true;

            // Check if node is valid
            if (u < 0 || u >= vertices) continue;

            AdjNode* curr = adjList[u];

            // Simple null check
            if (curr == nullptr) continue;

            // Safety counter to prevent infinite loops
            int safetyCount = 0;
            const int MAX_EDGES = 1000;

            /*
            It basically travel through all of the vertices distances we have calculated and find the
            parent orignal with shortest distance and also check infinite loop as it was giving us errors
            previously
            */
            while (curr != nullptr && safetyCount < MAX_EDGES)
            {
                safetyCount++;

                int v = curr->vertex;

                // Check if neighbor is valid
                if (v >= 0 && v < vertices && !visited[v])
                {
                    int newDist = dist[u] + curr->weight;

                    // Simple overflow check
                    if (newDist > dist[u] && newDist < dist[v])
                    {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }

                curr = curr->next;
            }
        }
    }

    /*
     Basically we are extracting the subgraph from here means that first we initialise each node with -1
     means in array and then what we do is in the first we loop through all the loops and then we extract
     the node type we need extract means where in the index the stop matches the type we need we write there
     the index of the stop which is of correct type while the other remains -1 So basic concept is once we
     create the sub graph we need to copy its neighbors means vertices too so what we do is we again loop
     through both neighbbor and fulltsub list and check if neighbor exist and is not -1 means it is also
     in sub graph so also adding it too
    */
    Graph extractSubgraph(const char* nodeType, const struct NodeInfo* registry, int totalNodes,
        int fullToSub[],
        int subToFull[])
    {
        Graph subgraph;
        int subgraphNodes = 0;

        // Initialize mappings as -1
        for (int i = 0; i < totalNodes; i++)
        {
            fullToSub[i] = -1;
        }

        //Here checking which nodes to include means which are of correct type
        for (int i = 0; i < totalNodes; i++)
        {
            if (strMatchHelper(registry[i].type, nodeType))
            {
                //Basically storing the number of subgraph node it is in full graph and in sub to full adding it as of correct type
                fullToSub[i] = subgraphNodes;
                subToFull[subgraphNodes] = i;
                subgraphNodes++;
            }
        }

        if (subgraphNodes == 0)
        {
            subgraph.initialize(1); // Initialising empty subgraph
            return subgraph;
        }

        subgraph.initialize(subgraphNodes);

        // Coppying edges too if also in the sub graph
        for (int i = 0; i < totalNodes; i++)
        {
            if (fullToSub[i] != -1)
            {
                int subI = fullToSub[i];
                AdjNode* curr = adjList[i];

                while (curr)
                {
                    int neighbor = curr->vertex;
                    if (fullToSub[neighbor] != -1)
                    {
                        int subNeighbor = fullToSub[neighbor];
                        // Add edge in subgraph 
                        if (subI < subNeighbor)
                        { // Avoid duplicate edges
                            AdjNode* newNode = new AdjNode(subNeighbor, curr->weight);
                            newNode->next = subgraph.adjList[subI];
                            subgraph.adjList[subI] = newNode;

                            //Same forming edges and all
                            newNode = new AdjNode(subI, curr->weight);
                            newNode->next = subgraph.adjList[subNeighbor];
                            subgraph.adjList[subNeighbor] = newNode;
                        }
                    }
                    curr = curr->next;
                }
            }
        }

        return subgraph;
    }

    /*
    It is same sub graph extraction as this is for extracting simple sub graph just it handles
    multiple types as we also need to extract path between hospital and school and all
    */
    Graph extractSubgraphWithBridges(const char* primaryType, const char* bridgeType, const struct NodeInfo* registry,
        int totalNodes, int fullToSub[], int subToFull[])
    {
        Graph subgraph;
        int subgraphNodes = 0;

        // Initialize
        for (int i = 0; i < totalNodes; i++) {
            fullToSub[i] = -1;
        }

        //Including all the primary type nodes 
        for (int i = 0; i < totalNodes; i++)
        {
            if (strMatchHelper(registry[i].type, primaryType))
            {
                fullToSub[i] = subgraphNodes;
                subToFull[subgraphNodes] = i;
                subgraphNodes++;
            }
        }

        //Including the briges means the second type too if and only if are connected to the primary type
        for (int i = 0; i < totalNodes; i++)
        {
            if (strMatchHelper(registry[i].type, bridgeType))
            {
                // Check if connected to any primary node means checking there adj list and finding connection available or not
                AdjNode* curr = adjList[i];
                bool hasConnection = false;

                while (curr)
                {
                    if (fullToSub[curr->vertex] != -1)
                    {
                        hasConnection = true;
                        break;
                    }
                    curr = curr->next;
                }

                if (hasConnection)
                {
                    fullToSub[i] = subgraphNodes;
                    subToFull[subgraphNodes] = i;
                    subgraphNodes++;
                }
            }
        }

        if (subgraphNodes == 0)
        {
            subgraph.initialize(1);
            return subgraph;
        }

        subgraph.initialize(subgraphNodes);

        //Now copying the edges if also included in the graph
        for (int i = 0; i < totalNodes; i++)
        {
            //Only including the nodes
            if (fullToSub[i] != -1)
            {
                int subI = fullToSub[i];
                AdjNode* curr = adjList[i];

                while (curr)
                {
                    int neighbor = curr->vertex;
                    if (fullToSub[neighbor] != -1) // Including the neighbor if it is connected
                    {
                        int subNeighbor = fullToSub[neighbor];
                        if (subI < subNeighbor)
                        {
                            AdjNode* newNode = new AdjNode(subNeighbor, curr->weight);
                            newNode->next = subgraph.adjList[subI];
                            subgraph.adjList[subI] = newNode;

                            newNode = new AdjNode(subI, curr->weight);
                            newNode->next = subgraph.adjList[subNeighbor];
                            subgraph.adjList[subNeighbor] = newNode;
                        }
                    }
                    curr = curr->next;
                }
            }
        }

        return subgraph;
    }
};


