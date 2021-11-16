`timescale 1 ps / 1 ps

module vga_controller(
        input  wire        hps_write,       // avalon.write
        input  wire [31:0] hps_writedata,   //       .writedata
        input  wire [17:0] hps_address,     //       .address
        input  wire [3:0]  hps_byteenable,  //       .byteenable
        output wire        hps_waitrequest, //       .waitrequest

        output wire [25:0] sdram_address,       // sdram.address
        output wire [1:0]  sdram_byteenable,    //      .byteenable
        output wire        sdram_read,          //      .read
        input  wire [15:0] sdram_readdata,      //      .readdata
        input  wire        sdram_readdatavalid, //      .readdatavalid
        input  wire        sdram_waitrequest,   //      .waitrequest
        output wire        sdram_write,         //      .write
        output wire [15:0] sdram_writedata,     //      .writedata
        output wire        sdram_outputenable,  //      .outputenable

        input  wire        vga_clk_in,  // vga_clk_in

        output reg  [7:0]  vga_r,       //    vga.vga_r
        output reg  [7:0]  vga_g,       //       .vga_g
        output reg  [7:0]  vga_b,       //       .vga_b
        output wire        vga_clk,     //       .vga_clk
        output wire        vga_sync_n,  //       .vga_sync_n
        output wire        vga_blank_n, //       .vga_blank_n
        output reg         vga_vs,      //       .vga_vs
        output reg         vga_hs,      //       .vga_hs
        input  wire        clk,         //    clk.clk
        input  wire        reset        //  reset.reset
    );

    localparam HSYNC_COUNT = 96;
    localparam BEFORE_ROW = 48;
    localparam AFTER_ROW = 16;
    localparam ROW_CNT = 800;

    localparam BEFORE_COL = 33;
    localparam AFTER_COL = 10;
    localparam VSYNC_COUNT = 2;
    localparam COL_CNT = 525;

    localparam ROW_PIXELS = 640;
    localparam COL_PIXELS = 480;

    assign vga_clk = vga_clk_in;
    assign hps_waitrequest = 1'b0;

    assign sdram_address = 'b0;
    assign sdram_byteenable = 'b0;
    assign sdram_read = 1'b0;
    assign sdram_write = 1'b0;
    assign sdram_writedata = 'b0;
    assign sdram_outputenable = 1'b0;

    reg [9:0] row_cnt;
    reg [9:0] col_cnt;

    always @(posedge vga_clk_in) begin
        if (reset) begin
            row_cnt <= 0;
            col_cnt <= 0;
        end else begin
            if (row_cnt >= ROW_CNT-1) begin
                row_cnt <= 0;
                if (col_cnt >= COL_CNT-1) begin
                    col_cnt <= 0;
                end else begin
                    col_cnt <= col_cnt + 1;
                end
            end else begin
                row_cnt <= row_cnt + 1;
            end
        end
    end

    always @(posedge vga_clk_in) begin
        if (reset) begin
            vga_hs <= 1;
        end else begin
            if (row_cnt >= ROW_PIXELS + AFTER_ROW && row_cnt <= ROW_CNT - BEFORE_ROW) begin
                vga_hs <= 0;
            end else begin
                vga_hs <= 1;
            end
        end 
    end

    always @(posedge vga_clk_in) begin
        if (reset) begin
            vga_vs <= 1;
        end else begin
            if (col_cnt >= COL_PIXELS + AFTER_COL && col_cnt <= COL_CNT - BEFORE_COL) begin
                vga_vs <= 0;
            end else begin
                vga_vs <= 1;
            end
        end 
    end

    always @(posedge vga_clk_in) begin
        if(reset) begin
            vga_b <= 0;
            vga_g <= 0;
            vga_r <= 0;
        end else begin
            if(row_cnt <= ROW_PIXELS && col_cnt <= COL_PIXELS) begin
                if(row_cnt <= 320) begin
                    if(col_cnt <= 240) begin
                        vga_r <= 8'b11111111;
                        vga_g <= 0;
                        vga_b <= 0;
                    end else begin
                        vga_r <= 0;
                        vga_g <= 8'b11111111;
                        vga_b <= 0;
                    end
                end else begin
                    if(col_cnt <= 240) begin
                        vga_r <= 0;
                        vga_g <= 0;
                        vga_b <= 8'b11111111;
                    end else begin
                        vga_r <= 8'b11111111;
                        vga_g <= 0;
                        vga_b <= 8'b11111111;
                    end
                end
            end else begin
                vga_r <= 8'b00000000;
                vga_g <= 8'b00000000;
                vga_b <= 8'b00000000;
            end
        end
    end

endmodule
