`timescale 1 ps / 1 ps

module button_controller(
        input  wire       clk,          //     clk.clk
        input  wire       reset,        //   reset.reset
        output wire [3:0] irq_buttons,  //     irq.irq_buttons
        output wire [9:0] irq_switches, //        .irq_switches
        input  wire [3:0] buttons,      // buttons.buttons
        input  wire [9:0] switches      //        .switches
    );

    wire [13:0] inputs;
    wire [13:0] clean;
    reg  [13:0] lasts;
    reg  [13:0] outs;

    assign inputs = { buttons, switches };
    assign irq_buttons = outs[13:10];
    assign irq_switches = outs[9:0];

    genvar j;
    generate
        for (j = 0; j < 14; j = j + 1) begin : debouncers
            debouncer#(.log2count(15), .count(25000)) btn_debouncer(.clk(clk), .reset(reset), .in(inputs[j]), .out(clean[j]));
        end
    endgenerate

    integer i;
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            lasts <= clean;
            outs <= 0;
        end else begin
            for(i = 0; i < 14; i = i + 1) begin
                if(lasts[i] != clean[i])
                    outs[i] <= 1;
                else
                    outs[i] <= 0;
            end
            lasts <= clean;
        end
    end

endmodule
