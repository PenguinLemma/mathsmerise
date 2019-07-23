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

    constexpr auto nodes() const noexcept;

    constexpr void addNode(NodeID node) noexcept;

    constexpr NodeID addNode() noexcept;

    template <class... Neighbours>
    constexpr void connect(NodeID node, NodeID n1, Neighbours... other_neighbours) noexcept;

    template <class Container>
    constexpr void connect(NodeID node, Container const& neighbours) noexcept;

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
constexpr auto Graph<IterativeGenerator>::nodes() const noexcept
{
    return nodes_;
}

template <class IterativeGenerator>
constexpr void Graph<IterativeGenerator>::addNode(NodeID node) noexcept
{
    if (nodes_.find(node) != std::end(nodes_))
        return;
    nodes_.insert(node);
}

template <class IterativeGenerator>
constexpr typename Graph<IterativeGenerator>::NodeID Graph<IterativeGenerator>::addNode() noexcept
{
    NodeID new_node_id = 0;
    if (!nodes_.empty()) {
        auto it_max_el = std::max_element(std::begin(nodes_), std::end(nodes_));
        new_node_id = *it_max_el + 1;
    }
    nodes_.insert(new_node_id);
    return new_node_id;
}

template <class IterativeGenerator>
template <class... Neighbours>
constexpr void Graph<IterativeGenerator>::connect(NodeID node,
                                                  NodeID n1,
                                                  Neighbours... other_neighbours) noexcept
{
    std::array<NodeID, sizeof...(other_neighbours) + 1> n = {n1, other_neighbours...};
    connect(node, n);
}

template <class IterativeGenerator>
template <class Container>
constexpr void Graph<IterativeGenerator>::connect(NodeID node, Container const& neighbours) noexcept
{
    using Iterator = typename AdjacencyMap::iterator;
    std::pair<Iterator, bool> node_inserted = adjacencies_.insert({node, {}});
    auto& node_adjacencies = node_inserted.first->second;

    if (node_inserted.second) {
        nodes_.insert(node);
    }

    for (auto neighbour : neighbours) {
        Iterator it;
        bool neighbour_inserted;
        std::tie(it, neighbour_inserted) = adjacencies_.insert({neighbour, {}});
        auto& neighbour_adjacencies = it->second;
        neighbour_adjacencies.insert(node);
        if (neighbour_inserted) {
            nodes_.insert(neighbour);
        }
        node_adjacencies.insert(neighbour);
    }
}  // namespace mm
}  // namespace mm
