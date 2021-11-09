package ece643.libbusiness

import java.io.File

class Business {
    init {
        System.load(File(File(Business::class.java.protectionDomain.codeSource.location.toURI()).parentFile, "libmain.so").absolutePath)
    }

    external fun run(setup: Runnable)
}
