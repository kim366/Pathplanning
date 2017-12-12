#pragma once

#include <vector>
#include <memory>
#include <initializer_list>
#include <optional>
#include <Node.hpp>
#include <Gui/Entity.hpp>
#include <utility>

class Graph : public Gui::Entity
{
public:
						Graph() = default;
						Graph(std::initializer_list<sf::Vector2i> node_positions_,
							std::initializer_list<std::pair<int, int>> node_indices_);

	void				createNode(sf::Vector2f position_);
	void				deleteNode(int node_index_);

	void 				connect(std::pair<int, int> node_indices_);
	void 				disconnect(std::pair<int, int> node_indices_);
	void				modifyWeight(std::pair<int, int> node_indices_, float new_weight_);

	Node& 				getNode(int node_index_) { return _nodes[node_index_]; }
	const Node&			getNode(int node_index_) const { return _nodes[node_index_]; }

	int					getIndex(const Node& node_) const;

	auto 				begin() { return _nodes.begin(); }
	auto				end() { return _nodes.end(); }

protected:
	void 				draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;
	void				update(float delta_time_, const Gui::Inputs& inputs_) override;

protected:
	std::vector<Node>	_nodes;

private:
	int	_selected_node_index{-1};
};

