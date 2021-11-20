# 
#  Design Timing Constraints Definitions
# 
set_time_format -unit ns -decimal_places 3
# #############################################################################
#  Create Input reference clocks
create_clock -name {system_pll_ref_clk_clk} -period 50.000 -waveform { 0.000 25.000 }
create_clock -name {vga_pll_refclk_clk} -period 50.000 -waveform { 0.000 25.000 }

# #############################################################################
#  Now that we have created the custom clocks which will be base clocks,
#  derive_pll_clock is used to calculate all remaining clocks for PLLs
derive_pll_clocks -create_base_clocks
derive_clock_uncertainty