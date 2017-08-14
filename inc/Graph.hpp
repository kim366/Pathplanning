#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>
#include <initializer_list>
#include <optional>
#include <Node.hpp>
#include <Gui/Entity.hpp>

class Graph : public Gui::Entity
{
public:
				Graph() {}
				Graph(std::initializer_list<sf::Vector2i> node_positions_,
					std::initializer_list<sf::Vector2i> node_indices_);

	void		createNode(sf::Vector2f position_);
	void		deleteNode(unsigned node_index_);

	void 		connect(sf::Vector2u node_indices_);
	void 		disconnect(sf::Vector2u node_indices_);

	void 		connect(Node* node1_, Node* node2_);
	void 		disconnect(Node* node1_, Node* node2_);

	auto* 		getNode(unsigned node_index_) { return _nodes[node_index_].get(); }

	auto 		begin() { return _nodes.begin(); }
	auto		end() { return _nodes.end(); }

protected:
	void 		draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;
	void		update(float delta_time_, const Gui::Inputs& inputs_) override;

protected:
	std::vector<std::unique_ptr<Node>>
				_nodes;

private:
	std::optional<Node*>
				_selected_node;
};

#endif // GRAPH_HPP