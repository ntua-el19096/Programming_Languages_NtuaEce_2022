#include<iostream>
#include<cstring>
#include<string>
#include<math.h>
#include <list>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>

bool debug=0;

using namespace std;

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt){
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void printGraph(vector<pair<int,int> > adj[], int V){
    int v, w;
    for (int u = 1; u <= V; u++){
        cout << "Node " << u << " makes an edge with " << endl;
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++){
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight =" << w << endl;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]){
    if (argc!=2) { // Input management
        cout << "Incorrect Input" << endl;
        return -1;
    }
    //open the file
    ifstream input;
    input.open(argv[1]);
    int map[10000];
    int temp;
    int i=0;
    while(input>>temp){
        map[i] = temp;
        ++i;
    }
    input.close();

    int mapSize = i;

    //DEBUGING
    if(debug){
        cout << "This is the int map size: " << mapSize << endl;
        cout << "This is the content of the integer map" << endl;
        for(int i=0; i<mapSize; i++){
            cout << map[i] << " ";
        }
        cout << endl;
    }

    // get info from input file
    int towns = map[0];
    int roads = map[1];
    vector<pair<int, int> > adj[roads];
    for(int i=0; i<roads; i++){
        addEdge(adj, map[2+(3*i)], map[3+(3*i)], map[4+(3*i)]);
    }

    if (debug){
        cout << "The amount of roads is: " << roads << endl;
        printGraph(adj, towns);
    }

    //The amount of liters required can be found as the maximum from the minimal spanning tree of the map
    //We used some code from the internet for finding the minimal spanning tree (Prim)
    //https://www.codespeedy.com/prims-mst-for-adjacency-list-representation-in-cpp/
    
    vector<bool> visited(roads, false);
    // to keep a track if the node has been already visited or not. Initially all are false as no node is visited
    vector<int> connection(roads,-1);
    // to track the final connections that the MST has
    vector<int> value(roads, INT_MAX);
    // to store the minimum weight value possible for a node
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    //priority queue to extract minimum weights

    int max=0;
    que.push(make_pair(0, 1));  //push the weight required to insert the source node =0 and the node itself(i.e 1)
    value[1]=0;                 //minimum weight for source is 0
    while (!que.empty()) {
        int node = que.top().second;  //get the node
        visited[node] = true;         //as it is visited now change its value to true
        que.pop();
        for (auto neighbor : adj[node]) {   //we check for all its neighbors
            int weight = neighbor.second;        //get their weight
            int vertex = neighbor.first;         //get their index
            if (!visited[vertex] && value[vertex] > weight) {   //if the node is not visited and if its weight along this edge is less than the
                value[vertex] = weight;                         //previous edge associated with it, then only we consider it
                connection[vertex] = node;
                que.push(make_pair(value[vertex], vertex));     //we update the values and then push it in the queue to examine its neighbors
            }
        }
    }


    for (int i=1; i<=towns; i++){
        if (debug) cout << value[i] << endl;
        if(value[i]>max) max = value[i];
    }
    if(debug) cout << "==" << endl;
    cout << max << endl;
}
