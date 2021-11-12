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
            val buf = buffer.asShortBuffer()
            var idx = offset / 2
            for (yi in y until y+height) {
                for (xi in x until x+width) {
                    val color = buf[++idx].toUShort().toInt()
                    image.setRGB(xi, yi,
                            color.and(0xF800).shl(8)
                        .or(color.and(0x07E0).shl(5))
                        .or(color.and(0x001F).shl(3)))
                }
            }
            repaint(Rectangle(x, y, width, height))
        }
    }
}
