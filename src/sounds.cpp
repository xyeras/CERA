#include <iostream>
#include "sounds.h"
using namespace std;

ISoundEngine* engine = createIrrKlangDevice();

sounds::sounds()
{
    //ctor
}

sounds::~sounds()
{
    //dtor
    engine->drop();
}

void sounds::playMusic(char* File)
{
    engine->play2D(File,true);
}

void sounds::Plays(char* File)
{
    engine->play2D(File,false,false);
}

void sounds::stopAllSounds()
{

}

int sounds::initSounds()
{
    if(!engine)
    {
        cout << "Could not Start the engine" << endl;
        return 0;
    }
    return 1;
}
