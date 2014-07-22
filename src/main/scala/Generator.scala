package org.wholezero.passify

import java.net.IDN
import org.bouncycastle.crypto.digests.SHA3Digest
import org.scaloid.common._

object Generator {
  import App._

  private val some_nulls : Array[Byte] = Array.fill(1024)(0)

  private def getHash(digest : SHA3Digest) : Array[Byte] = {
    var scratch = Array.ofDim[Byte](digest.getDigestSize())
    digest.doFinal(scratch, 0)
    scratch
  }

  def generate(username : Option[String], password: String,
               site : String, iterations : Integer) : String = {
    val start = System.currentTimeMillis()
    var digest = new SHA3Digest(512)
    val prefix = ((username match {
      case Some(s) => s ++ ":"
      case None    => ""
    }) ++ password ++ ":" ++ IDN.toASCII(site)).getBytes()
    digest.update(prefix, 0, prefix.length)
    for (_ <- 0 until iterations)
      digest.update(some_nulls, 0, some_nulls.length)
    val end = System.currentTimeMillis()
    info(f"generate: ${end - start}%dms")
    Hex.valueOf(getHash(digest))
  }
}
