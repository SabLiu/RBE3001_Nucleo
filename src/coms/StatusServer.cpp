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
   * ======= PART 1: Decode input packet (which may be empty) ==
   */
	if (packet[0] == 1){
		// run CALIBRATION COMMAND
		// Send the encoder values from STATUS to Nucleo
		// update global variable with offsets
//		homePosition[0] = myPidObjects[0]->GetPIDPosition();

	}
	else{
	// ELSE IF PACKET IS ALL 0S, SEND STATUS
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
	  // for lab 1 we first hardcode these 2 values
       position = myPidObjects[i]->GetPIDPosition();
       velocity = myPidObjects[i]->getVelocity();
       torque   = myPidObjects[i]->loadCell->read();

      packet[(i*3)+0] = position;
      packet[(i*3)+1] = velocity;
      packet[(i*3)+2] = torque;
    }
}
}
