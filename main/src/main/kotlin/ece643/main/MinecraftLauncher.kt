package ece643.main

class MinecraftLauncher : AutoCloseable {
    private val proc = Runtime.getRuntime().exec("/usr/bin/glxgears", arrayOf("DISPLAY=:0"))

    override fun close() {
        proc.destroy()
        proc.waitFor()
    }
}
