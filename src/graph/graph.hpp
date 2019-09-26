#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>

namespace graph_ns
{
 
template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType>
struct Graph final
{
    enum class Direction    { Input = 0, Output , BiDir };

    struct Neighbour;
    using NeighbourUPtr     = std::unique_ptr<Neighbour>;
    using NeighbourSPtr     = std::shared_ptr<Neighbour>;
    using NeighbourWPtr     = std::weak_ptr<Neighbour>;
    using NeighbourSPtrVec  = std::vector<NeighbourSPtr>;

    using IdVertexPair      = std::pair<VertexIndexType, VertexValueType>;
    using IdVertexPairCRef  = const IdVertexPair&;

    struct Neighbour
    {
        IdVertexPair    adjacent_;
        EdgeValueType   value_;
        Direction       direction_;
    };

    void addVertex(IdVertexPairCRef idVertexPair)
    {
        if(graph_.find(idVertexPair.first) == std::end(graph_))
        {
            graph_[idVertexPair.first] = std::make_pair(idVertexPair.second, NeighbourSPtrVec{});
        }
    }

    void addEdge(IdVertexPairCRef from, IdVertexPairCRef to, EdgeValueType edgeValue, Direction = Direction::BiDir)
    {
        graph_[from.first].second.emplace_back({to, edgeValue, Direction::Output});
        graph_[to.first].second.emplace_back({from, edgeValue, Direction::Input});
    }

private:
    std::unordered_map<VertexIndexType,
                       std::pair<VertexValueType,
                                 NeighbourSPtrVec>> graph_;
};

template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType>
using GraphUPtr = std::unique_ptr<Graph<VertexIndexType, VertexValueType, EdgeValueType>>;\

template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType>
using GraphSPtr = std::shared_ptr<Graph<VertexIndexType, VertexValueType, EdgeValueType>>;

template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType>
using GraphWPtr = std::weak_ptr<Graph<VertexIndexType, VertexValueType, EdgeValueType>>;

template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType,
          class... Args>
auto make_unique(Args&&... args)
{
    return std::make_unique<Graph<VertexIndexType, VertexValueType, EdgeValueType>>(std::forward<Args>(args)...);
}

template <class VertexIndexType,
          class VertexValueType,
          class EdgeValueType,
          class... Args>
auto make_shared(Args&&... args)
{
    return std::make_shared<Graph<VertexIndexType, VertexValueType, EdgeValueType>>(std::forward<Args>(args)...);
}

} // namespace graph_ns
