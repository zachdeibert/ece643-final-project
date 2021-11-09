package ece643.libhwio

import ece643.sim.PS2View
import java.util.*

class PS2(private val view: PS2View) {
    companion object {
        private const val PERIOD = 100
        private const val SCALE = 4f
    }

    private val values = LinkedList<Byte>()
    private var nextTime = System.currentTimeMillis() + PERIOD

    fun ready(): Boolean {
        if (nextTime >= System.currentTimeMillis()) {
            nextTime += PERIOD
            var b = 0x08.toUByte()
            val x = (SCALE * view.dx).toInt()
            val y = (SCALE * view.dy).toInt()
            if (x > 0xFF) {
                b = b.or(0x40.toUByte())
            }
            if (x < -0x100) {
                b = b.or(0x50.toUByte())
            } else if (x < 0) {
                b = b.or(0x10.toUByte())
            }
            if (y > 0xFF) {
                b = b.or(0x80.toUByte())
            }
            if (y < -0x100) {
                b = b.or(0xA0.toUByte())
            } else if (y < 0) {
                b = b.or(0x20.toUByte())
            }
            if (view.lmb) {
                b = b.or(0x01.toUByte())
            }
            if (view.mmb) {
                b = b.or(0x04.toUByte())
            }
            if (view.rmb) {
                b = b.or(0x02.toUByte())
            }
            values.push(b.toByte())
            values.push(x.toByte())
            values.push(y.toByte())
            return true
        }
        return false
    }

    fun poll(): Array<Byte> {
        return values.toTypedArray()
    }
}
