// Rahul Parikh
// 006950308
// This module will take 128 bit data as input and compute md5 operation and produce 128 bit digest.
// When action button press when start is high md5 operation start.

`define SALT_A 32'h67452301
`define SALT_B 32'hefcdab89
`define SALT_C 32'h98badcfe
`define SALT_D 32'h10325476

module md5_output(output reg [127:0] digest_out,input start,action,rst,input clk,input[127:0]data);
reg [511:0]message;
wire [127:0] state[4:0][15:0];
reg [127:0] answer;

// this generate block will create 64 identical md5_operation module. 
genvar i,j;
generate 
 for(i=0;i<4;i=i+1) begin:round
   for(j=0;j<16;j=j+1) begin:phase
	md5_operation operation(.round(i),.phase(j),.message(message),.current_state(state[i][j]),.next_state(state[j==15?i+1:i][j==15?0:j+1]));
   end
 end
endgenerate
assign state[0][0]={`SALT_A, `SALT_B, `SALT_C, `SALT_D};

always @(posedge clk) begin
 if(rst==1)
 message<={512{1'b0}};
 else begin
  case(start)
   1'b1:begin
    if (action==1'b1)
    message<={data,{384{1'b0}}};
   end

   1'b0:
 
    message<=message;

  endcase
 end
end
always @ (posedge clk)begin

answer<=state[4][0];
digest_out<={answer[127:96]+`SALT_A, answer[95:64]+`SALT_B, answer[63:32]+`SALT_C, answer[31:0]+`SALT_D};

end
endmodule
