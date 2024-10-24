//
// Created by brain.hu on 2024/9/24.
//

#include "common_jni.h"
#include <locale>
#include <codecvt>

namespace JniListener {
    static JavaVM *jvm = nullptr;

    std::string jstring2string(JNIEnv *jniEnv, jstring jstr) {
        if (jstr == nullptr) {
            return "";
        }
        const char *chars = jniEnv->GetStringUTFChars(jstr, nullptr);
        string ret(chars);
        jniEnv->ReleaseStringUTFChars(jstr, chars);
        return ret;
    }

    jstring string2jstring(JNIEnv *jniEnv, const string &string) {
        const auto emptyu16 = u"";
        auto chars = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>().from_bytes(string);
        auto s = reinterpret_cast<const jchar *>(chars.empty() ? emptyu16 : chars.data());
        return jniEnv->NewString(s, chars.length());
    }

    NativeCallback::NativeCallback(JNIEnv *_jniEnv, jobject _assetManager, jobject _mapCtrlInstance) {

    }

    void NativeCallback::bindJniEnvToThread(JNIEnv *jniEnv) {

    }

    jint NativeCallback::jniOnLoad(JavaVM *javaVM) {
        return 0;
    }

    void NativeCallback::jniOnUnload(JavaVM *javaVM) {

    }
} // NativeCallback