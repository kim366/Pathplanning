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
friend class NodeHandle;

public:
						Graph() = default;
						Graph(std::initializer_list<sf::Vector2i> node_positions_,
							std::initializer_list<std::pair<int, int>> node_indices_);
						Graph(const Graph& other_);
						
	void				createNode(sf::Vector2f position_);
	void				deleteNode(int node_index_);

	void 				connect(std::pair<int, int> node_indices_);
	void 				disconnect(std::pair<int, int> node_indices_);
	void 				connect(NodeHandle first_, NodeHandle second_);
	void 				disconnect(NodeHandle first_, NodeHandle second_);

	void				modifyWeight(NodeHandle first_, NodeHandle second_, float new_weight_);

	NodeHandle 			operator[](int index_);

	void				resetNodes();

protected:
	void 				draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;
	void				update(float delta_time_, const Gui::Inputs& inputs_) override;

protected:
	std::vector<Node>	_nodes;

private:
	int					_selected_node_index;
};

