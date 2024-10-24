#include <jni.h>
#include <string>
#include "common_jni.h"
#include "log_util.h"

using namespace JniListener;

extern "C" {

/*JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGCATE("%s, line=%d", __FUNCTION__, __LINE__);
    return NativeCallback::jniOnLoad(vm);
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGCATE("%s, line=%d", __FUNCTION__, __LINE__);
    NativeCallback::jniOnUnload(vm);
}*/

#define FUNC(CLASS, NAME) JNIEXPORT JNICALL Java_com_pursuit_transformlib_ ## CLASS ## _native ## NAME
#define NativeLib(NAME) FUNC(NativeLib, NAME)



}
extern "C" JNIEXPORT jstring JNICALL
Java_com_pursuit_transformlib_NativeLib_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}