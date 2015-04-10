#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#if __APPLE__ 
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Common/Base/Command.h"
#include "../../Common/Base/Singleton.h"
#include "../../Common/Base/Table.h"
#include "../../Common/Base/Types.h"
#include "../../Common/Resources/Constants.h"

#include "../../Engine/Input/InputController.h"
#include "../../Engine/Object/ObjectController.h"
#include "../../Engine/Render/RenderController.h"

#include <time.h>
#include <iostream>

class GameController : public Singleton< GameController >{

    private:

        friend class Singleton< GameController >;
        static AudioController & audio_controller;
        static InputController & input_controller;
        static ObjectController & object_controller;
        static RenderController & render_controller;
        static GameController & game_controller;

        int score;
        int player_health;
        time_t lastTime;
        int numFrames;
        int fps;

        Table< InputAction > input_action_table;

        GameController() {
            fps = 0;
            player_health = 100;
            score = 0;
        }

        static void keyboardInputCallback(unsigned char key, int x, int y) {
            input_controller.queueKeyboardEvent(key, x, y);
        }

        static void keyboardUpInputCallback(unsigned char key, int x, int y) {
            input_controller.dequeueKeyboardEvent(key, x, y);
        }

        static void mouseInputCallback(int button, int state, int x, int y) {
            input_controller.queueMouseEvent(button, state, x, y);
        }

        static void updateTimerCallback(int val) {
            game_controller.updateGameLoop(val);
        }

        static void renderDisplayCallback();

        static void reshapeCallback(int width, int height);

    public:
        
        void runCommand( String line );
        void runCommandFile( String filename );
        Command * parseCommand( StringStream & tokens );

        void handleInputEvent( const StringID& id );
        void registerInputAction( const StringID& id, const InputAction action );
        void registerValue( const StringID& id, String val );

        void setupGameLoop(int argc, char **argv);
        void updateGameLoop(int val);
        void runGameLoop();
};

#endif
