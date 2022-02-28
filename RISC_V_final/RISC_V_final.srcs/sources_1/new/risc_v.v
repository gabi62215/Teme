//////////////////////////////////////////////RISC-V_MODULE///////////////////////////////////////////////////
module RISC_V(input clk,reset,
              output [31:0]PC_EX_out,
              output [31:0]ALU_OUT_EX,
              output [31:0]PC_Branch_EX,
              output PC_Src,
              output [31:0]read_data,
              output [31:0]wb_data,
              output [1:0]forwardA,forwardB,
              output control_sel);
  
  //////////////////////////////////////////IF signals////////////////////////////////////////////////////////
  wire [31:0] PC_IF;               //current PC
  wire [31:0] INSTRUCTION_IF;
  
 
 /////////////////////////////////////IF Module/////////////////////////////////////
 IF instruction_fetch(clk, reset, 
                      PC_Src, PC_write,
                      PC_Branch_EX,
                      PC_IF,INSTRUCTION_IF);
  
  wire [31:0] PC_ID,INSTRUCTION_ID;
 //////////////////////////////////////pipeline registers////////////////////////////////////////////////////
 IF_ID_reg IF_ID_REGISTER(clk,reset,
                          IF_IFwrite,
                          PC_IF,INSTRUCTION_IF,
                          PC_ID,INSTRUCTION_ID);
  
   wire [31:0] IMM_ID;
   wire [31:0] REG_DATA1_ID,REG_DATA2_ID;
   wire RegWrite_ID,MemtoReg_ID,MemRead_ID,MemWrite_ID;
   wire [1:0] ALUop_ID;
   wire ALUSrc_ID;
   wire Branch_ID;
   wire [2:0] FUNCT3_ID;
   wire [6:0] FUNCT7_ID;
   wire [4:0] RS1_ID;
   wire [4:0] RS2_ID;
   
   wire [31:0]read_data_wb,address_wb; 
   wire [4:0]rd_wb;
   
   wire RegWrite_wb,MemtoReg_wb,MemRead_wb,MemWrite_wb;
   
   wire [31:0] IMM_EX_out; //valoarea immediate in EX
  wire [31:0] REG_DATA1_EX_out;
  wire [31:0] REG_DATA2_EX_out; //valoarea registrului sursa 2
  wire [2:0] FUNCT3_EX_out; //funct3 pentru instructiunea din EX
  wire [6:0] FUNCT7_EX_out; //funct7 pentru instructiunea din EX
  wire [4:0] RD_EX_out; //adresa registrului destinatie
  wire [4:0] RS1_EX_out; //adresa registrului sursa 1
  wire [4:0] RS2_EX_out; //adresa registrului sursa 2
  wire RegWrite_EX_out; //semnal de scriere in bancul de registri
  wire MemtoReg_EX_out; //...
  wire MemRead_EX_out; //semnal pentru activarea citirii din memorie
  wire MemWrite_EX_out; //semnal pentru activarea scrierii in memorie
  wire [1:0] ALUop_EX_out; //semnalul de control ALUop
  wire ALUSrc_EX_out; //semnal de selectie intre RS2 si valoarea imediata
  wire Branch_EX_out; //semnal de identificare a instructiunilor de tip branch
  
   wire [31:0]address_mem,write_data_mem;
   wire zero_mem;
   wire [4:0]rd_mem;
   wire RegWrite_mem,MemtoReg_mem,MemRead_mem,MemWrite_mem;
   
   wire [4:0] RD_ID; 
 ////////////////////////////////////////ID Module//////////////////////////////////
 ID instruction_decode(clk,
                       PC_ID,INSTRUCTION_ID,
                       RegWrite_EX_out, 
                       wb_data,
                       rd_wb,
                       control_sel,
                       IMM_ID,
                       REG_DATA1_ID,REG_DATA2_ID,
                       RegWrite_ID,MemtoReg_ID,MemRead_ID,MemWrite_ID,
                       ALUop_ID,
                       ALUSrc_ID,
                       Branch_ID,
                       FUNCT3_ID,
                       FUNCT7_ID,
                       RD_ID,
                       RS1_ID,
                       RS2_ID);
                       
  wire PC_write,IF_IFwrite;                  
  hazard_detection HAZARD_UNIT(RD_EX_out,
                               RS1_ID,
                               RS2_ID,
                               MemRead_EX_out,
                               PC_write,
                               IF_IFwrite,
                               control_sel);
                       
  forwarding FORWARDING_UNIT(RS1_EX_out, //adresa registrului sursa 1
                             RS2_EX_out,
                             rd_mem,
                             rd_wb,
                             RegWrite_mem,
                             RegWrite_wb,
                             forwardA,forwardB);
                             
                          
 
  id_ex ID_EX_REGISTER(clk,reset,1'b1,
                       IMM_ID,
                       REG_DATA1_ID,REG_DATA2_ID,
                       PC_ID,
                       FUNCT3_ID,
                       FUNCT7_ID,
                       RD_ID,
                       RS1_ID,
                       RS2_ID,
                       RegWrite_ID,MemtoReg_ID,MemRead_ID,MemWrite_ID,
                       ALUop_ID,
                       ALUSrc_ID,
                       Branch_ID,
                       IMM_EX_out, //valoarea immediate in EX
                       REG_DATA1_EX_out, //valoarea registrului sursa 1
                       REG_DATA2_EX_out, //valoarea registrului sursa 2
                       PC_EX_out, //adresa instructiunii curente in EX
                       FUNCT3_EX_out, //funct3 pentru instructiunea din EX
                       FUNCT7_EX_out, //funct7 pentru instructiunea din EX
                       RD_EX_out, //adresa registrului destinatie
                       RS1_EX_out, //adresa registrului sursa 1
                       RS2_EX_out, //adresa registrului sursa 2
                       RegWrite_EX_out, //semnal de scriere in bancul de registri
                       MemtoReg_EX_out, //...
                       MemRead_EX_out, //semnal pentru activarea citirii din memorie
                       MemWrite_EX_out, //semnal pentru activarea scrierii in memorie
                       ALUop_EX_out, //semnalul de control ALUop
                       ALUSrc_EX_out, //semnal de selectie intre RS2 si valoarea imediata
                       Branch_EX_out);
                       
   wire ZERO_EX;
   wire [31:0]REG_DATA2_EX_FINAL;          
   EX execution(IMM_EX_out, //valoarea immediate in EX
                REG_DATA1_EX_out, //valoarea registrului sursa 1
                REG_DATA2_EX_out, //valoarea registrului sursa 2
                PC_EX_out, //adresa instructiunii curente in EX
                FUNCT3_EX_out, //funct3 pentru instructiunea din EX
                FUNCT7_EX_out, //funct7 pentru instructiunea din EX
                RD_EX_out, //adresa registrului destinatie
                RS1_EX_out, //adresa registrului sursa 1
                RS2_EX_out, //adresa registrului sursa 2
                RegWrite_EX_out, //semnal de scriere in bancul de registri
                MemtoReg_EX_out, //...
                MemRead_EX_out, //semnal pentru activarea citirii din memorie
                MemWrite_EX_out, //semnal pentru activarea scrierii in memorie
                ALUop_EX_out, //semnalul de control ALUop
                ALUSrc_EX_out, //semnal de selectie intre RS2 si valoarea imediata
                Branch_EX_out, //semnal de identificare a instructiunilor de tip branch
                forwardA,forwardB, //semnalele de selectie pentru multiplexoarele de forwarding
                address_wb, //valoarea calculata de ALU, prezenta in WB
                address_mem,
                ZERO_EX, //flag-ul ZERO calculat de ALU
                ALU_OUT_EX, //rezultatul calculat de ALU in EX
                PC_Branch_EX, //adresa de salt calculata in EX
                REG_DATA2_EX_FINAL);
   
  
   
   
   ex_mem_reg EX_MEM_REGISTER(clk,reset,1'b1,
                              ALU_OUT_EX,REG_DATA2_EX_FINAL,
                              ZERO_EX,RD_EX_out,
                              RegWrite_EX_out,MemtoReg_EX_out,MemRead_EX_out,MemWrite_EX_out,
                              address_mem,write_data_mem,
                              zero_mem,rd_mem,
                              RegWrite_mem,MemtoReg_mem,MemRead_mem,MemWrite_mem);
                              
   assign PC_Src = zero_mem && Branch_EX_out;
   
   data_memory RAM(clk,MemRead_EX_out,MemWrite_EX_out,address_mem,write_data_mem,read_data);
    
   
                             
   mem_wb MEM_WB_REGISTER(clk,reset,1'b1,
                          read_data,address_mem,rd_mem,RegWrite_mem,MemtoReg_mem,MemRead_mem,MemWrite_mem,
                          read_data_wb,address_wb,rd_wb,RegWrite_wb,MemtoReg_wb,MemRead_wb,MemWrite_wb);
  
  
  mux_2_1 WB_MUX(address_wb,read_data_wb,MemtoReg_EX_out,wb_data);
  
                                              
endmodule
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
