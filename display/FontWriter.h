#include <map>
#include <math.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../prim/vec3f.h"
#include "/usr/local/sdl-1.3/include/SDL/SDL.h"

#include "../util/ShaderHandle.h"

#include "Obj.h"

//#include "../defines.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_projection.hpp"
#include "../glm/gtx/type_ptr.hpp"
#include "../glm/GLM_GTX_transform.h"

#ifndef FONTWRITER
#define FONTWRITER
class FontWriter {
	public:
		class Text {
			public:
				Text(std::string textIn, short rgbIn[3], vec3f posIn, vec3f rotIn, float sizeIn);
				std::string text;
				short rgb[3];
				vec3f pos;
				vec3f rot;
				float size;
		};

		static void initFontWriter();
		static void setText(std::string key, std::string text, short rgb[3], vec3f pos, vec3f rot, float size);
		static void writeOnce(std::string key, std::string text, short rgb[3], vec3f pos, vec3f rot, float size);
		static void remove(std::string key);
		static void render();

	private:
		static Obj *chars[95];
		static std::map<std::string, Text> text;
		static std::map<std::string, Text> tmpText;
	

};
#endif 
