`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:07:28 03/06/2019 
// Design Name: 
// Module Name:    FullAdderSub 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module FullAdderSub(S,C,Op,x,y);
output S,C;
input x,y;
input Op;
wire w1,w2,w3,w4;
xor(w4,Op,y);
xor(w1,x,y);
and(w2,x,y);
and(w3,w1,Op);
xor(S,w1,Op);
or(C,w3,w2);


endmodule
