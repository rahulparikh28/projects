
// This module take any number of bits and provide any number of output bits as per requirement.




module register #(parameter width_out=128,width_in=8)
                        (output reg[width_out-1:0] d_out,
							   input clk,capture_key,rst,left_shift,right_shift,start,
								input [width_in-1:0] d_in);

reg [6:0] i=0;	
reg[127:0]zero=0;			 
always @(posedge clk) begin
if(rst==1)begin
 d_out<=zero;
 i<=0;
end
else begin

  if(start==1)begin                      // if resert button is pressed or not

   i<=i;
  end
  else begin
   if(capture_key==1)               // if capture button is pressed or not  
    d_out[i+:8]<=d_in;
   else if(left_shift==1)begin          // if left shift button is pressed or not
    if(i==120) 
     i<=i;
    else
     i=i+6'd8;
   end
   else if(right_shift==1)begin         // if right shift button is pressed or not
    if(i==0) 
     i<=i;
    else
     i=i-6'd8;
   end


   else 
     d_out<=d_out;

end
end
end
endmodule
