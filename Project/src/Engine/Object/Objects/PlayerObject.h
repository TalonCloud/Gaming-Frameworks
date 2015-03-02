#ifndef _PLAYER_OBJECT_H
#define _PLAYER_OBJECT_H

#include "../../../Common/Base/Object.h"
#include <iostream>

class PlayerObject : public Object {
        
    private:

        int velocity;
        EntityState state;

    public:
        PlayerObject( const StringID& id, int x, int y, int width, int height ) :
            Object ( id, x, y, height, width ) {
            state = FACING_UP;
            velocity = 8;
        }

        EntityState getState() {
            return state;
        }
        int getVelocity() {
            return velocity;
        }
        void setState(EntityState s) {
            state = s;
        }

        void update() {
            switch(state) {
                case FACING_UP: y += velocity; break;
                case FACING_DOWN: y -= velocity; break;
                case FACING_LEFT: x -= velocity; break;
                case FACING_RIGHT: x += velocity; break;
                default: break;
            }
        }

        void draw() {
            // std::cout << "drawing: " << textures[direction] << std::endl;
            glBindTexture(GL_TEXTURE_2D, textures[state]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            int width;
            int height;

            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

            glBegin(GL_QUADS);
                glTexCoord2d(0, 1);
                glVertex2i( x, y );
                glTexCoord2d(1, 1);
                glVertex2i( x+width, y );
                glTexCoord2d(1, 0);
                glVertex2i( x+width, y+height );
                glTexCoord2d(0, 0);
                glVertex2i( x, y+height );
            glEnd();
        }
};

#endif
