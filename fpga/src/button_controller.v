`timescale 1 ps / 1 ps

module button_controller(
        input  wire       clk,          //     clk.clk
        input  wire       reset,        //   reset.reset
        output reg  [3:0] irq_buttons,  //     irq.irq_buttons
        output reg  [9:0] irq_switches, //        .irq_switches
        input  wire [3:0] buttons,      // buttons.buttons
        input  wire [9:0] switches      //        .switches
    );

    reg [9:0] last_switch;

    wire slow_clk;

    clock_divider #(.WIDTH(15), .COUNT(25000)) khz_div (.clk(clk), .clk_out(slow_clk));

    integer i;

    always @(posedge slow_clk or posedge reset) begin
        if(reset) begin
            irq_switches <= 10'b0;
            last_switch <= switches;
            irq_buttons <= 4'd0;
        end else begin
            for(i = 0; i < 10; i = i + 1) begin
                if(last_switch[i] != switches[i])
                    irq_switches[i] <= 1;
                else
                    irq_switches[i] <= 0;
            end
            irq_buttons <= ~buttons;
            last_switch <= switches;
        end
    end

endmodule
