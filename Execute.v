module Execute(
    input [3:0] opcode,
    input [11:0] operand,
    input [15:0] read_data1,
    input [15:0] read_data2,
    output reg [15:0] result,
    output reg N,
    output reg Z
);
    wire [15:0] alu_result;
    wire alu_N, alu_Z;

    // Instantiate ALU
    ALU alu(
        .A(read_data1),
        .B(read_data2),
        .opcode(opcode),
        .result(alu_result),
        .N(alu_N),
        .Z(alu_Z)
    );

    always @(*) begin
        case(opcode)
            4'b0000: result = {4'b0, operand}; // LOAD
            4'b0111: result = {4'b0, operand}; // JMP
            default: begin
                result = alu_result;
                N = alu_N;
                Z = alu_Z;
            end
        endcase
    end
endmodule
