
// This module take 5 bit input and produce 7 bit binary number to display number on 7-segment display
// Input:x(data)
// Output:S(Input for 7-segment)

module display(output wire[6:0]S,input[5:1]x);
wire [17:0]m;
assign m[0]=~x[5]&~x[4]&~x[3]&~x[2]&~x[1];
assign m[1]=~x[5]&~x[4]&~x[3]&~x[2]&x[1];
assign m[2]=~x[5]&~x[4]&~x[3]&x[2]&~x[1];
assign m[3]=~x[5]&~x[4]&~x[3]&x[2]&x[1];
assign m[4]=~x[5]&~x[4]&x[3]&~x[2]&~x[1];
assign m[5]=~x[5]&~x[4]&x[3]&~x[2]&x[1];
assign m[6]=~x[5]&~x[4]&x[3]&x[2]&~x[1];
assign m[7]=~x[5]&~x[4]&x[3]&x[2]&x[1];
assign m[8]=~x[5]&x[4]&~x[3]&~x[2]&~x[1];
assign m[9]=~x[5]&x[4]&~x[3]&~x[2]&x[1];
assign m[10]=~x[5]&x[4]&~x[3]&x[2]&~x[1];
assign m[11]=~x[5]&x[4]&~x[3]&x[2]&x[1];
assign m[12]=~x[5]&x[4]&x[3]&~x[2]&~x[1];
assign m[13]=~x[5]&x[4]&x[3]&~x[2]&x[1];
assign m[14]=~x[5]&x[4]&x[3]&x[2]&~x[1];
assign m[15]=~x[5]&x[4]&x[3]&x[2]&x[1];
assign m[16]=x[5]&~x[4]&~x[3]&~x[2]&~x[1];
assign m[17]=x[5]&x[4]&x[3]&x[2]&x[1];
                                                           
assign S[0]=m[1]|m[4]|m[11]|m[13]|m[16]|m[17];
assign S[1]=m[5]|m[6]|m[11]|m[12]|m[14]|m[15]|m[16]|m[17];
assign S[2]=m[2]|m[12]|m[14]|m[15]|m[16]|m[17];
assign S[3]=m[1]|m[4]|m[7]|m[10]|m[15]|m[16]|m[17];
assign S[4]=m[1]|m[3]|m[4]|m[5]|m[7]|m[9]|m[16]|m[17];
assign S[5]=m[1]|m[2]|m[3]|m[7]|m[13]|m[16]|m[17];
assign S[6]=m[0]|m[1]|m[7]|m[12]|m[17];
endmodule
