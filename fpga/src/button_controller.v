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

    wire [3:0] clean_buttons;
    wire [9:0] clean_switches;

    genvar j;
    generate
        for (j = 0; j < 4; j = j + 1) begin : button_loop
            debouncer#(.log2count(15), .count(25000)) btn_debouncer(.clk(clk), .reset(reset), .in(buttons[j]), .out(clean_buttons[j]));
        end
        for (j = 0; j < 10; j = j + 1) begin : switch_loop
            debouncer#(.log2count(15), .count(25000)) btn_debouncer(.clk(clk), .reset(reset), .in(switches[j]), .out(clean_switches[j]));
        end
    endgenerate

    integer i;

    always @(posedge clk or posedge reset) begin
        if(reset) begin
            irq_switches <= 10'b0;
            last_switch <= clean_switches;
            irq_buttons <= 4'd0;
        end else begin
            for(i = 0; i < 10; i = i + 1) begin
                if(last_switch[i] != clean_switches[i])
                    irq_switches[i] <= 1;
                else
                    irq_switches[i] <= 0;
            end
            irq_buttons <= ~clean_buttons;
            last_switch <= clean_switches;
        end
    end

endmodule
