package ece643.libhwio

import ece643.sim.SimWindow

class HWIO(window: SimWindow) {
    val accelerometer = Accelerometer()
    val interrupt = Interrupt()
    val led = LED(window.leds, window.sevenseg)
    val ps2 = PS2()
    val vga = VGA(window.vga)
}
