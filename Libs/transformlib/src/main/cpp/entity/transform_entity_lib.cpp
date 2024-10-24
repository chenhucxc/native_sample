//
// Created by brain.hu on 2024/10/16.
//

#include "jni.h"
#include "log_util.h"
#include "common_util.h"

extern "C" {

#define FUNC(CLASS, NAME) JNIEXPORT JNICALL Java_com_pursuit_transformlib_jni_ ## CLASS ## _native ## NAME
#define NativeEntityLib(NAME) FUNC(TransformEntityLib, NAME)

void NativeEntityLib(SetLocationInfo)(JNIEnv *env, jobject obj, jobject location_info) {
    auto locationInfoCls = env->GetObjectClass(location_info);
    if (nullptr == location_info) return;

    auto idFieldID = env->GetFieldID(locationInfoCls, "id", "I");
    auto xPosFieldID = env->GetFieldID(locationInfoCls, "x", "F");
    // TODO(这里的类型为什么是Ljava/lang/Float; 而不是F -> 这是因为kotlin中可空基础类型的变量是封装类)
    auto zPosFieldID = env->GetFieldID(locationInfoCls, "z", "Ljava/lang/Float;");
    auto latitudeFieldID = env->GetFieldID(locationInfoCls, "latitude", "D");
    auto addressFieldID = env->GetFieldID(locationInfoCls, "address", "Ljava/lang/String;");
    auto poiListFieldID = env->GetFieldID(locationInfoCls, "poiList", "Ljava/util/List;");
    auto isPositionedFieldID = env->GetFieldID(locationInfoCls, "isPositioned", "Z");
    auto isDefaultFieldID = env->GetFieldID(locationInfoCls, "isDefault", "Ljava/lang/Boolean;");

    auto id = env->GetIntField(location_info, idFieldID);
    auto xPos = env->GetFloatField(location_info, xPosFieldID);
    auto latitude = env->GetDoubleField(location_info, latitudeFieldID);
    auto isPositioned = env->GetBooleanField(location_info, isPositionedFieldID);
    LOGCATE("%s, line=%ld, id=%d, xPos=%f, latitude=%f, isPositioned=%d", __FUNCTION__, __LINE__, id, xPos, latitude, isPositioned);

    // 基础类型的封装类型转换需要额外处理，int、double这些的封装类处理类似
    auto zPosObj = env->GetObjectField(location_info, zPosFieldID);
    auto floatClz = env->FindClass("java/lang/Float");
    auto floatMethodID = env->GetMethodID(floatClz, "floatValue", "()F");
    auto zPos = env->CallFloatMethod(zPosObj, floatMethodID);
    LOGCATE("%s, line=%ld, zPos=%f", __FUNCTION__, __LINE__, zPos);
    env->DeleteLocalRef(floatClz);

    // list 的处理
    auto list_obj = env->GetObjectField(location_info, poiListFieldID);
    jclass listClazz = env->GetObjectClass(list_obj);
    jmethodID listGet = env->GetMethodID(listClazz, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(listClazz, "size", "()I");
    jint len = env->CallIntMethod(list_obj, listSize);
    for (int i = 0; i < len; ++i) {
        auto tileObj = env->CallObjectMethod(list_obj, listGet, i);
        auto poiElement = (jstring) tileObj; // TODO(如果这里是其他类型呢？？？)
        auto poi = CommonUtil::jstring2string(env, poiElement);
        LOGCATE("%s, line=%ld, poiElement=%s", __FUNCTION__, __LINE__, poi.c_str());
    }

    // string 类型处理不同于基础类型的封装类
    auto addressObj = env->GetObjectField(location_info, addressFieldID);
    auto jstr_address = (jstring) addressObj;
    auto address = env->GetStringUTFChars(jstr_address, nullptr);
    LOGCATE("%s, line=%ld, address=%s", __FUNCTION__, __LINE__, address);
    env->ReleaseStringUTFChars(jstr_address, address);
}

jobject NativeEntityLib(GetLocationInfo)(JNIEnv *env, jobject obj) {

    jint id = 11;
    jfloat xPos = 0.1f;
    jfloat yPos = 0.2f;
    jfloat zPos = 0.3f;
    jdouble lat = 0.22;
    jdouble lon = 0.33;
    jstring address = CommonUtil::string2jstring(env, "city:Shanghai");
    jboolean isPositioned = JNI_TRUE;
    jboolean isDefault = JNI_FALSE;

    // zPos 封装类处理
    auto floatClz = env->FindClass("java/lang/Float");
    auto floatConstruct = env->GetMethodID(floatClz, "<init>", "(F)V");
    auto zPosFloat = env->NewObject(floatClz, floatConstruct, zPos);

    // list
    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_construct = env->GetMethodID(list_cls, "<init>", "()V");
    jmethodID list_add = env->GetMethodID(list_cls, "add", "(Ljava/lang/Object;)Z");

    // poiList 数据处理
    auto poiList = env->NewObject(list_cls, list_construct);
    auto poiClazz = env->FindClass("java/lang/String");
    auto poiConstruct = env->GetMethodID(poiClazz, "<init>", "(Ljava/lang/String;)V");
    for (int i = 0; i < 5; ++i) {
        std::string elementStr("poi_element" + i);
        auto jstrPoi = CommonUtil::string2jstring(env, elementStr);
        auto poiElement = env->NewObject(poiClazz, poiConstruct, jstrPoi);
        env->CallBooleanMethod(poiList, list_add, poiElement);

        env->DeleteLocalRef(poiElement);
    }

    // isDefault
    auto booleanClz = env->FindClass("java/lang/Boolean");
    auto booleanConstruct = env->GetMethodID(booleanClz, "<init>", "(Z)V");
    auto isDefaultBoolean = env->NewObject(booleanClz, booleanConstruct, isDefault);

    // 最后的数据拼接
    auto locationClazz = env->FindClass("com/pursuit/transformlib/entities/LocationInfoBean");
    auto locationConstruct = env->GetMethodID(locationClazz, "<init>",
                                              "(IFFLjava/lang/Float;DDLjava/lang/String;Ljava/util/List;ZLjava/lang/Boolean;)V");
    auto jLocationObj = env->NewObject(locationClazz, locationConstruct, id, xPos, yPos, zPosFloat,
                                       lat, lon, address, poiList, isPositioned, isDefaultBoolean);

    // 资源释放
    env->DeleteLocalRef(locationClazz);
    env->DeleteLocalRef(floatClz);
    env->DeleteLocalRef(list_cls);
    env->DeleteLocalRef(poiList);
    env->DeleteLocalRef(booleanClz);

    return jLocationObj;
}

void NativeEntityLib(SetLocationList)(JNIEnv *env, jobject obj, jobject location_list) {

    jclass listClazz = env->GetObjectClass(location_list);
    jmethodID listGet = env->GetMethodID(listClazz, "get", "(I)Ljava/lang/Object;");
    jmethodID listSize = env->GetMethodID(listClazz, "size", "()I");
    jint size = env->CallIntMethod(location_list, listSize);

    for (int i = 0; i < size; ++i) {
        jobject location_info = env->CallObjectMethod(location_list, listGet, i);
        auto locationInfoCls = env->GetObjectClass(location_info);
        if (nullptr == location_info) return;
        // 此处的处理方式与上述的SetLocationInfo一致，不再重复
        auto idFieldID = env->GetFieldID(locationInfoCls, "id", "I");
        auto id = env->GetIntField(location_info, idFieldID);
        LOGCATI("id=%d", i);
        // 。。。。。
    }
    // TODO(上面循环读取出的值可以用一个vector来接收，这里就不再写出来了)
}

jobject NativeEntityLib(GetLocationList)(JNIEnv *env, jobject obj) {

    jclass listClazz = env->FindClass("java/util/ArrayList");
    jmethodID listConstruct = env->GetMethodID(listClazz, "<init>", "()V");
    jmethodID listAdd = env->GetMethodID(listClazz, "add", "(Ljava/lang/Object;)Z");

    jclass locationInfoCls = env->FindClass("com/pursuit/transformlib/entities/LocationInfoBean");
    jmethodID locationInfoConstruct = env->GetMethodID(locationInfoCls, "<init>", "(IFF)V");

    jobject locationInfoList = env->NewObject(listClazz, listConstruct);
    for (int i = 0; i < 3; ++i) {
        // 写法与上面的GetLocationInfo一样，因而示例只写几个属性
        jint id = 2 * i;
        jfloat xPos = i + i * 3.0f;
        jfloat yPos = 0.2f * i;
        jobject tileBean = env->NewObject(locationInfoCls, locationInfoConstruct, id, xPos, yPos);
        env->CallBooleanMethod(locationInfoList, listAdd, tileBean);
        env->DeleteLocalRef(tileBean);
    }

    env->DeleteLocalRef(listClazz);
    env->DeleteLocalRef(locationInfoCls);

    return locationInfoList;
}


// 嵌套类的处理示例
void NativeEntityLib(SetNestingInfo)(JNIEnv *env, jobject obj, jobject nesting_info) {
    auto nestingInfoCls = env->GetObjectClass(nesting_info);
    if (nullptr == nestingInfoCls) return;

    auto idFieldID = env->GetFieldID(nestingInfoCls, "id", "I");
    auto descFieldId = env->GetFieldID(nestingInfoCls, "desc", "Ljava/lang/String;");
    auto intArrField = env->GetFieldID(nestingInfoCls, "intArr", "[I");
    auto selectedCarField = env->GetFieldID(nestingInfoCls, "selectedCar", "Lcom/pursuit/transformlib/entities/EvCarBean;");
    auto remainCarsField = env->GetFieldID(nestingInfoCls, "remainCars", "Ljava/util/List;");

    jint id = env->GetIntField(nesting_info, idFieldID);
    auto desc = (jstring) env->GetObjectField(nesting_info, descFieldId);

    // 处理基本类型的数组，其他基本类型写法类似，具体可参照 basic_input_lib.cpp 中的写法
    auto intArr = (jintArray) env->GetObjectField(nesting_info, intArrField);
    auto retIntArr = env->GetIntArrayElements(intArr, nullptr);
    int arraySize = env->GetArrayLength(intArr);
    LOGCATI("intArr size = %d", arraySize);
    for (int i = 0; i < arraySize; ++i) {
        auto element = retIntArr[i];
    }
    // 使用完毕后需要释放
    env->ReleaseIntArrayElements(intArr, retIntArr, 0);

    // 嵌套类中的实体类
    auto evCarInfoObj = env->GetObjectField(nesting_info, selectedCarField);
    if (nullptr == evCarInfoObj) return;
    auto evCarInfoCls = env->GetObjectClass(evCarInfoObj);
    auto deviceIdFieldID = env->GetFieldID(evCarInfoCls, "deviceId", "Ljava/lang/String;");
    auto deviceIdJstr = (jstring) env->GetObjectField(evCarInfoObj, deviceIdFieldID);
    auto deviceId = CommonUtil::jstring2string(env, deviceIdJstr);
    // 其他属性写法类似，不再一一写出
    env->DeleteLocalRef(evCarInfoCls);

    // 嵌套类中的实体类列表
    auto listObj = env->GetObjectField(nesting_info, remainCarsField);
    auto listCls = env->GetObjectClass(listObj);
    auto listGet = env->GetMethodID(listCls, "get", "(I)Ljava/lang/Object;");
    auto listSize = env->GetMethodID(listCls, "size", "()I");

    jint len = env->CallIntMethod(listObj, listSize);
    for (int i = 0; i < len; ++i) {
        auto tileObj = env->CallObjectMethod(listObj, listGet, i);
        auto tileCls = env->GetObjectClass(listObj);
        if (nullptr == tileCls) continue;
        auto deviceIdFieldID = env->GetFieldID(evCarInfoCls, "deviceId", "Ljava/lang/String;");
        auto jstr = (jstring) env->GetObjectField(evCarInfoObj, deviceIdFieldID);
        auto deviceId = CommonUtil::jstring2string(env, jstr);
        LOGCATI("remain cars element deivceId = %s", deviceId.c_str());
        // 其他属性写法类似，不再一一写出
        env->DeleteLocalRef(tileCls);
    }
}

jobject NativeEntityLib(GetNestingInfo)(JNIEnv *env, jobject obj) {

    return nullptr;
}


}