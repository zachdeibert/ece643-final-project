`timescale 1 ps / 1 ps

module ps2_controller(
        input  wire [3:0] address,   // avalon.address
        output reg  [7:0] readdata,  //       .readdata
        input  wire       write,     //       .write
        input  wire [7:0] writedata, //       .writedata
        input  wire       clk,       //    clk.clk
        input  wire       reset,     //  reset.reset
        output reg        irq_ps2,   //    irq.irq_ps2
        input  wire       ps2_data,  //    ps2.data
        input  wire       ps2_clk    //       .ps2_clk
    );

    integer i;

    reg [7:0] fifostart;
    reg [7:0] fifoend;
    reg [7:0] fifo [13:0];

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            fifostart <= 0;
            readdata <= 0;
        end else if (address == 0) begin
            if (write) begin
                fifostart <= writedata;
            end
            readdata <= fifostart;
        end else if (address == 1) begin
            readdata <= fifoend;
        end else begin
            for (i = 0; i < 14; i = i + 1) begin: fifo_read
                if (address == i + 2) begin
                    readdata <= fifo[i];
                end
            end
        end
    end

    reg [7:0] datapart;
    reg [3:0] state;
    reg parity;

    always @(negedge ps2_clk or posedge reset) begin
        if (reset) begin
            fifoend <= 0;
            for (i = 0; i < 8; i = i + 1) begin: fifo_reset
                fifo[i] <= 0;
            end
            state <= 0;
            irq_ps2 <= 0;
        end else if (state == 0) begin
            if (!ps2_data) begin
                state <= 1;
                parity <= 0;
            end
        end else begin
            if (state < 8) begin
                datapart <= (datapart >> 1) | (ps2_data << 7);
                parity <= parity ^ ps2_data;
            end else if (state == 8) begin
                for (i = 0; i < 14; i = i + 1) begin: fifo_insert
                    if (fifoend == i) begin
                        if ((parity ^ ps2_data) == 1) begin
                            fifo[i] <= datapart;
                        end else begin
                            fifo[i] <= 0;
                        end
                    end
                end
            end else if (state == 9) begin
                fifoend <= fifoend + 1;
            end else if (state == 10) begin
                irq_ps2 <= 1;
            end else begin
                irq_ps2 <= 0;
            end
            state <= state + 1;
        end
    end

endmodule
