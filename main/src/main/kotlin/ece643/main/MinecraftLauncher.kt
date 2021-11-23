package ece643.main

import ece643.main.tweaks.ImplTweak
import ece643.main.tweaks.TimeTweak
import net.minecraft.launchwrapper.LaunchClassLoader
import java.io.File

class MinecraftLauncher : AutoCloseable {
    init {
        TimeTweak.initContext()
    }

    private val thread = Thread {
        val cl = LaunchClassLoader(System.getProperty("java.class.path").split(File.pathSeparatorChar).map { File(it).toURI().toURL() }.toTypedArray())
        cl.addClassLoaderExclusion("net.minecraft.launchwrapper")
        cl.addClassLoaderExclusion("ece643.main")
        val tweaker = Tweaker()
        tweaker.acceptOptions(listOf("ECE643", ""), File("/"), File("/"), "1.0.0")
        tweaker.injectIntoClassLoader(cl)
        val clazz = Class.forName(tweaker.launchTarget, false, cl)
        val workdirMethod = clazz.getMethod("b")
        val workdir = workdirMethod.invoke(null) as File
        File(File(workdir, "saves"), ImplTweak.worldDir).deleteRecursively()
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
    }
}

fun main() {
    MinecraftLauncher().waitFor()
}
