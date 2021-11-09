package ece643.libhwio

import ece643.sim.LEDView
import ece643.sim.SevenSegView

class LED(private val view: Array<LEDView>, private val sevenseg: SevenSegView) {
    fun set(leds: Int, hours: Int, minutes: Int, pm: Boolean) {
        try {
            for (i in 0 until 10) {
                view[i].active = leds.and(0x200.shr(i)) != 0
            }
            sevenseg.update(hours, minutes, pm)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}
