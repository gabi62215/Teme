`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/15/2022 07:42:09 PM
// Design Name: 
// Module Name: mux_4_1
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module mux_4_1(a,b,c,d,s0,s1,out);
    input [31:0]a;
    input [31:0]b;
    input [31:0]c;
    input [31:0]d;
    input s0,s1;
    output [31:0]out;
    
    
    assign out = s0 ? (s1 ? d : c) : (s1 ? b : a);
endmodule