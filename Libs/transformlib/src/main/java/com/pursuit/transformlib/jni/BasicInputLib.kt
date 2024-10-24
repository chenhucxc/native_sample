package com.pursuit.transformlib.jni

/**
 * @Description: 基础类型转换-java to c++
 * @ProjectName: native_sample
 * @ClassName: BasicInputLib
 * @Author: Brain.hu
 * @Date: 2024/10/14 14:23
 */
object BasicInputLib {

    init {
        NativeLibraryLoader.isNativeLibraryLoaded()
    }

    // TODO(Basic)
    external fun nativeSampleInt(value: Int)
    external fun nativeSampleFloat(value: Float)
    external fun nativeSampleDouble(value: Double)
    external fun nativeSampleLong(value: Long)
    external fun nativeSampleBoolean(value: Boolean)
    external fun nativeSampleString(value: String)

    // TODO(Array)
    external fun nativeSampleByteArray(array: ByteArray)
    external fun nativeSampleIntArray(array: IntArray)
    external fun nativeSampleFloatArray(array: FloatArray)
    external fun nativeSampleDoubleArray(value: DoubleArray)
    external fun nativeSampleLongArray(value: LongArray)
    external fun nativeSampleStringArray(value: Array<String>)

    // TODO(List)
    external fun nativeSampleStringList(value: List<String>)
}