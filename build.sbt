import android.Keys._

android.Plugin.androidBuild

name := "Passable"

scalaVersion := "2.11.1"

scalacOptions in Compile += "-feature"

platformTarget in Android := "android-10"

proguardCache in Android ++= Seq(
  ProguardCache("org.scaloid") % "org.scaloid"
)

proguardOptions in Android ++= Seq("-dontobfuscate", "-dontoptimize", "-dontwarn scala.collection.mutable.**", "-keep class scala.collection.SeqLike { public protected *; }")

libraryDependencies ++= Seq(
                              "org.scaloid" %% "scaloid" % "3.3-8",
                            "org.scalatest" %% "scalatest" % "2.2.0" % "test")

scalacOptions in Compile += "-feature"

// call install and run without having to prefix with android:
run <<= run in Android

install <<= install in Android
