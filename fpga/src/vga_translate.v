`timescale 1 ps / 1 ps

module vga_translate(
        input  wire        hps_write,       // avalon.write
        input  wire [31:0] hps_writedata,   //       .writedata
        input  wire [17:0] hps_address,     //       .address
        input  wire [3:0]  hps_byteenable,  //       .byteenable
        output wire        hps_waitrequest, //       .waitrequest

        output wire [25:0] sdram_address,       // sdram.address
        output wire [1:0]  sdram_byteenable,    //      .byteenable
        input  wire        sdram_waitrequest,   //      .waitrequest
        output wire        sdram_write,         //      .write
        output wire [15:0] sdram_writedata,     //      .writedata

        output wire [3:0]  vga_address,       //   vga.address
        output wire [3:0]  vga_byteenable,    //      .byteenable
        input  wire        vga_waitrequest,   //      .waitrequest
        output wire        vga_write,         //      .write
        output wire [31:0] vga_writedata,     //      .writedata

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
    assign sdram_write = 1'b0;
    assign sdram_writedata = 'b0;

    assign vga_address = 'b0;
    assign vga_byteenable = 'b0;
    assign vga_write = 1'b0;
    assign vga_writedata = 'b0;

endmodule
