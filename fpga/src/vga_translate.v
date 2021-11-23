`timescale 1 ps / 1 ps

module vga_translate(
        input  wire        hps_write,       // avalon.write
        input  wire [15:0] hps_writedata,   //       .writedata
        input  wire [18:0] hps_address,     //       .address
        input  wire [1:0]  hps_byteenable,  //       .byteenable
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

    localparam VGA_COLS = 640;
    localparam VGA_ROWS = 480;

    reg [25:0] pixel_address_mod;
    wire [25:0] pixel_address_endrow;
    reg [25:0] current_base_addr;
    reg [18:0] box_end_addr;

    assign hps_waitrequest = (hps_address < 6 || hps_address >= box_end_addr)? 1'b0: sdram_waitrequest;
    assign sdram_write = (hps_address < 6 || hps_address >= box_end_addr)? 1'b0: hps_write;
    assign sdram_address = hps_address + pixel_address_mod;
    assign sdram_byteenable = hps_byteenable;
    assign sdram_writedata = hps_writedata;

    assign vga_address = 'b0;
    assign vga_byteenable = 'b0;
    assign vga_write = 1'b0;
    assign vga_writedata = 'b0;

    reg [15:0] box_x;
    reg [15:0] box_y;
    reg [15:0] box_w;
    reg [15:0] box_h;

    reg have_new_box;

    assign pixel_address_endrow = pixel_address_mod + box_h;

    always @(posedge clk) begin
        if(reset) begin
            current_base_addr <= 'h0;
            pixel_address_mod <= 'h0;
        end else if (hps_write && ~hps_waitrequest) begin
            if(hps_address == 0) begin
                if(hps_byteenable[0])
                    box_x[7:0] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_x[15:8] <= hps_writedata[15:8];
            end else if(hps_address == 1) begin
                if(hps_byteenable[0])
                    box_y[7:0] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_y[15:8] <= hps_writedata[15:8];
            end else if(hps_address == 2) begin
                if(hps_byteenable[0])
                    box_w[7:0] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_w[15:8] <= hps_writedata[15:8];
            end else if(hps_address == 3) begin
                if(hps_byteenable[0])
                    box_h[7:0] <= hps_writedata[7:0];
                if(hps_byteenable[1]) begin
                    box_h[15:8] <= hps_writedata[15:8];

                    // This is where the start end end of box will be
                    pixel_address_mod <= current_base_addr + box_x + box_y * VGA_COLS - 6;
                    box_end_addr <= current_base_addr + box_x + box_y * VGA_COLS + box_w * VGA_COLS + box_h * VGA_COLS - 6;
                end
            end else if(sdram_address == pixel_address_endrow - 1) begin 
                if(hps_byteenable[1]) begin
                    pixel_address_mod <= pixel_address_mod + VGA_COLS;
                end
            end else if(sdram_address == box_end_addr - 1) begin
                have_new_box <= 1'b1;
            end
        end
    end

    reg last_frame_hold;

    reg need_new_buffer;

    always @(posedge clk) begin
        if(reset) begin
            last_frame_hold <= 1'b0;
        end else begin
            last_frame_hold <= frame_hold;
            if(frame_hold && ~last_frame_hold) begin
            end
        end
    end

    wire frame_posedge;
    assign frame_posedge = ~last_frame_hold && frame_hold;

endmodule
