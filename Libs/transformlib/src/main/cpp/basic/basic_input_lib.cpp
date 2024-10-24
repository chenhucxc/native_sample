//
// Created by brain.hu on 2024/10/14.
//
#include <jni.h>
#include "log_util.h"
#include <string>

extern "C" {

#define FUNC(CLASS, NAME) JNIEXPORT JNICALL Java_com_pursuit_transformlib_jni_ ## CLASS ## _native ## NAME
#define NativeBasicLib(NAME) FUNC(BasicInputLib, NAME)

// TODO(Basic Scope)
void NativeBasicLib(SampleInt)(JNIEnv *env, jobject obj, jint value) {
    int intValue = value;
    LOGCATI("%s, line=%ld, value=%d", __FUNCTION__, __LINE__, intValue);
}

void NativeBasicLib(SampleFloat)(JNIEnv *env, jobject obj, jfloat value) {
    float floatValue = value;
    LOGCATI("%s, line=%ld, value=%f", __FUNCTION__, __LINE__, floatValue);
}

void NativeBasicLib(SampleDouble)(JNIEnv *env, jobject obj, jdouble value) {
    double doubleValue = value;
    LOGCATI("%s, line=%ld, value=%f", __FUNCTION__, __LINE__, doubleValue);
}

void NativeBasicLib(SampleLong)(JNIEnv *env, jobject obj, jlong value) {
    long long longValue = value;
    LOGCATI("%s, line=%ld, value=%ld", __FUNCTION__, __LINE__, longValue);
}

void NativeBasicLib(SampleBoolean)(JNIEnv *env, jobject obj, jboolean value) {
    bool boolValue = value;
    LOGCATI("%s, line=%ld, value=%d", __FUNCTION__, __LINE__, boolValue);
}

void NativeBasicLib(SampleString)(JNIEnv *env, jobject obj, jstring value) {
    if (value == nullptr) {
        return;
    }
    const char *chars = env->GetStringUTFChars(value, nullptr);
    std::string ret(chars);
    env->ReleaseStringUTFChars(value, chars);
    LOGCATI("%s, line=%ld, value=%s", __FUNCTION__, __LINE__, ret.c_str());
}


// TODO(Array Scope)
void NativeBasicLib(SampleByteArray)(JNIEnv *env, jobject obj, jbyteArray value) {
    if (nullptr == value) {
        return;
    }
    auto size = env->GetArrayLength(value);
    LOGCATI("%s array size=%ld", __FUNCTION__, size);
    auto *byteArr = env->GetByteArrayElements(value, nullptr);
    for (int i = 0; i < size; ++i) {
        auto element = byteArr[i];
        LOGCATI("element byte2int = %d, hex=%x, HEX=%X", element, element, element);
    }

    env->ReleaseByteArrayElements(value, byteArr, JNI_ABORT);
}

void NativeBasicLib(SampleIntArray)(JNIEnv *env, jobject obj, jintArray value) {
    if (nullptr == value) {
        return;
    }
    auto size = env->GetArrayLength(value);
    auto *intArr = env->GetIntArrayElements(value, nullptr);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%d", __FUNCTION__, intArr[i]);
    }
    env->ReleaseIntArrayElements(value, intArr, JNI_ABORT);
}

void NativeBasicLib(SampleFloatArray)(JNIEnv *env, jobject obj, jfloatArray value) {
    if (nullptr == value) {
        return;
    }
    auto *retArr = env->GetFloatArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseFloatArrayElements(value, retArr, JNI_ABORT);
}

void NativeBasicLib(SampleDoubleArray)(JNIEnv *env, jobject obj, jdoubleArray value) {
    if (nullptr == value) {
        return;
    }
    auto *retArr = env->GetDoubleArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseDoubleArrayElements(value, retArr, JNI_ABORT);
}

void NativeBasicLib(SampleLongArray)(JNIEnv *env, jobject obj, jlongArray value) {
    if (nullptr == value) {
        return;
    }
    auto *retArr = env->GetLongArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseLongArrayElements(value, retArr, JNI_ABORT);
}

void NativeBasicLib(SampleStringArray)(JNIEnv *env, jobject obj, jobjectArray value) {
    if (nullptr == value) {
        return;
    }
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        // GetObjectArrayElement 不需要释放，但需要移除引用
        auto elementObj = env->GetObjectArrayElement(value, i);
        auto jstr = (jstring) elementObj;
        jboolean isCopy;
        auto retStr = env->GetStringUTFChars(jstr, &isCopy);
        LOGCATI("%s, line=%ld, value=%s", __FUNCTION__, __LINE__, retStr);
        env->ReleaseStringUTFChars(jstr, retStr);
        env->DeleteLocalRef(elementObj);
    }
}


// TODO(List)
void NativeBasicLib(SampleStringList)(JNIEnv *env, jobject obj, jobject list) {
    if (nullptr == list) {
        return;
    }
    jclass listClazz = env->GetObjectClass(list);
    jmethodID listGet = env->GetMethodID(listClazz, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(listClazz, "size", "()I");

    jint len = env->CallIntMethod(list, listSize);

    std::vector<std::string> retList;
    for (int i = 0; i < len; ++i) {
        jobject itemObj = env->CallObjectMethod(list, listGet, i);

        if (nullptr == itemObj) {
            env->DeleteLocalRef(itemObj);
            continue;
        }

        auto jstr = (jstring) itemObj;
        jboolean isCopy;
        auto retStr = env->GetStringUTFChars(jstr, &isCopy);
        LOGCATI("%s, line=%ld, value=%s", __FUNCTION__, __LINE__, retStr);
        env->ReleaseStringUTFChars(jstr, retStr);

        env->DeleteLocalRef(itemObj);
    }
    env->DeleteLocalRef(listClazz);
}


}