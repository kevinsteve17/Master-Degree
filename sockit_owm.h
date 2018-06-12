#ifndef SOCKIT_OWM_H
#define SOCKIT_OWM_H
#include "systemc.h" 
  
  // enable implementation of optional functionality
  #define OVD_E		1 // overdrive functionality is implemented by default
  #define CDR_E		1 // clock divider register is implemented by default
  // interface parameters
  #define BDW		32 // bus data width
  #define OWN		1  // number of 1-wire ports
  // computed bus address port width
  #define BAW		(BDW==32) ? 1 : 2

  // base time period
  #define BTP_N		"5.0" // normal    mode (5.0us options are "7.5" "5.0" and "6.0")
  #define BTP_O		"1.0" // overdrive mode (1.0us options are "1.0"       and "0.5")
  // normal mode timing
  #define T_RSTH_N	(BTP_N == "7.5") ?  64 : (BTP_N == "5.0") ?  96 :  80  // reset high
  #define T_RSTL_N	(BTP_N == "7.5") ?  64 : (BTP_N == "5.0") ?  96 :  80  // reset low
  #define T_RSTP_N	(BTP_N == "7.5") ?  10 : (BTP_N == "5.0") ?  15 :  10  // reset presence pulse
  #define T_DAT0_N	(BTP_N == "7.5") ?   8 : (BTP_N == "5.0") ?  12 :  10  // bit 0 low
  #define T_DAT1_N	(BTP_N == "7.5") ?   1 : (BTP_N == "5.0") ?   1 :   1  // bit 1 low
  #define T_BITS_N	(BTP_N == "7.5") ?   2 : (BTP_N == "5.0") ?   3 :   2  // bit sample
  #define T_RCVR_N	(BTP_N == "7.5") ?   1 : (BTP_N == "5.0") ?   1 :   1  // recovery
  #define T_IDLE_N	(BTP_N == "7.5") ? 128 : (BTP_N == "5.0") ? 200 : 160  // idle timer
  // overdrive mode timing
  #define T_RSTH_O	(BTP_O == "1.0") ?  48 :  96  // reset high
  #define T_RSTL_O	(BTP_O == "1.0") ?  48 :  96  // reset low
  #define T_RSTP_O	(BTP_O == "1.0") ?  10 :  15  // reset presence pulse
  #define T_DAT0_O	(BTP_O == "1.0") ?   6 :  12  // bit 0 low
  #define T_DAT1_O	(BTP_O == "1.0") ?   1 :   2  // bit 1 low
  #define T_BITS_O	(BTP_O == "1.0") ?   2 :   3  // bit sample
  #define T_RCVR_O	(BTP_O == "1.0") ?   2 :   4  // recovery
  #define T_IDLE_O	(BTP_O == "1.0") ?  96 : 192  // idle timer
  // clock divider ratios (defaults are for a 2MHz clock)
  #define CDR_N		5-1  // normal    mode
  #define CDR_O		1-1  // overdrive mode


SC_MODULE (sockit_owm) 
{
	// system signals
	sc_in_clk        	clk;
	sc_in<bool>		rst;
	// CPU bus interface
	sc_in<bool>           	bus_ren;  // read  enable
	sc_in<bool>           	bus_wen;  // write enable
	sc_in<sc_uint<BAW> > 	bus_adr;  // address
	sc_in<sc_uint<BDW> >  	bus_wdt;  // write data
	sc_out<sc_uint<BDW> >	bus_rdt;  // read  data
	sc_in<bool>            	bus_irq;  // interrupt request
	// 1-wire interface
	sc_out<sc_uint<OWN> >	owr_p;    // output power enable
	sc_out<sc_uint<OWN> > 	owr_e;    // output pull down enable
	sc_in<sc_uint<OWN> > 	owr_i;     // input from bidirectional wire
	
  /*
    //local signals
  // address dependent write enable
wire bus_ren_ctl_sts;
wire bus_wen_ctl_sts;
wire bus_wen_pwr_sel;
wire bus_wen_cdr_n;
wire bus_wen_cdr_o;

// read data bus segments
wire     [7:0] bus_rdt_ctl_sts;
wire [PDW-1:0] bus_rdt_pwr_sel;

// clock divider
reg  [CDW-1:0] div;
reg  [CDW-1:0] cdr_n;
reg  [CDW-1:0] cdr_o;
wire           pls;

// cycle control and status
reg            owr_cyc;  // cycle status
reg  [TDW-1:0] cnt;      // cycle counter

// port select
//generate if (OWN>1) begin : sel_declaration
reg  [SDW-1:0] owr_sel;
//end endgenerate

// modified input data for overdrive
wire           req_ovd;

// onewire signals
reg  [OWN-1:0] owr_pwr;  // power
reg            owr_ovd;  // overdrive
reg            owr_rst;  // reset
reg            owr_dat;  // data bit
reg            owr_smp;  // sample bit

reg            owr_oen;  // output enable
wire           owr_iln;  // input line

// interrupt signals
reg            irq_ena;  // interrupt enable
reg            irq_sts;  // interrupt status

// timing signals
wire [TDW-1:0] t_idl ;   // idle                 cycle    time
wire [TDW-1:0] t_rst ;   // reset                cycle    time
wire [TDW-1:0] t_bit ;   // data bit             cycle    time
wire [TDW-1:0] t_rstp;   // reset presence pulse sampling time
wire [TDW-1:0] t_rsth;   // reset                release  time
wire [TDW-1:0] t_dat0;   // data bit 0           release  time
wire [TDW-1:0] t_dat1;   // data bit 1           release  time
wire [TDW-1:0] t_bits;   // data bit             sampling time
wire [TDW-1:0] t_zero;   // end of               cycle    time
*/

	SC_HAS_PROCESS(sockit_owm);

  sockit_owm(sc_module_name name_) :
	sc_module(name_)
	{
		SC_THREAD(isr);
		sensitive << clk.pos();
		sensitive << rst.pos();
	}
  
	void isr();
  void cycle_timing();
  void bus_read();
  void bus_write();
  void clock_divider();
  void clock_divider_sync();
  void clock_divider_pulse();
  void sel_power_register();
  void sel_power_register_sync();
  void bus_interrupt();
  void one_wire_fsm();
  void input_output();

};
#endif
