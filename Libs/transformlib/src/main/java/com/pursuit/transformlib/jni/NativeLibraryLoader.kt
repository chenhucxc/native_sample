package com.pursuit.transformlib.jni

import android.util.Log

/**
 * @Description: 统一管理native lib的加载
 * @ProjectName: native_sample
 * @ClassName: NativeLibraryLoader
 * @Author: Brain.hu
 * @Date: 2024/10/14 14:16
 */
object NativeLibraryLoader {
    private const val TAG = "NativeLibraryLoader"
    private var isNativeLibraryLoaded = false

    init {
        val start = System.currentTimeMillis()
        val end: Long
        try {
            System.loadLibrary("transformlib")
            isNativeLibraryLoaded = true
            Log.i(TAG, "load native libraries success !!!")
        } catch (e: SecurityException) {
            e.printStackTrace()
        } catch (e: UnsatisfiedLinkError) {
            e.printStackTrace()
        } catch (e: NullPointerException) {
            e.printStackTrace()
        } finally {
            end = System.currentTimeMillis()
        }
        Log.e(TAG, "loadLibrary time diff: ${end - start}ms")
    }

    fun isNativeLibraryLoaded() = isNativeLibraryLoaded
}