//
// Created by bozie on 12.02.2016.
//

#include "GLES2/gl2.h"
#include "AndroidGLESViewport.h"
#include "log.h"
#include <android/native_window.h>

#define LOG_TAG "AndroidGLESViewport"

AndroidGLESViewport::AndroidGLESViewport(ANativeWindow * window):
_window(window)
{
    init();
}

AndroidGLESViewport::~AndroidGLESViewport()
{
    destroy();
}

void AndroidGLESViewport::SwapBuffers()
{
    if (!eglSwapBuffers(_display, _surface)) {
        LOG_ERROR("eglSwapBuffers() returned error %d", eglGetError());
    }
}

bool AndroidGLESViewport::init()
{
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
    };
    EGLDisplay display;
    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;
    EGLint width;
    EGLint height;



    LOG_INFO("Initializing context");

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        LOG_ERROR("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());
        destroy();
        return false;
    }

    ANativeWindow_setBuffersGeometry(_window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, _window, 0))) {
        LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());
        destroy();
        return false;
    }

    static const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    if (!(context = eglCreateContext(display, config, 0, contextAttribs))) {
        LOG_ERROR("eglCreateContext() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglMakeCurrent(display, surface, surface, context)) {
        LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return false;
    }

    _display = display;
    _surface = surface;
    _context = context;


    glClearColor(0, 0, 0, 0);

    glViewport(0, 0, width, height);

    return true;
}

void AndroidGLESViewport::destroy()
{
    LOG_INFO("Destroying context");

    eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(_display, _context);
    eglDestroySurface(_display, _surface);
    eglTerminate(_display);

    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
}