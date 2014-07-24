#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <android/log.h>

#include "KeccakSponge.h"
#include "org_wholezero_passify_KeccakSponge_KeccakSpongeNative.h"

static const char* TAG = "Passify";

#define VLOG(fmt, ...) \
  __android_log_print(ANDROID_LOG_VERBOSE, TAG, fmt, __VA_ARGS__)

static Keccak_SpongeInstance*
_get_instance(JNIEnv *e, jobject s)
{
  jclass   class;
  jfieldID fid;
  jobject  state;

  class = (*e)->GetObjectClass(e, s);
  fid = (*e)->GetFieldID(e, class, "state", "Ljava/nio/ByteBuffer;");
  state = (*e)->GetObjectField(e, s, fid);
  return (*e)->GetDirectBufferAddress(e, state);
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
  jclass                 class;
  jfieldID               fid;
  jint                   rate;
  Keccak_SpongeInstance* si;

  class = (*e)->GetObjectClass(e, s);

  fid = (*e)->GetFieldID(e, class, "rate", "I");
  rate = (*e)->GetIntField(e, s, fid);
  assert(rate <= 1600);

  si = _get_instance(e, s);

  if (0 != Keccak_SpongeInitialize(si, rate, 1600 - rate)) {
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

  start = _get_time_nsec();

  si = _get_instance(e, s);
  n = (*e)->GetArrayLength(e, bs);
  VLOG("absorb:start %u", n);
  es = (*e)->GetByteArrayElements(e, bs, 0);
  end = _get_time_nsec();
  VLOG("absorb:copied %lldms", (end - start) / 1000000LL);

  if (0 != Keccak_SpongeAbsorb(si, (unsigned char*)es, n)) {
    /* TODO throw */
    assert(!"sponge-absorb");
  }
  start = end;
  end = _get_time_nsec();
  VLOG("absorb:absorbed %lldms", (end - start) / 1000000LL);

  (*e)->ReleaseByteArrayElements(e, bs, es, JNI_ABORT);
  start = end;
  end = _get_time_nsec();
  VLOG("absorb:released %lldms", (end - start) / 1000000LL);
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
  assert(ret);

  es = (*e)->GetByteArrayElements(e, ret, 0);

  if (0 != Keccak_SpongeSqueeze(si, (unsigned char*)es, n)) {
    /* TODO throw */
    assert(!"sponge-squeeze");
  }

  (*e)->ReleaseByteArrayElements(e, ret, es, 0);
  return ret;
}
