#include <assert.h>
#include <stdlib.h>

#include "KeccakSponge.h"
#include "org_wholezero_passify_KeccakSponge_KeccakSpongeNative.h"

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
  jobject                state;
  Keccak_SpongeInstance* si;

  class = (*e)->GetObjectClass(e, s);

  fid = (*e)->GetFieldID(e, class, "rate", "I");
  rate = (*e)->GetIntField(e, s, fid);
  assert(rate <= 1600);

  fid = (*e)->GetFieldID(e, class, "state", "Ljava/nio/ByteBuffer;");
  state = (*e)->GetObjectField(e, s, fid);
  si = (Keccak_SpongeInstance*)(*e)->GetDirectBufferAddress(e, state);

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
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    absorbLastFewBits
 * Signature: (B)V
 */
JNIEXPORT void JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_absorbLastFewBits
  (JNIEnv *e, jobject s, jbyte b)
{
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    squeeze
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_squeeze
  (JNIEnv *e, jobject s, jint n)
{
  return 0;
}

/*
 * Class:     org_wholezero_passify_KeccakSponge_KeccakSpongeNative
 * Method:    dispose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wholezero_passify_KeccakSponge_00024KeccakSpongeNative_dispose
  (JNIEnv *e, jobject s)
{
}
