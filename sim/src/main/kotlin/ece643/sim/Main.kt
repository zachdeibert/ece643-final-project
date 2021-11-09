package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO

fun main() {
    val win = SimWindow()
    SimBusiness().run(HWIO(win))
    win.dispose()
}
