module CPU(
    input clk,
    input reset,
    input [15:0] mem_init [0:255]
);
    // Internal signals
    reg [15:0] pc;
    wire [15:0] instruction;
    wire [3:0] opcode;
    wire [3:0] read_addr1, read_addr2, write_addr;
    wire [11:0] operand;
    wire [15:0] read_data1, read_data2;
    wire [15:0] result;
    wire N, Z;
    reg write_enable;

    // Pipeline registers
    reg [15:0] instruction_reg;
    reg [3:0] opcode_reg;
    reg [3:0] read_addr1_reg, read_addr2_reg, write_addr_reg;
    reg [11:0] operand_reg;
    reg [15:0] read_data1_reg, read_data2_reg;
    reg [15:0] result_reg;
    reg N_reg, Z_reg;

    // Instantiate modules
    Fetch fetch(.clk(clk), .reset(reset), .pc(pc), .instruction(instruction), .mem_init(mem_init));
    Decode decode(.clk(clk), .reset(reset), .instruction(instruction_reg), .opcode(opcode), .src_addr1(read_addr1), .src_addr2(read_addr2), .dest_addr(write_addr), .operand(operand));
    Execute execute(.clk(clk), .reset(reset), .opcode(opcode_reg), .operand(operand_reg), .read_data1(read_data1_reg), .read_data2(read_data2_reg), .result(result), .N(N), .Z(Z));
    RegisterFile rf(.clk(clk), .reset(reset), .write_enable(write_enable), .read_addr1(read_addr1), .read_addr2(read_addr2), .write_addr(write_addr_reg), .write_data(result_reg), .read_data1(read_data1), .read_data2(read_data2));

    // Fetch to Decode pipeline register
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            instruction_reg <= 16'b0;
        end else begin
            instruction_reg <= instruction;
        end
    end

    // Decode to Execute pipeline register
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            opcode_reg <= 4'b0;
            read_addr1_reg <= 4'b0;
            read_addr2_reg <= 4'b0;
            write_addr_reg <= 4'b0;
            operand_reg <= 12'b0;
        end else begin
            opcode_reg <= opcode;
            read_addr1_reg <= read_addr1;
            read_addr2_reg <= read_addr2;
            write_addr_reg <= write_addr;
            operand_reg <= operand;
        end
    end

    // Execute to Writeback pipeline register
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            result_reg <= 16'b0;
            N_reg <= 0;
            Z_reg <= 0;
        end else begin
            result_reg <= result;
            N_reg <= N;
            Z_reg <= Z;
        end
    end

    // Program Counter and register update logic
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            pc <= 16'b0;
            write_enable <= 0;
        end else begin
            case(opcode_reg)
                4'b0000: begin  // LOAD
                    write_enable <= 1;
                    pc <= pc + 1;
                end
                4'b0011: begin  // STORE
                    write_enable <= 1;
                    pc <= pc + 1;
                end
                4'b0111: begin  // JMP
                    pc <= result_reg;
                    write_enable <= 0;
                end
                default: begin  // ADD, SUB, MUL, DIV, CMP
                    write_enable <= 1;
                    pc <= pc + 1;
                end
            endcase
        end
    end
endmodule
