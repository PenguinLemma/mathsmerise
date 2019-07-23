//
// Created by penguinlemma on 21.07.19.
//

#include "graph_test.hpp"

namespace mm {

static auto TrivialIterativeGenerator = []([[maybe_unused]] auto& graph) {};

static auto RopeIterativeGenerator = [](auto& graph) {
    if (graph.empty()) {
        graph.addNode(0);
        return;
    }
    auto new_node_id = graph.addNode();
    graph.connect(new_node_id - 1, new_node_id);
};

static auto IsolatedIterativeGenerator = [](auto& graph) { graph.addNode(); };

static auto CompleteIterativeGenerator = [](auto& graph) {
    if (graph.empty()) {
        graph.addNode(0);
        return;
    }
    auto nodes = graph.nodes();
    auto new_node_id = graph.addNode();
    graph.connect(new_node_id, nodes);
};

TEST_CASE("Constructors", "[graph]")
{
    Graph rope(RopeIterativeGenerator);
    Graph isolated(IsolatedIterativeGenerator);
    REQUIRE(rope.adjacencies().empty());
    REQUIRE(rope.nodes().empty());
    REQUIRE(isolated.adjacencies().empty());
    REQUIRE(isolated.nodes().empty());
}

TEST_CASE("connect with parameter pack", "[graph]")
{
    SECTION("All involved nodes are added")
    {
        Graph g(TrivialIterativeGenerator);
        g.connect(1UL, 2UL, 3UL, 4UL);
        auto nodes = g.nodes();
        CHECK(nodes.size() == 4);
        CHECK(nodes.find(1UL) != nodes.end());
        CHECK(nodes.find(2UL) != nodes.end());
        CHECK(nodes.find(3UL) != nodes.end());
        CHECK(nodes.find(4UL) != nodes.end());

        g.connect(2UL, 5UL, 6UL);
        nodes = g.nodes();
        CHECK(nodes.size() == 6);
        CHECK(nodes.find(5UL) != nodes.end());
        CHECK(nodes.find(6UL) != nodes.end());
    }

    SECTION("All edges are there")
    {
        Graph g(TrivialIterativeGenerator);
        g.connect(1UL, 2UL, 3UL, 4UL);
        auto adjacencies = g.adjacencies();
        CHECK(adjacencies.size() == 4);
        CHECK(adjacencies.find(1UL) != adjacencies.end());
        CHECK(adjacencies[1UL].size() == 3);
        CHECK(adjacencies[1UL].find(2UL) != adjacencies[1UL].end());
        CHECK(adjacencies[1UL].find(3UL) != adjacencies[1UL].end());
        CHECK(adjacencies[1UL].find(4UL) != adjacencies[1UL].end());
        CHECK(adjacencies.find(2UL) != adjacencies.end());
        CHECK(adjacencies[2UL].size() == 1);
        CHECK(adjacencies[2UL].find(1UL) != adjacencies[2UL].end());
        CHECK(adjacencies.find(3UL) != adjacencies.end());
        CHECK(adjacencies[3UL].size() == 1);
        CHECK(adjacencies[3UL].find(1UL) != adjacencies[3UL].end());
        CHECK(adjacencies.find(4UL) != adjacencies.end());
        CHECK(adjacencies[4UL].size() == 1);
        CHECK(adjacencies[4UL].find(1UL) != adjacencies[4UL].end());

        g.connect(2UL, 5UL, 6UL);
        adjacencies = g.adjacencies();
        CHECK(adjacencies.find(2UL) != adjacencies.end());
        CHECK(adjacencies[2UL].size() == 3);
        CHECK(adjacencies[2UL].find(1UL) != adjacencies[2UL].end());
        CHECK(adjacencies[2UL].find(5UL) != adjacencies[2UL].end());
        CHECK(adjacencies[2UL].find(6UL) != adjacencies[2UL].end());
        CHECK(adjacencies.find(5UL) != adjacencies.end());
        CHECK(adjacencies[5UL].size() == 1);
        CHECK(adjacencies[5UL].find(2UL) != adjacencies[5UL].end());
        CHECK(adjacencies.find(6UL) != adjacencies.end());
        CHECK(adjacencies[6UL].size() == 1);
        CHECK(adjacencies[6UL].find(2UL) != adjacencies[6UL].end());
    }
}

TEST_CASE("connect with NodeSet", "[graph]")
{
    SECTION("All involved nodes are added")
    {
        Graph g(TrivialIterativeGenerator);

        std::unordered_set<std::size_t> neighbours{2, 3, 4, 5};
        g.connect(1ULL, neighbours);
        auto nodes = g.nodes();
        CHECK(nodes.size() == 5);
        CHECK(nodes.find(1UL) != nodes.end());
        CHECK(nodes.find(2UL) != nodes.end());
        CHECK(nodes.find(3UL) != nodes.end());
        CHECK(nodes.find(4UL) != nodes.end());
        CHECK(nodes.find(5UL) != nodes.end());

        g.connect(2UL, 5UL, 6UL);
        nodes = g.nodes();
        CHECK(nodes.size() == 6);
        CHECK(nodes.find(6UL) != nodes.end());
    }

    SECTION("All edges are there")
    {
        Graph g(TrivialIterativeGenerator);
        std::unordered_set<std::size_t> neighbours{2, 3, 4, 5};
        g.connect(1UL, neighbours);
        auto adjacencies = g.adjacencies();
        CHECK(adjacencies.size() == 5);
        CHECK(adjacencies.find(1UL) != adjacencies.end());
        CHECK(adjacencies[1UL].size() == 4);
        CHECK(adjacencies[1UL].find(2UL) != adjacencies[1UL].end());
        CHECK(adjacencies[1UL].find(3UL) != adjacencies[1UL].end());
        CHECK(adjacencies[1UL].find(4UL) != adjacencies[1UL].end());
        CHECK(adjacencies[1UL].find(5UL) != adjacencies[1UL].end());
        CHECK(adjacencies.find(2UL) != adjacencies.end());
        CHECK(adjacencies[2UL].size() == 1);
        CHECK(adjacencies[2UL].find(1UL) != adjacencies[2UL].end());
        CHECK(adjacencies.find(3UL) != adjacencies.end());
        CHECK(adjacencies[3UL].size() == 1);
        CHECK(adjacencies[3UL].find(1UL) != adjacencies[3UL].end());
        CHECK(adjacencies.find(4UL) != adjacencies.end());
        CHECK(adjacencies[4UL].size() == 1);
        CHECK(adjacencies[4UL].find(1UL) != adjacencies[4UL].end());
        CHECK(adjacencies.find(5UL) != adjacencies.end());
        CHECK(adjacencies[5UL].size() == 1);
        CHECK(adjacencies[5UL].find(1UL) != adjacencies[5UL].end());

        neighbours = {5UL, 6UL};
        g.connect(2UL, neighbours);
        adjacencies = g.adjacencies();
        CHECK(adjacencies.find(2UL) != adjacencies.end());
        CHECK(adjacencies[2UL].size() == 3);
        CHECK(adjacencies[2UL].find(1UL) != adjacencies[2UL].end());
        CHECK(adjacencies[2UL].find(5UL) != adjacencies[2UL].end());
        CHECK(adjacencies[2UL].find(6UL) != adjacencies[2UL].end());
        CHECK(adjacencies.find(5UL) != adjacencies.end());
        CHECK(adjacencies[5UL].size() == 2);
        CHECK(adjacencies[5UL].find(1UL) != adjacencies[5UL].end());
        CHECK(adjacencies[5UL].find(2UL) != adjacencies[5UL].end());
        CHECK(adjacencies.find(6UL) != adjacencies.end());
        CHECK(adjacencies[6UL].size() == 1);
        CHECK(adjacencies[6UL].find(2UL) != adjacencies[6UL].end());
    }
}

TEST_CASE("Generation", "[graph]")
{
    SECTION("1 node")
    {
        std::size_t num_nodes = 1;
        Graph rope(RopeIterativeGenerator);
        Graph isolated(IsolatedIterativeGenerator);

        rope.generate(num_nodes);
        isolated.generate(num_nodes);
        CHECK(rope.nodes().size() == 1);
        CHECK(isolated.nodes().size() == 1);
    }
}

}  // namespace mm