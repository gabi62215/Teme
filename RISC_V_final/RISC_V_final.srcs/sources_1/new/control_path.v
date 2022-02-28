////////////////////////////////////////CONTROL_PATH_MODULE///////////////////////////////////////////////////      
module control_path(opcode,hazard_control,Branch,MemRead,MemtoReg,ALUop,MemWrite,ALUSrc,RegWrite);
  
  input [6:0] opcode;
  input hazard_control;
  output reg MemRead,MemtoReg,MemWrite,RegWrite,Branch,ALUSrc;
  output reg [1:0] ALUop;
  
  always@(opcode) begin
    if(hazard_control) begin
        MemRead <= 0;
        MemtoReg <= 0;
        MemWrite <= 0;
        RegWrite <= 0;
        Branch <= 0;
        ALUSrc <= 0;
        ALUop <= 2'b0;
    end
    else begin
        casex(opcode)
          7'b0000000: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b00000000; //nop from ISA
          7'b0000011: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b11110000; //lw
          7'b0100011: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b10001000; //sw
          7'b0110011: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b00100010; //R32-format
          7'b0010011: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b10100011; //Register32-Immediate Arithmetic Instructions
          7'b1100011: {ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUop} <= 8'b00000101; //branch instructions
        endcase
    end
  end

endmodule
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
