#include <Gui/Core.hpp>
#include <Args.hpp>

int main(int argc, char const *argv[])
{
	Gui::Core({argc, argv}).loop();
}
