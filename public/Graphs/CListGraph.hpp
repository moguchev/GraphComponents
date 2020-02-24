#ifndef I_LIST_GRAPH_HPP
#define I_LIST_GRAPH_HPP

#include <list>
#include <unordered_map>
#include "../Interfaces/IGraph.hpp"
#include "../Interfaces/IEdgesCollection.hpp"
#include "../Interfaces/IVerticesCollection.hpp"


template <class T>
class CListGraph : public IGraph<T> {
    using value_type = T;
    using const_reference = const value_type&;
    using adjacency_lists_t =
        std::unordered_map<value_type, std::list<value_type>>;
public:
    CListGraph() = default;

    virtual ~CListGraph() = default;

    virtual inline void addEdge(const_reference from, const_reference to) override;

    virtual std::list<T> getNextVertices(const_reference vertex) const override;

    virtual void importAllVertices(IVerticesCollection<T>& collection) const override;

    virtual void importAllEdges(IEdgesCollection<T>& collection) const override;
private:
    adjacency_lists_t _adjacencyLists;
};


template <class T>
inline void CListGraph<T>::addEdge(const_reference from, const_reference to) {
    _adjacencyLists[from].push_back(to);
    _adjacencyLists[to].push_back(from);
}

template <class T>
inline std::list<T> CListGraph<T>::getNextVertices(const_reference vertex) const {
    auto it = _adjacencyLists.find(vertex);
    if (it != _adjacencyLists.end()) {
        return (*it).second;
    }
    else {
        std::list<T> e;
        return e;
    }
}

template <class T>
inline void CListGraph<T>::importAllVertices(IVerticesCollection<T>& collection) const {
    collection.clear();
    for (const auto& v : _adjacencyLists) {
        collection.push(v.first);
    }
}

template <class T>
inline void CListGraph<T>::importAllEdges(IEdgesCollection<T>& collection) const {
    // TODO
}
#endif // I_LIST_GRAPH_HPP