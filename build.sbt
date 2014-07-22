import android.Keys._

android.Plugin.androidBuild

name := "Passable"

scalaVersion := "2.11.1"

scalacOptions in Compile ++= Seq("-feature", "-deprecation")

platformTarget in Android := "android-10"

proguardCache in Android ++= Seq(
  ProguardCache("org.scaloid") % "org.scaloid",
  ProguardCache("org.bouncycastle") % "org.bouncycastle"
)

proguardOptions in Android ++= Seq("-dontobfuscate", "-dontoptimize", "-dontwarn scala.collection.mutable.**", "-keep class scala.collection.SeqLike { public protected *; }")

proguardLibraries in Android ++= Seq(Path(System.getProperty("java.home")) / "lib" / "rt.jar")

libraryDependencies ++= Seq(
                         "org.bouncycastle" % "bcprov-jdk15on" % "1.50",
                              "org.scaloid" %% "scaloid" % "3.3-8",
                            "org.scalatest" %% "scalatest" % "2.2.0" % "test")

scalacOptions in Compile += "-feature"

// call install and run without having to prefix with android:
run <<= run in Android

install <<= install in Android
