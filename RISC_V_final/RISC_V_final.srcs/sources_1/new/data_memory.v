`timescale 1ns / 1ps


module data_memory(input clk,
                   input mem_read,
                   input mem_write,
                   input [31:0] address,
                   input [31:0] write_data,
                   output reg [31:0] read_data);
                   
    reg [31:0] memory [0:1023];
    
    always @(posedge clk) begin
        if(mem_write)
            memory[address >> 2] = write_data;
    end
    
    always @(mem_read)
           read_data <= memory[address >> 2];
endmodule
