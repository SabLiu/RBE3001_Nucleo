/**
 * @file GripperServer.h
 * @brief StatusServer for the RBE3001 robotic arm
 *
 * @section RBE3001 - Nucleo Firmware - GripperServer
 *
 */
// this is for controlling the gripper

#ifndef RBE3001_GRIPPER_SERVER
#define RBE3001_GRIPPER_SERVER


#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>              // needed for std::abs
#include "Servo.h"
#define GRIPPER_SERVER_ID 55      // identifier for this server

#define CLOSED 0.2
#define OPEN 1
/**
 *  @brief Class that receives setpoints through HID and sends them to
 *         the PID controller. Extends the `PacketEventAbstract' class.
 */
class GripperServer: public PacketEventAbstract
{
 private:
  Servo* myGripper;

 public:
  GripperServer (Servo* gripper)
    : PacketEventAbstract(GRIPPER_SERVER_ID)
  {
    myGripper = gripper;
  }

  // This method is called every time a packet from MATLAB is received
  // via HID
  void event(float * buffer);
};

#endif /* end of include guard: RBE3001_PID_SERVER */
