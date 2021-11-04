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
        output reg  [6:0]  sevenseg4,  //       .sevenseg4
        output wire [6:0]  sevenseg5   //       .sevenseg5
    );

    reg [3:0] hourTens;
    reg [3:0] hourOnes;
    reg [3:0] minuteTens;
    reg [3:0] minuteOnes;

    seven_segment ss0(.in(hourTens), .out(sevenseg0));
    seven_segment ss1(.in(hourOnes), .out(sevenseg1));
    seven_segment ss2(.in(minuteTens), .out(sevenseg2));
    seven_segment ss3(.in(minuteOnes), .out(sevenseg3));

    always @(posedge clk or posedge reset) begin
        if (reset)
            leds <= 0;
        else if (write) begin
            if(byteenable[0])
                leds[7:0] <= writedata[7:0];

            if(byteenable[1])
                leds[9:8] <= writedata[9:8];

            if (byteenable[2]) begin
                minuteOnes <= writedata[21:16] % 10;
                minuteTens <= writedata[21:16] / 10;
            end

            if (byteenable[3]) begin
                hourOnes <= writedata[27:24] % 10;
                hourTens <= writedata[27:24] / 10;
                if (writedata[28]) begin
                    sevenseg4 <= 7'b0001000;
                end else begin
                    sevenseg4 <= 7'b0011000;
                end
            end
        end
    end

    assign sevenseg5 = 7'b0001001;

endmodule
