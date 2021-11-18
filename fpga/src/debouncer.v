`timescale 1 ps / 1 ps

module debouncer#(
        parameter log2count,
        parameter count = 1 << log2count,
        parameter def = 0
    )(
        input  wire clk,
        input  wire reset,
        input  wire in,
        output reg  out
    );

    reg [log2count-1:0] counter;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            out <= def;
            counter <= 0;
        end else if (in == out) begin
            counter <= 0;
        end else if (counter >= count - 1) begin
            out <= ~out;
            counter <= 0;
        end else begin
            counter <= counter + 1;
        end
    end

endmodule
