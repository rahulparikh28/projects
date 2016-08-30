module out_window(output reg[4:0]seg,seg1,seg2,seg3,seg4,seg5,input clk,rst,capture,start
,left_shift,right_shift,input[127:0]data_in);
						

reg [17:0] position_track;
reg [17:0] data_valid;
reg[4:0]i;
reg[6:0]j;


initial begin
position_track=16'h0001;
data_valid=16'h0000;
i=4'b0000;
j=7'b0000000;
end
always @(posedge clk) begin
if (rst==1)begin
 position_track=18'h00001;
 data_valid=18'h00000;
 i=4'b0000;
 j=7'b0000000;
end
else begin
  case (start)
   1'b0: begin
    if (capture==1)begin
     data_valid<=data_valid|position_track;
    end
    if (left_shift==1)begin

     if (position_track==18'h08000)begin
      position_track<=position_track;
      i<=i;
      j<=j;
     end
     else begin
      position_track<=position_track<<1;
      i<=i+5'd1;j<=j+7'd8;
     end
     end
    if(right_shift==1)begin
     if(position_track==18'h00001)begin
      position_track<=position_track;
      i<=i;
      j<=j;
     end
  
     else begin
      position_track<=position_track>>1;
      i<=i-5'd1;
      j<=j-7'd8;
     end
    end
  end
  1'b1:begin
   i<=i;
   j<=j;
  end
 endcase
end
end
always @(posedge clk) begin
if (rst==1)begin
seg<={1'b1,{4{1'b0}}};
seg1<={1'b1,{4{1'b0}}};
seg2<={1'b1,{4{1'b0}}};
seg3<={1'b1,{4{1'b0}}};
seg4<={1'b1,{4{1'b0}}};
seg5<={1'b1,{4{1'b0}}};
end
else begin	
  case (start)
   1'b0: begin
    if (data_valid[i]==1)begin
     seg<={1'b0,data_in[j+:4]};
     seg1<={1'b0,data_in[(j+4)+:4]};
    end
    else begin
     seg<={1'b1,{4{1'b0}}};
     seg1<={1'b1,{4{1'b0}}};
    end
    if (data_valid[i+1]==1) begin
     seg2<={1'b0,data_in[(j+8)+:4]};
     seg3<={1'b0,data_in[(j+12)+:4]};

    end
    else  begin
     if ((j+8)==128)begin
      seg2<={1'b1,{4{1'b1}}};
      seg3<={1'b1,{4{1'b1}}};
     end
     else begin
      seg2<={1'b1,{4{1'b0}}};
      seg3<={1'b1,{4{1'b0}}};
     end
    end
    if (data_valid[i+2]==1) begin

     seg4<={1'b0,data_in[(j+16)+:4]};
     seg5<={1'b0,data_in[(j+20)+:4]};

    end
    else  begin
     if ((j+16)==136||(j+16)==128)begin
      seg4<={1'b1,{4{1'b1}}};
      seg5<={1'b1,{4{1'b1}}};
     end
     else begin
      seg4<={1'b1,{4{1'b0}}};
      seg5<={1'b1,{4{1'b0}}};
     end
    end
   end
  1'b1: begin
        end
endcase
end
end
endmodule
