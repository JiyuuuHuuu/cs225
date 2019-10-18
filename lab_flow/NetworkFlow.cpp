// valgrinded
/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

using std::vector;
using std::cout;
using std::endl;

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink)
{
  // YOUR CODE HERE

  // insert all the vertices
  for (auto temp_vertex : startingGraph.getVertices())
  {
    residual_.insertVertex(temp_vertex);
    flow_.insertVertex(temp_vertex);
  }

  // insert all the edges
  for (auto temp_edge : startingGraph.getEdges())
  {
    residual_.insertEdge(temp_edge.source, temp_edge.dest);
    residual_.insertEdge(temp_edge.dest, temp_edge.source); // set reversal edges
    residual_.setEdgeWeight(temp_edge.source, temp_edge.dest, startingGraph.getEdgeWeight(temp_edge.source, temp_edge.dest));
    residual_.setEdgeWeight(temp_edge.dest, temp_edge.source, 0);
    flow_.insertEdge(temp_edge.source, temp_edge.dest);
    flow_.setEdgeWeight(temp_edge.source, temp_edge.dest, 0);
  }

  maxFlow_ = 0;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const
{
  // YOUR CODE HERE
  int retVal = -1; // initialize to a impossible number
  for (unsigned i = 1; i < path.size(); i++)
  {
    int temp = residual_.getEdgeWeight(path[i - 1], path[i]);
    if (retVal < 0 || retVal > temp)
      retVal = temp;
  }
  return retVal;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow()
{
  // YOUR CODE HERE
  vector<Vertex> path;
  while (findAugmentingPath(source_, sink_, path))
  {
    int temp = pathCapacity(path);
    for (unsigned i = 1; i < path.size(); i++)
    {
      residual_.setEdgeWeight(path[i - 1], path[i], residual_.getEdgeWeight(path[i - 1], path[i]) - temp);
      residual_.setEdgeWeight(path[i], path[i - 1], residual_.getEdgeWeight(path[i], path[i - 1]) + temp);
      if (flow_.edgeExists(path[i - 1], path[i]))
        flow_.setEdgeWeight(path[i - 1], path[i], flow_.getEdgeWeight(path[i - 1], path[i]) + temp);
      else
        flow_.setEdgeWeight(path[i], path[i - 1], flow_.getEdgeWeight(path[i], path[i - 1]) - temp);
    }
  }
  for (Edge it : flow_.getEdges()) // update maxFlow_
  {
    if (it.source == source_)
    {
      maxFlow_ += flow_.getEdgeWeight(it.source, it.dest);
      // cout<<it.source<<"->"<<it.dest<<":"<<flow_.getEdgeWeight(it.source, it.dest)<<endl; // debug purpose
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
