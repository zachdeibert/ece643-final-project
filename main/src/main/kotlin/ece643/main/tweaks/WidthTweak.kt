package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.IntInsnNode
import org.objectweb.asm.tree.MethodNode

class WidthTweak : Tweak {
    override val className: String = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
    }

    override fun transform(method: MethodNode) {
        val iterator = method.instructions.iterator()
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.SIPUSH
                && ins is IntInsnNode
                && ins.operand == 854) {
                ins.operand = 640
            }
        }
    }
}
