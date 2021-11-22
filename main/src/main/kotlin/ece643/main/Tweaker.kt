package ece643.main

import net.minecraft.launchwrapper.LaunchClassLoader
import net.minecraft.launchwrapper.VanillaTweaker

class Tweaker : VanillaTweaker() {
    override fun injectIntoClassLoader(classLoader: LaunchClassLoader?) {
        classLoader!!.registerTransformer(TweakInjector::class.qualifiedName)
    }
}
