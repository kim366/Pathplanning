#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>
#include <initializer_list>
#include <experimental/optional>
#include <Node.hpp>

class Graph
{
public:
				Graph(std::initializer_list<sf::Vector2i> node_positions_,
					std::initializer_list<sf::Vector2i> node_indices_);

				void		createNode(sf::Vector2u position_);
	void		deleteNode(unsigned node_index_);

	void 		connect(sf::Vector2u node_indices_);
	void 		disconnect(sf::Vector2u node_indices_);

	const auto* getNode(unsigned node_index_) { return _nodes[node_index_].get(); }

private:
	std::vector<std::unique_ptr<Node>>
				_nodes;
};

#endif // GRAPH_HPP