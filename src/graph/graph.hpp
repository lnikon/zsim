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
    struct Neighbour;
    using NeighbourUPtr     = std::unique_ptr<Neighbour>;
    using NeighbourSPtr     = std::shared_ptr<Neighbour>;
    using NeighbourWPtr     = std::weak_ptr<Neighbour>;
    using NeighbourSPtrVec  = std::vector<NeighbourSPtr>;

    using IdVertexPair      = std::pair<VertexIndexType, VertexValueType>;
    using IdVertexPairCRef  = const IdVertexPair&;

    struct Neighbour
    {
        EdgeValueType   value_;
        IdVertexPair    adjacent_;
    };

    void addVertex(IdVertexPairCRef idVertexPair)
    {
        if(graph_.find(idVertexPair.first) == std::end(graph_))
        {
            graph_[idVertexPair.first] = std::make_pair(idVertexPair.second, NeighbourSPtrVec{});
        }
    }

    void addEdge(IdVertexPairCRef from, IdVertexPairCRef to)
    {

    }

private:
    std::unordered_map<VertexIndexType, std::pair<VertexValueType, NeighbourSPtrVec>> graph_;
};

} // namespace graph_ns
