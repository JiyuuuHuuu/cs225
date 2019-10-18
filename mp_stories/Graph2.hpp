#include <queue>
#include <algorithm>
#include <string>
#include <list>

using std::unordered_map;
using std::string;
using std::pair;
using std::queue;

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end)
{
  // TODO: Part 3
  unordered_map<string, pair<int, string>> DMap;
  unordered_map<string, bool> visited;
  queue<string> next;

  // initialize the visited map and DMap
  for (auto i : vertexMap)
  {
    visited.insert(pair<string, bool> (i.first, false));
    pair<int, string> temp(-1, "");
    DMap.insert(pair<string, pair<int, string>> (i.first, temp));
  }

  // initialize DMap
  DMap.at(start).first = 0;
  DMap.at(start).second = start;

  next.push(start);

  while(!next.empty())
  {
    string curr = next.front();
    next.pop();

    visited.at(curr) = true;
    for (auto i : adjList.at(curr))
    {
      string temp;
      if (i->get().source().key() == curr)
        temp = i->get().dest().key();
      else
        temp = i->get().source().key();

      if (!visited.at(temp))
        next.push(temp);

      int distance = DMap.at(curr).first + 1;
      if (DMap.at(temp).first < 0 || DMap.at(temp).first > distance)
      {
        DMap.at(temp).first = distance;
        DMap.at(temp).second = curr;
      }
    }
  }

  std::list<std::string> path;
  string curr = end;
  while (curr != start)
  {
    path.push_front(curr);
    curr = DMap.at(curr).second;
  }
  path.push_front(start);
  return path;
}
