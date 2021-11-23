package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.AbstractInsnNode
import org.objectweb.asm.tree.MethodNode

class TimeTweak : Tweak {
    companion object {
        private val tls = InheritableThreadLocal<Array<Long>>()

        val time: Long
            get() = tls.get()[0] % 24000L

        fun setTime(time: Long) {
            tls.get()[0] = time
        }

        fun initContext() {
            tls.set(arrayOf(0L))
        }
    }

    override val className = "si"

    override fun matches(method: MethodNode): Boolean {
        return method.desc == "(J)V" && method.name == "a"
    }

    override fun transform(method: MethodNode) {
        val injectCode = MethodNode()
        val injectLabel = Label()
        injectCode.visitLabel(injectLabel)
        injectCode.visitLineNumber(9001, injectLabel)
        val self = TimeTweak::class.qualifiedName!!.replace('.', '/')
        injectCode.visitFieldInsn(Opcodes.GETSTATIC, self, "Companion", "L${self}\$Companion;")
        injectCode.visitVarInsn(Opcodes.LLOAD, 1)
        injectCode.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "${self}\$Companion", "setTime", "(J)V")
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
