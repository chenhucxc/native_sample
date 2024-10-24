package com.pursuit.transformlib.jni

import com.pursuit.transformlib.entities.LocationInfoBean
import com.pursuit.transformlib.entities.NestingBean

/**
 * @Description:
 * @ProjectName: native_sample
 * @ClassName: TransformEntityLib
 * @Author: Brain.hu
 * @Date: 2024/10/16 09:58
 */
object TransformEntityLib {

    init {
        NativeLibraryLoader.isNativeLibraryLoaded()
    }

    external fun nativeSetLocationInfo(locationInfoBean: LocationInfoBean)

    external fun nativeGetLocationInfo(): LocationInfoBean?

    external fun nativeSetLocationList(locationInfos: List<LocationInfoBean>)

    external fun nativeGetLocationList(): List<LocationInfoBean>?

    // 嵌套类的处理
    external fun nativeSetNestingInfo(info: NestingBean)

    external fun nativeGetNestingInfo(): NestingBean
}