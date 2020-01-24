/**
 * @file StatusServer.h
 * @brief StatusServer for the RBE3001 robotic arm
 *
 * @section RBE3001 - Nucleo Firmware - StatusServer
 *
 * Instructions
 * ------------
 * This class implements a communication server that can be
 * used to send given setpoints (in joint space) to the robotic arm.
 * Setpoints generated in MATLAB and sent over HDI will be made available
 * to the `event()' function below. See the code in `StatusServer.cpp' for
 * for more details.
 *
 * IMPORTANT - Multiple communication servers can run in parallel, as shown
 *             in the main file of this firmware
 *             (see 'Part 2b' in /src/Main.cpp). To ensure that communication
 *             packets generated in MATLAB are routed to the appropriate
 *             server, we use unique identifiers. The identifier for this
 *             server is the integer number 37.
 *             In general, the identifier can be any 4-byte unsigned
 *             integer number.
 */

#ifndef RBE3001_STATUS_SERVER
#define RBE3001_STATUS_SERVER


#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>              // needed for std::abs

//#define PID_SERVER_ID 01      // identifier for this server
#define STATUS_SERVER_ID 02      // identifier for this server

/**
 *  @brief Class that receives setpoints through HID and sends them to
 *         the PID controller. Extends the `PacketEventAbstract' class.
 */
class StatusServer: public PacketEventAbstract
{
 private:
  PIDimp ** myPidObjects;    // array of PidServers - one for each joint
  int myPumberOfPidChannels;
  float position;
  float velocity;
  float torque;
 public:
  StatusServer (PIDimp ** pidObjects, int numberOfPidChannels)
    : PacketEventAbstract(STATUS_SERVER_ID)
  {
    myPidObjects = pidObjects;
    myPumberOfPidChannels = numberOfPidChannels;
  }

  // This method is called every time a packet from MATLAB is received
  // via HID
  void event(float * buffer);
};

#endif /* end of include guard: RBE3001_PID_SERVER */
