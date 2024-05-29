module RegisterFile(
    input clk,
    input reset,
    input write_enable,
    input [3:0] read_addr1,
    input [3:0] read_addr2,
    input [3:0] write_addr,
    input [15:0] write_data,
    output reg [15:0] read_data1,
    output reg [15:0] read_data2
);
    reg [15:0] registers [0:12];  // 13 registers (R0 to R12)
    integer i;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            for (i = 0; i < 13; i = i + 1) begin
                registers[i] <= 16'b0;
            end
        end else if (write_enable) begin
            registers[write_addr] <= write_data;
        end
    end

    always @(*) begin
        read_data1 = registers[read_addr1];
        read_data2 = registers[read_addr2];
    end
endmodule
