package ece643.libhwio

import ece643.sim.AccelerometerView
import java.lang.RuntimeException

class Accelerometer(private val view: AccelerometerView) {
    companion object {
        private const val PERIOD = 20
    }

    private var enabled = false
    private var nextTime = 0.toLong()

    fun enable() {
        try {
            enabled = true
            nextTime = System.currentTimeMillis() + PERIOD
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun disable() {
        try {
            enabled = false
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun ready(): Boolean {
        try {
            if (!enabled) {
                throw RuntimeException("Tried to read when accelerometer is not enabled")
            }
            return System.currentTimeMillis() >= nextTime
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return false
    }

    fun read(): Array<Short> {
        try {
            if (!ready()) {
                throw RuntimeException("Tried to read when accelerometer is not ready")
            }
            nextTime += PERIOD
            return view.values
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return arrayOf(0, 0, 0)
    }
}
