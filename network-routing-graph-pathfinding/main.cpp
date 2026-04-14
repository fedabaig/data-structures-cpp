/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 12/08/2025
 * Purpose: Read routes from routes.txt into a graph, then prompt the user
 *          for a starting and goal IP address and print a path between them.
 */

#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    graphType g;

    // Build the graph from routes.txt
    try
    {
        g.createGraph("routes.txt");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating graph: " << e.what() << std::endl;
        return 1;
    }

    std::string startIp;
    std::string goalIp;

    std::cout << "Enter the starting ip:\n";
    std::getline(std::cin, startIp);

    std::cout << "\nEnter the goal ip:\n";
    std::getline(std::cin, goalIp);

    std::cout << "\nFinding path from " << startIp
              << " to " << goalIp << std::endl;

    std::string path;
    if (g.findPath(startIp, goalIp, path))
    {
        std::cout << path << std::endl;
    }
    else
    {
        std::cout << "No path found from " << startIp
                  << " to " << goalIp << std::endl;
    }

    return 0;
}
