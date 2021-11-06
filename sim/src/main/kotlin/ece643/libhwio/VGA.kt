package ece643.libhwio

import java.nio.ByteBuffer

class VGA {
    fun buffer(data: ByteBuffer) {
        println("VGA::buffer()")
    }

    fun write(x: Int, y: Int, width: Int, height: Int, data: ByteBuffer) {
        println("VGA::write()")
    }
}
