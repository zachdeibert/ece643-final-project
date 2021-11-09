package ece643.libhwio

import ece643.sim.Button
import java.awt.event.WindowAdapter
import java.awt.event.WindowEvent
import javax.swing.JFrame

class Interrupt(window: JFrame, buttons: Array<Button>) {
    private var enableMask = 0
    private var activeMask = 0

    init {
        window.addWindowListener(object : WindowAdapter() {
            override fun windowClosing(e: WindowEvent?) {
                activeMask = activeMask.or(enableMask.and(0x000F0000))
            }
        })
        buttons.forEachIndexed { i, button ->
            val mask = 1.shl(if (i < 10) 9 - i else 29 - i)
            button.addActionListener {
                activeMask = activeMask.or(enableMask.and(mask))
            }
        }
    }

    fun enable(mask: Int) {
        try {
            enableMask = enableMask.or(mask)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun disable(mask: Int) {
        try {
            enableMask = enableMask.and(mask.inv())
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun poll(mask: Int): Int {
        try {
            val match = activeMask.and(mask)
            activeMask = activeMask.and(match.inv())
            return match
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return 0
    }
}
