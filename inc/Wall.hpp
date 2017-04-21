#ifndef WALL_HPP
#define WALL_HPP

class Wall
{
public:
	enum class Orientation : bool
	{
		Vertical,
		Horizontal
	};

	explicit Wall(Orientation orientation_);

private:
	Orientation _orientation;
};

#endif // WALL_HPP