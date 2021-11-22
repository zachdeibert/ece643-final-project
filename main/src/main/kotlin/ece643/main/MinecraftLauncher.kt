package ece643.main

import net.minecraft.launchwrapper.LaunchClassLoader
import java.io.File

class MinecraftLauncher : AutoCloseable {
    private val natives = NativeLoader()
    private val thread = Thread {
        val cl = LaunchClassLoader(System.getProperty("java.class.path").split(File.pathSeparatorChar).map { File(it).toURI().toURL() }.toTypedArray())
        cl.addClassLoaderExclusion("net.minecraft.launchwrapper")
        val tweaker = Tweaker()
        tweaker.acceptOptions(listOf("ECE643", ""), File("/"), File("/"), "1.0.0")
        tweaker.injectIntoClassLoader(cl)
        val clazz = Class.forName(tweaker.launchTarget, false, cl)
        val mainMethod = clazz.getMethod("main", Array<String>::class.java)
        mainMethod.invoke(null, tweaker.launchArguments)
    }.apply {
        start()
    }

    fun waitFor() {
        thread.join()
    }

    override fun close() {
        thread.interrupt()
        waitFor()
        natives.close()
    }
}

fun main() {
    MinecraftLauncher().waitFor()
}
