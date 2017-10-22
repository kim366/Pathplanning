#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <optional>
#include <Node.hpp>

class Pathplanner
{
public:
	virtual std::pair<std::vector<const Node*>, std::set<const Node*>>
					operator()(const Node* start_, const Node* goal_) = 0;
	virtual			~Pathplanner() = 0;

protected:
	virtual std::pair<float, float>
					evaluate(const Node* to_evaluate_, const Node* based_on_) const = 0;
	float			cost(const Node* from_, const Node* to_) const;

protected:
	const std::function<bool(Node*, Node*)>
					_compare{[this] (Node* x_, Node* y_)
					{
						if (x_->value == y_->value && x_ == _goal)
							return false;
						return x_->value > y_->value;
					}};
					
	std::priority_queue<Node*, std::vector<Node*>, decltype(_compare)>
					_open{_compare};
	const Node*		_start;
	const Node*		_goal;

public:
	enum Tag
	{
		New,
		Open,
		Closed
	};
};

#endif // PATHPLANNER_HPP