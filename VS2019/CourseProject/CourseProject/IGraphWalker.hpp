#ifndef I_GRAPH_WALKER_HPP
#define I_GRAPH_WALKER_HPP

#include <memory>
#include "IGraph.hpp"
#include "IGraphComponents.hpp"

template<class T>
struct IGraphWalker {
    virtual ~IGraphWalker() = default;

    virtual std::unique_ptr<IGraphComponents<T>>
        findComponentsInGraph(const IGraph<T>& graph) const = 0;
};

#endif // I_GRAPH_WALKER_HPP
