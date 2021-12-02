`timescale 1 ps / 1 ps

module vga_controller(
        input  wire        vga_clk_in,  // vga_clk_in
        input  wire        clk,         // clk

        output wire        frame_start, // vga_frame_ctrl.frame_start
        output wire        frame_hold,  //               .frame_hold

        output wire [7:0]  vga_r,       //    vga.vga_r
        output wire [7:0]  vga_g,       //       .vga_g
        output wire [7:0]  vga_b,       //       .vga_b
        output wire        vga_clk,     //       .vga_clk
        output wire        vga_sync_n,  //       .vga_sync_n
        output wire        vga_blank_n, //       .vga_blank_n
        output reg         vga_vs,      //       .vga_vs
        output reg         vga_hs,      //       .vga_hs

        input  wire [15:0] vga_data,    //  vga_sink.data
        output wire        vga_ready,   //          .ready
        input  wire        vga_valid,   //          .valid
        input  wire        vga_start,   //          .start
        input  wire        vga_end,     //          .end

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

    wire end_of_frame;
    localparam STATE_SYNC = 0;
    localparam STATE_SHOW = 1;
    reg state;
    reg next_state;
    wire visible_area;

    always @(posedge vga_clk_in)
    begin
        if (reset == 1'b1)
            state <= STATE_SYNC;
        else
            state <= next_state;
    end

    always @(*) begin
        if(reset) begin
            next_state <= STATE_SYNC;
        end else begin
            case(state)
                STATE_SYNC: begin
                    if (vga_valid & vga_start)
                        next_state <= STATE_SHOW;
                    else
                        next_state <= STATE_SYNC;
                end
                STATE_SHOW: begin
                    if (end_of_frame)
                        next_state <= STATE_SYNC;
                    else
                        next_state <= STATE_SHOW;
                end
                default: begin
                    next_state <= STATE_SYNC;
                end
            endcase
        end
    end

    assign vga_clk = vga_clk_in;

    reg [9:0] row_cnt;
    reg [9:0] col_cnt;

    reg [15:0] vga_pixel_color;
    assign vga_r = { vga_pixel_color[15:11], (vga_pixel_color[15])? 3'b111: 3'b000 };
    assign vga_g = { vga_pixel_color[10:5], (vga_pixel_color[10])? 2'b11: 2'b00 };
    assign vga_b = { vga_pixel_color[4:0], (vga_pixel_color[4])? 3'b111: 3'b000 };

    // Ready if either in drawable area or after frame but not at the next frame yet
    assign vga_ready = (state == STATE_SYNC) ? vga_valid & ~vga_start : visible_area;
    assign visible_area = (row_cnt < ROW_PIXELS && col_cnt < COL_PIXELS)? 1'b1 : 1'b0;

    assign end_of_frame = (row_cnt == ROW_PIXELS - 1 && col_cnt == COL_PIXELS - 1)? 1'b1 : 1'b0;

    assign frame_hold = 1'b0;
    assign frame_start = ~vga_vs;

    always @(posedge vga_clk_in) begin
        if (reset) begin
            vga_pixel_color <= 0;
        end else begin
            if(vga_valid && vga_ready) begin
                vga_pixel_color <= vga_data;
            end else begin
                vga_pixel_color <= 0;
            end
        end
    end

    // Manage VGA row and column positions
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

    assign vga_blank_n = ( vga_ready && row_cnt < ROW_PIXELS && col_cnt < COL_PIXELS) ? 1'b1: 1'b0;
    assign vga_sync_n = 1'b1;

endmodule
