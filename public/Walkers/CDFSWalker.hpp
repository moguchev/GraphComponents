#ifndef C_DFS_WALKER_HPP
#define C_DFS_WALKER_HPP

#include <memory>
#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>
#include "IGraphWalker.hpp"
#include "IGraphComponents.hpp"
#include "CUMapVCollection.hpp"
#include "CComponentsViaLists.hpp"
#include "CLinearSearcher.hpp"

template <class T>
class CDFSWalker : public IGraphWalker<T> {
    using value_type = T;
    using const_reference = const value_type&;
public:
    CDFSWalker() = default;

    virtual ~CDFSWalker() = default;

    virtual std::unique_ptr<IGraphComponents<value_type>> 
        findComponentsInGraph(const IGraph<T>& graph) const override;
};

template <class T>
std::unique_ptr<IGraphComponents<T>> 
    CDFSWalker<T>::findComponentsInGraph(const IGraph<T>& graph) const
{
    CLinearSearcher<T> search;

    return search.findComponentsInGraph(graph, CLinearSearcher<T>::Mode::DFS);
}

#endif // C_DFS_WALKER_HPP