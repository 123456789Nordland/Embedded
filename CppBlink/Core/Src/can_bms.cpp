/*
 * can_bms.cpp
 *
 *  Created on: Aug 4, 2025
 *      Author: malya
 */

#include "can_bms.h"


// can
can_msg_j1939 test_msg(100, 8,  CAN_ID_STD, 0x321 , CAN_RTR_DATA);

// can J1939
HVESSC1_PGN_6912_Rx trm_HVESSC1_PGN_6912;
HVESSC1_PGN_6912_SHM_Rx trm_HVESSC1_PGN_6912_SHM;

// transmit!
can_msg_transmit trm_can2;
