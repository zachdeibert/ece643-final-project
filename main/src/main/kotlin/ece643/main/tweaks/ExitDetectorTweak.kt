package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.*
import java.awt.Frame

class ExitDetectorTweak : Tweak {
    companion object {
        private val tls = InheritableThreadLocal<Array<Boolean>>()

        val exited: Boolean
            get() = tls.get()[0]

        fun exit() {
            Frame.getFrames().forEach { it.dispose() }
            tls.get()[0] = true
        }

        fun exit(@Suppress("UNUSED_PARAMETER") code: Int) {
            exit()
        }

        fun initContext() {
            tls.set(arrayOf(false))
        }
    }

    override val className = "net.minecraft.client.Minecraft"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "()V"
    }

    override fun transform(method: MethodNode) {
        val injectCode = MethodNode()
        val injectLabel = Label()
        injectCode.visitLabel(injectLabel)
        injectCode.visitLineNumber(9001, injectLabel)
        val self = ExitDetectorTweak::class.qualifiedName!!.replace('.', '/')
        injectCode.visitFieldInsn(Opcodes.GETSTATIC, self, "Companion", "L${self}\$Companion;")
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "${self}\$Companion", "exit", "()V")
        val iterator = method.instructions.iterator()
        var match = false
        while (iterator.hasNext()) {
            val ins = iterator.next() as AbstractInsnNode
            if (ins.opcode == Opcodes.INVOKESTATIC
                && ins is MethodInsnNode
                && ins.owner == "java/lang/System"
                && ins.name == "exit"
                && ins.desc == "(I)V") {
                match = true
                method.instructions.insertBefore(ins, FieldInsnNode(Opcodes.GETSTATIC, self, "Companion", "L${self}\$Companion;"))
                method.instructions.insertBefore(ins, InsnNode(Opcodes.SWAP))
                ins.opcode = Opcodes.INVOKEVIRTUAL
                ins.owner = "${self}\$Companion"
            } else if (match && ins.opcode == Opcodes.RETURN) {
                method.instructions.insertBefore(ins, injectCode.instructions)
                break
            }
        }
    }
}
