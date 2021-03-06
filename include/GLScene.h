#ifndef GLSCENE_H
#define GLSCENE_H

#include<windows.h>

#include<GL/glut.h>
#include<iostream>

using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        void resizeGLScene(GLsizei, GLsizei);
        void resetData();                       //reset number of lives, health, etc.
        void callLevelChanger(int);
        int windMsg(HWND,UINT,WPARAM,LPARAM);

        WPARAM wParam;
        float screenHeight;
        float screenWidth;

        int ActiveScene;
        int pausedScene;
        int returnScene;
        bool paused = false;


    protected:

    private:
};

#endif // GLSCENE_H
