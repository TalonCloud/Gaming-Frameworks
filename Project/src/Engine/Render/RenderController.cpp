#include "RenderController.h"

void RenderController::registerObjectTexture( StringID id, String path ) {
    Image* image = loadBMP(path.c_str());
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture

    glTexImage2D(GL_TEXTURE_2D,                 //Always GL_TEXTURE_2D
                 0,                             //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,   //Width and height
                 0,                             //The border of the image
                 GL_RGB,                        //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,              //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
                 image->pixels);                //The actual pixel data

    delete image;

	texture_paths.add( id, textureId );
	//Load texture into opengl.
}

GLuint RenderController::getTextureID( StringID id ) {
    GLuint ret = -1;
    if(texture_paths.has(id)) {
        ret = texture_paths.get(id).getValue();
    }
    return ret;
}

void RenderController::prepareScreen( int x, int y, String name ) {
	glutInitWindowSize(x, y);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(name.c_str());
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
}

Image* RenderController::loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    input.ignore(10);

    char buffer[4];
    input.read(buffer, 4);
    int dataOffset = (int)(((unsigned char)buffer[3] << 24) |
                          ((unsigned char)buffer[2] << 16) |
                          ((unsigned char)buffer[1] << 8) |
                          (unsigned char)buffer[0]);
    
    //Read the header
    input.read(buffer, 4);
    int headerSize = (int)(((unsigned char)buffer[3] << 24) |
                          ((unsigned char)buffer[2] << 16) |
                          ((unsigned char)buffer[1] << 8) |
                          (unsigned char)buffer[0]);

    int width;
    int height;
    // std::cout << headerSize << std::endl;
    if( headerSize != 40 ) {
        assert(!"Need BITMAPV3INFOHEADER. (56 bit header)");
    }
    input.read(buffer, 4);
    width = (int)(((unsigned char)buffer[3] << 24) |
            ((unsigned char)buffer[2] << 16) |
            ((unsigned char)buffer[1] << 8) |
            (unsigned char)buffer[0]);
    input.read(buffer, 4);
    height = (int)(((unsigned char)buffer[3] << 24) |
            ((unsigned char)buffer[2] << 16) |
            ((unsigned char)buffer[1] << 8) |
            (unsigned char)buffer[0]);
    input.ignore(6);

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
