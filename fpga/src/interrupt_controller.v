`timescale 1 ps / 1 ps

module interrupt_controller(
        input  wire [1:0]  address,      //      avalon.address
        input  wire [3:0]  byteenable,   //            .byteenable
        output reg  [31:0] readdata,     //            .readdata
        input  wire [31:0] writedata,    //            .writedata
        input  wire        write,        //            .write
        input  wire        clk,          //         clk.clk
        input  wire [3:0]  irq_buttons,  // irq_buttons.irq_buttons
        input  wire [9:0]  irq_switches, //            .irq_switches
        input  wire        irq_ps2,      //     irq_ps2.irq_ps2
        input  wire        reset         //       reset.reset
    );

    reg [9:0] switch_status;
    reg [9:0] switch_enable;
    reg [9:0] switch_clear;

    reg [3:0] button_status;
    reg [3:0] button_enable;
    reg [3:0] button_clear;

    reg ps2_status;
    reg ps2_enable;
    reg ps2_clear;

    // Set readdata depending on value of address
    always @(posedge clk or posedge reset) begin
        if(reset)
            readdata <= 32'b0;
        else begin
            if(address == 2'b00)
                readdata <= switch_status | (button_status << 16) | (ps2_status << 24);
            else if(address == 2'b01)
                readdata <= switch_enable | (button_enable << 16) | (ps2_enable << 24);
            else if(address == 2'b10)
                readdata <= switch_clear | (button_clear << 16) | (ps2_clear << 24);
            else
                readdata <= 32'b0;
        end
    end

    reg [9:0] switch_last;
    reg [3:0] button_last;
    reg ps2_last;

    wire [9:0] switch_edge;
    wire [3:0] button_edge;
    wire ps2_edge;

    assign switch_edge = ~switch_last & irq_switches;
    assign button_edge = ~button_last & irq_buttons;
    assign ps2_edge = ~ps2_last & irq_ps2;

    // Save last state of irq_switches, irq_buttons, and ps2_irq
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            switch_last <= 'b0;
            button_last <= 'b0;
            ps2_last <= 'b0;
        end else begin
            switch_last <= irq_switches;
            button_last <= irq_buttons;
            ps2_last <= irq_ps2;
        end
    end

    // Actually control the interupt statuses
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            switch_status <= 10'b0;
            button_status <= 4'b0;
            ps2_status <= 0;
        end else begin
            switch_status <= (switch_status | switch_edge) & switch_enable & ~switch_clear;
            button_status <= (button_status | button_edge) & button_enable & ~button_clear;
            ps2_status <= (ps2_status | ps2_edge) & ps2_enable & ~ps2_clear;
        end
    end

    // Handle writing
    always @(posedge clk or posedge reset) begin
        if(reset) begin
            switch_enable <= 10'b0;
            switch_clear <= 10'b0;
            button_enable <= 4'b0;
            button_clear <= 4'b0;
            ps2_enable <= 0;
            ps2_clear <= 0;
        end else begin
            if(write) begin
                if(address == 2'b01) begin
                    if(byteenable[0])
                        switch_enable[7:0] <= writedata[7:0];

                    if(byteenable[1])
                        switch_enable[9:8] <= writedata[9:8];

                    if(byteenable[2])
                        button_enable[3:0] <= writedata[19:16];

                    if(byteenable[3])
                        ps2_enable <= writedata[24];
                end else if(address == 2'b10) begin
                    if(byteenable[0])
                        switch_clear[7:0] <= writedata[7:0];

                    if(byteenable[1])
                        switch_clear[9:8] <= writedata[9:8];

                    if(byteenable[2])
                        button_clear[3:0] <= writedata[19:16];

                    if(byteenable[3])
                        ps2_clear <= writedata[24];
                end

            end else begin
                switch_clear <= 10'b0;
                button_clear <= 4'b0;
                ps2_clear <= 0;
            end
        end
    end

endmodule
