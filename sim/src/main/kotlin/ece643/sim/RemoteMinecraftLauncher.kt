package ece643.sim

import ece643.main.MinecraftLauncher

class RemoteMinecraftLauncher : AutoCloseable {
    private val proc = Runtime.getRuntime().exec(arrayOf(
            "java",
            "-cp", System.getProperty("java.class.path"),
            "-Djava.library.path=/tmp/ece643-minecraft-libs",
            "--illegal-access=debug",
            "--add-opens", "java.base/java.lang=ALL-UNNAMED",
            "-Xmx200M",
            RemoteMinecraftLauncher::class.qualifiedName + "Kt"
        ), arrayOf("DISPLAY=:2"))

    override fun close() {
        proc.destroy()
        proc.waitFor()
    }
}

fun main() {
    MinecraftLauncher().waitFor()
}
