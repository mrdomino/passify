package org.wholezero.passify;

public class KeccakSponge {
  public static interface Sponge {
    public void absorb(byte[] bs);
    public void absorbLastFewBits(byte b);
    public byte[] squeeze(int bytes);
    public void dispose();
  }

  private static class KeccakSpongeNative implements Sponge {
    private long sptr;
    private int  rate;
    public KeccakSpongeNative(int r) {
      rate = r;
    }
    native public void init();
    native public void absorb(byte[] bs);
    native public void absorbLastFewBits(byte b);
    native public byte[] squeeze(int bytes);
    native public void dispose();
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
