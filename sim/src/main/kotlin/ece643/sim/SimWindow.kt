package ece643.sim

import javax.swing.JFrame
import javax.swing.JPanel
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
    val accelerometer = AccelerometerView()
    val ps2 = PS2View()

    init {
        title = "ECE643 Final Project Simulator"
        defaultCloseOperation = DO_NOTHING_ON_CLOSE
        contentPane.apply {
            val layout = SpringLayout()
            setLayout(layout)

            add(vga)
            layout.putConstraint(NORTH, vga, 0, NORTH, this)
            layout.putConstraint(WEST, vga, 0, WEST, this)

            val subpanel = JPanel().apply {
                val sublayout = SpringLayout()
                setLayout(sublayout)

                add(leds[0])
                sublayout.putConstraint(NORTH, leds[0], 0, NORTH, this)
                sublayout.putConstraint(WEST, leds[0], 0, WEST, this)
                for (i in 1 until 10) {
                    add(leds[i])
                    sublayout.putConstraint(VERTICAL_CENTER, leds[i], 0, VERTICAL_CENTER, leds[i - 1])
                    sublayout.putConstraint(WEST, leds[i], 10, EAST, leds[i - 1])
                }

                for (i in 0 until 10) {
                    add(buttons[i])
                    sublayout.putConstraint(NORTH, buttons[i], 10, SOUTH, leds[i])
                    sublayout.putConstraint(HORIZONTAL_CENTER, buttons[i], 0, HORIZONTAL_CENTER, leds[i])
                }
                add(buttons[10])
                sublayout.putConstraint(VERTICAL_CENTER, buttons[10], 0, VERTICAL_CENTER, buttons[9])
                sublayout.putConstraint(WEST, buttons[10], 45, EAST, buttons[9])
                for (i in 11 until 14) {
                    add(buttons[i])
                    sublayout.putConstraint(VERTICAL_CENTER, buttons[i], 0, VERTICAL_CENTER, buttons[i - 1])
                    sublayout.putConstraint(WEST, buttons[i], 10, EAST, buttons[i - 1])
                }
                sublayout.putConstraint(EAST, this, 0, EAST, buttons[13])
                sublayout.putConstraint(SOUTH, this, 0, SOUTH, buttons[13])

                add(sevenseg)
                sublayout.putConstraint(VERTICAL_CENTER, sevenseg, 0, VERTICAL_CENTER, leds[9])
                sublayout.putConstraint(EAST, sevenseg, 0, EAST, buttons[13])
            }
            add(subpanel)
            layout.putConstraint(NORTH, subpanel, 10, SOUTH, vga)
            layout.putConstraint(HORIZONTAL_CENTER, subpanel, 0, HORIZONTAL_CENTER, vga)
            layout.putConstraint(SOUTH, this, 10, SOUTH, subpanel)

            add(accelerometer)
            layout.putConstraint(NORTH, accelerometer, 10, NORTH, this)
            layout.putConstraint(WEST, accelerometer, 10, EAST, vga)
            layout.putConstraint(EAST, this, 10, EAST, accelerometer)

            add(ps2)
            layout.putConstraint(NORTH, ps2, 10, SOUTH, accelerometer)
            layout.putConstraint(EAST, ps2, -10, EAST, this)
            layout.putConstraint(SOUTH, ps2, -10, SOUTH, this)
            layout.putConstraint(WEST, ps2, 10, EAST, vga)
        }
        pack()
        isResizable = false
        setLocationRelativeTo(null)
        isVisible = true
        toFront()
        requestFocus()
        state = NORMAL
    }
}
