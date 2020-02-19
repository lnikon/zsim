#pragma once

#include <memory>
#include <vector>
#include <variant>
#include <unordered_map>
#include <utility>

namespace graph_ns
{

template <class VertexValueType,
          class EdgeValueType>
struct Graph final
{
    Graph() {}
    ~Graph() {}

    enum class Direction { Input = 0, Output , BiDir };

    struct Neighbour;
    using NeighbourUPtr     = std::unique_ptr<Neighbour>;
    using NeighbourSPtr     = std::shared_ptr<Neighbour>;
    using NeighbourWPtr     = std::weak_ptr<Neighbour>;
    using NeighbourSPtrVec  = std::vector<NeighbourSPtr>;

    struct Neighbour
    {
        std::shared_ptr<EdgeValueType>      spEdge_{nullptr};
        Direction                           direction_;
    };

    void addVertex(const VertexValueType& vertex)
    {
        graph_.insert(vertex);
    }

    void addEdge(const VertexValueType& from, EdgeValueType edge, Direction direction)
    {
        graph_[from].emplace_back(edge, direction);
    }

private:
    std::unordered_map<VertexValueType, NeighbourSPtrVec> graph_;
};

template <class VertexValueType,
          class EdgeValueType>
using GraphUPtr = std::unique_ptr<Graph<VertexValueType, EdgeValueType>>;\

template <class VertexValueType,
          class EdgeValueType>
using GraphSPtr = std::shared_ptr<Graph<VertexValueType, EdgeValueType>>;

template <class VertexValueType,
          class EdgeValueType>
using GraphWPtr = std::weak_ptr<Graph<VertexValueType, EdgeValueType>>;

template <class VertexValueType,
          class EdgeValueType,
          class... Args>
auto make_unique(Args&&... args)
{
    return std::make_unique<Graph<VertexValueType, EdgeValueType>>(std::forward<Args>(args)...);
}

template <class VertexValueType,
          class EdgeValueType,
          class... Args>
auto make_shared(Args&&... args)
{
    return std::make_shared<Graph<VertexValueType, EdgeValueType>>(std::forward<Args>(args)...);
}

} // namespace graph_ns
