package ece643.sim

import java.awt.Color
import java.awt.Graphics
import java.awt.event.*
import javax.swing.*
import kotlin.math.sqrt

class PS2View : JPanel() {
    companion object {
        private const val DEAD_ZONE = 0.05f
        private const val DOT_SIZE = 8
        private const val TRIG_VAL = 0.7071067812f

        private const val NORTH = SpringLayout.NORTH
        private const val EAST = SpringLayout.EAST
        private const val SOUTH = SpringLayout.SOUTH
        private const val WEST = SpringLayout.WEST
        private const val HORIZONTAL_CENTER = SpringLayout.HORIZONTAL_CENTER
    }

    private var active = false
    var dx = 0f
        private set
    var dy = 0f
        private set
    var lmb = false
        private set
    var mmb = false
        private set
    var rmb = false
        private set

    init {
        val layout = SpringLayout()
        setLayout(layout)

        val title = JLabel("Mouse")
        add(title)
        layout.putConstraint(NORTH, title, 0, NORTH, this)
        layout.putConstraint(HORIZONTAL_CENTER, title, 0, HORIZONTAL_CENTER, this)

        val panel = object : JComponent() {
            init {
                addMouseListener(object : MouseAdapter() {
                    override fun mousePressed(e: MouseEvent) {
                        when (e.button) {
                            MouseEvent.BUTTON1 -> {
                                val x = e.x * 2f / width - 1
                                val y = e.y * 2f / height - 1
                                if (sqrt(x * x + y * y) <= DEAD_ZONE) {
                                    active = true
                                }
                            }
                            MouseEvent.BUTTON2 -> if (active) rmb = true
                            MouseEvent.BUTTON3 -> if (active) mmb = true
                        }
                    }

                    override fun mouseReleased(e: MouseEvent) {
                        when (e.button) {
                            MouseEvent.BUTTON1 -> mouseExited(e)
                            MouseEvent.BUTTON2 -> rmb = false
                            MouseEvent.BUTTON3 -> mmb = false
                        }
                    }

                    override fun mouseExited(e: MouseEvent) {
                        active = false
                        dx = 0f
                        dy = 0f
                        lmb = false
                        mmb = false
                        rmb = false
                    }
                })
                addMouseMotionListener(object : MouseMotionListener {
                    override fun mouseDragged(e: MouseEvent) {
                        mouseMoved(e)
                    }

                    override fun mouseMoved(e: MouseEvent) {
                        if (active) {
                            var x = e.x * 2f / width - 1
                            var y = e.y * 2f / height - 1
                            if (sqrt(x * x + y * y) <= DEAD_ZONE) {
                                x = 0f
                                y = 0f
                            }
                            dx = x
                            dy = y
                            repaint()
                        }
                    }

                })
                addKeyListener(object : KeyAdapter() {
                    override fun keyPressed(e: KeyEvent) {
                        if (active && e.keyChar == ' ') {
                            lmb = true
                        }
                    }

                    override fun keyReleased(e: KeyEvent) {
                        if (e.keyChar == ' ') {
                            lmb = false
                        }
                    }
                })
            }

            override fun paintComponent(g: Graphics) {
                run {
                    g.color = Color.WHITE
                    g.fillRect(0, 0, width, height)
                }
                run {
                    g.color = Color.DARK_GRAY
                    val rx = width * DEAD_ZONE
                    val ry = height * DEAD_ZONE
                    val cx = width / 2f
                    val cy = height / 2f
                    g.drawOval((cx - rx).toInt(), (cy - ry).toInt(), (2 * rx).toInt(), (2 * ry).toInt())
                    g.drawLine(0, 0, (cx - TRIG_VAL * rx).toInt(), (cy - TRIG_VAL * ry).toInt())
                    g.drawLine(0, height, (cx - TRIG_VAL * rx).toInt(), (cy + TRIG_VAL * ry).toInt())
                    g.drawLine(width, height, (cx + TRIG_VAL * rx).toInt(), (cy + TRIG_VAL * ry).toInt())
                    g.drawLine(width, 0, (cx + TRIG_VAL * rx).toInt(), (cy - TRIG_VAL * ry).toInt())
                }
                run {
                    g.color = Color.BLUE
                    val rx = DOT_SIZE / 2f
                    val ry = DOT_SIZE / 2f
                    val cx = (dx + 1) / 2 * width
                    val cy = (dy + 1) / 2 * height
                    g.fillOval((cx - rx).toInt(), (cy - ry).toInt(), DOT_SIZE, DOT_SIZE)
                }
            }
        }
        add(panel)
        layout.putConstraint(NORTH, panel, 10, SOUTH, title)
        layout.putConstraint(EAST, panel, 0, EAST, this)
        layout.putConstraint(SOUTH, panel, 0, SOUTH, this)
        layout.putConstraint(WEST, panel, 0, WEST, this)
    }
}
