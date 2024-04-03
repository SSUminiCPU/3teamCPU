module parity(
    input a, b, c,
    output F
);
    assign F = ~(a&b) & ~c;
endmodule
`timescale 1ns/ 1ps
module parity_tb;
reg a;
reg b;
reg c;
wire F;
parity instance_parity(
    .a(a),.b(b),.c(c),.F(F)
);
initial begin
    a=0; b=0; c=0;
    #10;
    a=0; b=0; c=1;
    #10;
    a=0; b=1; c=0;
    #10;
    a=0; b=1; c=1;
    #10;
    a=1; b=0; c=0;
    #10;
    a=1; b=0; c=1;
    #10;
    a=1; b=1; c=0;
    #10;
    a=1; b=1; c=1;
    #10;
    $finish;
end
initial begin
    $monitor("시간=%t, a=%b, b=%b, c=%b, F=%b", $time, a, b, c, F);
end
endmodule