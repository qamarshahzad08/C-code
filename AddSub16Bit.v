`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:28:57 03/07/2019 
// Design Name: 
// Module Name:    AddSub16Bit 
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
module AddSub16Bit(Ans,Carry,A,B,C,Op);
input[15:0] A;
input [15:0] B;
output[15:0] Ans;
output Carry;
input Op;
input C;
wire w1,w2,w3;
GateLevel4bitAddSub(Ans[3:0],w1,A[3:0],B[3:0],C,Op);
GateLevel4bitAddSub(Ans[7:4],w2,A[7:4],B[7:4],w1,Op);
GateLevel4bitAddSub(Ans[11:8],w3,A[11:8],B[11:8],w2,Op);
GateLevel4bitAddSub(Ans[15:12],Carry,A[15:12],B[15:12],w3,Op);


endmodule
