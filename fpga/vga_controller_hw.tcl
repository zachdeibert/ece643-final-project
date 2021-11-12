# TCL File Generated by Component Editor 20.1
# Wed Nov 03 14:49:35 CDT 2021
# DO NOT MODIFY


# 
# vga_controller "VGA Controller" v1.0
#  2021.11.03.14:49:35
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module vga_controller
# 
set_module_property DESCRIPTION ""
set_module_property NAME vga_controller
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME "VGA Controller"
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL vga_controller
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE true
add_fileset_file vga_controller.v VERILOG PATH src/vga_controller.v TOP_LEVEL_FILE


# 
# parameters
# 


# 
# display items
# 


# 
# connection point avalon
# 
add_interface avalon avalon end
set_interface_property avalon addressUnits WORDS
set_interface_property avalon associatedClock clk
set_interface_property avalon associatedReset reset
set_interface_property avalon bitsPerSymbol 8
set_interface_property avalon burstOnBurstBoundariesOnly false
set_interface_property avalon burstcountUnits WORDS
set_interface_property avalon explicitAddressSpan 0
set_interface_property avalon holdTime 0
set_interface_property avalon linewrapBursts false
set_interface_property avalon maximumPendingReadTransactions 0
set_interface_property avalon maximumPendingWriteTransactions 0
set_interface_property avalon readLatency 0
set_interface_property avalon readWaitTime 1
set_interface_property avalon setupTime 0
set_interface_property avalon timingUnits Cycles
set_interface_property avalon writeWaitTime 0
set_interface_property avalon ENABLED true
set_interface_property avalon EXPORT_OF ""
set_interface_property avalon PORT_NAME_MAP ""
set_interface_property avalon CMSIS_SVD_VARIABLES ""
set_interface_property avalon SVD_ADDRESS_GROUP ""

add_interface_port avalon write write Input 1
add_interface_port avalon writedata writedata Input 32
add_interface_port avalon address address Input 18
add_interface_port avalon byteenable byteenable Input 4
set_interface_assignment avalon embeddedsw.configuration.isFlash 0
set_interface_assignment avalon embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon embeddedsw.configuration.isPrintableDevice 0


# 
# connection point sdram
# 
add_interface sdram conduit end
set_interface_property sdram associatedClock clk
set_interface_property sdram associatedReset reset
set_interface_property sdram ENABLED true
set_interface_property sdram EXPORT_OF ""
set_interface_property sdram PORT_NAME_MAP ""
set_interface_property sdram CMSIS_SVD_VARIABLES ""
set_interface_property sdram SVD_ADDRESS_GROUP ""

add_interface_port sdram dram_dq dram_dq Bidir 16
add_interface_port sdram dram_addr dram_addr Output 13
add_interface_port sdram dram_ba dram_ba Output 2
add_interface_port sdram dram_clk dram_clk Output 1
add_interface_port sdram dram_cke dram_cke Output 1
add_interface_port sdram dram_ldqm dram_ldqm Output 1
add_interface_port sdram dram_udqm dram_udqm Output 1
add_interface_port sdram dram_we_n dram_we_n Output 1
add_interface_port sdram dram_cas_n dram_cas_n Output 1
add_interface_port sdram dram_ras_n dram_ras_n Output 1
add_interface_port sdram dram_cs_n dram_cs_n Output 1


# 
# connection point vga
# 
add_interface vga conduit end
set_interface_property vga associatedClock clk
set_interface_property vga associatedReset reset
set_interface_property vga ENABLED true
set_interface_property vga EXPORT_OF ""
set_interface_property vga PORT_NAME_MAP ""
set_interface_property vga CMSIS_SVD_VARIABLES ""
set_interface_property vga SVD_ADDRESS_GROUP ""

add_interface_port vga vga_r vga_r Output 8
add_interface_port vga vga_g vga_g Output 8
add_interface_port vga vga_b vga_b Output 8
add_interface_port vga vga_clk vga_clk Output 1
add_interface_port vga vga_sync_n vga_sync_n Output 1
add_interface_port vga vga_blank_n vga_blank_n Output 1
add_interface_port vga vga_vs vga_vs Input 1
add_interface_port vga vga_hs vga_hs Input 1


# 
# connection point clk
# 
add_interface clk clock end
set_interface_property clk clockRate 0
set_interface_property clk ENABLED true
set_interface_property clk EXPORT_OF ""
set_interface_property clk PORT_NAME_MAP ""
set_interface_property clk CMSIS_SVD_VARIABLES ""
set_interface_property clk SVD_ADDRESS_GROUP ""

add_interface_port clk clk clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clk
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset reset Input 1

