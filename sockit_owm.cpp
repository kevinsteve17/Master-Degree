//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Minimalistic 1-wire (onewire) master with Avalon MM bus interface       //
//                                                                          //
//  Copyright (C) 2010  Iztok Jeras                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  This RTL is free hardware: you can redistribute it and/or modify        //
//  it under the terms of the GNU Lesser General Public License             //
//  as published by the Free Software Foundation, either                    //
//  version 3 of the License, or (at your option) any later version.        //
//                                                                          //
//  This RTL is distributed in the hope that it will be useful,             //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//  GNU General Public License for more details.                            //
//                                                                          //
//  You should have received a copy of the GNU General Public License       //
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The clock divider parameter is computed with the next formula:           //
//                                                                          //
// CDR_N = f_CLK * BTP_N - 1  (example: CDR_N = 1MHz * 5.0us - 1 = 5-1)     //
// CDR_O = f_CLK * BTP_O - 1  (example: CDR_O = 1MHz * 1.0us - 1 = 1-1)     //
//                                                                          //
// If the dividing factor is not a round integer, than the timing of the    //
// controller will be slightly off, and would support only a subset of      //
// 1-wire devices with timing closer to the typical 30us slot.              //
//                                                                          //
// Base time periods BTP_N = "5.0" and BTP_O = "1.0" are optimized for      //
// onewire timing. The default timing restricts the range of available      //
// frequences to multiples of 1MHz.                                         //
//                                                                          //
// If even this restrictions are too strict use timing BTP_N = "6.0" and    //
// BTP_O = "0.5", where the actual periods can be in the range:             //
// 6.0us <= BTP_N <= 7.5us                                                  //
// 0.5us <= BTP_O <= 0.66us                                                 //
//                                                                          //
// A third timing option is available for normal mode BTP_N = "7.5", this   //
// option is optimized for logic size.                                      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include "sockit_owm.h"

void sockit_owm::isr()
{
  while(true) {
    wait(); // synchronous to rising edge
  }
}

