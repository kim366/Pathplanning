#pragma once

#include <SFML/System/String.hpp>

namespace Gui
{

namespace cst
{

namespace Window
{

const sf::String 	title{"Pathplanning"};
const auto 			size{500u};

} // namespace Window

namespace Input
{

const auto			threshold_drag{10u}; // in px; hypot threshold until a held button is considerered a drag

} // namespace Input

namespace Graph
{

const auto 			node_radius{10.f};
const auto 			edge_width{.901f * node_radius};

} // namespace Graph

} // namespace cst

} // namespace Gui


