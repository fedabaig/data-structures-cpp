/* Program name: graph.h
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Define a graph class that reads IP-based routes from a file,
 *          stores IPs and adjacency, and can find a path between two IPs.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "unorderedLinkedList.h"
#include "linkedQueue.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>   // for IP list
#include <regex>    // for regular expressions

class graphType
{
public:
    bool isEmpty() const;

    // Read routes.txt, using regex to separate IP list vs adjacency list
    void createGraph(std::string filename);

    void clearGraph();
    std::string printGraph() const;
    graphType(int size = 0);
    ~graphType();

    std::string depthFirstTraversal();
    std::string dftAtVertex(int vertex);
    std::string breadthFirstTraversal();

    // Find path between two IP addresses.
   
    bool findPath(const std::string &startIp,
                  const std::string &endIp,
                  std::string &pathOut);

private:
    int maxSize;
    int gSize;
    unorderedLinkedList<int> *graph;

    // Store IPs; index in this vector matches vertex index in adjacency list
    std::vector<std::string> ipAddresses;

    void dft(int v, bool visited[], std::string &output);

    int getIndexForIp(const std::string &ip) const;
};

#endif
