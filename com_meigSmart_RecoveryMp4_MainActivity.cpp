#include <jni.h>
#include "mp4.h"
#include "atom.h"
#include "com_meigSmart_RecoveryMp4_MainActivity.h"
using namespace std;



//将const char类型转换成jstring类型
jstring CStr2Jstring0(JNIEnv* env, const char* pat )
{
    // 定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String;");
    // 获取java String类方法String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    // 建立byte数组
    jbyteArray bytes = (env)->NewByteArray((jsize)strlen(pat));
    // 将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
    //设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    //将byte数组转换为java String,并输出
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);

}
char * Jstring2CStr0( JNIEnv * env, jstring jstr )
{
    char * rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte * ba = env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen > 0)
    {
        rtn = (char*)malloc(alen+1); //new char[alen+1];
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);

    return rtn;
}

jstring CharTojstring0(JNIEnv* env, char* str)
{
    jsize len = strlen(str);
    jclass  clsstring = env->FindClass("java/lang/String");
    jstring  strencode = env->NewStringUTF("GB2312");
    jmethodID  mid = env->GetMethodID(clsstring,"<init>","([BLjava/lang/String;)V");
    jbyteArray  barr = env-> NewByteArray(len);
    env-> SetByteArrayRegion(barr,0,len,(jbyte*)str);
    return (jstring)env-> NewObject(clsstring,mid,barr,strencode);
}

std::string jstring2str(JNIEnv* env, jstring jstr)
{  
    char*  rtn   =   NULL;   
    jclass  clsstring   =   env->FindClass("java/lang/String");  
    jstring  strencode   =   env->NewStringUTF("GB2312");  
    jmethodID  mid   =   env->GetMethodID(clsstring,   "getBytes",  "(Ljava/lang/String;)[B");  
    jbyteArray  barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);   
    jsize  alen   =   env->GetArrayLength(barr);   
    jbyte*  ba   =   env->GetByteArrayElements(barr,JNI_FALSE);   
    if(alen  >   0){  
        rtn  =   (char*)malloc(alen+1);        
        memcpy(rtn,ba,alen);  
        rtn[alen]=0;  
    }  
    env->ReleaseByteArrayElements(barr,ba,0);  
    std::string
	stemp(rtn);
    free(rtn);
    return   stemp;  
}  

void doExecuteRepairResult(JNIEnv * env, jobject obj, jstring sdp) {
	// 1.找到java的MainActivity的class
	jclass clazz = env->FindClass("com/meigSmart/RecoveryMp4/MainAcitivity");
	if (clazz == 0) {
		LOG("can't find clazz");
	}
	LOG(" find clazz");

	//2 找到class 里面的方法定义
	jmethodID methodid = env->GetMethodID(clazz, "NotifyRepairResult", "(Ljava/lang/String;)V");
	if (methodid == 0) {
		LOG("can't find methodid");
	}
	LOG(" find methodid");

	//3 .调用方法
	env->CallVoidMethod(clazz, methodid, sdp);
}



JNIEXPORT jint JNICALL Java_com_meigSmart_RecoveryMp4_MainActivity_RepairFile(JNIEnv *env, jobject obj, jstring ok_file, jstring broken_file )
{
	//own_env = env;
	string ok = jstring2str(env,ok_file);
	string corrupt = jstring2str(env,broken_file);
	LOG(" ok path=%s,broken_path=%s",ok.c_str(),corrupt.c_str());
	Mp4 mp4;

	mp4.open(ok);
	
	if(corrupt.size()) {
		mp4.repair(corrupt);
		mp4.saveVideo(corrupt + "_fixed.mp4");
	}
	
	//doExecuteRepairResult(CStr2Jstring0("OK"));
	
	return 0;
}
