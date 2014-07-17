package org.wholezero.passable

import android.app.Activity
import android.os.Bundle
import android.text.Editable
import org.scaloid.common._
import scala.language.postfixOps

class MainActivity extends SActivity with TypedActivity {
  def passify(masterPass : Editable, username : Editable, site : Editable) {
    toast(masterPass + " " + username + " " + site)
  }
  override def onCreate(bundle: Bundle) {
    super.onCreate(bundle)
    setContentView(new SVerticalLayout {
      STextView(R.string.header_doc).textSize(24.5 sp).<<.marginBottom(25 dip).>>
      STextView(R.string.master_passphrase)
      val masterPass = SEditText() inputType TEXT_PASSWORD
      STextView(R.string.username)
      val username = SEditText() singleLine true
      STextView(R.string.site)
      val site = SEditText() singleLine true
      SButton(R.string.passify, passify(masterPass.text, username.text, site.text))

      masterPass requestFocus ()
    })
  }
}
