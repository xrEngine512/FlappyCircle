//
// Created by bozie on 12.02.2016.
//
#include "islam_test_NativeGameWrapper.h"
#include "GameExport.h"
#include "AndroidGLESViewport.h"
#include <jni.h>
#include <android/native_window_jni.h>
#include <atomic>

#include "log.h"

#define LOG_TAG "Wrapper"

ANativeWindow               *window = nullptr;
AndroidGLESViewport         *viewport = nullptr;
std::atomic_bool 	        render(false);

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_SetSurface
        (JNIEnv *env, jclass, jobject surface)
{
    if (surface != 0) {
        window = ANativeWindow_fromSurface(env, surface);
        //LOG_INFO("Got window %p", window);
        if(viewport)
            delete viewport;

        viewport = new AndroidGLESViewport(window);
    } else {
        //LOG_INFO("Releasing window");
        ANativeWindow_release(window);
    }
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Start
        (JNIEnv *, jclass)
{
    GameExport::Start();
    render = true;
    while (render.load())
    {
        GameExport::Render();
        viewport->SwapBuffers();
    }
    ANativeWindow_release(window);
    delete viewport;
    viewport = nullptr;
    LOG_INFO("End of render loop");
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Stop
        (JNIEnv *, jclass)
{
    render.store(false);
    GameExport::Stop();
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Press
        (JNIEnv *, jclass)
{
    GameExport::Press();
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Play
        (JNIEnv *, jclass)
{
    GameExport::Play();
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Pause
        (JNIEnv *, jclass)
{
    GameExport::Pause();
}

JNIEXPORT void JNICALL Java_islam_test_NativeGameWrapper_Release
        (JNIEnv *, jclass)
{
    GameExport::Release();
}

JNIEXPORT jboolean JNICALL Java_islam_test_NativeGameWrapper_IsOver
        (JNIEnv *, jclass)
{
    return GameExport::IsOver();
}
