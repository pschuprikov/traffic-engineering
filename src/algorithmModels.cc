#include "algorithmModels.h"


namespace TrafficEngineering {

Graph::Graph(int vertex_number, const std::vector<Edge> edges) :
    _names(vertex_number),
    _distances(vertex_number, std::vector<double>(vertex_number, INF)),
    _parent(vertex_number, std::vector<int>(vertex_number))
{
    for (const auto &edge : edges) {
        if (_indexes.count(edge.from) == 0) {
            _names[_indexes.size()] = edge.from;
            _indexes[edge.from] = _indexes.size();
        }
        if (_indexes.count(edge.to) == 0) {
            _names[_indexes.size()] = edge.to;
            _indexes[edge.to] = _indexes.size();
        }
        _distances[_indexes[edge.from]][_indexes[edge.to]] = edge.weight;
        _parent[_indexes[edge.from]][_indexes[edge.to]] = _indexes[edge.from];
    }
    for (int i = 0; i < vertex_number; i++) {
        _distances[i][i] = 0;
        _parent[i][i] = i;
    }

    for (int k = 0; k < vertex_number; k++) {
        for (int i = 0; i < vertex_number; i++) {
            for (int j = 0; j < vertex_number; j++) {
                if (_distances[i][j] > _distances[i][k] + _distances[k][j]) {
                    _distances[i][j] = _distances[i][k] + _distances[k][j];
                    _parent[i][j] = k;
                }
            }
        }
    }
}

double Graph::theShortestPathWeight(const std::string &from, const std::string &to) {
    assert(_indexes.count(from) != 0);
    assert(_indexes.count(to) != 0);
    return _distances[_indexes[from]][_indexes[to]];
}

std::vector<Edge> Graph::theShortestPath(const std::string &from, const std::string &to) {
    assert(_indexes.count(from) != 0);
    assert(_indexes.count(to) != 0);
    std::string vertex = _names[_parent[_indexes[from]][_indexes[to]]];
    if (from == vertex) {
        return {{from, to, 0}};
    }
    auto left = theShortestPath(from, vertex);
    auto right = theShortestPath(vertex, to);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}


Tree::Tree(const std::string &root) {
    _edges[root] = {};
}

void Tree::addEdge(const Edge &edge) {
    assert(_edges.count(edge.from) != 0);
    _edges[edge.from].push_back(edge);
}

void Tree::addBranch(const std::vector<Edge> &branch) {
    for (const auto &edge : branch) {
        addEdge(edge);
    }
}

double Tree::theLongestPathWeight(const std::string &node) const {
    assert(_edges.count(node) != 0);
    double result = 0;
    for (const auto &edge : _edges.at(node)) {
        result = std::max(result, edge.weight + theLongestPathWeight(edge.to));
    }
    return result;
}

std::vector<std::string> Tree::getAllNodes() const {
    std::vector<std::string> result;
    for (const auto &entry : _edges) {
        result.push_back(entry.first);
    }
    return result;
}

} // namespace TrafficEngineering
