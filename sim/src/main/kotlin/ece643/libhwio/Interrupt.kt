package ece643.libhwio

class Interrupt {
    fun enable(mask: Int) {
        println("Interrupt::enable()")
    }

    fun disable(mask: Int) {
        println("Interrupt::disable()")
    }

    fun poll(mask: Int): Int {
        println("Interrupt::poll()")
        return 0
    }
}
