package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.MethodInsnNode
import org.objectweb.asm.tree.MethodNode
import java.awt.Frame

class UndecoratedWindowTweak : Tweak {
    override val className = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
    }

    override fun transform(method: MethodNode) {
        val injectCode = MethodNode()
        val injectLabel = Label()
        injectCode.visitLabel(injectLabel)
        injectCode.visitLineNumber(9001, injectLabel)
        injectCode.visitInsn(Opcodes.DUP)
        injectCode.visitInsn(Opcodes.ICONST_1)
        val frame = Frame::class.qualifiedName!!.replace('.', '/')
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, frame, "setUndecorated", "(Z)V")
        val iterator = method.instructions.iterator()
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.INVOKESPECIAL
                && ins is MethodInsnNode
                && ins.desc == "(Ljava/lang/String;)V"
                && ins.name == "<init>"
                && ins.owner == frame) {
                method.instructions.insert(ins, injectCode.instructions)
                break
            }
        }
    }
}
