// Rahul Parikh
// 006950308
// data is input to module under test

`timescale 1ns/1ps
module out_window_tb();
reg capture,left_shift,right_shift,rst,start;
reg [127:0]data;
reg clk=0;
wire [4:0]seg,seg1,seg2,seg3,seg4,seg5;
integer i=0,errorcnt=0;
reg error=0;
out_window  out_window_ut(.seg(seg),.seg1(seg1),.seg2(seg2),.seg3(seg3),.seg4(seg4),.seg5(seg5),.clk(clk),.rst(rst)
,.capture(capture),.left_shift(left_shift),.right_shift(right_shift),.data_in(data),.start(start));


always @ (clk) #1 clk <= ~clk;


initial begin
data=128'h14240000650011001100220033664400;
@(posedge clk)
 capture=0;
   left_shift=0;
   right_shift=0;
   rst=0;
	start=0;
	// first test to check the initial condition
	#3 @(posedge clk)
	if ({seg5,seg4,seg3,seg2,seg1,seg}=={6{5'b10000}})
	error=0;
	else begin 
	error=1;
	errorcnt=errorcnt+1;	
	end	
	left_shift_press();
	left_shift_press();
	capture_press();
	// second test to check capture is working or not
	#3 @(posedge clk)
	if(seg==5'b00110)
	error=0;
	else begin
	error=1;
   errorcnt=errorcnt+1;
   end   
	// now make some shift and capture operation
	
	left_shift_press();
	capture_press();
	left_shift_press();
	capture_press();
	left_shift_press();
	capture_press();
	right_shift_press();
	right_shift_press();
	
	
	// after all the operation check the output
	#3 @(posedge clk)
	if ({seg5,seg4,seg3,seg2,seg1,seg}=={5'b00010,5'b00010,5'b00000,5'b00000,5'b00011,5'b00011})
	error=0;
	else begin
	error=1;
   errorcnt=errorcnt+1;
   end
 
   // now make start button high
   // then press any of those push button
   // for this condition push button should not have any impact
   
	@(posedge clk)
	start=1;
	left_shift_press();
	#3 @(posedge clk)
	if(seg==5'b00011)
	error=0;
	else begin
	error=1;
   errorcnt=errorcnt+1;
   end   
	
	// now press reset button device should be reset
	
	reset_press();
	#3 @(posedge clk)
	if ({seg5,seg4,seg3,seg2,seg1,seg}=={6{5'b10000}})
	error=0;
	else begin 
	error=1;
	errorcnt=errorcnt+1;	
	end	
	
end		
	// this task is for capture button
	task capture_press();
	begin
	@(posedge clk)
	capture=1;
	@(posedge clk)
	capture=0;
	end 
	endtask
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
	
	