package ece643.main.tweaks

import ece643.main.Tweak
import org.lwjgl.input.Controllers
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.FieldInsnNode
import org.objectweb.asm.tree.MethodInsnNode
import org.objectweb.asm.tree.MethodNode

class ControllerInitTweak : Tweak {
    companion object {
        fun create() {
        }
    }

    override val className = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "()V"
    }

    override fun transform(method: MethodNode) {
        val iterator = method.instructions.iterator()
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.INVOKESTATIC
                && ins is MethodInsnNode
                && ins.desc == "()V"
                && ins.name == "create"
                && ins.owner == Controllers::class.qualifiedName!!.replace('.', '/')) {
                val self = ControllerInitTweak::class.qualifiedName!!.replace('.', '/')
                method.instructions.insertBefore(ins, FieldInsnNode(Opcodes.GETSTATIC, self, "Companion", "L${self}\$Companion;"))
                ins.opcode = Opcodes.INVOKEVIRTUAL
                ins.owner = "${self}\$Companion"
                break
            }
        }
    }
}
