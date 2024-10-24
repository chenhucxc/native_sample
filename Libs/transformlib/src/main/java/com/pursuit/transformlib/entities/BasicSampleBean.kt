package com.pursuit.transformlib.entities

/**
 * 基础测试类
 */
data class LocationInfoBean @JvmOverloads constructor(
    val id: Int = 0,
    val x: Float = 0f,
    val y: Float = 0f,
    val z: Float? = null,
    val latitude: Double = 0.0,
    val longitude: Double = 0.0,
    val address: String? = null,
    val poiList: List<String>? = null,
    val isPositioned: Boolean = true,
    val isDefault: Boolean? = false,
) {
    override fun toString(): String {
        return "LocationInfoBean(id=$id, x=$x, y=$y, z=$z, latitude=$latitude, longitude=$longitude, address=$address, poiList=$poiList, isPositioned=$isPositioned, isDefault=$isDefault)"
    }
}

/**
 * 多层嵌套的情况
 */
data class EvCarBean(
    val deviceId: String = "",
    val type: Int = 0,
    val brandCode: Long = 0L,
    val recommendPrice: Double = 0.0,
)

data class NestingBean @JvmOverloads constructor(
    val id: Int = 0,
    val desc: String = "",
    val intArr: IntArray? = null,
    val selectedCar: EvCarBean? = null,
    val remainCars: List<EvCarBean>? = null,
) {
    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as NestingBean

        if (id != other.id) return false
        if (desc != other.desc) return false
        if (intArr != null) {
            if (other.intArr == null) return false
            if (!intArr.contentEquals(other.intArr)) return false
        } else if (other.intArr != null) return false
        if (selectedCar != other.selectedCar) return false
        if (remainCars != other.remainCars) return false

        return true
    }

    override fun hashCode(): Int {
        var result = id
        result = 31 * result + desc.hashCode()
        result = 31 * result + (intArr?.contentHashCode() ?: 0)
        result = 31 * result + (selectedCar?.hashCode() ?: 0)
        result = 31 * result + (remainCars?.hashCode() ?: 0)
        return result
    }
}