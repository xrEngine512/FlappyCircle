LOCAL_PATH := $(call my-dir)
CPP_FILES := $(wildcard C:/Users/bozie/AndroidStudioProjects/Test/app/src/main/jni/Game/src/*.cpp)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := C:/Users/bozie/AndroidStudioProjects/Test/app/src/main/jni/Game/include
LOCAL_C_INCLUDES += ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_MODULE := GameLib
LOCAL_SRC_FILES := $(CPP_FILES) islam_test_NativeGameWrapper.cpp AndroidGLESViewport.cpp
LOCAL_LDLIBS := -lGLESv2
LOCAL_LDLIBS += -lEGL
LOCAL_LDLIBS += -landroid
LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)
