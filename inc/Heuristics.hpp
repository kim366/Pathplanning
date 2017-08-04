#ifndef HEURISITICS_HPP
#define HEURISITICS_HPP

#include <math.h>

class Heuristic
{
public:
					Heuristic(const Node*& end_) : _end(end_) {}
	virtual float 	operator()(const Node* node_) const = 0;

protected:
	const Node*& 	_end;
};

struct Euclidean : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		sf::Vector2f distance{_end->getPosition() - node_->getPosition()}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		return 0.f;
	}
};

#endif // HEURISITICS_HPP