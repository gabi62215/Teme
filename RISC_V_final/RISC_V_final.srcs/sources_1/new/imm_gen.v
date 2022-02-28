`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/27/2021 06:46:46 PM
// Design Name: 
// Module Name: imm_gen
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


module imm_gen(input [31:0] in,
               output reg [31:0] out);
    always @(in) begin
        case(in[6:0])
            7'b0010011 : out = {{21{in[31]}},in[30:25],in[24:21],in[20]}; // I-immediate
            7'b0100011 : out = {{21{in[31]}},in[30:25],in[11:8],in[7]}; // S-immediate
            7'b1100011 : out = {{20{in[31]}},in[7],in[30:25],in[11:8],1'b0};// B-immediate
            7'b0000011 : out = {{21{in[31]}},in[30:25],in[24:21],in[20]}; // I-immediate (LW)
            default : out = 0;
        endcase
    
    end
    
endmodule
