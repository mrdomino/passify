LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE=KeccakSpongeJ
LOCAL_CFLAGS := -Wall -Werror -I$(SBT_SOURCE_MANAGED)
LOCAL_SRC_FILES=KeccakSpongeJ.c KeccakSponge.c KeccakF-1600-reference.c displayIntermediateValues.c

include $(BUILD_SHARED_LIBRARY)
