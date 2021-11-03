`timescale 1 ps / 1 ps

module button_controller(
        input  wire       clk,          //     clk.clk
        input  wire       reset,        //   reset.reset
        output wire [3:0] irq_buttons,  //     irq.irq_buttons
        output wire [9:0] irq_switches, //        .irq_switches
        input  wire [3:0] buttons,      // buttons.buttons
        input  wire [9:0] switches      //        .switches
    );

    assign irq_buttons = 4'b0000;
    assign irq_switches = 10'b0000000000;

endmodule
