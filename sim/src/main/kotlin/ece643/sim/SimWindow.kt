package ece643.sim

import java.awt.Dimension
import javax.swing.JFrame
import javax.swing.SpringLayout

class SimWindow : JFrame() {
    companion object {
        private const val NORTH = SpringLayout.NORTH
        private const val EAST = SpringLayout.EAST
        private const val SOUTH = SpringLayout.SOUTH
        private const val WEST = SpringLayout.WEST
        private const val HORIZONTAL_CENTER = SpringLayout.HORIZONTAL_CENTER
        private const val VERTICAL_CENTER = SpringLayout.VERTICAL_CENTER
    }

    val vga = VGAView()
    val leds = Array(10) { _ -> LEDView() }
    val sevenseg = SevenSegView()
    val buttons = Array(14) { _ -> Button() }

    init {
        title = "ECE643 Final Project Simulator"
        size = Dimension(640, 580)
        minimumSize = size
        preferredSize = size
        defaultCloseOperation = DO_NOTHING_ON_CLOSE
        contentPane.apply {
            val layout = SpringLayout()
            setLayout(layout)

            add(vga)
            layout.putConstraint(NORTH, vga, 0, NORTH, this)
            layout.putConstraint(HORIZONTAL_CENTER, vga, 0, HORIZONTAL_CENTER, this)

            add(leds[0])
            layout.putConstraint(NORTH, leds[0], 10, SOUTH, vga)
            layout.putConstraint(WEST, leds[0], 10, WEST, this)
            for (i in 1 until 10) {
                add(leds[i])
                layout.putConstraint(VERTICAL_CENTER, leds[i], 0, VERTICAL_CENTER, leds[i - 1])
                layout.putConstraint(WEST, leds[i], 10, EAST, leds[i - 1])
            }

            for (i in 0 until 10) {
                add(buttons[i])
                layout.putConstraint(NORTH, buttons[i], 10, SOUTH, leds[i])
                layout.putConstraint(HORIZONTAL_CENTER, buttons[i], 0, HORIZONTAL_CENTER, leds[i])
            }
            add(buttons[10])
            layout.putConstraint(VERTICAL_CENTER, buttons[10], 0, VERTICAL_CENTER, buttons[9])
            layout.putConstraint(WEST, buttons[10], 45, EAST, buttons[9])
            for (i in 11 until 14) {
                add(buttons[i])
                layout.putConstraint(VERTICAL_CENTER, buttons[i], 0, VERTICAL_CENTER, buttons[i - 1])
                layout.putConstraint(WEST, buttons[i], 10, EAST, buttons[i - 1])
            }

            add(sevenseg)
            layout.putConstraint(VERTICAL_CENTER, sevenseg, 0, VERTICAL_CENTER, leds[9])
            layout.putConstraint(EAST, sevenseg, 0, EAST, buttons[13])
        }
        isVisible = true
        toFront()
        requestFocus()
        state = NORMAL
    }
}
