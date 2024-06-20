module Fetch(
    input clk,
    input reset,
    input [15:0] pc,
    output reg [15:0] instruction,
    input [15:0] mem_init [0:255]
);
    reg [15:0] memory [0:255]; // 256-word memory

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            instruction <= 16'b0;
        end else begin
            instruction <= memory[pc];
        end
    end

    always @(posedge clk) begin
        integer i;
        for (i = 0; i < 256; i = i + 1) begin
            memory[i] <= mem_init[i];
        end
    end
endmodule
