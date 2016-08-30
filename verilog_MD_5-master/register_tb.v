// Rahul Parikh
// 006950308
// key_input[2] is capture button
// key_input[1] is left shift button
// key_input[0] is right shift
// d_out is 128 bit output
// there are three error signals
// data is register for pre defined input


 
`define width_in 8
`define width_out 128

module register_tb();
// define signals
reg rst;reg [2:0] key_input;reg clk=0;
reg [`width_in-1:0]d_in;
wire [`width_out-1:0]d_out;
reg [`width_out-1:0]data;
reg error=1,error1=1,error2=1,start;
integer i=0,j=0,errorcnt=0;

 register  #(.width_out(`width_out),.width_in(`width_in)) register_ut(.d_out(d_out),.clk(clk),.rst(rst),
.capture_key(key_input[2]),.d_in(d_in),.left_shift(key_input[1]),.right_shift(key_input[0]),.start(start));

 
initial begin
data=128'h14240000650011001100220033004400;
  
  @(posedge clk)                                       
   {rst,start,key_input}={1'b0,1'b0,3'b100};            // give initial value
register(128'h14240000650011001100220033004400,15);  // call task register
  
  @(posedge clk)
   error=compare(data,d_out);                           // call function compare
  
  @(posedge clk)
   if (error==1)
   errorcnt=errorcnt+1;
   else
   errorcnt=errorcnt;
  
  @(posedge clk)
   key_input=3'b001;
  
  @(posedge clk)
   key_input=3'b100;
   d_in=8'h00;
   error=compare(128'h14240000650011001100220033004400,d_out);
  
  @(posedge clk)
   if (error==1)
   errorcnt=errorcnt+1;
   else
   errorcnt=errorcnt;
end
task register(input [127:0]data,input integer i);
integer j,k;
begin
k=0;
for(j=0;j<=i;j=j+1)begin         // for loop to give 128 bit as input
  @(posedge clk)
  d_in<=data[k+:8];

  @(posedge clk)
  #1 key_input[2]=0;
  #1 key_input[1]=1;
  #1 key_input[2]=1;
  #1 key_input[1]=0;
  k=k+8;
end
end
endtask

// this compare function i have taken from professor kredo's code
function compare(input[127:0]a,input[127:0]b);
begin
if (a===b)
compare=0;
else 
compare=1;
end
endfunction
always @ (clk) #1 clk <= ~clk;

endmodule
