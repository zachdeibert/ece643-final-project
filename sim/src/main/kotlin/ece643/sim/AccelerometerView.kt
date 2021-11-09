package ece643.sim

import javax.swing.*

class AccelerometerView : JPanel() {
    companion object {
        private const val NORTH = SpringLayout.NORTH
        private const val EAST = SpringLayout.EAST
        private const val SOUTH = SpringLayout.SOUTH
        private const val WEST = SpringLayout.WEST
        private const val HORIZONTAL_CENTER = SpringLayout.HORIZONTAL_CENTER
        private const val VERTICAL_CENTER = SpringLayout.VERTICAL_CENTER
    }

    private val sliders = arrayOf(
        JSlider(JSlider.HORIZONTAL, -512, 512, 0),
        JSlider(JSlider.HORIZONTAL, -512, 512, 0),
        JSlider(JSlider.HORIZONTAL, -512, 512, 256))

    val values: Array<Short>
        get() = arrayOf(sliders[0].value.toShort(), sliders[1].value.toShort(), sliders[2].value.toShort())

    init {
        sliders.forEach {
            it.majorTickSpacing = 256
            it.minorTickSpacing = 32
            it.paintTicks = true
            it.paintLabels = true
        }

        val layout = SpringLayout()
        setLayout(layout)

        val title = JLabel("Accelerometer")
        add(title)
        layout.putConstraint(NORTH, title, 0, NORTH, this)
        layout.putConstraint(HORIZONTAL_CENTER, title, 0, HORIZONTAL_CENTER, this)

        val labels = arrayOf(JLabel("X:"), JLabel("Y:"), JLabel("Z:"))
        add(sliders[0])
        layout.putConstraint(NORTH, sliders[0], 10, SOUTH, title)
        layout.putConstraint(EAST, sliders[0], 0, EAST, this)
        add(labels[0])
        layout.putConstraint(VERTICAL_CENTER, labels[0], 0, VERTICAL_CENTER, sliders[0])
        layout.putConstraint(WEST, labels[0], 0, WEST, this)
        layout.putConstraint(WEST, sliders[0], 10, EAST, labels[0])
        layout.putConstraint(EAST, sliders[0], Spring.constant(300, 300, Int.MAX_VALUE), WEST, sliders[0])
        layout.putConstraint(EAST, this, 0, EAST, sliders[0])
        for (i in 1 until 3) {
            add(sliders[i])
            layout.putConstraint(NORTH, sliders[i], 10, SOUTH, sliders[i - 1])
            layout.putConstraint(EAST, sliders[i], 0, EAST, this)
            layout.putConstraint(WEST, sliders[i], 0, WEST, sliders[i - 1])
            add(labels[i])
            layout.putConstraint(VERTICAL_CENTER, labels[i], 0, VERTICAL_CENTER, sliders[i])
            layout.putConstraint(WEST, labels[0], 0, WEST, this)
        }
        layout.putConstraint(SOUTH, this, 0, SOUTH, sliders[2])
    }
}
