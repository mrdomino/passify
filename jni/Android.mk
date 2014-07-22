LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE=Keccak1600
LOCAL_SRC_FILES=Keccak1600.c KeccakSponge.c KeccakF-1600-reference.c displayIntermediateValues.c

include $(BUILD_SHARED_LIBRARY)
