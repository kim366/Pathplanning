#pragma once

template <typename T>
class Key
{
	friend T;
	Key() {}; // must not be `= default`
	Key(Key const&) {};
};
