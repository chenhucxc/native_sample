//
// Created by brain.hu on 2024/10/14.
//

#ifndef NATIVE_SAMPLE_COMMON_UTIL_H
#define NATIVE_SAMPLE_COMMON_UTIL_H

#include <jni.h>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

namespace CommonUtil {
    static string jstring2string(JNIEnv *env, jstring jstr) {
        if (jstr == nullptr) {
            return "";
        }
        const char *chars = env->GetStringUTFChars(jstr, nullptr);
        string ret(chars);
        env->ReleaseStringUTFChars(jstr, chars);
        return ret;
    }

    static jstring string2jstring(JNIEnv *env, const string &string) {
        const auto emptyu16 = u"";
        auto chars = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>().from_bytes(string);
        auto s = reinterpret_cast<const jchar *>(chars.empty() ? emptyu16 : chars.data());
        return env->NewString(s, chars.length());
    }

    static long getCurrentMs() {
        struct timespec res{};
        clock_gettime(CLOCK_REALTIME, &res);
        return 1000 * res.tv_sec + res.tv_nsec / 1e6;
    }

    static long long GetSysCurrentTime() {
        struct timeval time{};
        gettimeofday(&time, nullptr);
        long long curTime = ((long long) (time.tv_sec)) * 1000 + time.tv_usec / 1000;
        return curTime;
    }
}


#endif //NATIVE_SAMPLE_COMMON_UTIL_H
