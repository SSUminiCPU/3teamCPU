module MUX(
    input A,B,select,
    output out);
    assign out = select ? A:B;
endmodule
