#ifndef GUI_BUTTON_STATE
#define GUI_BUTTON_STATE

namespace Gui
{

namespace Button
{

enum class State
{
	NotPressed,
	Clicked,
	Dragged
};

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