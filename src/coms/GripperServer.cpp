/**
 * RBE3001 - Nucleo Firmware
 * See header file for more detail on this class.
 */
#include "GripperServer.h"

/**
 *  @brief This function handles incoming HID packets from MATLAB.
 *
 *  @description This method has two parts: in part 1, we will decode the incoming
 *               packet, extract the setpoints and send those values to the
 *               PID controller; in part 2, we will generate a response that will be
 *               sent back to MATLAB through HID. This is useful to e.g. send sensor
 *               data to MATLAB for plotting.
 */
void GripperServer::event(float * packet){
	// close the gripper
	if (packet[0]== 0){
		myGripper->write(CLOSED);

	}
	// open the gripper
	else {
		myGripper->write(OPEN);

	}
}
