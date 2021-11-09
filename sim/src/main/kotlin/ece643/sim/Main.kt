package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO
import ece643.main.MinecraftLauncher

fun main() {
    var win: SimWindow? = null
    var mc: MinecraftLauncher? = null
    try {
        win = SimWindow()
        SimBusiness().run(HWIO(win)) {
            mc = MinecraftLauncher()
        }
    } finally {
        mc?.close()
        win?.dispose()
    }
}
