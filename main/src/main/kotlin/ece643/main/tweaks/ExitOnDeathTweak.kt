package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.MethodNode

class ExitOnDeathTweak : Tweak {
    override val className = "j"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "()V" && method.name != "<init>"
    }

    override fun transform(method: MethodNode) {
        method.instructions.clear()
        method.localVariables.clear()
        method.tryCatchBlocks.clear()
        val label = Label()
        method.visitLabel(label)
        method.visitLineNumber(9001, label)
        method.visitVarInsn(Opcodes.ALOAD, 0)
        method.visitFieldInsn(Opcodes.GETFIELD, "xe", "l", "Lnet/minecraft/client/Minecraft;")
        method.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "net/minecraft/client/Minecraft", "f", "()V")
        method.visitInsn(Opcodes.RETURN)
    }
}
