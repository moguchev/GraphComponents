#ifndef C_DSU_WALKER_HPP
#define C_DSU_WALKER_HPP

#include <functional>
#include <memory>
#include <stack>
#include <unordered_map>
#include <utility>
#include "../Interfaces/IGraphWalker.hpp"
#include "../Interfaces/IGraphComponents.hpp"
#include "../Components/CComponentsViaDSU.hpp"
#include "../Collections/CListPairsECollection.hpp"
#include "../CDSU.hpp"


template <class T>
class CDSUWalker : public IGraphWalker<T> {
    using value_type = T;
    using const_reference = const value_type&;
public:
    CDSUWalker() = default;

    virtual ~CDSUWalker() = default;

    virtual std::unique_ptr<IGraphComponents<T>> 
        findComponentsInGraph(const IGraph<T>& graph) const override;
};

template <class T>
std::unique_ptr<IGraphComponents<T>> 
    CDSUWalker<T>::findComponentsInGraph(const IGraph<T>& graph) const
{
    CDSU<T> dsu;

    CListPairsECollection<T> collection;
    graph.importAllEdges(collection);
    auto edges = collection.getCollection();

    for (const auto& e : edges) {
        dsu.makeSet(e.first);  // если элемент уже существует, то ничего не произойдет
        dsu.makeSet(e.second);
        dsu.unionSets(e.first, e.second);
    }

    return std::make_unique<CComponentsViaDSU<T>>(std::move(dsu));
}

#endif // C_DSU_WALKER_HPP
