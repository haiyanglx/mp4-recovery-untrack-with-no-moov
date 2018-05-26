LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := testRecoveryMp4

LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES :=      \
	$(LOCAL_PATH)  \
	prebuilts/ndk/current/sources/cxx-stl/stlport/stlport \
	$(LOCAL_PATH)/master/libav-12.2

STL_PATH=$(LOCAL_PATH)/../../../../prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a
STLPORT_PATH=$(LOCAL_PATH)/../../../../prebuilts/ndk/current/sources/cxx-stl/stlport/libs/arm64-v8a
LOCAL_SRC_FILES += TestRecovery.cpp

LOCAL_SHARED_LIBRARIES := libRecoveryMp4 \
	libavutil		\
	libavcodec       \
	libavdevice		\
	libavfilter 		\
	libavformat		\
	libavresample	\
	libswscale		\

LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -llog -lz -lm -lstdc++ -L$(STL_PATH) -lgnustl_static -lsupc++ -L$(STLPORT_PATH) -lstlport_shared

LOCAL_CPPFLAGS := \
-DNULL=0 -DSCOKLEN_T=socklen_t -DNO_SSTREAM -DBSD=1 -DNO_SSTREAM -fno-exceptions -DANDROID -DXLOCALE_NOT_USED -fPIC -frtti

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

LOCAL_MODULE_TAGS := optional

LOCAL_MULTILIB := 64

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_MODULE := libRecoveryMp4

LOCAL_SDK_VERSION := 24

LOCAL_SRC_FILES := atom.cpp \
	file.cpp \
	mp4.cpp \
	track.cpp


LOCAL_C_INCLUDES :=      \
	bionic \
	prebuilts/ndk/current/sources/cxx-stl/stlport/stlport \
	$(LOCAL_PATH)/master/libav-12.2

#LOCAL_STATIC_LIBRARIES   +=   libstlport_static
#arm64-v8a
#armeabi-v7a
STL_PATH=$(LOCAL_PATH)/../../../../prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a

LOCAL_CPPFLAGS := \
-DNULL=0 -DSCOKLEN_T=socklen_t -DNO_SSTREAM -DBSD=1 -DNO_SSTREAM -fno-exceptions -DANDROID -DXLOCALE_NOT_USED -fPIC -frtti -g


LOCAL_SHARED_LIBRARIES :=   \
	libavutil		\
	libavcodec       \
	libavdevice		\
	libavfilter 		\
	libavformat		\
	libavresample	\
	libswscale		\




LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -llog -lz -lm -lstdc++ -L$(STL_PATH) -lgnustl_static -lsupc++

LOCAL_MULTILIB := 64
LOCAL_MODULE_TAGS := optional
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)
include $(LOCAL_PATH)/master/libav-12.2/Android.mk

