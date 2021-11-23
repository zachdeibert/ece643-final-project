package ece643.sim

import ece643.main.MinecraftLauncher
import java.util.*
import java.util.concurrent.locks.ReentrantLock
import kotlin.concurrent.withLock

class RemoteMinecraftLauncher : AutoCloseable {
    private val proc = Runtime.getRuntime().exec(arrayOf(
            "java",
            "-cp", System.getProperty("java.class.path"),
            "--illegal-access=debug",
            "--add-opens", "java.base/java.lang=ALL-UNNAMED",
            "-Xmx200M",
            RemoteMinecraftLauncher::class.qualifiedName + "Kt"
        ), arrayOf("DISPLAY=:2"))
    private val lock = ReentrantLock()
    private val cond = lock.newCondition()
    private val stdout = Thread {
        Scanner(proc.inputStream).use { scan ->
            while (scan.hasNext()) {
                val line = scan.nextLine()
                if (line.startsWith("!state=")) {
                    lock.withLock {
                        _state = line.substring(7).toLong()
                        cond.signalAll()
                    }
                } else {
                    println(line)
                }
            }
        }
    }.apply {
        start()
    }
    private val stderr = Thread {
        Scanner(proc.errorStream).use { scan ->
            while (scan.hasNext()) {
                System.err.println(scan.nextLine())
            }
        }
    }.apply {
        start()
    }

    private var _state = 0L

    val state: Long
        get() {
            lock.withLock {
                _state = Long.MIN_VALUE
                proc.outputStream.write('s'.code)
                proc.outputStream.flush()
                while (_state == Long.MIN_VALUE) {
                    cond.await()
                }
                return _state
            }
        }

    override fun close() {
        proc.outputStream.write('c'.code)
        proc.outputStream.close()
        proc.destroy()
        proc.waitFor()
        stdout.join()
        stderr.join()
    }
}

fun main() {
    val mc = MinecraftLauncher()
    while (true) {
        when (System.`in`.read()) {
            -1, 'c'.code -> {
                mc.close()
                return
            }
            's'.code -> println("!state=${mc.state}")
        }
    }
}
