// Rahul Parikh
// 006950308
// input: data_in is 128 bit input data from md5_output module(basically computed digest)
// input: there are several other contorl inputs such as reset, left_shift, right_shift,start
// there is only 2 states one is md5 state i which we cannot take user input we can only see computed digest
// here in this module we output 6 5bit values for 7-segment to display


module out_digest(output reg[4:0]seg,seg1,seg2,seg3,seg4,seg5,input clk,rst,start
,left_shift,right_shift,input[127:0]data_in);
integer i=0;						

always @(posedge clk)begin
if (rst==1)begin                       
i<=0;
end
else begin	
 if (start==1)begin                       // if start is high that means machine is in md5 state
  
  if (left_shift==1)begin
   if(i==120)
    i<=i;
	else
    i<=i+8;
  end
  else if(right_shift==1)begin
   if(i==0)
    i<=i;
	else
    i<=i-8;
  end
 else begin
  i<=i;
 end
end
end
end
always @(posedge clk)begin
{seg5,seg4,seg3,seg2,seg1,seg}<={i>=112?5'b11111:{1'b0,data_in[(i+20)+:4]},i>=112?5'b11111:{1'b0,data_in[(i+16)+:4]}
                                ,i>=120?5'b11111:{1'b0,data_in[(i+12)+:4]},i>=120?5'b11111:{1'b0,data_in[(i+8)+:4]}
										  ,{1'b0,data_in[(i+4)+:4]},{1'b0,data_in[i+:4]}};
end
endmodule										 