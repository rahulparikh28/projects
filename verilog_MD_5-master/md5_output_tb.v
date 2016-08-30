// this module test the md5_output module 
// key_in is action button
// start is sw_in[9]


`timescale 1ns/10ps
module md5_output_tb();
wire [127:0]digest_out;
reg start,clk=0,action,rst;
reg [127:0] data;
reg error;
integer errorcnt=0;



md5_output md5_ut(.digest_out(digest_out),.start(start),.clk(clk),.action(action),.data(data),.rst(rst));
always @ (clk) #1 clk <= ~clk;
initial begin 
error=0;
start=1'b1;
action=1'b1;
// give message value as all bits highz0
// compare digest with output
// digest is only valid when satrt and key_in is high and rst is low.
// otherwise input message has no effect on output when this condition is not met


md5_operation(128'hffffffffffffffffffffffffffffffff,128'hf9d971aef6e7183fd0b0d1a06c7e530c,1'b1,1'b0,1'b1);
 @(posedge clk)
  if(digest_out==128'hf9d971aef6e7183fd0b0d1a06c7e530c)begin          // all condition met
   error=0;
   errorcnt=errorcnt;
  end
  else begin
   error=1;
   errorcnt=errorcnt+1;
  end 
md5_operation(128'h6162636465666768696a6b6c6d6e6f70,128'h173f57c5b31e3457938e1b07d0ef7592,1'b0,1'b0,1'b1);
 @(posedge clk)
  if(digest_out==128'hf9d971aef6e7183fd0b0d1a06c7e530c)begin           // here start sw is low so device is not in md5 state
   error=0;
   errorcnt=errorcnt;
  end
  else begin
   error=1;
   errorcnt=errorcnt+1;
  end 

md5_operation({128{1'b0}},128'h2d8ccdedcb43b0a7cd7051d939917dc2,1'b1,1'b0,1'b0);
 @(posedge clk)
  if(digest_out==128'hf9d971aef6e7183fd0b0d1a06c7e530c)begin        // here action button is not pressed
   error=0;
   errorcnt=errorcnt;
  end
  else begin
   error=1;
   errorcnt=errorcnt+1;
  end 

md5_operation(128'h61616161616161616161616161616161,128'h031f1dac6ea58ed01fab67b774317791,1'b1,1'b1,1'b1);
  @(posedge clk)
  if(digest_out==128'h031f1dac6ea58ed01fab67b774317791)begin             // here device should reset
   error=0;
   errorcnt=errorcnt;
  end
  else begin
   error=1;
   errorcnt=errorcnt+1;
  end 

end

task md5_operation(input[127:0]data_in,input[127:0]digest,input start_t,rst_t,action_t);
begin
 @(posedge clk)


start=start_t;
rst=rst_t;
action=action_t;
data=data_in;
#10;
end
endtask

endmodule
