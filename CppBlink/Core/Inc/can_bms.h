#ifndef INC_CAN_BMS_H_
#define INC_CAN_BMS_H_



#pragma once
#include "main.h"


constexpr uint16_t ID = 0x321;
const uint32_t CYCLE_TIME= 20;
constexpr uint32_t HVESSC1_PGN_6912_SHM_Rx_ID = 0x040EF321;
constexpr uint32_t HVESSC1_PGN_6912_Rx_ID = 0x041BF321;

constexpr uint8_t PGN_6912_SDM_SA = 0x21;
constexpr uint8_t PGN_6912_SDM_PS = 0xF3;
constexpr uint8_t PGN_6912_SDM_PF = 0x1B;


class can_msg_j1939
{
public:

	can_msg_j1939(uint32_t TransmitRate, uint32_t DLC, uint32_t IDtype, uint32_t ID, uint32_t DataFrame)
    {
        TxHeader.DLC = DLC;
        TxHeader.IDE = IDtype;
        TxHeader.ExtId = ID;
        TxHeader.RTR = DataFrame;
        this->TransmitRate = TransmitRate;
    }

    const CAN_TxHeaderTypeDef* getTxHeader() const { return &TxHeader;}
    const  uint8_t* getTxData() const { return TxData;}          // Zum Schreiben/Lesen
    uint32_t getTransmitRate() const { return TransmitRate;}
    uint32_t* getTxMailbox() { return &TxMailbox;}

    virtual void fillTxData() {};

protected:

    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TransmitRate;
    uint8_t TxData[8];
    uint32_t TxMailbox;
};

// HVESSC1_PGN_6912     20 mS
class HVESSC1_PGN_6912_Rx : public can_msg_j1939
{
public:

	HVESSC1_PGN_6912_Rx():can_msg_j1939(20, 8,  CAN_ID_STD, HVESSC1_PGN_6912_Rx_ID , CAN_RTR_DATA){};

	 void fillTxData() override
	 {
	    TxData[0] = (HS_HiUBusCnctCmd_Rx1) | (HS_PwrDwnCmd_Rx1 << 2) | (HS_HiUBusAcvIslnTestCmd_Rx1 << 4) | (HS_HiUBusPasIslnTestCmd_Rx1 << 6);
	    TxData[1] = (HS_CellBalnCmd_Rx1) | (HS_EnaIntChrgrCmd_Rx1 << 2) | (HS_OperConsent_Rx1 << 4) | (HS_HiUBusHiSideRestrCnctReq_Rx1 << 6);
	    TxData[2]  = HS_HiUBusLoSideRestrCnctReq_Rx1;
	    TxData[3] = 0;
	    TxData[4]  = 0;
	    TxData[5]  = 0;
	    TxData[6] = 0; // HS_Ctl1Ctr_Rx1;
	    TxData[7] = 10; // HS_Ctl1CRC_Rx1;
	         }

    void SetHS_HiUBusCnctCmd_Rx1(uint8_t val)	 		{HS_HiUBusCnctCmd_Rx1 = val; }
    void SetHS_PwrDwnCmd_Rx1(uint8_t val) 				{HS_PwrDwnCmd_Rx1 = val; }
    void SetHS_HiUBusAcvIslnTestCmd_Rx1(uint8_t val) 	{HS_HiUBusAcvIslnTestCmd_Rx1 = val; }
    void SetHS_HiUBusPasIslnTestCmd_Rx1(uint8_t val) 	{HS_HiUBusPasIslnTestCmd_Rx1 = val; }
    void SetHS_CellBalnCmd_Rx1(uint8_t val) 			{HS_CellBalnCmd_Rx1 = val; }
    void SetHS_EnaIntChrgrCmd_Rx1(uint8_t val)	 		{HS_EnaIntChrgrCmd_Rx1 = val; }
    void SetHS_OperConsent_Rx1(uint8_t val) 			{HS_OperConsent_Rx1 = val; }
    void SetHS_HiUBusHiSideRestrCnctReq_Rx1(uint8_t val) {HS_HiUBusLoSideRestrCnctReq_Rx1 = val; }

protected:

    // Variablen
    uint8_t HS_HiUBusCnctCmd_Rx1;			     	// Command to connect the High Voltage Energy Storage System (or Pack 1 in systems with only one pack) to the high-voltage bus.  The emergency contactor closure request may be used in situations where one or more faults in the hybrid powertrain prevent norm
    uint8_t HS_PwrDwnCmd_Rx1;						// Command to shut down the High Voltage Energy Storage System (or Pack 1 in systems with only one pack).  A normal power-down may involve steps that take some period of time (tests, writing of data, etc.).  However, an emergency power-down should shut down
    uint8_t HS_HiUBusAcvIslnTestCmd_Rx1;     		// Command for the High Voltage Energy Storage System (or Pack 1 in systems with only one pack) to perform an active electrical isolation test on the high voltage bus.An active isolation test might use a generated signal (e.g. an injected AC signal) and
    uint8_t HS_HiUBusPasIslnTestCmd_Rx1;	 		// Command for the High Voltage Energy Storage System (or Pack 1 in systems with only one pack) to perform a passive electrical isolation test on the high voltage bus.A passive isolation test uses additional circuitry (e.g. a high impedance network) to
    uint8_t HS_CellBalnCmd_Rx1; 				 	// Command for the High Voltage Energy Storage System (or Pack 1 in systems with only one pack) to perform cell balancing.This parameter provides HVES system level information. If there are multiple packs in the system, then both individual pack message
    uint8_t HS_EnaIntChrgrCmd_Rx1;			 	    // When the HVES has an internal charger this parameter will enable it.   External chargers may use the External Energy Source Connection Demand (SPN 7890) and related SPs.This parameter provides HVES system level information. If there are multiple pack
    uint8_t HS_OperConsent_Rx1;				 	    // This parameter provides an indication to the High Voltage Energy Storage System (or Pack 1 in systems with only one pack) that an external device is ready for this HVES instance to proceed with normal operation.  In applications which support this parame
    uint8_t HS_HiUBusHiSideRestrCnctReq_Rx1;        // // This parameter is used to request connection of this HVES instance High-Voltage bus high side resistor in order to perform an isolation test.  See also SPN 8434  (HVESS High-Voltage Bus Low Side Resistor Connect Request).This parameter provides HVES
    uint8_t HS_HiUBusLoSideRestrCnctReq_Rx1;


};


// HVESSC1_PGN_6912  SHM
class HVESSC1_PGN_6912_SHM_Rx : public can_msg_j1939
{
public:

	HVESSC1_PGN_6912_SHM_Rx():can_msg_j1939(20, 8,  CAN_ID_STD, HVESSC1_PGN_6912_Rx_ID , CAN_RTR_DATA){};

	 void fillTxData() override
	 {
	    TxData[0] = SHM_Counter_1;
	    TxData[1] =  (~PGN_6912_SDM_SA & 0xFF);
	    TxData[2]  = (~PGN_6912_SDM_PS & 0xFF);
	    TxData[3] = (~PGN_6912_SDM_PF & 0xFF);
	    TxData[4]  = (uint8_t)crc32_sum;
	    TxData[5]  = (uint8_t)(crc32_sum >> 8);
	    TxData[6] = (uint8_t)(crc32_sum >> 16);
	    TxData[7] = (uint8_t)(crc32_sum >> 24);
	         }

   //setters


private:

    // Variablen
	 uint8_t SHM_Counter_1;
	 uint32_t crc32_sum;


};

// Transmit************************************************************
class can_msg_transmit {
public:
	void trm_can_msg_j1939(can_msg_j1939 *msg, uint32_t cyclusTime)
	{

		static uint32_t trm_cnt;
		trm_cnt += CYCLE_TIME;

			if (trm_cnt == msg->getTransmitRate())
			{
				//msg->fillTxData();
				if (HAL_CAN_AddTxMessage(&hcan2, msg->getTxHeader(), msg->getTxData(), msg->getTxMailbox()) != HAL_OK)
					 {
							            // Falls alle 3 Mailboxen voll sind oder Fehler
			          }
				trm_cnt = 0;
			}

	}

};
extern can_msg_j1939 test_msg;
extern HVESSC1_PGN_6912_Rx trm_HVESSC1_PGN_6912;
extern HVESSC1_PGN_6912_SHM_Rx trm_HVESSC1_PGN_6912_SHM;
extern can_msg_transmit trm_can2;

#endif /* INC_CAN_BMS_H_ */
