`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:14:03 03/07/2019 
// Design Name: 
// Module Name:    AddSub4bitBeh 
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
module AddSub4bitBeh(Sum,Carry,A,B,C,Op);

output [3:0] Sum;
output Carry;
input [3:0] A;
input [3:0] B;
input C,Op;
reg [3:0] Sum;
reg Carry;
 always @ (A or B or C or Op)
 begin
 if (Op==0)
 begin 
  {Carry,Sum} = A + B;
 end
 else if (Op==1)
 begin
  Sum = A - B;
  Carry = 1'b0;
 end
 else
 begin
 Sum=0;
 Carry=0;
 end
 end


endmodule
