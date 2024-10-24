//
// Created by brain.hu on 2024/9/24.
//

#ifndef NATIVE_SAMPLE_COMMON_JNI_H
#define NATIVE_SAMPLE_COMMON_JNI_H

#include "jni.h"
#include <string>
#include <android/asset_manager.h>

using namespace std;

namespace JniListener {
    std::string jstring2string(JNIEnv *jniEnv, jstring jstr);

    jstring string2jstring(JNIEnv *jniEnv, const string &string);

    class NativeCallback {
        NativeCallback(JNIEnv *_jniEnv, jobject _assetManager, jobject _mapCtrlInstance);

        ~NativeCallback();

    public:

        static void bindJniEnvToThread(JNIEnv *jniEnv);

        static jint jniOnLoad(JavaVM *javaVM);

        static void jniOnUnload(JavaVM *javaVM);
    };

} // NativeCallback

#endif //NATIVE_SAMPLE_COMMON_JNI_H
