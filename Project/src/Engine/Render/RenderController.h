#ifndef _RENDER_CONTROLLER_H
#define _RENDER_CONTROLLER_H

#if __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Common/Base/Singleton.h"
#include "../../Common/Base/Table.h"
#include "../../Common/Base/Types.h"
#include "Image.h"

#include <iostream>

class RenderController:
	
	public Singleton< RenderController > {

	private:

		friend class Singleton< RenderController >;
		Table< GLuint > texture_paths;

		RenderController() {

		}

        Image* loadBMP(const char* filename);
	
	public:

		void registerObjectTexture( StringID, String );
		GLuint getTextureID( StringID );

		void prepareScreen( int x, int y, String name );
};

#endif
