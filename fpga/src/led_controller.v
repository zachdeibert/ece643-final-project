`timescale 1 ps / 1 ps

module led_controller(
        input  wire [3:0]  byteenable, // avalon.byteenable
        input  wire [31:0] writedata,  //       .writedata
        input  wire        write,      //       .write
        input  wire        clk,        //    clk.clk
        input  wire        reset,      //  reset.reset
        output wire [9:0]  leds,       //   leds.leds
        output wire [6:0]  sevenseg0,  //       .sevenseg0
        output wire [6:0]  sevenseg1,  //       .sevenseg1
        output wire [6:0]  sevenseg2,  //       .sevenseg2
        output wire [6:0]  sevenseg3,  //       .sevenseg3
        output wire [6:0]  sevenseg4,  //       .sevenseg4
        output wire [6:0]  sevenseg5   //       .sevenseg5
    );

    assign leds = 10'b0000000000;
    assign sevenseg0 = 7'b0000000;
    assign sevenseg1 = 7'b0000000;
    assign sevenseg2 = 7'b0000000;
    assign sevenseg3 = 7'b0000000;
    assign sevenseg4 = 7'b0000000;
    assign sevenseg5 = 7'b0000000;

endmodule
