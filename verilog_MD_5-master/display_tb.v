module display_tb();
reg [4:0] input_num;
wire [6:0] out;
reg error;

display d1(.x(input_num),.S(out));

initial begin
#10
input_num=5'b00000;
#10 if (out==7'b1000000)
 error=0;
 else
 error=1;
 #10 input_num=5'b01000;
 #10 if(out==7'b0000000)
 error=0;
 else
 error=1;
 #10 input_num=5'b10000;
 #10 if(out==7'b0111111)
 error=0;
 else
 error=1;
 #10 input_num=5'b01001;
 #10 if(out==7'b0010000)
 error=0;
 else
 error=1;
 #10 input_num=5'b00111;
 #10 if(out==7'b1111000)
 error=0;
 else
 error=1;
 #10 input_num=5'b11111;
 #10 if(out==7'b1111111)
 error=0;
 else
 error=1;
 end	
endmodule 