package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO
import ece643.main.MinecraftLauncher

fun main() {
    val win = SimWindow()
    var mc: MinecraftLauncher? = null
    SimBusiness().run(HWIO(win)) {
        mc = MinecraftLauncher()
    }
    mc?.close()
    win.dispose()
}
