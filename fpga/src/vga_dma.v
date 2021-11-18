`timescale 1 ps / 1 ps

module vga_dma(
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

        output reg  [15:0] pixels_out_data,  // pixels_out.pixels_out_data
        output reg         pixels_out_valid, //           .pixels_out_valid
        input  wire        pixels_out_ready, //           .pixels_out_ready

        input  wire        clk,         //    clk.clk
        input  wire        reset,       //  reset.reset

        input  wire        frame_start, // vga_frame_ctrl.frame_start
        input  wire        frame_hold   //               .frame_hold
    );

    localparam VGA_PIXELS = 307200;
    localparam VGA_COLS = 640;
    localparam VGA_ROWS = 480;

    localparam BOX_X = 200;
    localparam BOX_Y = 200;
    localparam BOX_W = 100;
    localparam BOX_H = 100;

    localparam START_POS = BOX_X + BOX_Y * VGA_COLS;
    localparam END_POS = BOX_X + BOX_W + BOX_Y * VGA_COLS + BOX_H * VGA_COLS;
    localparam POS_JUMP = VGA_COLS;

    localparam STATE_IDLE = 0;
    localparam VGA_SET_ADDR = 1;
    localparam VGA_WAIT_DATA = 2;
    localparam WRITE_SET_ADDR = 3;
    localparam WRTIE_WAIT_DONE = 4;
    reg [4:0] read_state;

    assign hps_waitrequest = 1'b0;

    assign sdram_address = 'b0;
    assign sdram_byteenable = 'b0;
    assign sdram_read = 1'b0;
    assign sdram_write = 1'b0;
    assign sdram_writedata = 'b0;
    assign sdram_outputenable = 1'b0;

/*
    always @(posedge clk) begin
        if (reset) begin
            read_state <= STATE_IDLE;
        end else begin
            if(read_state == STATE_IDLE) begin
            end else if(read_state == VGA_SET_ADDR) begin
                if(sdram_waitrequest) begin
                    read_state <= VGA_WAIT_DATA;
                end else begin
                    
                end
            end
        end
    end
*/

    // Create a place to store count of pixels written and reset the count when frame_start is high
    reg frame_done;
    reg [31:0] pixels_written;
    reg [31:0] box_start;
    reg [31:0] box_end;
    always @(posedge clk) begin
        if (reset) begin
            pixels_written <= 0;
            frame_done <= 0;
            pixels_out_valid <= 0;
            box_start <= START_POS;
            box_end <= START_POS + BOX_W;
        end else begin
            if (frame_start) begin
                pixels_written <= 0;
                frame_done <= 0;
            end else if (~frame_done) begin
                if (pixels_written >= VGA_PIXELS) begin
                    frame_done <= 1;
                    pixels_out_valid <= 0;
                    box_start <= START_POS;
                    box_end <= START_POS + BOX_W;
                end else if(~frame_hold) begin
                    if(pixels_out_ready) begin
                        if(pixels_written >= box_start && pixels_written < box_end && pixels_written < END_POS) begin
                            pixels_out_data <= 16'hffff;
                        end else if (pixels_written >= box_end) begin
                            pixels_out_data <= 16'h0000;
                            box_end <= box_end + POS_JUMP;
                            box_start <= box_start + POS_JUMP;
                        end else begin
                            pixels_out_data <= 16'h0000;
                        end

                        pixels_out_valid <= 1;
                        pixels_written <= pixels_written + 1;
                    end
                end
            end
        end
    end


endmodule
