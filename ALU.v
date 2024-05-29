module ALU(
    input [15:0] A,
    input [15:0] B,
    input [3:0] opcode,
    output reg [15:0] result,
    output reg N,
    output reg Z
);
    always @(*) begin
        case(opcode)
            4'b0001: result = A + B;          // ADD
            4'b0010: result = A - B;          // SUB
            4'b0100: result = A * B;          // MUL
            4'b0101: result = A / B;          // DIV
            4'b0110: begin                    // CMP
                result = A - B;
                N = (result < 0) ? 1 : 0;
                Z = (result == 0) ? 1 : 0;
            end
            default: result = 16'b0;
        endcase
    end
endmodule
