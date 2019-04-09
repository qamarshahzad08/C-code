`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:36:48 03/06/2019 
// Design Name: 
// Module Name:    Adder4bitDataFlow 
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
//Op=0 C=0 -> Addition
//Op=1 C=1 -> Subtraction
//////////////////////////////////////////////////////////////////////////////////
module Adder4bitDataFlow(Sum,Carry,A,B,Op,C);
input[3:0] A;
input [3:0] B;
output[3:0] Sum;
output Carry;
input Op;
input C;
wire w1,w2,w3;
wire B0,B1,B2,B3;

assign B0 = B[0]^Op;
assign B1 = B[1]^Op;
assign B2 = B[2]^Op;
assign B3 = B[3]^Op;

assign Sum[0]= (A[0]^B0)^C;
assign w1 = ((A[0]^B0)&Op)|(A[0]&B0); 

assign Sum[1]= (A[1]^B1)^w1;
assign w2 = ((A[1]^B1)&w2)|(A[1]&B1); 


assign Sum[2]= (A[2]^B2)^w2;
assign w3 = ((A[2]^B2)&w2)|(A[2]&B2); 


assign Sum[3]= (A[3]^B3)^w3;
assign Carry = ((A[3]^B3)&w3)|(A[3]&B3); 
endmodule
