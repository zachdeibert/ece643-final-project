`timescale 1 ps / 1 ps

module interrupt_controller(
        input  wire [1:0]  address,      //      avalon.address
        input  wire [3:0]  byteenable,   //            .byteenable
        output wire [31:0] readdata,     //            .readdata
        input  wire [31:0] writedata,    //            .writedata
        input  wire        write,        //            .write
        input  wire        clk,          //         clk.clk
        input  wire [3:0]  irq_buttons,  // irq_buttons.irq_buttons
        input  wire [9:0]  irq_switches, //            .irq_switches
        input  wire        irq_ps2,      //     irq_ps2.irq_ps2
        input  wire        reset         //       reset.reset
    );

    assign readdata = 32'b00000000000000000000000000000000;

endmodule
