#pragma once

#include <utility>
#include <memory>
#include <optional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Gui/RawInputs.hpp>

namespace Gui
{

class RawInputReceiver
{
public:
	void		receiveInput(std::unique_ptr<sf::RenderWindow>& window_);
	const auto&	getInputs() { return _raw_inputs; }
	bool		shouldWindowClose() { return _should_window_close; }

private:
	RawInputs	_raw_inputs;
	bool		_should_window_close{false};
	
};

} // namespace Gui


