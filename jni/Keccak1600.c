#include <assert.h>
#include <stdlib.h>

#include "KeccakSponge.h"

#include "org_wholezero_passify_Keccak1600_KeccakSponge.h"

static Keccak_SpongeInstance*
_get_sponge_instance(JNIEnv *e, jobject s)
{
  Keccak_SpongeInstance* ret;
  jclass                 class;
  jfieldID               fid;

  class = (*e)->GetObjectClass(e, s);
  fid = (*e)->GetFieldID(e, class, "sptr", "I");
  assert(fid != 0);
  ret = (Keccak_SpongeInstance*)(*e)->GetIntField(e, s, fid);
  return ret;
}

/*
 * Class:     org_wholezero_passify_Keccak1600_KeccakSponge
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_org_wholezero_passify_Keccak1600_00024KeccakSponge_init
(JNIEnv *e, jobject s)
{
  Keccak_SpongeInstance* sponge;
  jclass                 class;
  jfieldID               fid;
  size_t                 rate;
  int                    r;

  class = (*e)->GetObjectClass(e, s);
  fid = (*e)->GetFieldID(e, class, "r", "I");
  assert(fid != 0);
  rate = (*e)->GetIntField(e, s, fid);
  assert(rate <= 1600);

  sponge = malloc(sizeof(*sponge));
  assert(((int)sponge) == sponge);
  r = Keccak_SpongeInitialize(sponge, rate, 1600 - rate);
  assert(0 == r);

  fid = (*e)->GetFieldID(e, class, "sptr", "I");
  assert(fid != 0);
  (*e)->SetIntField(e, s, fid, (int)sponge);
}

/*
 * Class:     org_wholezero_passify_Keccak1600_KeccakSponge
 * Method:    absorb
 * Signature: (Lscala/collection/Seq;)V
 */
JNIEXPORT void JNICALL
Java_org_wholezero_passify_Keccak1600_00024KeccakSponge_absorb
(JNIEnv *e, jobject s, jobject bs)
{
}

/*
 * Class:     org_wholezero_passify_Keccak1600_KeccakSponge
 * Method:    absorbLastFewBits
 * Signature: (B)V
 */
JNIEXPORT void JNICALL
Java_org_wholezero_passify_Keccak1600_00024KeccakSponge_absorbLastFewBits
(JNIEnv *e, jobject s, jbyte b)
{
}


/*
 * Class:     org_wholezero_passify_Keccak1600_KeccakSponge
 * Method:    squeeze
 * Signature: (I)Lscala/collection/Seq;
 */
JNIEXPORT jobject JNICALL
Java_org_wholezero_passify_Keccak1600_00024KeccakSponge_squeeze
(JNIEnv *e, jobject s, jint n)
{
  return 0;
}

/*
 * Class:     org_wholezero_passify_Keccak1600_KeccakSponge
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_org_wholezero_passify_Keccak1600_00024KeccakSponge_destroy
(JNIEnv *e, jobject s)
{
  Keccak_SpongeInstance* sponge = _get_sponge_instance(e, s);

  free(sponge);
}
