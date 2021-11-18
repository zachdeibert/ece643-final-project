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

        output wire [15:0] pixels_out_data,  // pixels_out.pixels_out_data
        output wire        pixels_out_valid, //           .pixels_out_valid
        input  wire        pixels_out_ready, //           .pixels_out_ready

        input  wire        clk,         //    clk.clk
        input  wire        reset,       //  reset.reset

        input  wire        frame_start // vga_frame_ctrl.frame_start
    );

    assign hps_waitrequest = 1'b0;

    assign sdram_address = 'b0;
    assign sdram_byteenable = 'b0;
    assign sdram_read = 1'b0;
    assign sdram_write = 1'b0;
    assign sdram_writedata = 'b0;
    assign sdram_outputenable = 1'b0;
    assign pixels_out_data = 'b0;
    assign pixels_out_valid = 'b0;

endmodule
