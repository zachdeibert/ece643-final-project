`timescale 1 ps / 1 ps

module ps2_controller(
        input  wire [3:0] address,   // avalon.address
        output wire [7:0] readdata,  //       .readdata
        input  wire       write,     //       .write
        input  wire [7:0] writedata, //       .writedata
        input  wire       clk,       //    clk.clk
        input  wire       reset,     //  reset.reset
        output wire       irq_ps2,   //    irq.irq_ps2
        input  wire       ps2_data,  //    ps2.data
        input  wire       ps2_clk    //       .ps2_clk
    );

    assign irq_ps2 = 1'b0;
    assign readdata = 8'b00000000;

endmodule
