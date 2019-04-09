`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:48:16 03/10/2019 
// Design Name: 
// Module Name:    Multiplier2bit 
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
module Multiplier2bit(Output,Input1,Input2);
output [5:0] Output;
input [3:0] Input1;
input [1:0] Input2;
wire [2:0] w1;
wire [3:0] w2;
wire w3;
and(Output[0],Input1[0],Input2[0]);
and(w1[0],Input1[1],Input2[0]);
and(w1[1],Input1[2],Input2[0]);
and(w1[2],Input1[3],Input2[0]);

and(w2[0],Input1[0],Input2[0]);
and(w2[1],Input1[1],Input2[0]);
and(w2[2],Input1[2],Input2[0]);
and(w2[3],Input1[3],Input2[0]);


GateLevel4bitAddSub A1(Output[4:1],Output[5],{1'b0,w1[2:0]},w2[3:0],{1'b0},{1'b0});

endmodule
