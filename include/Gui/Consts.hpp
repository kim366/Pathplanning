#pragma once

#include <SFML/System/String.hpp>

namespace Gui
{

namespace cst
{

namespace Window
{

const sf::String 	title{"Pathplanning"};
const auto 			size{951u};

} // namespace Window

namespace Input
{

const auto			threshold_drag{10u}; // in px; hypot threshold until a held button is considerered a drag

} // namespace Input

namespace Graph
{

} // namespace Graph

} // namespace cst

} // namespace Gui


