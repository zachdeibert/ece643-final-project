package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.InsnNode
import org.objectweb.asm.tree.MethodInsnNode
import org.objectweb.asm.tree.MethodNode
import java.util.*

class ImplTweak : Tweak {
    companion object {
        const val worldDir = "ece643-world"
    }

    override val className = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.name == "run"
    }

    override fun transform(method: MethodNode) {
        val injectCode = MethodNode()
        val injectLabel = Label()
        injectCode.visitLabel(injectLabel)
        injectCode.visitLineNumber(9001, injectLabel)
        injectCode.visitInsn(Opcodes.DUP)
        injectCode.visitInsn(Opcodes.DUP)
        injectCode.visitTypeInsn(Opcodes.NEW, "dm")
        injectCode.visitInsn(Opcodes.DUP)
        injectCode.visitVarInsn(Opcodes.ALOAD, 0)
        injectCode.visitMethodInsn(Opcodes.INVOKESPECIAL, "dm", "<init>", "(Lnet/minecraft/client/Minecraft;)V")
        injectCode.visitFieldInsn(Opcodes.PUTFIELD, "net/minecraft/client/Minecraft", "c", "Laes;")
        injectCode.visitLdcInsn(worldDir)
        injectCode.visitLdcInsn("ECE643 Final Project")
        injectCode.visitTypeInsn(Opcodes.NEW, "yw")
        injectCode.visitInsn(Opcodes.DUP)
        injectCode.visitLdcInsn(Random().nextLong())
        injectCode.visitInsn(Opcodes.ICONST_0)
        injectCode.visitInsn(Opcodes.ICONST_1)
        injectCode.visitInsn(Opcodes.ICONST_0)
        injectCode.visitMethodInsn(Opcodes.INVOKESPECIAL, "yw", "<init>", "(JIZZ)V")
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "net/minecraft/client/Minecraft", "a", "(Ljava/lang/String;Ljava/lang/String;Lyw;)V")
        injectCode.visitInsn(Opcodes.ACONST_NULL)
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "net/minecraft/client/Minecraft", "a", "(Lxe;)V")
        val iterator = method.instructions.iterator()
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.INVOKEVIRTUAL
                && ins is MethodInsnNode
                && ins.desc == "()V"
                && ins.owner == "net/minecraft/client/Minecraft") {
                method.instructions.insertBefore(ins, InsnNode(Opcodes.DUP))
                method.instructions.insert(ins, injectCode.instructions)
                break
            }
        }
    }
}
