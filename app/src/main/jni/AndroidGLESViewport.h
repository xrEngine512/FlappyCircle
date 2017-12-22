//
// Created by bozie on 12.02.2016.
//

#ifndef TEST_ANDROIDGLESVIEWPORT_H
#define TEST_ANDROIDGLESVIEWPORT_H

#include <EGL/egl.h>

class ANativeWindow;

class AndroidGLESViewport {
public:
    AndroidGLESViewport(ANativeWindow * window);
    ~AndroidGLESViewport();

    void SwapBuffers();
private:
    ANativeWindow*      _window;
    EGLDisplay          _display;
    EGLSurface          _surface;
    EGLContext          _context;

    bool init();
    void destroy();
};


#endif //TEST_ANDROIDGLESVIEWPORT_H
