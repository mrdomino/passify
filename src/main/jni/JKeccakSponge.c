#include <assert.h>
#include <stdlib.h>

#include "KeccakSponge.h"
#include "org_wholezero_passify_KeccakSponge_KeccakSpongeNative.h"

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
  jint                   n;

  si = _get_instance(e, s);
  n = (*e)->GetArrayLength(e, bs);
  es = (*e)->GetByteArrayElements(e, bs, 0);

  if (0 != Keccak_SpongeAbsorb(si, (unsigned char*)es, n)) {
    /* TODO throw */
    assert(!"sponge-absorb");
  }

  (*e)->ReleaseByteArrayElements(e, bs, es, JNI_ABORT);
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
