g++ -std=c++11 -Wall -Wno-deprecated -o test.exe ../Engine/Input/InputController.cpp ../Engine/Object/ObjectController.cpp ../Engine/Game/GameController.cpp ../Engine/Render/RenderController.cpp Test.cpp ../Engine/Audio/AudioController.h -llibOpenAL32.dll.a -lfreeglut.dll -I C:/local/boost_1_56_0/ -I ../../include -L ../../lib
pause

clang++ -std=c++11 -Wall -Wno-deprecated ../Engine/Input/InputController.cpp ../Engine/Object/ObjectController.cpp ../Engine/Game/GameController.cpp ../Engine/Render/RenderController.cpp Test.cpp ../Engine/Audio/AudioController.h -o test.exe  -llibOpenAL32.dll.a -lfreeglut.dll -I ../../include -L ../../lib
