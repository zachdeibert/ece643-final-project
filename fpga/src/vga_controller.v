`timescale 1 ps / 1 ps

module vga_controller(
        input  wire        write,       // avalon.write
        input  wire [31:0] writedata,   //       .writedata
        input  wire [17:0] address,     //       .address
        input  wire [3:0]  byteenable,  //       .byteenable
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
        output wire [7:0]  vga_r,       //    vga.vga_r
        output wire [7:0]  vga_g,       //       .vga_g
        output wire [7:0]  vga_b,       //       .vga_b
        output wire        vga_clk,     //       .vga_clk
        output wire        vga_sync_n,  //       .vga_sync_n
        output wire        vga_blank_n, //       .vga_blank_n
        input  wire        vga_vs,      //       .vga_vs
        input  wire        vga_hs,      //       .vga_hs
        input  wire        clk,         //    clk.clk
        input  wire        reset        //  reset.reset
    );

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
    assign vga_b = 8'b00000000;
    assign vga_blank_n = 1'b0;
    assign vga_clk = 1'b0;
    assign vga_g = 8'b00000000;
    assign vga_r = 8'b00000000;
    assign vga_sync_n = 1'b0;

endmodule
