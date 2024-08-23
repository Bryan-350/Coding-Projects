/*  Name: Bryan Flores
    Description: Traversing a graph to find the path from one vertex to another. 
                 This project demonstrates knowledge of CS concepts such as, 
                 object-oriented programming, recursion,  and depth first search
    Input: text file of vertices and edge weights
    Output:ouputs whether the path from two points exists and then outputs the path itself
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

/*
    struct that holds the next node and the edge weight
*/
struct vertexType
{ 
    string destination;
    int length;
};

/*
    Depth First Search function
    takes in an adjacency List, a map of previous nodes,
    a map that stores previously visited nodes and the starting and end nodes
    It will recursively go through the list and find a path from start to end
    If found it will return true, otherwise it will return false                                                                                                            
*/
bool dfs(unordered_map<string, list<vertexType>>& adjList,
         unordered_map<string, string>& predecessor,
         unordered_map<string, bool>& visited, string current, string end, int stamina)
{
    //base case - if the current node reached the end with
    if (current == end && stamina >= 1) {return true;}

    //sets the node to visited
    visited[current] = true;

    for (auto& neighbor:adjList[current])
    {
        string next = neighbor.destination;
        int nextDistance = neighbor.length;

        //if the next node hasn't been visited and stamina >= 1 then we can continue
        if (!visited[next] && stamina - nextDistance >= 1)
        {
            //sets current as the next node's predecessor
            predecessor[next] = current;

            //if this recursive call returns true, then return true
            if (dfs(adjList, predecessor, visited, next, end, stamina - nextDistance))
            {
                return true;
            }
        }
    }

    //resets current to not visited in case we need to back track
    visited[current] = false;

    //returns false because no path was found
    return false;
}

/*
    The main function reads in a file via linux redirection
    Additionally, it adds the verticies into an adjacency list
    And then runs the dfs function to determine if a path exists
    Finally it outputs the path if it exists
*/
int main()
{
    unordered_map<string, list<vertexType>> adjList;
    unordered_map<string, string> predecessor;
    unordered_map<string, bool> visited;

    string startNode, endNode, line;
    int startingStamina;

    cin >> startNode >> endNode >> startingStamina;

    //sets the new line character to the first edge
    getline(cin, line); 
    getline(cin, line);

    //counts the number of times getline(cin, line) is empty
    int counter = 0;    

    while (getline(cin, line))
    {   
        //if the counter = 2 then we are at the end of the file
        if (counter == 2)
        {
            break;
        }

        //if line is empty, inc counter and move to next iteration
        if (line.empty())
        {
            counter++;
            continue;
        }

        //resets counter if line was not empty
        counter = 0;
        
        string vertex1, vertex2;
        int length;

        istringstream iss(line);

        //read in the vertexes and edge weight from string stream
        iss >> vertex1 >> vertex2 >> length;

        //push the values back into the list
        adjList[vertex1].push_back({vertex2, length});
    }

    //if dfs returns true, this outputs the path
    if (dfs(adjList, predecessor, visited, startNode, endNode, startingStamina))
    {
        cout << "Time to cool off!" << endl;
        cout << "Path: ";

        vector<string> path;
        string current = endNode;

        while (current != startNode)
        {
            //push the current node to the back of vector
            path.push_back(current);

            //current is equal to it's predecessor.
            current = predecessor[current];
        }

        //inserts the first node to the list
        path.push_back(startNode);

        //traverses the path vector in reverse order
        for (int i = path.size() - 1; i >= 0; i--)
        {   
            //prints out the path size. 
            cout << path[i] << " ";
        }
    }

    else
        cout << "This is going to be a long summer..." << endl;
}
