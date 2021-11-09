package ece643.sim

import java.awt.Color
import java.awt.Dimension
import java.awt.Graphics
import javax.swing.JButton

class Button : JButton() {
    init {
        minimumSize = Dimension(25, 25)
        maximumSize = minimumSize
        preferredSize = minimumSize
        isBorderPainted = false
    }

    override fun paintComponent(g: Graphics) {
        g.clearRect(0, 0, width, height)
        g.color = if (hasFocus()) Color.GRAY else Color.DARK_GRAY
        g.fillOval(0, 0, width, height)
    }
}
