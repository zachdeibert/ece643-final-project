package ece643.main

import ece643.libbusiness.Business

fun main() {
    var mc: MinecraftLauncher? = null
    try {
        Business().run<Business, Unit> {
            mc = MinecraftLauncher()
        }
    } finally {
        mc?.close();
    }
}
