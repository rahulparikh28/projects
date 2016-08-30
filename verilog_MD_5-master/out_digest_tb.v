`timescale 1ns/10ps
module out_digest_tb();
reg left_shift,right_shift,clk=1'b0,start,rst;
reg [127:0]data_in;
wire [4:0]seg,seg1,seg2,seg3,seg4,seg5;
reg error;
integer errorcnt;

out_digest digest(.seg(seg),.seg1(seg1),.seg2(seg2),.seg3(seg3),.seg4(seg4),.seg5(seg5)
                  ,.data_in(data_in),.clk(clk),.left_shift(left_shift),.right_shift(right_shift),.start(start),.rst(rst));
always @ (clk) #1 clk <= ~clk;
initial begin
@(posedge clk)
data_in=128'hf9d971aef6e7183fd0b0d1a06c7e530c;
left_shift=1'b0;
right_shift=1'b0;
start=1'b1;
rst=1'b0;
error=1'b0;
errorcnt=0;


// do some shift operations 
repeat(8) left_shift_press();
repeat(2) right_shift_press();


// now check if module under test working correctly 
#3 @(posedge clk )
  if (seg4==5'b01111)
   error=0;
  else begin	 	
   error=1;
   errorcnt=errorcnt+1;
  end

  
// now make start low and do some operations
// module dosen't suppose to do anything
@ (posedge clk )
start=0;
repeat (5) left_shift_press();
repeat (2) right_shift_press();
 
// check the output 
#3 @(posedge clk)
  if (seg4==5'b01111)
   error=0;
  else begin	 	
   error=1;
   errorcnt=errorcnt+1;
  end

  // now make reset button high
  reset_press();

  // check the output
#3 @(posedge clk)
  if (seg1==5'b00000)
   error=0;
  else begin	 	
   error=1;
   errorcnt=errorcnt+1;
  end

end
// this task is for left_shift button
	task left_shift_press();
	  begin
	  @(posedge clk)
	  left_shift=1;
	  @(posedge clk)
	  left_shift=0;
	  end 
	endtask
	// this task is for right_shift button
	task right_shift_press();
	  begin
	  @(posedge clk)
	  right_shift=1;
	  @(posedge clk)
	  right_shift=0;
	  end 
	endtask
   // this task is for reset button
	task reset_press();
	  begin
	  @(posedge clk)
	  rst=1;
	  @(posedge clk)
	  rst=0;
	  end 
	endtask
	
endmodule
