package ece643.main

import ece643.libbusiness.Business

fun main() {
    var mc: MinecraftLauncher? = null
    try {
        Business()::run {
            mc = MinecraftLauncher()
        }
    } finally {
        mc?.close();
    }
}
