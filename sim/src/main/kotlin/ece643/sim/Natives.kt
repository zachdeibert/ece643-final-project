package ece643.sim

import java.io.File;

class Natives {
    init {
        System.load(File(File(Natives::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libsim.so").absolutePath)
    }

    external fun init()
}
