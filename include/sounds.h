#ifndef SOUNDS_H
#define SOUNDS_H

#include <SNDS/irrKlang.h>
#pragma comment(lib,"irrKlang.lib") // link your dll to the program

using namespace irrklang;

class sounds
{
    public:
        sounds();
        virtual ~sounds();
        void playMusic(char *);
        void Plays(char *);
        void stopAllSounds();
        int initSounds();

    protected:

    private:
};

#endif // SOUNDS_H
