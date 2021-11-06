package ece643.sim

import ece643.libbusiness.Business
import ece643.libhwio.HWIO

fun main() {
    println("Hello from sim")
    Business().run(HWIO())
}
