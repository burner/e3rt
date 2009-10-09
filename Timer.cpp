#include "Timer.h"
std::map<std::string, Uint32> Timer::times;
Uint32 Timer::createTimer(std::string name) {
	Uint32 now = SDL_GetTicks(); 
	Timer::times.insert(std::make_pair(name, now));
	return now;
}

Uint32 Timer::read(std::string name) {
	return SDL_GetTicks() - Timer::times[name];
}

Uint32 Timer::reset(std::string name) {
	Uint32 now = SDL_GetTicks();
	Uint32 time = now - Timer::times[name];
	Timer::times[name] = now;
	return time;
}

Uint32 Timer::remove(std::string name) {
	Uint32 time = SDL_GetTicks() - Timer::times[name];
	Timer::times.erase(name);
	return time;
}
