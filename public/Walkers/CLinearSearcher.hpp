#ifndef C_LINEAR_SEARCHER_HPP
#define C_LINEAR_SEARCHER_HPP

#include <any>
#include <memory>
#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>
#include <queue>
#include "IGraph.hpp"
#include "IGraphComponents.hpp"
#include "CUMapVCollection.hpp"
#include "CComponentsViaLists.hpp"

template <class T>
class CLinearSearcher {
    using value_type = T;
    using const_reference = const value_type&;
public:
    enum class Mode {
        DFS,
        BFS,
    };

    CLinearSearcher() = default;

    virtual ~CLinearSearcher() = default;

    static std::list<value_type> DFS(
        const IGraph<value_type>& graph,
        const_reference vertex,
        std::function<void(const_reference)> func
    );

    static std::list<value_type> BFS(
        const IGraph<value_type>& graph,
        const_reference vertex,
        std::function<void(const_reference)> func
    );

    std::unique_ptr<IGraphComponents<value_type>>
        findComponentsInGraph(const IGraph<T>& graph, const Mode& mode) const;
};


template <class T>
std::list<T> CLinearSearcher<T>::BFS(
    const IGraph<T>& graph,
    const_reference vertex,
    std::function<void(const_reference)> func
) {
    std::unordered_map<T, bool> visited;
    std::queue<T> nextVertices;
    std::list<T> result;
    nextVertices.push(vertex);

    while (nextVertices.size()) {
        auto current = nextVertices.front();
        nextVertices.pop();
        if (!visited[current]) {
            func(current);
            result.push_back(current);
            visited[current] = true;
        }
        else {
            continue;
        }

        auto v = graph.getNextVertices(current);
        for (const auto& nextVertex : v) {
            if (!visited[nextVertex]) {
                nextVertices.push(nextVertex);
            }
        }
    }
    return result;
}

template <class T>
std::list<T> CLinearSearcher<T>::DFS(
    const IGraph<T>& graph,
    const_reference vertex,
    std::function<void(const_reference)> func
) {
    std::unordered_map<T, bool> visited;
    std::stack<T> nextVertices;
    std::list<T> result;
    nextVertices.push(vertex);

    while (nextVertices.size()) {
        auto current = nextVertices.top();
        nextVertices.pop();
        if (!visited[current]) {
            func(current);
            result.push_back(current);
            visited[current] = true;
        }
        else {
            continue;
        }

        auto v = graph.getNextVertices(current);
        for (const auto& nextVertex : v) {
            if (!visited[nextVertex]) {
                nextVertices.push(nextVertex);
            }
        }
    }
    return result;
}

template <class T>
std::unique_ptr<IGraphComponents<T>>
CLinearSearcher<T>::findComponentsInGraph(const IGraph<T>& graph, const Mode& mode) const
{
    std::unique_ptr<CComponentsViaLists<T>> components = std::make_unique<CComponentsViaLists<T>>();

    CUMapVCollection<T> collection;
    graph.importAllVertices(collection);
    auto visited = collection.getCollection();

    std::function<void(const T&)> update = [&visited](const T& vertex) {
        auto it = visited.find(vertex);
        if (it != visited.end()) {
            (*it).second = true;
        }
    };

    for (auto vertex : visited) {
        if (!vertex.second) {
            std::list<T> component;
            if (mode == Mode::DFS) {
                component = CLinearSearcher::DFS(graph, vertex.first, update);
            }
            else if (mode == Mode::BFS) {
                component = CLinearSearcher::BFS(graph, vertex.first, update);
            }
                
            components->push(std::move(component));
        }
    }

    return components;
}

#endif // C_DFS_WALKER_HPP