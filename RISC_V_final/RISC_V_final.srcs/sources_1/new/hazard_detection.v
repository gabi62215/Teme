`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/14/2022 01:37:20 AM
// Design Name: 
// Module Name: hazard_detection
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


module hazard_detection(input [4:0] rd,
                        input [4:0] rs1,
                        input [4:0] rs2,
                        input MemRead,
                        output reg PCwrite,
                        output reg IF_IDwrite,
                        output reg control_sel);
    always @(*) begin
        if(MemRead && ((rd == rs1) || (rd == rs2))) begin
            PCwrite <= 0;
            IF_IDwrite <= 0;
            control_sel <= 1;
        end
        else begin
            control_sel <= 0;
            PCwrite <= 1;
            IF_IDwrite <= 1;
        end
    end
endmodule
