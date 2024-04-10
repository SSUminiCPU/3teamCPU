`timescale 1ns/1ps
module Decoder_tb;
    reg A,B;
    wire [1:0] out;
    Decoder Dec_inst(.A(A),.B(B),.out(out));
    
    initial begin
        A=0; B=0;
        #10 
        A=0; B=1;
        #10 
        A=1; B=0;
        #10 
        A=1; B=1;
        #10 
        $finish;
    end
    
    initial begin
      $monitor("A=%d B=%d, out=%d%d",A,B,out[1],out[0]);
    end
    
endmodule
