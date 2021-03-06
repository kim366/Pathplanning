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
friend class NodePtr;

public:
						Graph() = default;
						Graph(std::optional<int> seed_, float node_radius_ = 4.f);
						Graph(std::initializer_list<sf::Vector2i> node_positions_,
							std::initializer_list<std::pair<int, int>> node_indices_,
							float node_radius_ = 4.f);
						Graph(const Graph& other_);
						
	void				createNode(sf::Vector2f position_);
	void				deleteNode(int node_index_);

	void 				connect(std::pair<int, int> node_indices_);
	void 				disconnect(std::pair<int, int> node_indices_);
	void 				connect(NodePtr first_, NodePtr second_);
	void 				disconnect(NodePtr first_, NodePtr second_);

	void 				generateMaze();
	void				modifyWeight(NodePtr first_, NodePtr second_, float new_weight_);

	NodePtr 			operator[](int index_);
	Graph&				operator=(const Graph& other_);

	void				resetNodes();
	std::vector<Node>	_nodes;
protected:
	void 				draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;
	void				update(float delta_time_, const Gui::Inputs& inputs_) override;
protected:
	std::optional<int>	_seed;
	float				_node_radius;

private:
	int					_selected_node_index{-1};
};
