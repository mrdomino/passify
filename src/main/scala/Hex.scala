package org.wholezero.passify

object Hex {
  def valueOf(buf : Seq[Byte]) : String = buf.map("%02x" format _).mkString
}
