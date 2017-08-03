#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

#include <vector>
#include <queue>
#include <functional>
#include <experimental/optional>
#include <Node.hpp>

class Graph;

class Pathplanner
{
public:
	virtual std::experimental::optional<std::pair<std::vector<const Node*>, unsigned>>
					operator()(const Node* start_, const Node* end_) = 0;
	virtual			~Pathplanner() = 0;

protected:
	virtual float	evaluate(Node* to_evaluate_, Node* based_on_) = 0;
	float			cost(const Node* from_, const Node* to_) const;

protected:
	const std::function<bool(Node*, Node*)>
					_compare{[this] (Node* x_, Node* y_)
					{
						if (x_->value == y_->value && x_ == _end)
							return false;
						return x_->value > y_->value;
					}};
					
	std::priority_queue<Node*, std::vector<Node*>, decltype(_compare)>
					_open{_compare};
	const Node*		_start;
	const Node*		_end;
};

#endif // PATHPLANNER_HPP