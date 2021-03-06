//
// Created by JuneLeo on 2020-06-21.
//

#include <jni.h>
#include "com_cheetah_test_Hello.h"
#include <android/log.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <vector>


#define TAG "song" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

using namespace std;

extern "C" JNIEXPORT jstring JNICALL Java_com_cheetah_test_Hello_sayHello
        (JNIEnv *env, jobject jobj) {
    const char *hello = "I am from c++";
    return env->NewStringUTF(hello);
}

extern "C" JNIEXPORT void JNICALL Java_com_cheetah_test_Hello_callbackHello
        (JNIEnv *env, jobject jobj) {
    const char *hello_class_address = "com/cheetah/test/Hello";
    jclass hello_class = env->FindClass(hello_class_address);
    //jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
    jmethodID hello_method = env->GetMethodID(hello_class, "hello", "(Ljava/lang/String;)V");
    const char *hello_method_call_back_txt_address = "I am from callback method hello！";
    env->CallVoidMethod(jobj, hello_method, env->NewStringUTF(hello_method_call_back_txt_address));

}


extern "C" JNIEXPORT void JNICALL Java_com_cheetah_test_Hello_execute
        (JNIEnv *env, jobject jobj) {
    clock_t start_time = clock();
    LOGD("native 计算1亿次for循环");

    int i = 0;
    int b = 0;
    for (i = 0; i < 100000000; ++i) {
        b += 1;
//        LOGD("计算中 %d", b);
    }


    clock_t end_time = clock();
    LOGD("native 花费时间：%f 秒 ", (double) (end_time - start_time) / CLOCKS_PER_SEC);


}


extern "C" JNIEXPORT jobject JNICALL Java_com_cheetah_test_Hello_getModel
        (JNIEnv *env, jobject jobj, jint jage, jstring jname) {
    jclass june_leo_model_class = env->FindClass("com/cheetah/test/JuneLeoModel");
    jobject jmodel = env->AllocObject(june_leo_model_class);
    jfieldID jageId = env->GetFieldID(june_leo_model_class, "age", "I");
    jfieldID jnameId = env->GetFieldID(june_leo_model_class, "name", "Ljava/lang/String;");
    env->SetIntField(jmodel, jageId, jage);
    env->SetObjectField(jmodel, jnameId, jname);
    return jmodel;
}

void recursive_file(vector<string>, string);

extern "C" JNIEXPORT void JNICALL Java_com_cheetah_test_Hello_getFiles
        (JNIEnv *env, jobject jobj, jstring jpath) {
    LOGD("jni file");
    jboolean is_copy;
    const char *path_dir = env->GetStringUTFChars(jpath, &is_copy);

    vector<string> vector_file;
    path_dir ="/mnt/sdcard";
    recursive_file(vector_file, string(path_dir));

}


void recursive_file(vector<string> vector, string dir) {
    DIR *dir_path = opendir(dir.c_str());

    if (dir_path == NULL) {
        LOGD("%s is null",dir.c_str());
        return;
    }
    struct dirent *file;
    while ((file = readdir(dir_path)) != NULL) {
//        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
//            continue;
//        }
        if (file->d_type == DT_DIR) {
            char *dir_name = file->d_name;
            LOGD("%s", dir_name);
//            recursive_file(vector,)
        } else {
            char *file_name = file->d_name;
            LOGD("%s", file_name);
        }
    }
}




