`timescale 1ps / 1ps

module clock_divider
#(
    parameter WIDTH = 8,
    parameter COUNT = 250
)
(
    input clk,
    input reset,
    output reg clk_out
);

    reg [WIDTH-1:0] count;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 'b0;
            clk_out <= 'b0;
        end else begin
            if (count >= COUNT-1) begin
                count <= 'b0;
                clk_out = ~clk_out; // Sequential because of the loop
            end else begin
                count <= count + 1;
            end
        end
    end

endmodule