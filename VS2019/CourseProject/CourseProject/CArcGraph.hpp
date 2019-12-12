#ifndef I_ARC_GRAPH_HPP
#define I_ARC_GRAPH_HPP

#include <list>
#include <typeinfo>
#include <utility>
#include <vector>
#include "IGraph.hpp"
#include "IEdgesCollection.hpp"
#include "IVerticesCollection.hpp"
#include "CListPairsECollection.hpp"

template <class T>
class CArcGraph : public IGraph<T> {
    using value_type = T;
    using const_reference = const value_type&;
    using edges_t = std::vector<std::pair<value_type, value_type>>;
public:
    CArcGraph() = default;

    virtual ~CArcGraph() = default;

    virtual inline void addEdge(const_reference from, const_reference to) override;

    virtual std::list<T> getNextVertices(const_reference vertex) const override;

    virtual void importAllVertices(IVerticesCollection<T>& collection) const override;

    virtual void importAllEdges(IEdgesCollection<T>& collection) const override;
private:
    edges_t _edges;
};

template <class T>
inline void CArcGraph<T>::addEdge(const_reference from, const_reference to) {
    for (const auto& e : _edges)
        if (e.first == from && e.second == to)
            return;
    _edges.push_back(std::make_pair(from, to));
}

template <class T>
std::list<T> CArcGraph<T>::getNextVertices(const_reference vertex) const {
    std::list<T> vertices;
    for (const auto& e : _edges)
        if (e.first == vertex)
            vertices.push_back(e.second);
    return vertices;
}

template <class T>
void CArcGraph<T>::importAllVertices(IVerticesCollection<T>& collection) const {
    // TODO
}

template <class T>
void CArcGraph<T>::importAllEdges(IEdgesCollection<T>& collection) const {
    collection.clear();
    for (const auto& e : _edges) {
        collection.push(e.first, e.second);
    }
}

#endif // I_ARC_GRAPH_HPP