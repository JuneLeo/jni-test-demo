package com.cheetah.test;

import android.util.Log;

public class Hello {


    static {
        System.loadLibrary("test-jni");
    }


    public native String sayHello();

    public native void callbackHello();

    public void hello(String hello) {
        Log.d("song", hello);
    }


    public native void execute();

    public native JuneLeoModel getModel(int age,String name);
}
