package ece643.main

import org.objectweb.asm.tree.MethodNode

interface Tweak {
    val className: String

    fun matches(method: MethodNode): Boolean

    fun transform(method: MethodNode)
}
