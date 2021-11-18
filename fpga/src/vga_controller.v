`timescale 1 ps / 1 ps

module vga_controller(
        input  wire        vga_clk_in,  // vga_clk_in
        input  wire        clk,         // clk

        output reg         frame_start, // vga_frame_ctrl.frame_start

        output wire [7:0]  vga_r,       //    vga.vga_r
        output wire [7:0]  vga_g,       //       .vga_g
        output wire [7:0]  vga_b,       //       .vga_b
        output wire        vga_clk,     //       .vga_clk
        output wire        vga_sync_n,  //       .vga_sync_n
        output wire        vga_blank_n, //       .vga_blank_n
        output reg         vga_vs,      //       .vga_vs
        output reg         vga_hs,      //       .vga_hs

        input  wire [15:0] vga_data,    //  vga_sink.vga_data
        output reg         vga_ready,   //          .vga_ready
        input  wire        vga_valid,   //          .vga_valid

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

    reg [18:0] vga_in_pixel_addr;

    reg [9:0] row_cnt;
    reg [9:0] col_cnt;

    reg [15:0] vga_pixel_color;
    assign vga_r = { vga_pixel_color[15:11], 3'b000 };
    assign vga_g = { vga_pixel_color[10:5], 2'b00 };
    assign vga_b = { vga_pixel_color[4:0], 3'b00 };


    always @(posedge vga_clk_in) begin
        if (reset) begin
            vga_pixel_color <= 0;
        end else begin
            vga_pixel_color <= vga_in_pixel_addr[15:0];
        end
    end

    // Manage VGA row and column positions
    always @(posedge vga_clk_in) begin
        if (reset) begin
            row_cnt <= 0;
            col_cnt <= 0;
            vga_in_pixel_addr <= 0;
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
                if (row_cnt < ROW_PIXELS)
                    if (col_cnt < COL_PIXELS)
                        vga_in_pixel_addr <= vga_in_pixel_addr + 1;
                else
                    vga_in_pixel_addr <= 0;
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

    reg vga_has_read_priority;
    always @(posedge vga_clk_in) begin
        if (reset) begin
            vga_has_read_priority <= 0;
        end else begin
            if (row_cnt >= ROW_PIXELS || col_cnt >= COL_PIXELS) begin
                vga_has_read_priority <= 0;
            end else begin
                vga_has_read_priority <= 1;
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

    assign vga_blank_n = 1'b1;
    assign vga_sync_n = 1'b1;

endmodule
