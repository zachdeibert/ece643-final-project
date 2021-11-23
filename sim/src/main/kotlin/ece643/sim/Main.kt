package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO
import java.util.function.Supplier

fun main() {
    var win: SimWindow? = null
    var mc: RemoteMinecraftLauncher? = null
    try {
        win = SimWindow()
        SimBusiness().run(HWIO(win), { mc = RemoteMinecraftLauncher() }, object : Supplier<Long> {
            override fun get(): Long {
                return mc?.state ?: Long.MIN_VALUE
            }
        })
    } finally {
        mc?.close()
        win?.dispose()
    }
}
