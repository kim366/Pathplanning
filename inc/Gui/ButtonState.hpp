#ifndef GUI_BUTTON_STATE
#define GUI_BUTTON_STATE

namespace Gui
{

namespace Button
{

namespace State
{

enum class Mouse
{
	NoAction,
	Pressed,
	Held,
	Clicked,
	Dragged,
	DragReleased
};

enum class Keyboard : bool
{
	NotPressed,
	Pressed
};

} // namespace State

enum class RawState
{
	Released,
	Pressed,
	PressedThisFrame,
	ReleasedThisFrame
};

} // namespace Button

} // namespace Gui

#endif // GUI_BUTTON_STATE