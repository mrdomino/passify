package org.wholezero.passify

import java.util.List
import java.util.concurrent.{LinkedBlockingQueue,ThreadPoolExecutor,TimeUnit}
import android.app.Activity
import android.os.Bundle
import android.text.Editable
import android.widget.{ArrayAdapter,ListView}
import org.scaloid.common._
import scala.concurrent.{Future,ExecutionContext}
import scala.language.implicitConversions
import scala.language.postfixOps

sealed case class Pass(username : Option[String], site : String, pass : String)
{
  override def toString() = username.map({u => s"${u}@"}).getOrElse("") + s"$site: $pass"
}

class MainActivity extends SActivity with TypedActivity {
  implicit val exec = ExecutionContext.fromExecutor(
      new ThreadPoolExecutor(1, 1, 0, TimeUnit.SECONDS,
          new LinkedBlockingQueue[Runnable]))
  override implicit val loggerTag = App.loggerTag

  implicit def editableToString(e : Editable) : String = e.toString()

  def passify(masterPass : Editable, username : Editable, site : Editable) {
    val username_opt : Option[String] = if (username.length() > 0) {
      Some(username)
    }
    else None
    passifyButton setText R.string.passifying
    passifyButton setEnabled false
    Future {
      val pass = Generator.generate(username_opt, masterPass, site, 10000)
      runOnUiThread {
        addPass(Pass(username_opt, site, pass))
        toast(R.string.generated)
        passifyButton setText R.string.passify
        passifyButton setEnabled true
      }
    }
  }

  private lazy val passifyButton = new SButton(R.string.passify)
  private lazy val passesAdapter = new ArrayAdapter(ctx, android.R.layout.simple_list_item_1, passes)
  private val passes : List[Pass] = new java.util.ArrayList()
  private def addPass(p : Pass) { passesAdapter.insert(p, 0) }
  private def clearPasses() { passesAdapter.clear() }

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
      this += passifyButton
      passifyButton onClick passify(masterPass.text, username.text, site.text)

      SListView() setAdapter passesAdapter

      masterPass requestFocus ()
    })
  }
}
