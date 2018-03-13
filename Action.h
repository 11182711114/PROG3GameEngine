#ifndef ACTION_H
#define ACTION_H
#include <functional>
#include <SDL.h>
#include <vector>

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

class KeyAction {
private:
	std::function <void(const Uint8*)> function;
	
public:
	/*template <typename T>
	static Action bind(T *object, void(T::*mf)(SDL_Event& event)) {
	return new Action(object, mf);
	}*/
	void execute(const Uint8* state) {
		function(state);
	}

	template <typename T>
	KeyAction(T *object, void(T::*mf)(const Uint8*)) { 
		function = std::bind(mf, object, std::placeholders::_1); 
	};
	~KeyAction();
};

#endif