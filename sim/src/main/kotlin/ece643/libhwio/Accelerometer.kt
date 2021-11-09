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
        enabled = true
        nextTime = System.currentTimeMillis() + PERIOD
    }

    fun disable() {
        enabled = false
    }

    fun ready(): Boolean {
        if (!enabled) {
            throw RuntimeException("Tried to read when accelerometer is not enabled")
        }
        return System.currentTimeMillis() >= nextTime
    }

    fun read(): Array<Short> {
        if (!ready()) {
            throw RuntimeException("Tried to read when accelerometer is not ready")
        }
        nextTime += PERIOD
        return view.values
    }
}
