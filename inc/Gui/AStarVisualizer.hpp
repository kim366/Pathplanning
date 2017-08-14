#ifndef GUI_A_STAR_VISUALIZER_HPP
#define GUI_A_STAR_VISUALIZER_HPP

#include <Gui/Entity.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class AStarVisualizer : public Entity
{
public:
	AStarVisualizer(Graph& graph_, const Node* begin_, const Node* end_);

private:
	virtual void 	update(float delta_time_, const Inputs& inputs_) override;

private:
	AStarPathplanner<Euclidean>
					_find_shortest_path;
	std::pair<std::optional<std::vector<const Node*>>, std::set<const Node*>>
					_result;
	const Node*		_begin;
	const Node*		_end;
	Graph&			_graph;
};

} // namespace Gui

#endif // GUI_A_STAR_VISUALIZER_HPP