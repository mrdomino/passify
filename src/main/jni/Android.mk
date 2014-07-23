LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := JKeccakSponge
LOCAL_CFLAGS := -Wall -Werror -I$(SBT_SOURCE_MANAGED)
LOCAL_SRC_FILES := JKeccakSponge.c KeccakSponge.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/common
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	LOCAL_ARM_MODE := arm
	LOCAL_C_INCLUDES := $(LOCAL_C_INCLUDES) $(LOCAL_PATH)/armv7a
	LOCAL_SRC_FILES := $(LOCAL_SRC_FILES) armv7a/KeccakF-1600-inplace-32bi-armv7a-le-gcc.S
else
	LOCAL_CFLAGS := $(LOCAL_CFLAGS) -Wno-strict-aliasing
	LOCAL_C_INCLUDES := $(LOCAL_C_INCLUDES) $(LOCAL_PATH)/32bi
	LOCAL_SRC_FILES := $(LOCAL_SRC_FILES) 32bi/KeccakF-1600-inplace32BI.c 32bi/SnP-FBWL-default.c
endif

include $(BUILD_SHARED_LIBRARY)
