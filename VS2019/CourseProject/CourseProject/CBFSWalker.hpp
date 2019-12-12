#ifndef C_BFS_WALKER_HPP
#define C_BFS_WALKER_HPP

#include <memory>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include "IGraphWalker.hpp"
#include "IGraphComponents.hpp"
#include "CComponentsViaLists.hpp"
#include "CUMapVCollection.hpp"

template <class T>
class CBFSWalker : public IGraphWalker<T> {
    using value_type = T;
    using const_reference = const value_type&;
public:
    CBFSWalker() = default;

    virtual ~CBFSWalker() = default;

    static std::list<value_type> BFS(
        const IGraph<value_type>& graph,
        const_reference vertex,
        std::function<void(const_reference)> func
    );

    virtual std::unique_ptr<IGraphComponents<value_type>>
        findComponentsInGraph(const IGraph<T>& graph) const override;
};

template <class T>
std::list<T> CBFSWalker<T>::BFS(
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
std::unique_ptr<IGraphComponents<T>>
CBFSWalker<T>::findComponentsInGraph(const IGraph<T>& graph) const
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
            std::list<T> component = CBFSWalker::BFS(graph, vertex.first, update);
            components->push(std::move(component));
        }
    }

    return components;
}

#endif // C_BFS_WALKER_HPP