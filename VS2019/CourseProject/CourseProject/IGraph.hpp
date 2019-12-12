#ifndef I_GRAPH_HPP
#define I_GRAPH_HPP

#include <list>
#include "IEdgesCollection.hpp"
#include "IVerticesCollection.hpp"


template<class T>
struct IGraph {
    IGraph() = default;

    virtual ~IGraph() = default;

    //  Добавление ребра от from к to.
    virtual void addEdge(const T& from, const T& to) = 0;

    virtual std::list<T> getNextVertices(const T& vertex) const = 0;

    virtual void importAllVertices(
        IVerticesCollection<T>& collection) const = 0;

    virtual void importAllEdges(IEdgesCollection<T>& collection) const = 0;
};

#endif // I_GRAPH_HPP