package ece643.sim

import java.awt.*
import java.awt.image.BufferedImage
import java.nio.ByteBuffer
import java.nio.ByteOrder
import javax.swing.JComponent

class VGAView : JComponent() {
    private val image = BufferedImage(640, 480, BufferedImage.TYPE_INT_RGB)

    init {
        minimumSize = Dimension(640, 480)
        maximumSize = minimumSize
        preferredSize = minimumSize
    }

    override fun paintComponent(g: Graphics) {
        g.drawImage(image, 0, 0, null)
    }

    fun updateRect(x: Int, y: Int, width: Int, height: Int, buffer: ByteBuffer, offset: Int) {
        EventQueue.invokeAndWait {
            buffer.order(ByteOrder.LITTLE_ENDIAN)
            val buf = buffer.asIntBuffer()
            var idx = offset / 4
            for (yi in y until y+height) {
                for (xi in x until x+width) {
                    image.setRGB(xi, yi, buf[++idx])
                }
            }
            repaint(Rectangle(x, y, width, height))
        }
    }
}
