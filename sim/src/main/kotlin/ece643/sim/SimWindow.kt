package ece643.sim

import java.awt.Dimension
import javax.swing.JFrame
import javax.swing.SpringLayout

class SimWindow : JFrame() {
    companion object {
        private const val NORTH = SpringLayout.NORTH
        private const val HORIZONTAL_CENTER = SpringLayout.HORIZONTAL_CENTER
    }

    val vga = VGAView()

    init {
        title = "ECE643 Final Project Simulator"
        size = Dimension(640, 580)
        minimumSize = size
        preferredSize = size
        defaultCloseOperation = EXIT_ON_CLOSE
        contentPane.apply {
            val layout = SpringLayout()
            setLayout(layout)

            add(vga)
            layout.putConstraint(NORTH, vga, 0, NORTH, this)
            layout.putConstraint(HORIZONTAL_CENTER, vga, 0, HORIZONTAL_CENTER, this)
        }
        isVisible = true
        toFront()
        requestFocus()
        state = NORMAL
    }
}
