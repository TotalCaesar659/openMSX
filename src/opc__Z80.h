// $Id$

/********************************************************************/
/*                                                                  */
/* This file contains all the common opcode tablesas can be found   */
/* in both R800 and Z80.                                            */
/*                                                                  */
/* The timing cycles are stored in different files for each CPU.    */
/* Also instructions with hardcoded timing information are stored   */
/* in these seperate files                                          */
/*                                                                  */
/*                                                 David Heremans   */
/*                                                                  */
/********************************************************************/


unsigned Z80::cycles_main[256] = {
  4,10,7,6,4,4,7,4,
  4,11,7,6,4,4,7,4,
  8,10,7,6,4,4,7,4,
  7,11,7,6,4,4,7,4,
  7,10,16,6,4,4,7,4,
  7,11,16,6,4,4,7,4,
  7,10,13,6,11,11,10,4,
  7,11,13,6,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  7,7,7,7,7,7,4,7,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  4,4,4,4,4,4,7,4,
  5,10,10,10,10,11,7,11,
  5,4,10,0,10,10,7,11,
  5,10,10,11,10,11,7,11,
  5,4,10,11,10,0,7,11,
  5,10,10,19,10,11,7,11,
  5,4,10,4,10,0,7,11,
  5,10,10,4,10,11,7,11,
  5,6,10,4,10,0,7,11
};

unsigned Z80::cycles_cb[256] = {
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,12,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8,
  8,8,8,8,8,8,15,8
};
unsigned Z80::cycles_xx_cb[256] = {
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0,
  0,0,0,0,0,0,23,0
};
unsigned Z80::cycles_xx[256] = {
  0,0,0,0,0,0,0,0,
  0,15,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,15,0,0,0,0,0,0,
  0,14,20,10,9,9,9,0,
  0,15,20,10,9,9,9,0,
  0,0,0,0,23,23,19,0,
  0,15,0,0,0,0,0,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  9,9,9,9,9,9,9,9,
  9,9,9,9,9,9,9,9,
  19,19,19,19,19,19,19,19,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,9,9,19,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,14,0,23,0,15,0,0,
  0,8,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,10,0,0,0,0,0,0
};
unsigned Z80::cycles_ed[256] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  12,12,15,20,8,8,8,9,
  12,12,15,20,8,8,8,9,
  12,12,15,20,8,8,8,9,
  12,12,15,20,8,8,8,9,
  12,12,15,20,8,8,8,18,
  12,12,15,20,8,8,8,18,
  12,12,15,20,8,8,8,0,
  12,12,15,20,8,8,8,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  16,16,16,16,0,0,0,0,
  16,16,16,16,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0
};

opcode_fn Z80::opcode_dd_cb[256] = {
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rlc_xix  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rrc_xix  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rl_xix   ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rr_xix   ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sla_xix  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sra_xix  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sll_xix  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::srl_xix  ,&Z80::no_op_xx ,
 &Z80::bit_0_xix,&Z80::bit_0_xix,&Z80::bit_0_xix,&Z80::bit_0_xix,
 &Z80::bit_0_xix,&Z80::bit_0_xix,&Z80::bit_0_xix,&Z80::bit_0_xix,
 &Z80::bit_1_xix,&Z80::bit_1_xix,&Z80::bit_1_xix,&Z80::bit_1_xix,
 &Z80::bit_1_xix,&Z80::bit_1_xix,&Z80::bit_1_xix,&Z80::bit_1_xix,
 &Z80::bit_2_xix,&Z80::bit_2_xix,&Z80::bit_2_xix,&Z80::bit_2_xix,
 &Z80::bit_2_xix,&Z80::bit_2_xix,&Z80::bit_2_xix,&Z80::bit_2_xix,
 &Z80::bit_3_xix,&Z80::bit_3_xix,&Z80::bit_3_xix,&Z80::bit_3_xix,
 &Z80::bit_3_xix,&Z80::bit_3_xix,&Z80::bit_3_xix,&Z80::bit_3_xix,
 &Z80::bit_4_xix,&Z80::bit_4_xix,&Z80::bit_4_xix,&Z80::bit_4_xix,
 &Z80::bit_4_xix,&Z80::bit_4_xix,&Z80::bit_4_xix,&Z80::bit_4_xix,
 &Z80::bit_5_xix,&Z80::bit_5_xix,&Z80::bit_5_xix,&Z80::bit_5_xix,
 &Z80::bit_5_xix,&Z80::bit_5_xix,&Z80::bit_5_xix,&Z80::bit_5_xix,
 &Z80::bit_6_xix,&Z80::bit_6_xix,&Z80::bit_6_xix,&Z80::bit_6_xix,
 &Z80::bit_6_xix,&Z80::bit_6_xix,&Z80::bit_6_xix,&Z80::bit_6_xix,
 &Z80::bit_7_xix,&Z80::bit_7_xix,&Z80::bit_7_xix,&Z80::bit_7_xix,
 &Z80::bit_7_xix,&Z80::bit_7_xix,&Z80::bit_7_xix,&Z80::bit_7_xix,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_0_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_1_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_2_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_3_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_4_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_5_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_6_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_7_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_0_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_1_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_2_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_3_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_4_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_5_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_6_xix,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_7_xix,&Z80::no_op_xx
};

opcode_fn Z80::opcode_fd_cb[256] = {
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rlc_xiy  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rrc_xiy  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rl_xiy   ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::rr_xiy   ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sla_xiy  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sra_xiy  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::sll_xiy  ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::srl_xiy  ,&Z80::no_op_xx ,
 &Z80::bit_0_xiy,&Z80::bit_0_xiy,&Z80::bit_0_xiy,&Z80::bit_0_xiy,
 &Z80::bit_0_xiy,&Z80::bit_0_xiy,&Z80::bit_0_xiy,&Z80::bit_0_xiy,
 &Z80::bit_1_xiy,&Z80::bit_1_xiy,&Z80::bit_1_xiy,&Z80::bit_1_xiy,
 &Z80::bit_1_xiy,&Z80::bit_1_xiy,&Z80::bit_1_xiy,&Z80::bit_1_xiy,
 &Z80::bit_2_xiy,&Z80::bit_2_xiy,&Z80::bit_2_xiy,&Z80::bit_2_xiy,
 &Z80::bit_2_xiy,&Z80::bit_2_xiy,&Z80::bit_2_xiy,&Z80::bit_2_xiy,
 &Z80::bit_3_xiy,&Z80::bit_3_xiy,&Z80::bit_3_xiy,&Z80::bit_3_xiy,
 &Z80::bit_3_xiy,&Z80::bit_3_xiy,&Z80::bit_3_xiy,&Z80::bit_3_xiy,
 &Z80::bit_4_xiy,&Z80::bit_4_xiy,&Z80::bit_4_xiy,&Z80::bit_4_xiy,
 &Z80::bit_4_xiy,&Z80::bit_4_xiy,&Z80::bit_4_xiy,&Z80::bit_4_xiy,
 &Z80::bit_5_xiy,&Z80::bit_5_xiy,&Z80::bit_5_xiy,&Z80::bit_5_xiy,
 &Z80::bit_5_xiy,&Z80::bit_5_xiy,&Z80::bit_5_xiy,&Z80::bit_5_xiy,
 &Z80::bit_6_xiy,&Z80::bit_6_xiy,&Z80::bit_6_xiy,&Z80::bit_6_xiy,
 &Z80::bit_6_xiy,&Z80::bit_6_xiy,&Z80::bit_6_xiy,&Z80::bit_6_xiy,
 &Z80::bit_7_xiy,&Z80::bit_7_xiy,&Z80::bit_7_xiy,&Z80::bit_7_xiy,
 &Z80::bit_7_xiy,&Z80::bit_7_xiy,&Z80::bit_7_xiy,&Z80::bit_7_xiy,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_0_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_1_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_2_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_3_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_4_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_5_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_6_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::res_7_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_0_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_1_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_2_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_3_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_4_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_5_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_6_xiy,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::no_op_xx ,
 &Z80::no_op_xx ,&Z80::no_op_xx ,&Z80::set_7_xiy,&Z80::no_op_xx
};

opcode_fn Z80::opcode_cb[256]=
{
 &Z80::rlc_b  ,&Z80::rlc_c  ,&Z80::rlc_d  ,&Z80::rlc_e  ,&Z80::rlc_h  ,&Z80::rlc_l  ,&Z80::rlc_xhl  ,&Z80::rlc_a  ,
 &Z80::rrc_b  ,&Z80::rrc_c  ,&Z80::rrc_d  ,&Z80::rrc_e  ,&Z80::rrc_h  ,&Z80::rrc_l  ,&Z80::rrc_xhl  ,&Z80::rrc_a  ,
 &Z80::rl_b   ,&Z80::rl_c   ,&Z80::rl_d   ,&Z80::rl_e   ,&Z80::rl_h   ,&Z80::rl_l   ,&Z80::rl_xhl   ,&Z80::rl_a   ,
 &Z80::rr_b   ,&Z80::rr_c   ,&Z80::rr_d   ,&Z80::rr_e   ,&Z80::rr_h   ,&Z80::rr_l   ,&Z80::rr_xhl   ,&Z80::rr_a   ,
 &Z80::sla_b  ,&Z80::sla_c  ,&Z80::sla_d  ,&Z80::sla_e  ,&Z80::sla_h  ,&Z80::sla_l  ,&Z80::sla_xhl  ,&Z80::sla_a  ,
 &Z80::sra_b  ,&Z80::sra_c  ,&Z80::sra_d  ,&Z80::sra_e  ,&Z80::sra_h  ,&Z80::sra_l  ,&Z80::sra_xhl  ,&Z80::sra_a  ,
 &Z80::sll_b  ,&Z80::sll_c  ,&Z80::sll_d  ,&Z80::sll_e  ,&Z80::sll_h  ,&Z80::sll_l  ,&Z80::sll_xhl  ,&Z80::sll_a  ,
 &Z80::srl_b  ,&Z80::srl_c  ,&Z80::srl_d  ,&Z80::srl_e  ,&Z80::srl_h  ,&Z80::srl_l  ,&Z80::srl_xhl  ,&Z80::srl_a  ,
 &Z80::bit_0_b,&Z80::bit_0_c,&Z80::bit_0_d,&Z80::bit_0_e,&Z80::bit_0_h,&Z80::bit_0_l,&Z80::bit_0_xhl,&Z80::bit_0_a,
 &Z80::bit_1_b,&Z80::bit_1_c,&Z80::bit_1_d,&Z80::bit_1_e,&Z80::bit_1_h,&Z80::bit_1_l,&Z80::bit_1_xhl,&Z80::bit_1_a,
 &Z80::bit_2_b,&Z80::bit_2_c,&Z80::bit_2_d,&Z80::bit_2_e,&Z80::bit_2_h,&Z80::bit_2_l,&Z80::bit_2_xhl,&Z80::bit_2_a,
 &Z80::bit_3_b,&Z80::bit_3_c,&Z80::bit_3_d,&Z80::bit_3_e,&Z80::bit_3_h,&Z80::bit_3_l,&Z80::bit_3_xhl,&Z80::bit_3_a,
 &Z80::bit_4_b,&Z80::bit_4_c,&Z80::bit_4_d,&Z80::bit_4_e,&Z80::bit_4_h,&Z80::bit_4_l,&Z80::bit_4_xhl,&Z80::bit_4_a,
 &Z80::bit_5_b,&Z80::bit_5_c,&Z80::bit_5_d,&Z80::bit_5_e,&Z80::bit_5_h,&Z80::bit_5_l,&Z80::bit_5_xhl,&Z80::bit_5_a,
 &Z80::bit_6_b,&Z80::bit_6_c,&Z80::bit_6_d,&Z80::bit_6_e,&Z80::bit_6_h,&Z80::bit_6_l,&Z80::bit_6_xhl,&Z80::bit_6_a,
 &Z80::bit_7_b,&Z80::bit_7_c,&Z80::bit_7_d,&Z80::bit_7_e,&Z80::bit_7_h,&Z80::bit_7_l,&Z80::bit_7_xhl,&Z80::bit_7_a,
 &Z80::res_0_b,&Z80::res_0_c,&Z80::res_0_d,&Z80::res_0_e,&Z80::res_0_h,&Z80::res_0_l,&Z80::res_0_xhl,&Z80::res_0_a,
 &Z80::res_1_b,&Z80::res_1_c,&Z80::res_1_d,&Z80::res_1_e,&Z80::res_1_h,&Z80::res_1_l,&Z80::res_1_xhl,&Z80::res_1_a,
 &Z80::res_2_b,&Z80::res_2_c,&Z80::res_2_d,&Z80::res_2_e,&Z80::res_2_h,&Z80::res_2_l,&Z80::res_2_xhl,&Z80::res_2_a,
 &Z80::res_3_b,&Z80::res_3_c,&Z80::res_3_d,&Z80::res_3_e,&Z80::res_3_h,&Z80::res_3_l,&Z80::res_3_xhl,&Z80::res_3_a,
 &Z80::res_4_b,&Z80::res_4_c,&Z80::res_4_d,&Z80::res_4_e,&Z80::res_4_h,&Z80::res_4_l,&Z80::res_4_xhl,&Z80::res_4_a,
 &Z80::res_5_b,&Z80::res_5_c,&Z80::res_5_d,&Z80::res_5_e,&Z80::res_5_h,&Z80::res_5_l,&Z80::res_5_xhl,&Z80::res_5_a,
 &Z80::res_6_b,&Z80::res_6_c,&Z80::res_6_d,&Z80::res_6_e,&Z80::res_6_h,&Z80::res_6_l,&Z80::res_6_xhl,&Z80::res_6_a,
 &Z80::res_7_b,&Z80::res_7_c,&Z80::res_7_d,&Z80::res_7_e,&Z80::res_7_h,&Z80::res_7_l,&Z80::res_7_xhl,&Z80::res_7_a,
 &Z80::set_0_b,&Z80::set_0_c,&Z80::set_0_d,&Z80::set_0_e,&Z80::set_0_h,&Z80::set_0_l,&Z80::set_0_xhl,&Z80::set_0_a,
 &Z80::set_1_b,&Z80::set_1_c,&Z80::set_1_d,&Z80::set_1_e,&Z80::set_1_h,&Z80::set_1_l,&Z80::set_1_xhl,&Z80::set_1_a,
 &Z80::set_2_b,&Z80::set_2_c,&Z80::set_2_d,&Z80::set_2_e,&Z80::set_2_h,&Z80::set_2_l,&Z80::set_2_xhl,&Z80::set_2_a,
 &Z80::set_3_b,&Z80::set_3_c,&Z80::set_3_d,&Z80::set_3_e,&Z80::set_3_h,&Z80::set_3_l,&Z80::set_3_xhl,&Z80::set_3_a,
 &Z80::set_4_b,&Z80::set_4_c,&Z80::set_4_d,&Z80::set_4_e,&Z80::set_4_h,&Z80::set_4_l,&Z80::set_4_xhl,&Z80::set_4_a,
 &Z80::set_5_b,&Z80::set_5_c,&Z80::set_5_d,&Z80::set_5_e,&Z80::set_5_h,&Z80::set_5_l,&Z80::set_5_xhl,&Z80::set_5_a,
 &Z80::set_6_b,&Z80::set_6_c,&Z80::set_6_d,&Z80::set_6_e,&Z80::set_6_h,&Z80::set_6_l,&Z80::set_6_xhl,&Z80::set_6_a,
 &Z80::set_7_b,&Z80::set_7_c,&Z80::set_7_d,&Z80::set_7_e,&Z80::set_7_h,&Z80::set_7_l,&Z80::set_7_xhl,&Z80::set_7_a
};

opcode_fn Z80::opcode_dd[256]=
{
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_ix_bc ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_ix_de ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::ld_ix_word,&Z80::ld_xword_ix,&Z80::inc_ix   ,
  &Z80::inc_ixh   ,&Z80::dec_ixh   ,&Z80::ld_ixh_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_ix_ix ,&Z80::ld_ix_xword,&Z80::dec_ix   ,
  &Z80::inc_ixl   ,&Z80::dec_ixl   ,&Z80::ld_ixl_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::inc_xix   ,&Z80::dec_xix   ,&Z80::ld_xix_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_ix_sp ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_b_ixh  ,&Z80::ld_b_ixl  ,&Z80::ld_b_xix   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_c_ixh  ,&Z80::ld_c_ixl  ,&Z80::ld_c_xix   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_d_ixh  ,&Z80::ld_d_ixl  ,&Z80::ld_d_xix   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_e_ixh  ,&Z80::ld_e_ixl  ,&Z80::ld_e_xix   ,&Z80::no_op    ,
  &Z80::ld_ixh_b  ,&Z80::ld_ixh_c  ,&Z80::ld_ixh_d   ,&Z80::ld_ixh_e ,
  &Z80::ld_ixh_ixh,&Z80::ld_ixh_ixl,&Z80::ld_h_xix   ,&Z80::ld_ixh_a ,
  &Z80::ld_ixl_b  ,&Z80::ld_ixl_c  ,&Z80::ld_ixl_d   ,&Z80::ld_ixl_e ,
  &Z80::ld_ixl_ixh,&Z80::ld_ixl_ixl,&Z80::ld_l_xix   ,&Z80::ld_ixl_a ,
  &Z80::ld_xix_b  ,&Z80::ld_xix_c  ,&Z80::ld_xix_d   ,&Z80::ld_xix_e ,
  &Z80::ld_xix_h  ,&Z80::ld_xix_l  ,&Z80::no_op      ,&Z80::ld_xix_a ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_a_ixh  ,&Z80::ld_a_ixl  ,&Z80::ld_a_xix   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::add_a_ixh ,&Z80::add_a_ixl ,&Z80::add_a_xix  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::adc_a_ixh ,&Z80::adc_a_ixl ,&Z80::adc_a_xix  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::sub_ixh   ,&Z80::sub_ixl   ,&Z80::sub_xix    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::sbc_a_ixh ,&Z80::sbc_a_ixl ,&Z80::sbc_a_xix  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::and_ixh   ,&Z80::and_ixl   ,&Z80::and_xix    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::xor_ixh   ,&Z80::xor_ixl   ,&Z80::xor_xix    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::or_ixh    ,&Z80::or_ixl    ,&Z80::or_xix     ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::cp_ixh    ,&Z80::cp_ixl    ,&Z80::cp_xix     ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::dd_cb    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::pop_ix    ,&Z80::no_op      ,&Z80::ex_xsp_ix,
  &Z80::no_op     ,&Z80::push_ix   ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::jp_ix     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::ld_sp_ix  ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op
};

opcode_fn Z80::opcode_ed[256]=
{
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::in_b_c,&Z80::out_c_b,&Z80::sbc_hl_bc,&Z80::ld_xword_bc,&Z80::neg,&Z80::retn,&Z80::im_0 ,&Z80::ld_i_a,
 &Z80::in_c_c,&Z80::out_c_c,&Z80::adc_hl_bc,&Z80::ld_bc_xword,&Z80::neg,&Z80::reti,&Z80::im_0 ,&Z80::ld_r_a,
 &Z80::in_d_c,&Z80::out_c_d,&Z80::sbc_hl_de,&Z80::ld_xword_de,&Z80::neg,&Z80::retn,&Z80::im_1 ,&Z80::ld_a_i,
 &Z80::in_e_c,&Z80::out_c_e,&Z80::adc_hl_de,&Z80::ld_de_xword,&Z80::neg,&Z80::reti,&Z80::im_2 ,&Z80::ld_a_r,
 &Z80::in_h_c,&Z80::out_c_h,&Z80::sbc_hl_hl,&Z80::ld_xword_hl,&Z80::neg,&Z80::retn,&Z80::im_0 ,&Z80::rrd   ,
 &Z80::in_l_c,&Z80::out_c_l,&Z80::adc_hl_hl,&Z80::ld_hl_xword,&Z80::neg,&Z80::reti,&Z80::im_0 ,&Z80::rld   ,
 &Z80::in_0_c,&Z80::out_c_0,&Z80::sbc_hl_sp,&Z80::ld_xword_sp,&Z80::neg,&Z80::retn,&Z80::im_1 ,&Z80::nop   ,
 &Z80::in_a_c,&Z80::out_c_a,&Z80::adc_hl_sp,&Z80::ld_sp_xword,&Z80::neg,&Z80::reti,&Z80::im_2 ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::ldi   ,&Z80::cpi    ,&Z80::ini      ,&Z80::outi       ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::ldd   ,&Z80::cpd    ,&Z80::ind      ,&Z80::outd       ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::ldir  ,&Z80::cpir   ,&Z80::inir     ,&Z80::otir       ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::lddr  ,&Z80::cpdr   ,&Z80::indr     ,&Z80::otdr       ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::patch,&Z80::nop   ,
 &Z80::nop   ,&Z80::nop    ,&Z80::nop      ,&Z80::nop        ,&Z80::nop,&Z80::nop ,&Z80::nop  ,&Z80::nop
};

opcode_fn Z80::opcode_fd[256]=
{
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_iy_bc ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_iy_de ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::ld_iy_word,&Z80::ld_xword_iy,&Z80::inc_iy   ,
  &Z80::inc_iy    ,&Z80::dec_iy    ,&Z80::ld_iyh_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_iy_iy ,&Z80::ld_iy_xword,&Z80::dec_iy   ,
  &Z80::inc_iy    ,&Z80::dec_iy    ,&Z80::ld_iyl_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::inc_xiy   ,&Z80::dec_xiy   ,&Z80::ld_xiy_byte,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::add_iy_sp ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_b_iyh  ,&Z80::ld_b_iyl  ,&Z80::ld_b_xiy   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_c_iyh  ,&Z80::ld_c_iyl  ,&Z80::ld_c_xiy   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_d_iyh  ,&Z80::ld_d_iyl  ,&Z80::ld_d_xiy   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_e_iyh  ,&Z80::ld_e_iyl  ,&Z80::ld_e_xiy   ,&Z80::no_op    ,
  &Z80::ld_iyh_b  ,&Z80::ld_iyh_c  ,&Z80::ld_iyh_d   ,&Z80::ld_iyh_e ,
  &Z80::ld_iyh_iyh,&Z80::ld_iyh_iyl,&Z80::ld_h_xiy   ,&Z80::ld_iyh_a ,
  &Z80::ld_iyl_b  ,&Z80::ld_iyl_c  ,&Z80::ld_iyl_d   ,&Z80::ld_iyl_e ,
  &Z80::ld_iyl_iyh,&Z80::ld_iyl_iyl,&Z80::ld_l_xiy   ,&Z80::ld_iyl_a ,
  &Z80::ld_xiy_b  ,&Z80::ld_xiy_c  ,&Z80::ld_xiy_d   ,&Z80::ld_xiy_e ,
  &Z80::ld_xiy_h  ,&Z80::ld_xiy_l  ,&Z80::no_op      ,&Z80::ld_xiy_a ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::ld_a_iyh  ,&Z80::ld_a_iyl  ,&Z80::ld_a_xiy   ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::add_a_iyh ,&Z80::add_a_iyl ,&Z80::add_a_xiy  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::adc_a_iyh ,&Z80::adc_a_iyl ,&Z80::adc_a_xiy  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::sub_iyh   ,&Z80::sub_iyl   ,&Z80::sub_xiy    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::sbc_a_iyh ,&Z80::sbc_a_iyl ,&Z80::sbc_a_xiy  ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::and_iyh   ,&Z80::and_iyl   ,&Z80::and_xiy    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::xor_iyh   ,&Z80::xor_iyl   ,&Z80::xor_xiy    ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::or_iyh    ,&Z80::or_iyl    ,&Z80::or_xiy     ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::cp_iyh    ,&Z80::cp_iyl    ,&Z80::cp_xiy     ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::fd_cb    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::pop_iy    ,&Z80::no_op      ,&Z80::ex_xsp_iy,
  &Z80::no_op     ,&Z80::push_iy   ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::jp_iy     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::ld_sp_iy  ,&Z80::no_op      ,&Z80::no_op    ,
  &Z80::no_op     ,&Z80::no_op     ,&Z80::no_op      ,&Z80::no_op 
};


opcode_fn Z80::opcode_main[256]=
{
 &Z80::nop     ,&Z80::ld_bc_word,&Z80::ld_xbc_a   ,&Z80::inc_bc    ,
 &Z80::inc_b   ,&Z80::dec_b     ,&Z80::ld_b_byte  ,&Z80::rlca      ,
 &Z80::ex_af_af,&Z80::add_hl_bc ,&Z80::ld_a_xbc   ,&Z80::dec_bc    ,
 &Z80::inc_c   ,&Z80::dec_c     ,&Z80::ld_c_byte  ,&Z80::rrca      ,
 &Z80::djnz    ,&Z80::ld_de_word,&Z80::ld_xde_a   ,&Z80::inc_de    ,
 &Z80::inc_d   ,&Z80::dec_d     ,&Z80::ld_d_byte  ,&Z80::rla       ,
 &Z80::jr      ,&Z80::add_hl_de ,&Z80::ld_a_xde   ,&Z80::dec_de    ,
 &Z80::inc_e   ,&Z80::dec_e     ,&Z80::ld_e_byte  ,&Z80::rra       ,
 &Z80::jr_nz   ,&Z80::ld_hl_word,&Z80::ld_xword_hl,&Z80::inc_hl    ,
 &Z80::inc_h   ,&Z80::dec_h     ,&Z80::ld_h_byte  ,&Z80::daa       ,
 &Z80::jr_z    ,&Z80::add_hl_hl ,&Z80::ld_hl_xword,&Z80::dec_hl    ,
 &Z80::inc_l   ,&Z80::dec_l     ,&Z80::ld_l_byte  ,&Z80::cpl       ,
 &Z80::jr_nc   ,&Z80::ld_sp_word,&Z80::ld_xbyte_a ,&Z80::inc_sp    ,
 &Z80::inc_xhl ,&Z80::dec_xhl   ,&Z80::ld_xhl_byte,&Z80::scf       ,
 &Z80::jr_c    ,&Z80::add_hl_sp ,&Z80::ld_a_xbyte ,&Z80::dec_sp    ,
 &Z80::inc_a   ,&Z80::dec_a     ,&Z80::ld_a_byte  ,&Z80::ccf       ,
 &Z80::ld_b_b  ,&Z80::ld_b_c    ,&Z80::ld_b_d     ,&Z80::ld_b_e    ,
 &Z80::ld_b_h  ,&Z80::ld_b_l    ,&Z80::ld_b_xhl   ,&Z80::ld_b_a    ,
 &Z80::ld_c_b  ,&Z80::ld_c_c    ,&Z80::ld_c_d     ,&Z80::ld_c_e    ,
 &Z80::ld_c_h  ,&Z80::ld_c_l    ,&Z80::ld_c_xhl   ,&Z80::ld_c_a    ,
 &Z80::ld_d_b  ,&Z80::ld_d_c    ,&Z80::ld_d_d     ,&Z80::ld_d_e    ,
 &Z80::ld_d_h  ,&Z80::ld_d_l    ,&Z80::ld_d_xhl   ,&Z80::ld_d_a    ,
 &Z80::ld_e_b  ,&Z80::ld_e_c    ,&Z80::ld_e_d     ,&Z80::ld_e_e    ,
 &Z80::ld_e_h  ,&Z80::ld_e_l    ,&Z80::ld_e_xhl   ,&Z80::ld_e_a    ,
 &Z80::ld_h_b  ,&Z80::ld_h_c    ,&Z80::ld_h_d     ,&Z80::ld_h_e    ,
 &Z80::ld_h_h  ,&Z80::ld_h_l    ,&Z80::ld_h_xhl   ,&Z80::ld_h_a    ,
 &Z80::ld_l_b  ,&Z80::ld_l_c    ,&Z80::ld_l_d     ,&Z80::ld_l_e    ,
 &Z80::ld_l_h  ,&Z80::ld_l_l    ,&Z80::ld_l_xhl   ,&Z80::ld_l_a    ,
 &Z80::ld_xhl_b,&Z80::ld_xhl_c  ,&Z80::ld_xhl_d   ,&Z80::ld_xhl_e  ,
 &Z80::ld_xhl_h,&Z80::ld_xhl_l  ,&Z80::halt       ,&Z80::ld_xhl_a  ,
 &Z80::ld_a_b  ,&Z80::ld_a_c    ,&Z80::ld_a_d     ,&Z80::ld_a_e    ,
 &Z80::ld_a_h  ,&Z80::ld_a_l    ,&Z80::ld_a_xhl   ,&Z80::ld_a_a    ,
 &Z80::add_a_b ,&Z80::add_a_c   ,&Z80::add_a_d    ,&Z80::add_a_e   ,
 &Z80::add_a_h ,&Z80::add_a_l   ,&Z80::add_a_xhl  ,&Z80::add_a_a   ,
 &Z80::adc_a_b ,&Z80::adc_a_c   ,&Z80::adc_a_d    ,&Z80::adc_a_e   ,
 &Z80::adc_a_h ,&Z80::adc_a_l   ,&Z80::adc_a_xhl  ,&Z80::adc_a_a   ,
 &Z80::sub_b   ,&Z80::sub_c     ,&Z80::sub_d      ,&Z80::sub_e     ,
 &Z80::sub_h   ,&Z80::sub_l     ,&Z80::sub_xhl    ,&Z80::sub_a     ,
 &Z80::sbc_a_b ,&Z80::sbc_a_c   ,&Z80::sbc_a_d    ,&Z80::sbc_a_e   ,
 &Z80::sbc_a_h ,&Z80::sbc_a_l   ,&Z80::sbc_a_xhl  ,&Z80::sbc_a_a   ,
 &Z80::and_b   ,&Z80::and_c     ,&Z80::and_d      ,&Z80::and_e     ,
 &Z80::and_h   ,&Z80::and_l     ,&Z80::and_xhl    ,&Z80::and_a     ,
 &Z80::xor_b   ,&Z80::xor_c     ,&Z80::xor_d      ,&Z80::xor_e     ,
 &Z80::xor_h   ,&Z80::xor_l     ,&Z80::xor_xhl    ,&Z80::xor_a     ,
 &Z80::or_b    ,&Z80::or_c      ,&Z80::or_d       ,&Z80::or_e      ,
 &Z80::or_h    ,&Z80::or_l      ,&Z80::or_xhl     ,&Z80::or_a      ,
 &Z80::cp_b    ,&Z80::cp_c      ,&Z80::cp_d       ,&Z80::cp_e      ,
 &Z80::cp_h    ,&Z80::cp_l      ,&Z80::cp_xhl     ,&Z80::cp_a      ,
 &Z80::ret_nz  ,&Z80::pop_bc    ,&Z80::jp_nz      ,&Z80::jp        ,
 &Z80::call_nz ,&Z80::push_bc   ,&Z80::add_a_byte ,&Z80::rst_00    ,
 &Z80::ret_z   ,&Z80::ret       ,&Z80::jp_z       ,&Z80::cb        ,
 &Z80::call_z  ,&Z80::call      ,&Z80::adc_a_byte ,&Z80::rst_08    ,
 &Z80::ret_nc  ,&Z80::pop_de    ,&Z80::jp_nc      ,&Z80::out_byte_a,
 &Z80::call_nc ,&Z80::push_de   ,&Z80::sub_byte   ,&Z80::rst_10    ,
 &Z80::ret_c   ,&Z80::exx       ,&Z80::jp_c       ,&Z80::in_a_byte ,
 &Z80::call_c  ,&Z80::dd        ,&Z80::sbc_a_byte ,&Z80::rst_18    ,
 &Z80::ret_po  ,&Z80::pop_hl    ,&Z80::jp_po      ,&Z80::ex_xsp_hl ,
 &Z80::call_po ,&Z80::push_hl   ,&Z80::and_byte   ,&Z80::rst_20    ,
 &Z80::ret_pe  ,&Z80::jp_hl     ,&Z80::jp_pe      ,&Z80::ex_de_hl  ,
 &Z80::call_pe ,&Z80::ed        ,&Z80::xor_byte   ,&Z80::rst_28    ,
 &Z80::ret_p   ,&Z80::pop_af    ,&Z80::jp_p       ,&Z80::di        ,
 &Z80::call_p  ,&Z80::push_af   ,&Z80::or_byte    ,&Z80::rst_30    ,
 &Z80::ret_m   ,&Z80::ld_sp_hl  ,&Z80::jp_m       ,&Z80::ei        ,
 &Z80::call_m  ,&Z80::fd        ,&Z80::cp_byte    ,&Z80::rst_38  
};

