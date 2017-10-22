#pragma once

#include <array>
#include <SFML/System/Vector2.hpp>

namespace Directions
{	

enum
{
	North,
	East,
	South,
	West,
	Northeast,
	Southeast,
	Southwest,
	Northwest
};

const std::array<sf::Vector2i, 8>
	vectors{{{0, -1}, {1, 0}, {0, 1}, {-1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}}};

} // namespace Directions


