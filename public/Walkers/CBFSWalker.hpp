#ifndef C_BFS_WALKER_HPP
#define C_BFS_WALKER_HPP

#include <memory>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include "../Interfacs/IGraphWalker.hpp"
#include "../Interfacs/IGraphComponents.hpp"
#include "../Components/CComponentsViaLists.hpp"
#include "../Collections/CUMapVCollection.hpp"
#include "CLinearSearcher.hpp"

template <class T>
class CBFSWalker : public IGraphWalker<T> {
    using value_type = T;
    using const_reference = const value_type&;
public:
    CBFSWalker() = default;

    virtual ~CBFSWalker() = default;

    virtual std::unique_ptr<IGraphComponents<value_type>>
        findComponentsInGraph(const IGraph<T>& graph) const override;
};


template <class T>
std::unique_ptr<IGraphComponents<T>>
CBFSWalker<T>::findComponentsInGraph(const IGraph<T>& graph) const
{
    CLinearSearcher<T> search;

    return search.findComponentsInGraph(graph, CLinearSearcher<T>::Mode::BFS);
}

#endif // C_BFS_WALKER_HPP