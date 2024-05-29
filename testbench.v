`timescale 1ns / 1ps

module testbench();
    reg clk;
    reg reset;
    reg [15:0] mem_init [0:255];

    // Instantiate CPU
    CPU cpu(.clk(clk), .reset(reset), .mem_init(mem_init));

    // Initialize clock
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // Clock with 10 ns period
    end

    // Test procedure
    initial begin
        // Initialize memory with instructions
        mem_init[0] = 16'b0000000000000001;  // LOAD R0, 1
        mem_init[1] = 16'b0000000100000010;  // LOAD R1, 2
        mem_init[2] = 16'b0001000000010000;  // ADD R0, R1
        mem_init[3] = 16'b0010000000010000;  // SUB R0, R1
        mem_init[4] = 16'b0110000000010000;  // CMP R0, R1
        mem_init[5] = 16'b0111000000001000;  // JMP 8
        mem_init[6] = 16'b0000000000000000;  // NOOP
        mem_init[7] = 16'b0000001000000011;  // LOAD R2, 3
        mem_init[8] = 16'b0000001100000100;  // LOAD R3, 4
        // Initialize other memory locations to zero
        integer i;
        for (i = 9; i < 256; i = i + 1) begin
            mem_init[i] = 16'b0;
        end

        // Initialize reset
        reset = 1;
        #10;
        reset = 0;

        // Monitor registers and flags
        $monitor("Time: %d, PC: %d, ReadData1: %d, ReadData2: %d, N: %b, Z: %b", $time, cpu.pc, cpu.rf.read_data1, cpu.rf.read_data2, cpu.execute.N, cpu.execute.Z);

        // Run for some time
        #1000;

        // Finish simulation
        $finish;
    end
endmodule
