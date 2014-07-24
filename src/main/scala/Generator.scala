package org.wholezero.passify

import java.net.IDN
import org.scaloid.common._

object Generator {
  import App._

  private val some_nulls : Array[Byte] = Array.fill(1024)(0)

  def generate(username : Option[String], password: String,
               site : String, iterations : Int) : String = {
    val start = System.currentTimeMillis()
    var sponge = KeccakSponge.build(64)
    val prefix = ((username match {
      case Some(s) => s ++ ":"
      case None    => ""
    }) ++ password ++ ":" ++ IDN.toASCII(site)).getBytes()
    sponge absorb prefix
    for (_ <- 0 until iterations) sponge absorb some_nulls
    val end = System.currentTimeMillis()
    info(f"generate: ${end - start}%dms")
    Hex.valueOf(sponge.squeeze(64))
  }
}
