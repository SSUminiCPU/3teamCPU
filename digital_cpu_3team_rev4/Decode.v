module Decode(
    input [15:0] instruction,
    output reg [3:0] opcode,
    output reg [3:0] src_addr1,
    output reg [3:0] src_addr2,
    output reg [3:0] dest_addr,
    output reg [11:0] operand
);
    always @(*) begin
        opcode = instruction[15:12];
        src_addr1 = instruction[11:8];
        src_addr2 = instruction[7:4];
        dest_addr = instruction[3:0];
        operand = instruction[11:0];
    end
endmodule
