package com.pursuit.native_sample

import android.app.Activity
import android.os.Bundle
import android.util.Log
import com.pursuit.native_sample.databinding.ActivityNativeTransformBinding
import com.pursuit.transformlib.entities.LocationInfoBean
import com.pursuit.transformlib.jni.BasicCallbackLib
import com.pursuit.transformlib.jni.BasicInputLib
import com.pursuit.transformlib.jni.TransformEntityLib

/**
 * @Description:
 * @ProjectName: native_sample
 * @ClassName: NativeTransformActivity
 * @Author: Brain.hu
 * @Date: 2024/10/14 15:23
 */
class NativeTransformActivity : Activity() {
    companion object {
        private const val TAG = "NativeTransformActivity"
    }

    private val binding by lazy {
        ActivityNativeTransformBinding.inflate(layoutInflater)
    }

    private val byteArr = byteArrayOf(0xAA.toByte(), 0x55.toByte())
    private val intArr = intArrayOf(0, 1, 2)
    private val floatArr = floatArrayOf(3f, 4f, 5f)
    private val doubleArr = doubleArrayOf(6.0, 7.0, 8.0)
    private val longArr = longArrayOf(10, 11, 12)
    private val stringArr = Array<String>(5) { "xxxxx" }
    private val stringList = listOf("111", "222", "333", "4444", "555")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)
        binding.btnBasicTest.setOnClickListener {
            BasicInputLib.apply {
                nativeSampleInt(10)
                nativeSampleFloat(20f)
                nativeSampleDouble(30.0)
                nativeSampleLong(40L)
                nativeSampleBoolean(false)
                nativeSampleString("111222233333")

                nativeSampleByteArray(byteArr)
                nativeSampleIntArray(intArr)
                nativeSampleFloatArray(floatArr)
                nativeSampleDoubleArray(doubleArr)
                nativeSampleLongArray(longArr)
                nativeSampleStringArray(stringArr)
                nativeSampleStringList(stringList)
            }
        }
        binding.btnBasicTestOut.setOnClickListener {
            BasicCallbackLib.apply {
                val retInt = nativeSampleInt(10)
                Log.i(TAG, "onCreate: retInt=$retInt")

                val retFloat = nativeSampleFloat(20f)
                Log.i(TAG, "onCreate: retFloat=$retFloat")

                val retDouble = nativeSampleDouble(30.0)
                Log.i(TAG, "onCreate: retDouble=$retDouble")

                val retLong = nativeSampleLong(40L)
                Log.i(TAG, "onCreate: retLong=$retLong")

                val retBoolean = nativeSampleBoolean(true)
                Log.i(TAG, "onCreate: retBoolean=$retBoolean")

                val retString = nativeSampleString("input str---")
                Log.i(TAG, "onCreate: retString=$retString")

                val retStringArr = nativeSampleStringArray(stringArr) ?: arrayOf()
                Log.i(TAG, "onCreate: retStringArr=${retStringArr.contentToString()}")

                val retStringList = nativeSampleStringList(stringList)
                Log.i(TAG, "onCreate: retStringList=$retStringList")
            }
        }
        binding.btnEntitySimple.setOnClickListener {
            // 设置数据
            val testLocationInfo = LocationInfoBean(
                id = 1010, x = 1.0f, y = 2.0f, z = 3.0f,
                latitude = 5.0, longitude = 6.0,
                address = "上海市浦东新区-------",
                poiList = arrayListOf("水果店", "肉铺", "包子店", "足浴店"), isPositioned = true, isDefault = false,
            )
            TransformEntityLib.nativeSetLocationInfo(testLocationInfo)

            // 获取数据
            val retLocationInfo = TransformEntityLib.nativeGetLocationInfo()
            Log.i(TAG, "onCreate: retLocationInfo=${retLocationInfo.toString()}")

            // list
            TransformEntityLib.nativeSetLocationList(listOf(testLocationInfo))
            val retList = TransformEntityLib.nativeGetLocationList()
            Log.i(TAG, "onCreate: retList=$retList")
        }
    }
}