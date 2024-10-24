//
// Created by brain.hu on 2024/10/14.
//

#include <jni.h>
#include <string>
#include "log_util.h"
#include "common_util.h"

extern "C" {

#define FUNC(CLASS, NAME) JNIEXPORT JNICALL Java_com_pursuit_transformlib_jni_ ## CLASS ## _native ## NAME
#define NativeBasicCallLib(NAME) FUNC(BasicCallbackLib, NAME)

// TODO(Basic Scope)
jint NativeBasicCallLib(SampleInt)(JNIEnv *env, jobject obj, jint value) {
    int intValue = value;
    LOGCATI("%s, line=%ld, value=%d", __FUNCTION__, __LINE__, intValue);
    return intValue++;
}

jfloat NativeBasicCallLib(SampleFloat)(JNIEnv *env, jobject obj, jfloat value) {
    float floatValue = value;
    LOGCATI("%s, line=%ld, value=%f", __FUNCTION__, __LINE__, floatValue);
    return floatValue++;
}

jdouble NativeBasicCallLib(SampleDouble)(JNIEnv *env, jobject obj, jdouble value) {
    double doubleValue = value;
    LOGCATI("%s, line=%ld, value=%f", __FUNCTION__, __LINE__, doubleValue);
    return doubleValue++;
}

jlong NativeBasicCallLib(SampleLong)(JNIEnv *env, jobject obj, jlong value) {
    long long longValue = value;
    LOGCATI("%s, line=%ld, value=%ld", __FUNCTION__, __LINE__, longValue);
    return longValue++;
}

jboolean NativeBasicCallLib(SampleBoolean)(JNIEnv *env, jobject obj, jboolean value) {
    bool boolValue = value;
    LOGCATI("%s, line=%ld, value=%d", __FUNCTION__, __LINE__, boolValue);
    return JNI_TRUE;
}

jstring NativeBasicCallLib(SampleString)(JNIEnv *env, jobject obj, jstring value) {
    jstring retStr;
    if (value == nullptr) {
        return retStr;
    }
    const char *chars = env->GetStringUTFChars(value, nullptr);
    std::string ret(chars);
    env->ReleaseStringUTFChars(value, chars);
    LOGCATI("%s, line=%ld, value=%s", __FUNCTION__, __LINE__, ret.c_str());

    std::string extra = "extra data";
    auto tmpStr = std::string(ret + extra);

    retStr = CommonUtil::string2jstring(env, tmpStr);
    return retStr;
}


// TODO(Array Scope)
jbyteArray NativeBasicCallLib(SampleByteArray)(JNIEnv *env, jobject obj, jbyteArray value) {
    if (nullptr == value) {
        return nullptr;
    }
    auto size = env->GetArrayLength(value);
    LOGCATI("%s array size=%ld", __FUNCTION__, size);
    auto *byteArr = env->GetByteArrayElements(value, nullptr);
    for (int i = 0; i < size; ++i) {
        auto element = byteArr[i];
        LOGCATI("element byte2int = %d, hex=%x, HEX=%X", element, element, element);
    }
    env->ReleaseByteArrayElements(value, byteArr, JNI_ABORT);

    // callback new array
    auto jarr = env->NewByteArray(size);
    auto *arr = env->GetByteArrayElements(jarr, nullptr);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    // 对于最后一个参数(如果指针指向的数组为副本时，否则该参数不起作用)
    // 0: 更新数组并释放elems缓冲区
    // JNI_COMMIT: 更新但不释放elems 缓冲区
    // JNI_ABORT: 不作更新但释放elems缓冲区
    env->ReleaseByteArrayElements(jarr, arr, 0);
    return jarr;
}

jintArray NativeBasicCallLib(SampleIntArray)(JNIEnv *env, jobject obj, jintArray value) {
    if (nullptr == value) {
        return nullptr;
    }
    auto size = env->GetArrayLength(value);
    auto *intArr = env->GetIntArrayElements(value, nullptr);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%d", __FUNCTION__, intArr[i]);
    }
    env->ReleaseIntArrayElements(value, intArr, JNI_ABORT);

    auto jarr = env->NewIntArray(size);
    auto *arr = env->GetIntArrayElements(jarr, nullptr);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 2;
    }
    env->ReleaseIntArrayElements(jarr, arr, 0);
    return jarr;
}

jfloatArray NativeBasicCallLib(SampleFloatArray)(JNIEnv *env, jobject obj, jfloatArray value) {
    if (nullptr == value) {
        return nullptr;
    }
    auto *retArr = env->GetFloatArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        LOGCATI("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseFloatArrayElements(value, retArr, JNI_ABORT);

    auto jarr = env->NewFloatArray(size);
    auto *arr = env->GetFloatArrayElements(jarr, nullptr);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 2;
    }
    env->ReleaseFloatArrayElements(jarr, arr, 0);
    return jarr;
}

jdoubleArray NativeBasicCallLib(SampleDoubleArray)(JNIEnv *env, jobject obj, jdoubleArray value) {
    if (nullptr == value) {
        return nullptr;
    }
    auto *retArr = env->GetDoubleArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseDoubleArrayElements(value, retArr, JNI_ABORT);

    auto jarr = env->NewDoubleArray(size);
    auto *arr = env->GetDoubleArrayElements(jarr, nullptr);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 2;
    }
    env->ReleaseDoubleArrayElements(jarr, arr, 0);
    return jarr;
}

jlongArray NativeBasicCallLib(SampleLongArray)(JNIEnv *env, jobject obj, jlongArray value) {
    if (nullptr == value) {
        return nullptr;
    }
    auto *retArr = env->GetLongArrayElements(value, nullptr);
    auto size = env->GetArrayLength(value);
    for (int i = 0; i < size; ++i) {
        ("%s int array element=%f", __FUNCTION__, retArr[i]);
    }
    env->ReleaseLongArrayElements(value, retArr, JNI_ABORT);

    auto jarr = env->NewLongArray(size);
    auto *arr = env->GetLongArrayElements(jarr, nullptr);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 2;
    }
    env->ReleaseLongArrayElements(jarr, arr, 0);
    return jarr;
}

jobjectArray NativeBasicCallLib(SampleObjectArray)(JNIEnv *env, jobject obj) {
    int size = 10;
    // 声明一个对象数组
    jobjectArray result;
    // 找到对象数组中具体的对象类型,[I 指的就是数组类型
    jclass intArrayCls = env->FindClass("[I");

    if (intArrayCls == nullptr) {
        return nullptr;
    }
    // 相当于初始化一个对象数组，用指定的对象类型
    result = env->NewObjectArray(size, intArrayCls, nullptr);

    if (result == nullptr) {
        return nullptr;
    }
    for (int i = 0; i < size; ++i) {
        // 用来给整型数组填充数据的缓冲区
        jint tmp[256];
        // 声明一个整型数组
        jintArray iarr = env->NewIntArray(size);
        if (iarr == nullptr) {
            return nullptr;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        // 给整型数组填充数据
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        // 给对象数组指定位置填充数据，这个数据就是一个一维整型数组
        env->SetObjectArrayElement(result, i, iarr);
        // 释放局部引用
        env->DeleteLocalRef(iarr);
    }
    return result;
}

jobjectArray NativeBasicCallLib(SampleStringArray)(JNIEnv *env, jobject obj, jobjectArray value) {
    if (nullptr == value) {
        return nullptr;
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

    // 创建数组
    jobjectArray resultArr;
    // 声明一个对象数组中具体的对象类型
    auto strObj = env->FindClass("java/lang/String");
    // 初始化一个对象数组，用指定的对象类型
    resultArr = env->NewObjectArray(size, strObj, nullptr);

    if (nullptr == resultArr) return nullptr;

    // 获取/设置数组元素
    for (int i = 0; i < size; ++i) {
        auto index = std::to_string(i);
        //LOGCATE("i=%d, index=%s", i, index.c_str());
        std::string content("element-" + index);
        //LOGCATE("content=%s", content.c_str());
        // 局部变量需要释放内存，如果返回到java层，则无需释放
        jstring jstr = env->NewStringUTF(content.c_str());
        env->SetObjectArrayElement(resultArr, i, jstr);

        env->DeleteLocalRef(jstr);
    }
    //env->DeleteLocalRef(resultArr);
    return resultArr;
}


// TODO(List)
jobject NativeBasicCallLib(SampleStringList)(JNIEnv *env, jobject obj, jobject list) {
    if (nullptr == list) {
        return nullptr;
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

    // callback
    jclass m_arraylist = env->FindClass("java/util/ArrayList");
    jmethodID list_construct = env->GetMethodID(m_arraylist, "<init>", "()V");
    jobject list_obj = env->NewObject(m_arraylist, list_construct);
    jmethodID list_add = env->GetMethodID(m_arraylist, "add", "(Ljava/lang/Object;)Z");

    for (int i = 0; i < len; ++i) {
        auto index = std::to_string(i);
        std::string content("element-" + index);
        jstring element = env->NewStringUTF(content.c_str());
        env->CallBooleanMethod(list_obj, list_add, element);
        env->DeleteLocalRef(element);
    }

    env->DeleteLocalRef(m_arraylist);
    return list_obj;
}

}