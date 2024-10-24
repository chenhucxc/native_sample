package com.pursuit.transformlib.jni

/**
 * @Description: 基础类型转换-c++ to java
 * @ProjectName: native_sample
 * @ClassName: BasicCallLib
 * @Author: Brain.hu
 * @Date: 2024/10/14 14:23
 */
object BasicCallbackLib {

    init {
        NativeLibraryLoader.isNativeLibraryLoaded()
    }

    // TODO(Basic)
    external fun nativeSampleInt(value: Int): Int
    external fun nativeSampleFloat(value: Float): Float
    external fun nativeSampleDouble(value: Double): Double
    external fun nativeSampleLong(value: Long): Long
    external fun nativeSampleBoolean(value: Boolean): Boolean
    external fun nativeSampleString(value: String): String

    // TODO(Array)
    external fun nativeSampleByteArray(array: ByteArray): ByteArray?
    external fun nativeSampleIntArray(array: IntArray): IntArray?
    external fun nativeSampleFloatArray(array: FloatArray): FloatArray?
    external fun nativeSampleDoubleArray(value: DoubleArray): DoubleArray?
    external fun nativeSampleLongArray(value: LongArray): LongArray?
    external fun nativeSampleObjectArray(): Array<IntArray>?
    external fun nativeSampleStringArray(value: Array<String>): Array<String>?

    // TODO(List)
    external fun nativeSampleStringList(value: List<String>): List<String>?
}