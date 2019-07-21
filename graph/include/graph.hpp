//
// Created by penguinlemma on 21.07.19.
//

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <algorithm>

namespace mm {

template <class IterativeGenerator>
class Graph
{
  public:
    using NodeID = std::size_t;
    using NodeSet = std::unordered_set<NodeID>;
    using AdjacencyMap = typename std::unordered_map<std::size_t, NodeSet>;

    typedef typename std::unordered_set<NodeID>::size_type size_type;

    Graph(IterativeGenerator ig);

    constexpr void generate(size_type number_of_nodes) noexcept;

    constexpr auto begin() noexcept;
    constexpr auto begin() const noexcept;
    constexpr auto end() noexcept;
    constexpr auto end() const noexcept;

    constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;

    constexpr auto adjacencies() const noexcept;

    constexpr void addNode(NodeID node) noexcept;

    template <class... Neighbours>
    constexpr void connect(NodeID node, Neighbours... neighbours) noexcept;

  private:
    AdjacencyMap adjacencies_;
    NodeSet nodes_;
    IterativeGenerator grow_;
};

template <class IterativeGenerator>
inline Graph<IterativeGenerator>::Graph(IterativeGenerator ig) : grow_{ig}
{
}

template <class IterativeGenerator>
inline constexpr void Graph<IterativeGenerator>::generate(size_type number_of_nodes) noexcept
{
    while (size() < number_of_nodes) {
        grow_(*this);
    }
}

template <class IterativeGenerator>
constexpr auto Graph<IterativeGenerator>::begin() noexcept
{
    return std::begin(adjacencies_);
}

template <class IterativeGenerator>
constexpr auto Graph<IterativeGenerator>::begin() const noexcept
{
    return std::begin(adjacencies_);
}

template <class IterativeGenerator>
constexpr auto Graph<IterativeGenerator>::end() noexcept
{
    return std::end(adjacencies_);
}

template <class IterativeGenerator>
constexpr auto Graph<IterativeGenerator>::end() const noexcept
{
    return std::end(adjacencies_);
}

template <class IterativeGenerator>
constexpr bool Graph<IterativeGenerator>::empty() const noexcept
{
    return nodes_.empty();
}

template <class IterativeGenerator>
constexpr typename Graph<IterativeGenerator>::size_type Graph<IterativeGenerator>::size() const
    noexcept
{
    return nodes_.size();
}

template <class IterativeGenerator>
constexpr auto Graph<IterativeGenerator>::adjacencies() const noexcept
{
    return adjacencies_;
}

template <class IterativeGenerator>
constexpr void Graph<IterativeGenerator>::addNode(NodeID node) noexcept
{
    if (nodes_.find(node) != std::end(nodes_))
        return;
    nodes_.insert(node);
}

template <class IterativeGenerator>
template <class... Neighbours>
constexpr void Graph<IterativeGenerator>::connect(NodeID node, Neighbours... neighbours) noexcept
{
    using iterator = typename AdjacencyMap::iterator;
    std::pair<iterator, bool> node_found = adjacencies_.insert({node, {}});
    //< -this breaks
    // constexprness, the line above doesn't  ??
    // auto node_found = adjacencies_.insert(node);
    if (!node_found.second) {
        nodes_.insert(node);
    }
    std::array<std::pair<iterator, bool>, sizeof...(neighbours)> n = {
        adjacencies_.insert({neighbours, {}})...};
    for (auto const& [it_n, found] : n) {
        it_n.second.insert(node);
        if (!found) {
            nodes_.insert(it_n.first);
        }
    }
}

}  // namespace mm
