#pragma once

#include <sys/types.h>
#include <libgte.h>

// Structure for storing processed controller data
typedef struct
{
    int             xpos, ypos;     // Stored position for sprite(s)
    int             xpos2, ypos2;   // controlled by this controller.
    unsigned char   status;         // These 8 values are obtained
    unsigned char   type;           // directly from the controller
    unsigned char   button1;        // buffer we installed with InitPAD.
    unsigned char   button2;
    unsigned char   analog0;
    unsigned char   analog1;
    unsigned char   analog2;
    unsigned char   analog3;
} Controller_Data;
// All-purpose controller data buffer
typedef struct
{
    unsigned char pad[34];          // 8-bytes w/o Multi-Tap, 34-bytes w/Multi-Tap
} Controller_Buffer;

// Pad stuff
extern Controller_Buffer controllers[2];   // Buffers for reading controllers
extern Controller_Data theControllers[8];  // Processed controller data

void get_digital_direction( Controller_Data *c, int buttondata );

void read_controller( Controller_Data *c, unsigned char *buf, int port );

