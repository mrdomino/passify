#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <android/log.h>

#include "KeccakSponge.h"
#include "org_wholezero_passify_KeccakSponge_KeccakSpongeNative.h"

static const char* TAG = "Passify";
static jfieldID    g_state;
static jfieldID    g_rate;

#define LOGV(...) \
  __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) \
  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) \
  __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

__inline__ static Keccak_SpongeInstance*
_get_instance(JNIEnv *e, jobject s)
{
  return (*e)->GetDirectBufferAddress(e, (*e)->GetObjectField(e, s, g_state));
}

static int64_t
_get_time_nsec()
{
  struct timespec ts;

  if (0 == clock_gettime(CLOCK_MONOTONIC, &ts)) {
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
  }
  else return -1;
}

jint JNI_OnLoad
  (JavaVM *vm, void *reserved)
{
  JNIEnv *e;
  jclass  class;

  if ((*vm)->GetEnv(vm, (void**)&e, JNI_VERSION_1_6) != JNI_OK) {
    LOGE("%s failed", __func__);
    return -1;
  }

  class = (*e)->FindClass(e,
      "org/wholezero/passify/KeccakSponge$KeccakSpongeNative");
  g_state = (*e)->GetFieldID(e, class, "state", "Ljava/nio/ByteBuffer;");
  g_rate = (*e)->GetFieldID(e, class, "rate", "I");

  return JNI_VERSION_1_6;
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    sizeofSpongeInstance
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_sizeofSpongeInstance
  (JNIEnv *e, jclass _unused)
{
  return sizeof(Keccak_SpongeInstance);
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_init
  (JNIEnv *e, jobject s)
{
  jint                   rate;
  Keccak_SpongeInstance* si;

  rate = (*e)->GetIntField(e, s, g_rate);
  assert(rate <= 1600);

  si = _get_instance(e, s);

  if (0 != Keccak_SpongeInitialize(si, rate, 1600 - rate)) {
    LOGE("Keccak_SpongeInitialize failed");
    /* TODO throw */
    assert(!"sponge-init");
  }
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    absorb
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_absorb
  (JNIEnv *e, jobject s, jbyteArray bs)
{
  Keccak_SpongeInstance* si;
  jbyte*                 es;
  jsize                  n;
  int64_t                start, end;

  si = _get_instance(e, s);
  n = (*e)->GetArrayLength(e, bs);
  es = (*e)->GetByteArrayElements(e, bs, 0);

  start = _get_time_nsec();
  if (0 != Keccak_SpongeAbsorb(si, (unsigned char*)es, n)) {
    /* TODO throw */
    LOGE("Keccak_SpongeAbsorb failed");
    assert(!"sponge-absorb");
  }
  end = _get_time_nsec();
  if (end - start > 5000000LL) {
    LOGD("absorb:absorbed %u bytes in %lldms",
         n, (end - start) / 1000000LL);
  }

  (*e)->ReleaseByteArrayElements(e, bs, es, 0);
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    absorbLastFewBits
 * Signature: (B)V
 */
JNIEXPORT void JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_absorbLastFewBits
  (JNIEnv *e, jobject s, jbyte b)
{
  Keccak_SpongeInstance* si;

  si = _get_instance(e, s);
  if (0 != Keccak_SpongeAbsorbLastFewBits(si, b)) {
    /* TODO throw */
    LOGE("Keccak_SpongeAbsorbLastFewBits failed");
    assert(!"sponge-absorblastfewbits");
  }
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    squeeze
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_squeeze
  (JNIEnv *e, jobject s, jint n)
{
  Keccak_SpongeInstance* si;
  jbyteArray             ret;
  jbyte*                 es;

  si = _get_instance(e, s);
  ret = (*e)->NewByteArray(e, n);
  /* TODO throw */
  if (!ret) {
    LOGE("Got NULL from NewByteArray");
    assert(!"null-ret");
  }

  es = (*e)->GetByteArrayElements(e, ret, 0);

  if (0 != Keccak_SpongeSqueeze(si, (unsigned char*)es, n)) {
    /* TODO throw */
    LOGE("Keccak_SpongeSqueeze failed");
    assert(!"sponge-squeeze");
  }

  (*e)->ReleaseByteArrayElements(e, ret, es, 0);
  return ret;
}
