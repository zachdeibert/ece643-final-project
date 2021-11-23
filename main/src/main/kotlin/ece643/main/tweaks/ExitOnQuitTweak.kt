package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.*

class ExitOnQuitTweak : Tweak {
    override val className = "nd"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "()V" || method.desc == "(Lct;)V"
    }

    override fun transform(method: MethodNode) {
        if (method.desc == "(Lct;)V") {
            val iterator = method.instructions.iterator()
            while (iterator.hasNext()) {
                val ins = iterator.next() as AbstractInsnNode
                if (ins.opcode == Opcodes.NEW
                    && ins is TypeInsnNode
                    && ins.desc == "eh") {
                    method.instructions.insertBefore(ins, InsnNode(Opcodes.DUP))
                    method.instructions.insertBefore(ins, MethodInsnNode(Opcodes.INVOKEVIRTUAL, "net/minecraft/client/Minecraft", "f", "()V"))
                    break
                }
            }
        } else {
            val iterator = method.instructions.iterator()
            while (iterator.hasNext()) {
                val ins = iterator.next() as AbstractInsnNode
                if (ins.opcode == Opcodes.LDC
                    && ins is LdcInsnNode
                    && ins.cst == "Save and quit to title") {
                    ins.cst = "Quit ECE643 final project"
                    break
                }
            }
        }
    }
}
