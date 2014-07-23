package org.wholezero.passify;

import java.nio.*;

public class KeccakSponge {
  static {
    System.loadLibrary("JKeccakSponge");
  }

  public static interface Sponge {
    public void absorb(byte[] bs);
    public void absorbLastFewBits(byte b);
    public byte[] squeeze(int bytes);
  }

  private static class KeccakSpongeNative implements Sponge {
    private ByteBuffer state;
    private int rate;

    native private static int sizeofSpongeInstance();

    public KeccakSpongeNative(int r) {
      state = ByteBuffer.allocateDirect(sizeofSpongeInstance());
      rate = r;
    }
    native public void init();
    native public void absorb(byte[] bs);
    native public void absorbLastFewBits(byte b);
    native public byte[] squeeze(int bytes);
  }

  public static Sponge build(int r) {
    assert(r <= 1600);
    assert(r > 0);
    assert((r % 8) == 0);
    KeccakSpongeNative ret = new KeccakSpongeNative(r);
    ret.init();
    return ret;
  }
}
