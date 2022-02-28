`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/14/2022 01:20:15 AM
// Design Name: 
// Module Name: EX
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


module EX(input [31:0] IMM_EX, //valoarea immediate in EX
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
          input [1:0] forwardA,forwardB, //semnalele de selectie pentru multiplexoarele de forwarding
            
          input [31:0] ALU_DATA_WB, //valoarea calculata de ALU, prezenta in WB
          input [31:0] ALU_OUT_MEM, //valoarea calculata de ALU, prezenta in MEM

          output ZERO_EX, //flag-ul ZERO calculat de ALU
          output [31:0] ALU_OUT_EX, //rezultatul calculat de ALU in EX
          output [31:0] PC_Branch_EX, //adresa de salt calculata in EX
          output [31:0] REG_DATA2_EX_FINAL //valoarea registrului sursa 2 selectata dintre
); //valorile prezente in etapele EX, MEM si WB

    wire [3:0] ALU_control;
    wire [31:0] ALU_SOURCE1;
    wire [31:0] ALU_SOURCE2;
    wire [31:0] MUX_B_temp;
    assign REG_DATA2_EX_FINAL = MUX_B_temp;
    
    ALU ALU_MODULE(ALU_control,
    ALU_SOURCE1,ALU_SOURCE2,
    ZERO_EX,ALU_OUT_EX);
    
    ALUcontrol ALU_CONTROL_MODULE(ALUop_EX, //ALUop
    FUNCT7_EX, //funct7
    FUNCT3_EX, //funct3
    ALU_control);
    
    mux_2_1 MUX_RS2_IMM(MUX_B_temp, //rs2
    IMM_EX, //imm
    ALUSrc_EX, //ALUSrc
    ALU_SOURCE2);
    
    adder ADDER_IMM_EX(PC_EX, //PC
    IMM_EX, //imm
    PC_Branch_EX);
    
    mux_4_1 MUX_FORWARD_A(REG_DATA1_EX, //ID_EX source
    ALU_DATA_WB, //MEM_WB source
    ALU_OUT_MEM, //EX_MEM source
    32'b0, //not used
    forwardA[0],
    forwardA[1],
    ALU_SOURCE1);
    
    mux_4_1 MUX_FORWARD_B(REG_DATA2_EX, //ID_EX source
    ALU_DATA_WB, //MEM_WB source
    ALU_OUT_MEM, //EX_MEM source
    32'b0, //not used
    forwardB[0],
    forwardB[1],
    MUX_B_temp);



endmodule
