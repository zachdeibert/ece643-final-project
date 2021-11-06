package ece643.libhwio

class Accelerometer {
    fun enable() {
        println("Accelerometer::enable()")
    }

    fun disable() {
        println("Accelerometer::disable()")
    }

    fun ready(): Boolean {
        println("Accelerometer::ready()")
        return false
    }

    fun read(): Array<Short> {
        println("Accelerometer::read()")
        return arrayOf(0, 0, 0)
    }
}
