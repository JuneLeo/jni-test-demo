package com.cheetah.test;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    Hello hello = new Hello();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onJniTest(View view) {
        JuneLeoModel pengfei = hello.getModel(25, "pengfei");
        Log.d("song", pengfei.toString());
    }

    public void onJavaExec(View view) {
        Log.d("song", "java 计算1亿次for循环");
        long start = System.currentTimeMillis();
        int b = 0;
        for (int i = 0; i < 100000000; ++i) {
            b += 1;
//        LOGD("计算中 %d", b);
        }
        long end = System.currentTimeMillis();
        Log.d("song", String.format("java 花费时间：%f 秒", (double) (end - start) / 1000));

    }

    public void onJniExec(View view) {
        hello.execute();
    }
}
