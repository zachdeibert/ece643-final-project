package ece643.libhwio

import ece643.sim.VGAView
import java.lang.Exception
import java.nio.ByteBuffer

class VGA(private val view: VGAView) {
    private var first = true

    fun buffer(data: ByteBuffer) {
        try {
            if (first) {
                first = false
                return
            }
            val header = data.asShortBuffer()
            view.updateRect(header[0].toInt(), header[1].toInt(), header[2].toInt(), header[3].toInt(), data, 12)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun write(x: Int, y: Int, width: Int, height: Int, data: ByteBuffer) {
        try {
            view.updateRect(x, y, width, height, data, 0)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}
