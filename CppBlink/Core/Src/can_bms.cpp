/*
 * can_bms.cpp
 *
 *  Created on: Aug 4, 2025
 *      Author: malya
 */

#include "can_bms.h"


// can
can_msg test_msg(100, 8,  CAN_ID_STD, 0x321 , CAN_RTR_DATA);

// can J1939
can_msg_HVESSC1_PGN_6912 k_msg;
