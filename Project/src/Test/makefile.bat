g++ -std=c++11 -Wall -Wno-deprecated -o test.exe ../Engine/Input/InputController.cpp ../Engine/Object/ObjectController.cpp ../Engine/Game/GameController.cpp ../Engine/Render/RenderController.cpp ../Engine/Audio/AudioController.cpp Test.cpp -I ../../include -L ../../lib -lopengl32 -lglu32 -llibOpenAL32 -lfreeglut
pause