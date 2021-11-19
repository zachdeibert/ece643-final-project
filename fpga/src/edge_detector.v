`timescale 1ps / 1ps

module edge_detector#(
        parameter is_rising
    )(
        input  wire clk,
        input  wire reset,
        input  wire in,
        output wire out
    );

    reg ready;
    assign out = ready && (in == is_rising);

    always @(posedge clk or posedge reset) begin
        ready <= reset || in != is_rising;
    end

endmodule
