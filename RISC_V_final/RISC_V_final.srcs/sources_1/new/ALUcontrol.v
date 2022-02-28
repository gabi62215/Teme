`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/14/2022 01:01:03 AM
// Design Name: 
// Module Name: ALUcontrol
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


module ALUcontrol(input [1:0] ALUop,
                  input [6:0] funct7,
                  input [2:0] funct3,
                  output reg [3:0] ALUinput);
     always  @(*) begin
        if(ALUop == 2'b00) //ld,sd
            ALUinput = 4'b0010; 
        if(ALUop == 2'b01) //beq
            ALUinput = 4'b0110;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b000) 
            ALUinput = 4'b0010;
        if(ALUop == 2'b10 && funct7 == 7'b0100000 && funct3 == 3'b000)
            ALUinput = 4'b0110;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b111)
            ALUinput = 4'b0000;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b110)
            ALUinput = 4'b0001;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b100)
            ALUinput = 4'b0011;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b010)
            ALUinput = 4'b1000;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b011)
            ALUinput = 4'b0111;
        if(ALUop == 2'b10 && funct7 == 7'b0100000 && funct3 == 3'b101)
            ALUinput = 4'b1001;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b101)
            ALUinput = 4'b0101;
        if(ALUop == 2'b10 && funct7 == 7'b0000000 && funct3 == 3'b001)
            ALUinput = 4'b0100;
        if(ALUop == 2'b01 && funct3 == 3'b100)
            ALUinput = 4'b1000;
        if(ALUop == 2'b10 && funct3 == 3'b110)
            ALUinput = 4'b0111;
     end 
endmodule
