package ece643.main

import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import java.util.jar.JarInputStream

class NativeLoader : AutoCloseable {
    private val dir: File = File(System.getProperty("java.library.path"))

    init {
        dir.deleteRecursively()
        dir.mkdirs()
        System.getProperty("java.class.path").split(File.pathSeparatorChar).forEach {
            val file = File(it)
            if (file.extension == "jar" && file.exists()) {
                JarInputStream(FileInputStream(file)).use { stream ->
                    var ent = stream.nextJarEntry
                    while (ent != null) {
                        if (ent.name.endsWith(".so")) {
                            val out = File(dir, ent.name)
                            FileOutputStream(out).use { outStream ->
                                stream.copyTo(outStream)
                            }
                        }
                        ent = stream.nextJarEntry
                    }
                }
            }
        }
    }

    override fun close() {
        dir.deleteRecursively()
    }
}
