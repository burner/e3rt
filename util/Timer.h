#include <map>
#include <string>
#include "/usr/local/sdl-1.3/include/SDL/SDL.h"
#ifndef TIMER
#define TIMER
class Timer {
	private:
		static std::map<std::string, Uint32> times;
		
	public:
		static Uint32 createTimer(std::string name);
		static Uint32 read(std::string name);
		static Uint32 reset(std::string name);
		static Uint32 remove(std::string name);
};
#endif
