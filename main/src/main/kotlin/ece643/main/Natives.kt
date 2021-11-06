package ece643.main

import java.io.File;

class Natives {
    init {
        System.load(File(File(Natives::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libmain.so").absolutePath)
    }

    external fun init()
}
