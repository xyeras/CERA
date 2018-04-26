#ifndef FONTS_H
#define FONTS_H
#include<string.h>
#include<iostream>

using namespace std;

typedef struct
{
  char letter;                 // optional
  float xmin,xmax,ymin,ymax;   // texture coord
  float offset;
  float fontSize;
}charSet;

class Fonts
{
    public:
        Fonts();
        virtual ~Fonts();

        void initFonts(char*);
        void buildFont(char*);
        void drawFont(int);
        charSet C[1024];
        int cCnt;

        float xpos;
        float ypos;
        float zpos;

        float zoom;

    protected:

    private:
};

#endif // FONTS_H
