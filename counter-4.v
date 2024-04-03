module counter(clk,rst_n,cnt);
input clk,rst_n;
output [3:0] cnt;

reg [3:0] cnt;

always @(posedge clk) begin
if(~rst_n)
    cnt=4'b0000;
else
    cnt=cnt+1;
end
endmodule

`timescale 1ns/1ps
module counter_tb;
reg clk,rst_n;
wire [3:0] cnt;

counter counter_inst(.clk(clk),.rst_n(rst_n),.cnt(cnt));

initial begin
    clk=0; rst_n=1;
    #10
    rst_n=0;
    #10
    rst_n=1;    
    #200
    rst_n=0;
    #10
    rst_n=1;    
    #10
    $finish;
end
always #5 clk = ~clk;

initial begin
    $monitor("시간 = %t, output cnt = %d", $time, cnt);
end
endmodule