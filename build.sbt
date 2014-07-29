proguardCache in Android += ProguardCache("org.scaloid") % "org.scaloid"

libraryDependencies += "org.scaloid" %% "scaloid" % "3.3-8"

scalacOptions in Compile ++= Seq("-feature", "-deprecation")
