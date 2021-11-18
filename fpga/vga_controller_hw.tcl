# TCL File Generated by Component Editor 20.1
# Thu Nov 18 13:08:00 CST 2021
# DO NOT MODIFY


# 
# vga_controller "VGA Controller" v1.0
#  2021.11.18.13:08:00
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
# connection point vga
# 
add_interface vga conduit end
set_interface_property vga associatedClock ""
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
add_interface_port vga vga_vs vga_vs Output 1
add_interface_port vga vga_hs vga_hs Output 1


# 
# connection point vga_clk_in
# 
add_interface vga_clk_in clock end
set_interface_property vga_clk_in clockRate 0
set_interface_property vga_clk_in ENABLED true
set_interface_property vga_clk_in EXPORT_OF ""
set_interface_property vga_clk_in PORT_NAME_MAP ""
set_interface_property vga_clk_in CMSIS_SVD_VARIABLES ""
set_interface_property vga_clk_in SVD_ADDRESS_GROUP ""

add_interface_port vga_clk_in vga_clk_in clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock vga_clk_in
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset reset Input 1


# 
# connection point vga_sink
# 
add_interface vga_sink avalon_streaming end
set_interface_property vga_sink associatedClock vga_clk_in
set_interface_property vga_sink associatedReset reset
set_interface_property vga_sink dataBitsPerSymbol 16
set_interface_property vga_sink errorDescriptor ""
set_interface_property vga_sink firstSymbolInHighOrderBits true
set_interface_property vga_sink maxChannel 0
set_interface_property vga_sink readyLatency 0
set_interface_property vga_sink ENABLED true
set_interface_property vga_sink EXPORT_OF ""
set_interface_property vga_sink PORT_NAME_MAP ""
set_interface_property vga_sink CMSIS_SVD_VARIABLES ""
set_interface_property vga_sink SVD_ADDRESS_GROUP ""

add_interface_port vga_sink vga_data data Input 16
add_interface_port vga_sink vga_ready ready Output 1
add_interface_port vga_sink vga_valid valid Input 1


# 
# connection point vga_frame_ctrl
# 
add_interface vga_frame_ctrl conduit end
set_interface_property vga_frame_ctrl associatedClock clk
set_interface_property vga_frame_ctrl associatedReset ""
set_interface_property vga_frame_ctrl ENABLED true
set_interface_property vga_frame_ctrl EXPORT_OF ""
set_interface_property vga_frame_ctrl PORT_NAME_MAP ""
set_interface_property vga_frame_ctrl CMSIS_SVD_VARIABLES ""
set_interface_property vga_frame_ctrl SVD_ADDRESS_GROUP ""

add_interface_port vga_frame_ctrl frame_start frame_start Output 1
add_interface_port vga_frame_ctrl frame_hold frame_hold Output 1


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