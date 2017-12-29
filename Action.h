#pragma once
#include <functional>
#include <SDL.h>

class Action {
private:
	std::function <void(SDL_Event&)> function;
public:
	/*template <typename T>
	static Action bind(T *object, void(T::*mf)(SDL_Event& event)) {
		return new Action(object, mf);
	}*/
	void execute(SDL_Event& event) {
		function(event);
	}

	template <typename T>
	Action(T *object, void(T::*mf)(SDL_Event&)) { function = std::bind(mf, object, std::placeholders::_1); };
	~Action();
};

