`timescale 1ns/1ps
module MUX_tb;
    reg A,B,select;
    wire out;
    MUX MUX_inst(.A(A),.B(B),.select(select),.out(out));
    
    initial begin
        A=0; B=0; ;select=0;
        #10 
        A=0; B=1; ;select=0;
        #10 
        A=1; B=0; ;select=0;
        #10 
        A=1; B=1; ;select=0;
        #10 
        A=0; B=0; ;select=1;
        #10 
        A=0; B=1; ;select=1;
        #10 
        A=1; B=0; ;select=1;
        #10 
        A=1; B=1; ;select=1;
        #10
        $finish;
    end
    
    initial begin
      $monitor("A=%d B=%d select=%d, out=%d",A,B,select,out);
    end
    
endmodule
