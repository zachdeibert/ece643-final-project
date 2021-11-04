`timescale 1 ps / 1 ps

module led_controller(
        input  wire [3:0]  byteenable, // avalon.byteenable
        input  wire [31:0] writedata,  //       .writedata
        input  wire        write,      //       .write
        input  wire        clk,        //    clk.clk
        input  wire        reset,      //  reset.reset
        output reg  [9:0]  leds,       //   leds.leds
        output wire [6:0]  sevenseg0,  //       .sevenseg0
        output wire [6:0]  sevenseg1,  //       .sevenseg1
        output wire [6:0]  sevenseg2,  //       .sevenseg2
        output wire [6:0]  sevenseg3,  //       .sevenseg3
        output wire [6:0]  sevenseg4,  //       .sevenseg4
        output wire [6:0]  sevenseg5   //       .sevenseg5
    );

    always @(posedge clk or posedge reset) begin
        if (reset)
            leds <= 0;
        else if (write) begin
            if(byteenable[0])
                leds[7:0] <= writedata[7:0];

            if(byteenable[1])
                leds[9:8] <= writedata[9:8];
        end
    end

   /*
    reg [31:0] clk_cnt = 32'd0;

    always @(posedge clk or posedge reset) begin
        if (reset)
            leds <= 0;
        else begin
            clk_cnt = clk_cnt + 1;
            if(clk_cnt == 32'd50000000) begin
                clk_cnt = 32'd0;
                leds = ~leds;
            end
        end
    end
    */

    assign sevenseg0 = 7'b0000000;
    assign sevenseg1 = 7'b0000000;
    assign sevenseg2 = 7'b0000000;
    assign sevenseg3 = 7'b0000000;
    assign sevenseg4 = 7'b0000000;
    assign sevenseg5 = 7'b0000000;

endmodule
