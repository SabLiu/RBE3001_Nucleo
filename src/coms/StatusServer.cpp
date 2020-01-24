/**
 * RBE3001 - Nucleo Firmware
 * See header file for more detail on this class.
 */
#include "StatusServer.h"

/**
 *  @brief This function handles incoming HID packets from MATLAB.
 *
 *  @description This method has two parts: in part 1, we will decode the incoming
 *               packet, extract the setpoints and send those values to the
 *               PID controller; in part 2, we will generate a response that will be
 *               sent back to MATLAB through HID. This is useful to e.g. send sensor
 *               data to MATLAB for plotting.
 */
void StatusServer::event(float * packet){
/*
 * If input packet is all 0s, then run status command
 * If first element in packet is 1, then run calibration command
 */
//	if (packet[0] == 1){	// run CALIBRATION COMMAND
//		// reset our home position to the new position
//		for (int i = 0; i < myPumberOfPidChannels; i++){
//			myPidObjects[i]->pidReset(myPidObjects[i]->GetPIDPosition());
//		}
//	}
//	else{
		uint8_t * buff = (uint8_t *) packet;

  // re-initialize the packet to all zeros
  for (int i = 0; i < 60; i++)
      buff[i] = 0;

  /**
   * The following loop reads sensor data (encoders ticks, joint velocities and
   * force readings) and writes it in the response packet.
   */
  for(int i = 0; i < myPumberOfPidChannels; i++)
    {
       position = myPidObjects[i]->GetPIDPosition();
       velocity = myPidObjects[i]->getVelocity();
       torque   = myPidObjects[i]->loadCell->read();

      packet[(i*3)+0] = position;
      packet[(i*3)+1] = velocity;
      packet[(i*3)+2] = torque;
    }
//}
}
