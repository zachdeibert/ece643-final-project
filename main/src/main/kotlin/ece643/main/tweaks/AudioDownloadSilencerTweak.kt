package ece643.main.tweaks

import ece643.main.Tweak
import org.objectweb.asm.Label
import org.objectweb.asm.Opcodes
import org.objectweb.asm.tree.MethodNode

class AudioDownloadSilencerTweak : Tweak {
    override val className = "ng"

    override fun matches(method: MethodNode): Boolean {
        return method.name == "run"
    }

    override fun transform(method: MethodNode) {
        method.instructions.clear()
        method.localVariables.clear()
        method.tryCatchBlocks.clear()
        val label = Label()
        method.visitLabel(label)
        method.visitLineNumber(9001, label)
        method.visitInsn(Opcodes.RETURN)
    }
}
