/* Program name: graph.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Implement graphType for routing between IPs using an
 *          adjacency list and regular expressions to parse the input file.
 */

#include "graph.h"

bool graphType::isEmpty() const
{
    return gSize == 0;
}

void graphType::createGraph(std::string filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }

    // Reset any previous graph
    clearGraph();
    ipAddresses.clear();

    std::string line;
    std::vector<std::string> adjacencyLines;
    bool readingAdjacency = false;

    // Simple IPv4 regex: 4 groups of 1–3 digits separated by dots
    std::regex ipRegex(R"(^\s*(\d{1,3}\.){3}\d{1,3}\s*$)");

    while (std::getline(in, line))
    {
        // Skip empty / whitespace-only lines
        if (line.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        if (!readingAdjacency && std::regex_match(line, ipRegex))
        {
            // This line is an IP address
            ipAddresses.push_back(line);
        }
        else
        {
            // Once we hit a non-IP line, we treat the rest as adjacency
            readingAdjacency = true;
            adjacencyLines.push_back(line);
        }
    }

    in.close();

    // Number of vertices = number of IPs
    gSize = static_cast<int>(ipAddresses.size());
    if (gSize == 0)
    {
        return; // nothing to do
    }

    // Resize graph array if needed
    if (gSize > maxSize)
    {
        delete[] graph;
        maxSize = gSize;
        graph = new unorderedLinkedList<int>[maxSize];
    }

    // Make sure adjacency lists are empty
    for (int i = 0; i < gSize; ++i)
    {
        graph[i].destroyList();
    }

    // Parse adjacency lines: format like "0 1 8 5 -999"
    for (const auto &adjLine : adjacencyLines)
    {
        std::istringstream iss(adjLine);
        int vertex;
        if (!(iss >> vertex))
            continue;

        int neighbor;
        while (iss >> neighbor && neighbor != -999)
        {
            if (vertex >= 0 && vertex < gSize &&
                neighbor >= 0 && neighbor < gSize)
            {
                graph[vertex].insert(neighbor);
            }
        }
    }
}

void graphType::clearGraph()
{
    for (int i = 0; i < gSize; i++)
    {
        graph[i].destroyList();
    }
    gSize = 0;
}

std::string graphType::printGraph() const
{
    std::ostringstream out;
    for (int i = 0; i < gSize; i++)
    {
        out << i << " ";
        graph[i].print(out);
        out << std::endl;
    }
    out << std::endl;
    return out.str();
}

graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    graph = new unorderedLinkedList<int>[size > 0 ? size : 1]; // avoid new[0]
}

graphType::~graphType()
{
    clearGraph();
    delete[] graph;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited = new bool[gSize];
    std::string out = "";

    for (int i = 0; i < gSize; i++)
        visited[i] = false;

    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
            dft(i, visited, out);
    }

    delete[] visited;
    return out;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;

    std::string out = "";
    dft(vertex, visited, out);

    delete[] visited;
    return out;
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;

    std::string out = "";
    linkedListIterator<int> graphIt;

    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out = out + " " + std::to_string(i) + " ";

            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out = out + " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }

    delete[] visited;
    return out;
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";

    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[w])
            dft(w, visited, output);
    }
}

// Helper: map IP string to index (or -1 if not found)
int graphType::getIndexForIp(const std::string &ip) const
{
    for (int i = 0; i < static_cast<int>(ipAddresses.size()); ++i)
    {
        if (ipAddresses[i] == ip)
            return i;
    }
    return -1;
}

// Find a path from startIp to endIp using BFS on the adjacency list
bool graphType::findPath(const std::string &startIp,
                         const std::string &endIp,
                         std::string &pathOut)
{
    pathOut.clear();

    int startIdx = getIndexForIp(startIp);
    int endIdx = getIndexForIp(endIp);

    if (startIdx == -1 || endIdx == -1)
    {
        return false; // one or both IPs not in the graph
    }

    if (startIdx == endIdx)
    {
        pathOut = startIp;
        return true;
    }

    // BFS to find shortest path in unweighted graph
    std::vector<bool> visited(gSize, false);
    std::vector<int> pred(gSize, -1);

    linkedQueue<int> q;
    q.enqueue(startIdx);
    visited[startIdx] = true;

    bool found = false;

    while (!q.isEmptyQueue() && !found)
    {
        int u = q.dequeue();

        linkedListIterator<int> it;
        for (it = graph[u].begin(); it != graph[u].end(); ++it)
        {
            int w = *it;
            if (!visited[w])
            {
                visited[w] = true;
                pred[w] = u;
                q.enqueue(w);

                if (w == endIdx)
                {
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        return false; // no path from start to end
    }

    // Reconstruct path from endIdx back to startIdx
    std::vector<int> pathIndices;
    int crawl = endIdx;
    pathIndices.push_back(crawl);

    while (pred[crawl] != -1)
    {
        crawl = pred[crawl];
        pathIndices.push_back(crawl);
    }

    // Path is currently end, start, reverse it
    std::reverse(pathIndices.begin(), pathIndices.end());

    // Build string "ip1-->ip2-->ip3"
    std::ostringstream out;
    for (size_t i = 0; i < pathIndices.size(); ++i)
    {
        out << ipAddresses[pathIndices[i]];
        if (i + 1 < pathIndices.size())
            out << "-->";
    }

    pathOut = out.str();
    return true;
}
