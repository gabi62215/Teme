`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/21/2022 05:46:08 PM
// Design Name: 
// Module Name: id_ex
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


module id_ex(input clk,
             input reset,
             input write,
             input [31:0] IMM_EX, //valoarea immediate in EX
             input [31:0] REG_DATA1_EX, //valoarea registrului sursa 1
             input [31:0] REG_DATA2_EX, //valoarea registrului sursa 2
             input [31:0] PC_EX, //adresa instructiunii curente in EX
             input [2:0] FUNCT3_EX, //funct3 pentru instructiunea din EX
             input [6:0] FUNCT7_EX, //funct7 pentru instructiunea din EX
             input [4:0] RD_EX, //adresa registrului destinatie
             input [4:0] RS1_EX, //adresa registrului sursa 1
             input [4:0] RS2_EX, //adresa registrului sursa 2
             input RegWrite_EX, //semnal de scriere in bancul de registri
             input MemtoReg_EX, //...
             input MemRead_EX, //semnal pentru activarea citirii din memorie
             input MemWrite_EX, //semnal pentru activarea scrierii in memorie
             input [1:0] ALUop_EX, //semnalul de control ALUop
             input ALUSrc_EX, //semnal de selectie intre RS2 si valoarea imediata
             input Branch_EX, //semnal de identificare a instructiunilor de tip branch
             output reg [31:0] IMM_EX_out, //valoarea immediate in EX
             output reg [31:0] REG_DATA1_EX_out, //valoarea registrului sursa 1
             output reg [31:0] REG_DATA2_EX_out, //valoarea registrului sursa 2
             output reg [31:0] PC_EX_out, //adresa instructiunii curente in EX
             output reg [2:0] FUNCT3_EX_out, //funct3 pentru instructiunea din EX
             output reg [6:0] FUNCT7_EX_out, //funct7 pentru instructiunea din EX
             output reg [4:0] RD_EX_out, //adresa registrului destinatie
             output reg [4:0] RS1_EX_out, //adresa registrului sursa 1
             output reg [4:0] RS2_EX_out, //adresa registrului sursa 2
             output reg RegWrite_EX_out, //semnal de scriere in bancul de registri
             output reg MemtoReg_EX_out, //...
             output reg MemRead_EX_out, //semnal pentru activarea citirii din memorie
             output reg MemWrite_EX_out, //semnal pentru activarea scrierii in memorie
             output reg [1:0] ALUop_EX_out, //semnalul de control ALUop
             output reg ALUSrc_EX_out, //semnal de selectie intre RS2 si valoarea imediata
             output reg Branch_EX_out); //semnal de identificare a instructiunilor de tip branch
    
    always@(posedge clk) begin
    if (reset) begin
        IMM_EX_out <= 0;
        REG_DATA1_EX_out <= 0;
        REG_DATA2_EX_out <= 0;
        PC_EX_out <= 0;
        FUNCT3_EX_out <= 0;
        FUNCT7_EX_out <= 0;
        RD_EX_out <= 0;
        RS1_EX_out <= 0;
        RS2_EX_out <= 0;
        RegWrite_EX_out <= 0;
        MemtoReg_EX_out <= 0;
        MemRead_EX_out <= 0;
        MemWrite_EX_out <= 0;
        ALUop_EX_out <= 0;
        ALUSrc_EX_out <= 0;
        Branch_EX_out <= 0;
    end
    else begin
      if(write) begin
        IMM_EX_out <= IMM_EX;
        REG_DATA1_EX_out <= REG_DATA1_EX;
        REG_DATA2_EX_out <= REG_DATA2_EX;
        PC_EX_out <= PC_EX;
        FUNCT3_EX_out <= FUNCT3_EX;
        FUNCT7_EX_out <= FUNCT7_EX;
        RD_EX_out <= RD_EX;
        RS1_EX_out <= RS1_EX;
        RS2_EX_out <= RS2_EX;
        RegWrite_EX_out <= RegWrite_EX;
        MemtoReg_EX_out <= MemtoReg_EX;
        MemRead_EX_out <= MemRead_EX;
        MemWrite_EX_out <= MemWrite_EX;
        ALUop_EX_out <= ALUop_EX;
        ALUSrc_EX_out <= ALUSrc_EX;
        Branch_EX_out <= Branch_EX;
      end
    end
  end   
endmodule
