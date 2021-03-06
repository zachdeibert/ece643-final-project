package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.MethodNode
import java.awt.Dimension
import java.awt.Frame
import java.awt.Robot
import java.awt.event.InputEvent
import javax.imageio.ImageIO

class MainTweak : Tweak {
    companion object {
        fun inject() {
            ImageIO.setUseCache(false)
            val frame = Frame.getFrames().last()
            frame.title = "ECE643 Final Project"
            frame.size = Dimension(640, 480)
            val robot = Robot()
            robot.mouseMove(frame.x + frame.width / 2, frame.y + frame.height / 2)
            robot.mousePress(InputEvent.BUTTON1_DOWN_MASK)
            robot.mouseRelease(InputEvent.BUTTON1_DOWN_MASK)
        }
    }

    override val className = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.name == "main"
    }

    override fun transform(method: MethodNode) {
        val injectCode = MethodNode()
        val injectLabel = Label()
        injectCode.visitLabel(injectLabel)
        injectCode.visitLineNumber(9001, injectLabel)
        val self = MainTweak::class.qualifiedName!!.replace('.', '/')
        injectCode.visitFieldInsn(Opcodes.GETSTATIC, self, "Companion", "L${self}\$Companion;")
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "${self}\$Companion", "inject", "()V")
        val iterator = method.instructions.iterator()
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.RETURN) {
                method.instructions.insertBefore(ins, injectCode.instructions)
                break
            }
        }
    }
}
