package org.wholezero.passify

trait Sponge {
  def absorb(bs : Seq[Byte]) : Unit
  def squeeze(bits : Integer) : Seq[Byte]
}

object Keccak1600 {
  System.loadLibrary("Keccak1600")

  private class KeccakSponge(val r : Integer) extends Sponge {
    private var sptr : Int = 0

    @native private def init : Unit = {}
    @native override def absorb(bs : Seq[Byte]) : Unit
    @native override def squeeze(bits : Integer) : Seq[Byte]

    init
  }

  def apply(r : Integer) : Sponge = {
    require(r <= 1600)
    require((r % 8) == 0)
    require(r > 0)
    new KeccakSponge(r)
  }
}
