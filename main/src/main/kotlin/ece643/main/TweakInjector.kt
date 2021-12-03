package ece643.main

import ece643.main.tweaks.*
import net.minecraft.launchwrapper.IClassTransformer
import org.objectweb.asm.ClassReader
import org.objectweb.asm.ClassWriter
import org.objectweb.asm.tree.ClassNode
import org.objectweb.asm.tree.MethodNode

class TweakInjector : IClassTransformer {
    companion object {
        private val tweaks = arrayOf(
            AudioDownloadSilencerTweak(),
            ControllerInitTweak(),
            ExitDetectorTweak(),
            ExitOnDeathTweak(),
            ExitOnQuitTweak(),
            ImageDownloadSilencerTweak(),
            ImplTweak(),
            MainTweak(),
            TimeTweak(),
            UndecoratedWindowTweak(),
            WidthTweak())
    }

    init {
        // Preload Kotlin extensions so ClassLoader doesn't detect circular reference
        val str = ""
        str == ""
    }

    override fun transform(name: String?, transformedName: String?, bytes: ByteArray?): ByteArray? {
        if (bytes == null) {
            return null
        }
        val tweaks = tweaks.filter { name == it.className }
        if (tweaks.isEmpty()) {
            return bytes
        }
        val classNode = ClassNode()
        val classReader = ClassReader(bytes)
        classReader.accept(classNode, ClassReader.EXPAND_FRAMES)
        var any = false
        tweaks.forEach { tweak ->
            classNode.methods.mapNotNull { it as? MethodNode }.filter { tweak.matches(it) }.map {
                tweak.transform(it)
                any = true
            }
        }
        if (!any) {
            return bytes
        }
        val writer = ClassWriter(ClassWriter.COMPUTE_MAXS.or(ClassWriter.COMPUTE_FRAMES))
        classNode.accept(writer)
        return writer.toByteArray()
    }
}
