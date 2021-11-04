`timescale 1 ps / 1 ps

module button_controller(
        input  wire       clk,          //     clk.clk
        input  wire       reset,        //   reset.reset
        output wire [3:0] irq_buttons,  //     irq.irq_buttons
        output reg  [9:0] irq_switches, //        .irq_switches
        input  wire [3:0] buttons,      // buttons.buttons
        input  wire [9:0] switches      //        .switches
    );

    assign irq_buttons = (reset)? 4'd0: ~buttons;

    reg [9:0] last_switch = 10'b0;

    integer i;

    always @(posedge clk or posedge reset) begin
        if(reset)
            irq_switches <= 10'b0;
        else begin
            for(i = 0; i < 10; i = i + 1) begin
                if(last_switch[i] != switches[i])
                    irq_switches[i] <= 1;
                else
                    irq_switches[i] <= 0;
            end
            last_switch <= switches;
        end
    end

endmodule
