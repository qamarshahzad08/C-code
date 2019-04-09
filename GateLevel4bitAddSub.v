`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:32:13 03/06/2019 
// Design Name: 
// Module Name:    GateLevel4bitAddSub 
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
//Op = 0 C = 0 -> For Addition
//Op = 1 C = 1-> For Subtraction
//////////////////////////////////////////////////////////////////////////////////
module GateLevel4bitAddSub(Ans,Carry,A,B,C,Op);
input[3:0] A;
input [3:0] B;
output[3:0] Ans;
output Carry;
input Op;
input C;
wire w1,w2,w3;
wire w4,w5,w6,w7;
xor(w4,B[0],Op);
xor(w5,B[1],Op);
xor(w6,B[2],Op);
xor(w7,B[3],Op);

 FullAdder A1(Ans[0],w1,A[0],w4,C);
 FullAdder A2(Ans[1],w2,A[1],w5,w1);
 FullAdder A3(Ans[2],w3,A[2],w6,w2);
 FullAdder A4(Ans[3],Carry,A[3],w7,w3);

endmodule
