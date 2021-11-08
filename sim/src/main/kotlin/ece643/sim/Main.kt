package ece643.sim

import ece643.libbusiness.SimBusiness
import ece643.libhwio.HWIO

fun main() {
    SimBusiness().run(HWIO(SimWindow()))
}
