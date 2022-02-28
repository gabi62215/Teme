`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2022 10:57:14 PM
// Design Name: 
// Module Name: risc_v_tb
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


module risc_v_tb();
    reg clk,reset;
    
    wire [31:0]PC_EX_out;
    wire [31:0]ALU_OUT_EX;
    wire [31:0]PC_Branch_EX;
    wire PC_Src;
    wire [31:0]read_data;
    wire [31:0]wb_data;
    wire [1:0]forwardA,forwardB;
    wire control_sel;
    
    RISC_V procesor(clk,reset,PC_EX_out,ALU_OUT_EX,PC_Branch_EX,PC_Src,read_data,wb_data,forwardA,forwardB,control_sel);
    
    always begin 
        #5 clk=~clk; 
        $display("instructiune=%h",procesor.instruction_decode.RS1_ID); 
        $display("RS1_EX=%h",procesor.execution.RS1_EX);
        $display("alu OUT=%h",procesor.execution.ALU_OUT_EX);
    end
  
  initial begin
    #0 clk=1'b0; reset=1'b1;
      
    #10 reset=1'b0; 
    #400 $finish;
  end
endmodule
