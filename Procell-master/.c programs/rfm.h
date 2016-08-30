#ifndef _RFM73_H_
   40 #define _RFM73_H_
   41 
   42 //***************************************************************************//
   43 //
   65 //
   66 //***************************************************************************//
   67 
   68 //***************************************************************************//
   69 //
   82 //
   83 //***************************************************************************//
   84 
   85 
   87 //
   89 #define RFM73_LIB_VERSION "V1.03 (2012-11-16)"
   90 
   92 //
   94 #define RFM73_MAX_PACKET_LEN  32
   95 
   97 //
   99 typedef unsigned char rfm73_buffer [ RFM73_MAX_PACKET_LEN ];
  100 
  101 
  102 //***************************************************************************//
  103 //
  104 // RFM73 SPI commands
  105 //
  106 //***************************************************************************//
  107 
  110 
  112 #define RFM73_CMD_R_RX_PAYLOAD         0x61
  113 
  115 #define RFM73_CMD_W_TX_PAYLOAD         0xA0
  116 
  118 #define RFM73_CMD_FLUSH_TX             0xE1
  119 
  121 #define RFM73_CMD_FLUSH_RX             0xE2
  122 
  124 #define RFM73_CMD_REUSE_TX_PL          0xE3
  125 
  127 #define RFM73_CMD_W_TX_PAYLOAD_NOACK   0xB0
  128 
  130 #define RFM73_CMD_W_ACK_PAYLOAD        0xA8
  131 
  133 #define RFM73_CMD_ACTIVATE             0x50
  134 
  136 #define RFM73_CMD_R_RX_PL_WID          0x60
  137 
  139 #define RFM73_CMD_NOP                  0xFF
  140 
  141 //***************************************************************************//
  142 //
  143 // RFM73 register addresses
  144 //
  145 //***************************************************************************//
  146 
  148 //
  158 #define RFM73_REG_CONFIG               0x00
  159 
  161 //
  170 #define RFM73_REG_EN_AA                0x01
  171 
  173 //
  182 #define RFM73_REG_EN_RXADDR            0x02
  183 
  185 //
  189 #define RFM73_REG_SETUP_AW             0x03
  190 
  192 //
  196 #define RFM73_REG_SETUP_RETR           0x04
  197 
  199 //
  201 #define RFM73_REG_RF_CH                0x05
  202 
  204 //
  210 #define RFM73_REG_RF_SETUP             0x06
  211 
  213 //
  229 #define RFM73_REG_STATUS               0x07
  230 
  232 //
  242 #define RFM73_REG_OBSERVE_TX           0x08
  243 
  245 //
  249 #define RFM73_REG_CD                   0x09
  250 
  252 //
  256 #define RFM73_REG_RX_ADDR_P0           0x0A
  257 
  259 //
  263 #define RFM73_REG_RX_ADDR_P1           0x0B
  264 
  266 //
  270 #define RFM73_REG_RX_ADDR_P2           0x0C
  271 
  273 //
  277 #define RFM73_REG_RX_ADDR_P3           0x0D
  278 
  280 //
  284 #define RFM73_REG_RX_ADDR_P4           0x0E
  285 
  287 //
  291 #define RFM73_REG_RX_ADDR_P5           0x0F
  292 
  294 //
  298 #define RFM73_REG_TX_ADDR              0x10
  299 
  301 //
  304 #define RFM73_REG_RX_PW_P0             0x11
  305 
  307 //
  310 #define RFM73_REG_RX_PW_P1             0x12
  311 
  313 //
  316 #define RFM73_REG_RX_PW_P2             0x13
  317 
  319 //
  322 #define RFM73_REG_RX_PW_P3             0x14
  323 
  325 //
  328 #define RFM73_REG_RX_PW_P4             0x15
  329 
  331 //
  334 #define RFM73_REG_RX_PW_P5             0x16
  335 
  337 //
  346 #define RFM73_REG_FIFO_STATUS          0x17
  347 
  349 //
  360 #define RFM73_REG_DYNPD                0x1C
  361 
  363 //
  369 #define RFM73_REG_FEATURE              0x1D
  370 
  372 
  373 
  374 
  375 
  377 //
  394 void rfm73_init( void );
  395 
  397 //
  401 unsigned char rfm73_register_read( unsigned char reg );
  402 
  404 //
  408 void rfm73_buffer_read(
  409    unsigned char reg,
  410    unsigned char buf[],
  411    unsigned char length
  412 );
  413 
  415 //
  419 void rfm73_register_write( unsigned char reg, unsigned char val );
  420 
  422 //
  427 void rfm73_buffer_write(
  428    char reg,
  429    const unsigned char buf[],
  430    unsigned char length
  431 );
  432 
  433 //***************************************************************************//
  434 //
  435 // high-level interface
  436 //
  437 //***************************************************************************//
  438 
  440 //
  446 unsigned char rfm73_is_present( void );
  447 
  449 //
  453 void rfm73_mode_transmit( void );
  454 
  456 //
  460 void rfm73_mode_receive( void );
  461 
  463 //
  471 void rfm73_mode_standby( void );
  472 
  474 //
  479 void rfm73_mode_powerdown( void );
  480 
  482 //
  486 void rfm73_lna_low( void );
  487 
  489 //
  493 void rfm73_lna_high( void );
  494 
  496 //
  503 void rfm73_channel( unsigned char ch );
  504 
  506 //
  516 void rfm73_air_data_rate( unsigned char rate );
  517 
  519 //
  527 void rfm73_crc_length( unsigned char len );
  528 
  530 //
  537 void rfm73_address_length( unsigned char len );
  538 
  540 //
  549 void rfm73_power( unsigned char level ); 
  550 
  552 //
  568 void rfm73_retransmit_delay_attempts( unsigned char d, unsigned char n );
  569 
  571 //
  576 unsigned char rfm73_retransmit_count( void );
  577 
  579 //
  587 unsigned char rfm73_lost_packets_count( void );
  588 
  590 //
  594 void rfm73_lost_packets_reset( void );
  595 
  597 //
  604 void rfm73_pipe_autoack( unsigned char pipe, unsigned char enabled );
  605 
  607 //
  613 void rfm73_pipe_enable( unsigned char d, unsigned char enabled );
  614 
  616 //
  625 void rfm73_receive_address_p0( const unsigned char address[ 5 ] );
  626 
  628 //
  637 void rfm73_receive_address_p1( const unsigned char address[ 5 ] );
  638 
  640 //
  645 void rfm73_receive_address_pn( unsigned char channel, unsigned char address );
  646 
  648 //
  655 void rfm73_channel_payload_size( unsigned char n, unsigned char size );
  656 
  658 //
  662 void rfm73_transmit_address( const unsigned char address[] );   
  663 
  665 //
  668 unsigned char rfm73_transmit_fifo_full( void );
  669 
  671 //
  674 unsigned char rfm73_receive_fifo_empty( void );
  675 
  677 //
  692 void rfm73_transmit_message(
  693    const unsigned char buf[],
  694    unsigned char length
  695 );
  696 
  698 //
  711 void rfm73_transmit_message_once(
  712    const unsigned char buf[],
  713    unsigned char length
  714 );
   
   //
   unsigned char rfm73_receive_next_pipe( void );
   
   //
   unsigned char rfm73_receive_next_length( void );
   
   //
   unsigned char rfm73_receive(
      unsigned char * pipe,
      unsigned char buf[],
      unsigned char * length ); 
  #endif
