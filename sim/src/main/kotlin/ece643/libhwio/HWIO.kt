package ece643.libhwio

import ece643.sim.SimWindow

class HWIO(window: SimWindow) {
    val accelerometer = Accelerometer(window.accelerometer)
    val led = LED(window.leds, window.sevenseg)
    val ps2 = PS2(window.ps2)
    val interrupt = Interrupt(window, window.buttons, ps2)
    val vga = VGA(window.vga)
}
