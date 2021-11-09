`timescale 1 ps / 1 ps

module led_controller(
        input  wire [3:0]  byteenable, // avalon.byteenable
        input  wire [31:0] writedata,  //       .writedata
        input  wire        write,      //       .write
        input  wire        clk,        //    clk.clk
        input  wire        reset,      //  reset.reset
        output reg  [9:0]  leds,       //   leds.leds
        output wire [6:0]  sevenseg0,  //       .sevenseg0
        output reg  [6:0]  sevenseg1,  //       .sevenseg1
        output wire [6:0]  sevenseg2,  //       .sevenseg2
        output wire [6:0]  sevenseg3,  //       .sevenseg3
        output wire [6:0]  sevenseg4,  //       .sevenseg4
        output wire [6:0]  sevenseg5   //       .sevenseg5
    );

    reg [3:0] hourTens;
    reg [3:0] hourOnes;
    reg [3:0] minuteTens;
    reg [3:0] minuteOnes;

    seven_segment ss5(.in(hourTens), .out(sevenseg5));
    seven_segment ss4(.in(hourOnes), .out(sevenseg4));
    seven_segment ss3(.in(minuteTens), .out(sevenseg3));
    seven_segment ss2(.in(minuteOnes), .out(sevenseg2));

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
                    sevenseg1 <= 7'b0001100;
                end else begin
                    sevenseg1 <= 7'b0001000;
                end
            end
        end
    end

    assign sevenseg0 = 7'b0101011;

endmodule
