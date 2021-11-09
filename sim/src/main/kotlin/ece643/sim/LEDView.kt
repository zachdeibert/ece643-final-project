package ece643.sim

import java.awt.Color
import java.awt.Dimension
import java.awt.Graphics
import javax.swing.JComponent

class LEDView : JComponent() {
    private var _active = false
    var active: Boolean
        get() = _active
        set(value) {
            _active = value
            repaint()
        }

    init {
        minimumSize = Dimension(25, 25)
        maximumSize = minimumSize
        preferredSize = minimumSize
    }

    override fun paintComponent(g: Graphics) {
        g.clearRect(0, 0, width, height)
        g.color = if (active) Color.RED else Color.GRAY
        g.fillOval(0, 0, width, height)
    }
}
