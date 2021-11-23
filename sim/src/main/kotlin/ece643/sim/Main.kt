package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO

fun main() {
    var win: SimWindow? = null
    var mc: RemoteMinecraftLauncher? = null
    try {
        win = SimWindow()
        SimBusiness().run(HWIO(win)) {
            mc = RemoteMinecraftLauncher()
        }
    } finally {
        mc?.close()
        win?.dispose()
    }
}
