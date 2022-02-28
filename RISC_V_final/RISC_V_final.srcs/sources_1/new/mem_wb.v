`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/16/2022 12:51:30 AM
// Design Name: 
// Module Name: mem_wb
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


module mem_wb(clk,reset,write,read_data_in,address_in,rd_in,reg_write_in,mem_to_reg_in,mem_read_in,mem_write_in,
                read_data_out,address_out,rd_out,reg_write_out,mem_to_reg_out,mem_read_out,mem_write_out);
    input clk,write,reset,reg_write_in,mem_to_reg_in,mem_read_in,mem_write_in;
    input [31:0] address_in;
    input [31:0] read_data_in;
    input [4:0] rd_in;
    
    output reg [31:0] read_data_out;
    output reg [31:0] address_out;
    output reg [4:0] rd_out;
    output reg reg_write_out,mem_to_reg_out,mem_read_out,mem_write_out;
    
    always @(posedge clk) begin
        if(reset) begin
            rd_out <= 5'b0;
            read_data_out <= 32'b0;
            address_out <= 32'b0;
            reg_write_out <= 0;
            mem_to_reg_out <= 0;
            mem_read_out <= 0;
            mem_write_out <= 0;
        end
        else begin
            if(write) begin
                rd_out <= rd_in;
                read_data_out <= read_data_in;   
                address_out <= address_in; 
                reg_write_out <= reg_write_in;
                mem_to_reg_out <= mem_to_reg_in;
                mem_read_out <= mem_read_in;
                mem_write_out <= mem_write_in;
            end
        end
    end
endmodule
