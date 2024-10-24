package com.pursuit.transformlib

class NativeLib {

    /**
     * A native method that is implemented by the 'transformlib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'transformlib' library on application startup.
        init {
            System.loadLibrary("transformlib")
        }
    }
}