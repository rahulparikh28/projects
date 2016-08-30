// Rahul Parikh
// ID No:006950308
// This is top module.
// Output: seg(Output for seven segment display)
// Output: seg1(Output for seven segment display)
// Output: seg2(Output for seven segment display)
// Output: seg3(Output for seven segment display)
// Output: seg4(Output for seven segment display)
// Output: seg5(Output for seven segment display)
// Input:  sw_in(8bit switch input)
// Input:  key_input(Control inputs)
// Input:  clk(Clock for the circuit)
// Input:  rst(Input switch to reset the circuit)
// Input:  sw_in[9] is for state selection	


module main (output wire[6:0]seg,seg1,seg2,seg3,seg4,seg5,
input [8:0] sw_in,
input [2:0] key_input,
input clk_in,rst_n);
reg [127:0] data;
reg [329:0] dis_data;

// declare some wire connections
wire locked_port,rst;
wire clk;
wire [3:0]key_out;
wire [127:0] data_out,digest_out;
wire [4:0]n,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12;
lab3_pll pll1(.refclk(clk_in),.rst(~rst_n),.outclk_0(clk),.locked(locked_port));
assign rst=~rst_n|~locked_port;

// Instanciate one_time module to get control switch result


one_time  #(.EDGE(0))pressed1(.pulse_out(key_out[1]),.clk(clk),.signal(key_input[0]));
one_time  #(.EDGE(0))pressed2(.pulse_out(key_out[2]),.clk(clk),.signal(key_input[1]));
one_time  #(.EDGE(0))pressed3(.pulse_out(key_out[3]),.clk(clk),.signal(key_input[2]));

// this register module will take data given by user and store it into ne register
// also it will give this data to other module it this data will be used	

register	 #(.width_out(128),.width_in(8)) s2p(.d_out(data_out),.clk(clk),.rst(rst),
.capture_key(key_out[3]),.d_in(sw_in[7:0]),.left_shift(key_out[2]),.right_shift(key_out[1]),.start(sw_in[8]));


// out_window module will decide weather data is entered on the register or not 
// this module also control window movement when not in md5 operation state
 
out_window  window1(.seg(n),.seg1(n1),.seg2(n2),.seg3(n3),.seg4(n4),.seg5(n5),.clk(clk),.rst(rst)
,.capture(key_out[3]),.left_shift(key_out[2]),.right_shift(key_out[1]),.data_in(data_out),.start(sw_in[8]));


// basicaly md5_output will provide 128 bit computed digest as a output when 128 bit data is given


md5_output digest(.digest_out(digest_out),.data(data_out),.start(sw_in[8]),.clk(clk),.action(key_out[3]),.rst(rst));

// this module take care of window movement when in md5 state


out_digest  window2(.seg(n6),.seg1(n7),.seg2(n8),.seg3(n9),.seg4(n10),.seg5(n11),.clk(clk),.rst(rst)
,.left_shift(key_out[2]),.right_shift(key_out[1]),.data_in(digest_out),.start(sw_in[8]));

// Instanciate dispaly module to get dispaly on 7-segment


display dis1(.x(dis_data[4:0]),.S(seg));
display dis2(.x(dis_data[9:5]),.S(seg1));
display dis3(.x(dis_data[14:10]),.S(seg2));
display dis4(.x(dis_data[19:15]),.S(seg3));
display dis5(.x(dis_data[24:20]),.S(seg4));
display dis6(.x(dis_data[29:25]),.S(seg5));

// this always loop will decide what should be on display on 7-segment

always @ (posedge clk)begin
if(sw_in[8]==1'b1 )
dis_data={n11,n10,n9,n8,n7,n6};
else
dis_data={n5,n4,n3,n2,n1,n};
end

endmodule	



