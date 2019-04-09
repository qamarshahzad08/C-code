`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:25:17 04/08/2019
// Design Name:   statemachine
// Module Name:   E:/Semesters/Semester1stMS/VerilogHD/StateMachine1/checkstatemachine.v
// Project Name:  StateMachine1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: statemachine
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module checkstatemachine;

	// Inputs
	reg x;
	reg clk;
	reg rst;

	// Outputs
	wire y;

	// Instantiate the Unit Under Test (UUT)
	statemachine uut (
		.y(y), 
		.x(x), 
		.clk(clk), 
		.rst(rst)
	);

	initial begin
		// Initialize Inputs
		  x = 0;
		clk = 1'b0;
		rst = 1;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		 
		 #10;
		 x = 1;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 

		// Wait 100 ns for global reset to finish
		 #10;//1
		 x = 1;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 #10;
		 x = 1;//1
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 #10;
		 x = 0;//0
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 #10;
		 x = 1;//1
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 #10;//1
		 x = 1;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 
		 		 #10;
		 x = 0;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 		 #10;
		 x = 1;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;
		 
		 		 #10;
		 x = 0;
		 rst = 0;
		 #5 clk=~clk;
		 #5 clk=~clk;

	end
      
endmodule

