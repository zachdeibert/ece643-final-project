`timescale 1 ps / 1 ps

module vga_translate(
        input  wire        hps_write,       // avalon.write
        input  wire [15:0] hps_writedata,   //       .writedata
        input  wire [18:0] hps_address,     //       .address
        input  wire [1:0]  hps_byteenable,  //       .byteenable
        output wire        hps_waitrequest, //       .waitrequest

        output wire [31:0] sdram_address,       // sdram.address
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

    localparam ROW_LEN	= 8;
    localparam COL_LEN	= 9;

    reg [31:0] current_base_addr;

    reg [ROW_LEN:0] row_addr_pre;
    reg [COL_LEN:0] col_addr_pre;

    wire [ROW_LEN:0] row_addr;
    wire [COL_LEN:0] col_addr;

    reg blocked;

    assign col_addr = (col_addr_pre < VGA_COLS) ? col_addr_pre : 0;
    assign row_addr = (row_addr_pre < VGA_ROWS) ? row_addr_pre : 0;

    assign hps_waitrequest = (blocked)? 1'b1: (hps_address < 6)? 1'b0: sdram_waitrequest;
    assign sdram_write = (blocked)? 1'b0: (hps_address < 6)? 1'b0: hps_write;
    assign sdram_address = current_base_addr + {row_addr,col_addr,1'b0};
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

    always @(posedge clk) begin
        if(reset) begin
            current_base_addr <= 'h0;
            row_addr_pre <= 'h0;
            col_addr_pre <= 'h0;
            box_x <= 0;
            box_y <= 0;
            box_w <= 0;
            box_h <= 0;
        end else if (hps_write && ~hps_waitrequest) begin
            if(hps_address == 0) begin
                if(hps_byteenable[0])
                    box_x[15:8] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_x[7:0] <= hps_writedata[15:8];
            end else if(hps_address == 1) begin
                if(hps_byteenable[0])
                    box_y[15:8] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_y[7:0] <= hps_writedata[15:8];
            end else if(hps_address == 2) begin
                if(hps_byteenable[0])
                    box_w[15:8] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_w[7:0] <= hps_writedata[15:8];
            end else if(hps_address == 3) begin
                if(hps_byteenable[0])
                    box_h[15:8] <= hps_writedata[7:0];
                if(hps_byteenable[1])
                    box_h[7:0] <= hps_writedata[15:8];
            end else if(hps_address == 4) begin
                // Setup variables based on box definition
                if(hps_byteenable[1]) begin
                    row_addr_pre <= box_y;
                    col_addr_pre <= box_x;
                    current_base_addr <= 'h0;
                end
            end else if(hps_address >= 6) begin 
                if(hps_byteenable[1]) begin
                    if(col_addr_pre >= box_w + box_x - 1) begin
                        row_addr_pre <= row_addr + 1;
                        col_addr_pre <= box_x;
                    end else begin
                        col_addr_pre <= col_addr_pre + 1;
                    end
                end
            end
        end
    end

    reg [7:0] cnt;
    reg counting;

    // Count the number of sucessful writes, then wait for 32 clocks every 32 writes
    always @(posedge clk) begin
        if(reset) begin
            cnt <= 0;
            blocked <= 1'b0;
        end begin
            if(blocked) begin
                cnt <= cnt + 1;
                if(cnt >= 120) begin
                    blocked <= 0;
                    cnt <= 0;
                end 
            end else if(hps_write && ~hps_waitrequest) begin
                cnt <= cnt + 1;
                if(cnt >= 8) begin
                    blocked <= 1'b1;
                    cnt <= 0;
                end
            end
        end
    end
endmodule
