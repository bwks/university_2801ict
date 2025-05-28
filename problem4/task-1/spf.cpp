#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

struct Node {
  int toll;
  unordered_map<string, int> roads;
};

struct Route {
  vector<string> path;
  int distance;
  int toll;
};

// Helper function for path reconstruction
vector<string> path_reconstructor(const unordered_map<string, string>& previous, const string& start, const string& end) {
  vector<string> path;
  if (previous.find(end) == previous.end()) return path;

  string current = end;
  while (current != start) {
    path.push_back(current);
    current = previous.at(current);
  }
  path.push_back(start);
  reverse(path.begin(), path.end());
  return path;
}

// Remove sub-optimal (dominated) routes
vector<Route> filter_routes(const vector<Route>& routes) {
  vector<Route> filtered;
  for (const auto& route : routes) {
    bool dominated = false;
    for (const auto& other : routes) {
      if (&route == &other) continue;
      if (other.distance < route.distance && other.toll < route.toll) {
        dominated = true;
        break;
      }
    }
    if (!dominated) {
      filtered.push_back(route);
    }
  }
  return filtered;
}

Route ShortestPath(const string& start, const string& end, const unordered_map<string, Node>& graph) {
  unordered_map<string, string> previous;
  unordered_map<string, int> distance;
  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

  distance[start] = 0;
  pq.push({ 0, start });

  while (!pq.empty()) {
    auto [current_distance, u] = pq.top();
    pq.pop();

    if (u == end) break;
    if (current_distance > distance[u]) continue;

    for (const auto& [v, edge_distance] : graph.at(u).roads) {
      int new_distance = distance[u] + edge_distance;
      if (!distance.count(v) || new_distance < distance[v]) {
        distance[v] = new_distance;
        previous[v] = u;
        pq.push({ new_distance, v });
      }
    }
  }

  vector<string> path = path_reconstructor(previous, start, end);
  int total_distance = distance.count(end) ? distance[end] : INT_MAX;
  int total_toll = 0;
  if (!path.empty()) {
    for (size_t i = 1; i < path.size(); ++i) {
      total_toll += graph.at(path[i]).toll;
    }
  }
  return { path, total_distance, total_toll };
}

Route LeastToll(const string& start, const string& end, const unordered_map<string, Node>& graph) {
  unordered_map<string, int> toll_cost;
  unordered_map<string, string> previous;
  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

  toll_cost[start] = 0;
  pq.push({ 0, start });

  while (!pq.empty()) {
    auto [current_toll, u] = pq.top();
    pq.pop();

    if (u == end) break;
    if (current_toll > toll_cost[u]) continue;

    for (const auto& [v, edge_distance] : graph.at(u).roads) {
      int new_toll = current_toll + graph.at(v).toll;
      if (!toll_cost.count(v) || new_toll < toll_cost[v]) {
        toll_cost[v] = new_toll;
        previous[v] = u;
        pq.push({ new_toll, v });
      }
    }
  }

  vector<string> path = path_reconstructor(previous, start, end);
  int total_toll = toll_cost.count(end) ? toll_cost[end] : INT_MAX;
  int total_distance = 0;
  if (!path.empty()) {
    string current = start;
    for (size_t i = 1; i < path.size(); ++i) {
      string next = path[i];
      total_distance += graph.at(current).roads.at(next);
      current = next;
    }
  }
  return { path, total_distance, total_toll };
}

Route BalancedRoute(const string& start, const string& end, const unordered_map<string, Node>& graph) {
  unordered_map<string, int> cost;
  unordered_map<string, string> previous;
  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

  cost[start] = 0;
  pq.push({ 0, start });

  while (!pq.empty()) {
    auto [current_cost, u] = pq.top();
    pq.pop();

    if (u == end) break;
    if (current_cost > cost[u]) continue;

    for (const auto& [v, edge_distance] : graph.at(u).roads) {
      int new_cost = current_cost + edge_distance + graph.at(v).toll;
      if (!cost.count(v) || new_cost < cost[v]) {
        cost[v] = new_cost;
        previous[v] = u;
        pq.push({ new_cost, v });
      }
    }
  }

  vector<string> path = path_reconstructor(previous, start, end);
  int total_distance = 0;
  int total_toll = 0;
  if (!path.empty()) {
    string current = path[0];
    for (size_t i = 1; i < path.size(); ++i) {
      string next = path[i];
      total_distance += graph.at(current).roads.at(next);
      total_toll += graph.at(next).toll;
      current = next;
    }
  }
  return { path, total_distance, total_toll };
}

int main() {
  unordered_map<string, Node> graph = {
      {"A", {0, {{"B", 4}, {"C", 8}}}},
      {"B", {2, {{"A", 4}, {"C", 2}, {"D", 5}}}},
      {"C", {3, {{"A", 8}, {"B", 2}, {"D", 3}, {"E", 6}}}},
      {"D", {2, {{"B", 5}, {"C", 3}, {"E", 2}}}},
      {"E", {5, {{"C", 6}, {"D", 2}}}},
  };

  string start = "A";
  string end = "E";

  Route shortest_path = ShortestPath(start, end, graph);
  Route least_toll = LeastToll(start, end, graph);
  Route balanced_route = BalancedRoute(start, end, graph);

  vector<Route> routes = { shortest_path, least_toll, balanced_route };
  vector<Route> filtered = filter_routes(routes);

  for (const auto& route : filtered) {
    cout << "Route: ";
    for (size_t i = 0; i < route.path.size(); ++i) {
      cout << route.path[i];
      if (i < route.path.size() - 1) {
        cout << " -> ";
      }
    }
    cout << "\nDistance: " << route.distance << " | Toll: " << route.toll << std::endl << std::endl;
  }

  return 0;
}
