`timescale 1 ps / 1 ps

module vga_controller(
        input  wire        write,       // avalon.write
        input  wire [31:0] writedata,   //       .writedata
        input  wire [17:0] address,     //       .address
        input  wire [3:0]  byteenable,  //       .byteenable

        input  wire        vga_clk_in,  // vga_clk_in

        inout  wire [15:0] dram_dq,     //  sdram.dram_dq
        output wire [12:0] dram_addr,   //       .dram_addr
        output wire [1:0]  dram_ba,     //       .dram_ba
        output wire        dram_clk,    //       .dram_clk
        output wire        dram_cke,    //       .dram_cke
        output wire        dram_ldqm,   //       .dram_ldqm
        output wire        dram_udqm,   //       .dram_udqm
        output wire        dram_we_n,   //       .dram_we_n
        output wire        dram_cas_n,  //       .dram_cas_n
        output wire        dram_ras_n,  //       .dram_ras_n
        output wire        dram_cs_n,   //       .dram_cs_n
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

    assign dram_addr = 13'b0000000000000;
    assign dram_ba = 2'b00;
    assign dram_cas_n = 1'b0;
    assign dram_cke = 1'b0;
    assign dram_clk = 1'b0;
    assign dram_cs_n = 1'b0;
    assign dram_ldqm = 1'b0;
    assign dram_ras_n = 1'b0;
    assign dram_udqm = 1'b0;
    assign dram_we_n = 1'b0;
    assign vga_blank_n = 1'b1;
    assign vga_sync_n = 1'b1;

endmodule
