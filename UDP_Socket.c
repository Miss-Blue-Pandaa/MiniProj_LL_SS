/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network:Service
 * Copyright (c) 2004-2019 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    UDP_Socket.c
 * Purpose: UDP Socket Code Template
 * Rev.:    V7.0.0
 *----------------------------------------------------------------------------*/
//! [code_UDP_Socket]
#include "rl_net.h"
#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include <stdio.h>

//include ANGLE and DIST ou extern


int32_t udp_sock;                       // UDP socket handle
 
// Notify the user application about UDP socket events.
uint32_t udp_cb_func (int32_t socket, const  NET_ADDR *addr, const uint8_t *buf, uint32_t len) 
  uint8_t *sendbuf;
  sendbuf = netUDP_GetBuffer (50);
  // Data received
  /* Example
  if ((buf[0] == ANGLE) && (len == 2)) {
    if ((ANGLE < 180)&&(ANGLE > 0)) {
      sendbuf = 'OK';
    } 
    else {
      sendbuff = 'ERR<motif>';  
    }
  }
   /* Example
  if ((buf[1] == DIST) && (len == 2)) {
    if ((DIST < 100)&&(DIST > 0)) {  
    sendbuf = 'DIST<cm>';
  } 
    else {
      sendbuf = 'DIST TIMEOUT';  
    }
  }
  
  */
  netUDP_Send (udp_sock, &addr, sendbuf, 50);
  return (0);
}
 
// Send UDP data to destination client.
void send_udp_data (void) {
 

    
  }
}
 
// Allocate and initialize the socket.
void Init_Ethernet (void) {
 
  netInitialize (); 
  // Initialize UDP socket and open port 5000
  udp_sock = netUDP_GetSocket (udp_cb_func);
  if (udp_sock > 0) {
    netUDP_Open (udp_sock, 5000);
  }
}

//! [code_UDP_Socket]
