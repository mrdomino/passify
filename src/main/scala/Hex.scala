package org.wholezero.passify

object Hex {
  def valueOf(buf : Array[Byte]) : String = buf.map("%02x" format _).mkString
}
