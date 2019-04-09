`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:25:07 04/08/2019 
// Design Name: 
// Module Name:    statemachine 
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
module statemachine(y,x,clk,rst);
output reg y;
input x,clk,rst;
reg [1:0] current_state;
always @ (posedge clk or posedge rst)
begin
if(rst)
begin
y<=0;
current_state<=2'b00;
end
else
begin
case(current_state)
2'b00:begin
if(x==1)
begin
current_state<=01;
y<=0;
end
else
begin
current_state<=00;
y<=0;
end
end
2'b01:begin
if(x==0)
begin
current_state<=10;
y<=0;
end
else
begin
current_state<=01;
y<=0;
end
end

2'b10:begin
if(x)
begin
current_state<=11;
y<=0;
end
else
begin
current_state<=00;
y<=0;
end
end
2'b11:begin
if(x)
begin
current_state<=01;
y<=1;
end
else
begin
current_state<=10;
y<=0;
end
end
endcase
end
end

endmodule
