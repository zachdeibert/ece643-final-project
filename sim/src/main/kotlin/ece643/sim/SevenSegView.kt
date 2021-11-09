package ece643.sim

import java.awt.Color
import javax.swing.JLabel

class SevenSegView : JLabel() {
    init {
        foreground = Color.RED
        font = font.deriveFont(25f)
    }

    fun update(hours: Int, minutes: Int, pm: Boolean) {
        text = "${if (hours == 0) 12 else hours}:${minutes.toString().padStart(2, '0')} ${if (pm) "PM" else "AM"}"
    }
}
