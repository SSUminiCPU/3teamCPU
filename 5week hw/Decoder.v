module Decoder(
    input A,B,
    output [1:0] out);
    assign out = A ? (B ? 2'b11:2'b10):(B ? 2'b01:2'b00);
endmodule
