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

//extern ANGLE // fonction boucle de test servo avec affichage de ANGLE et DIST
//extern DIST
 
int32_t udp_sock;                       // UDP socket handle
 
// Notify the user application about UDP socket events.
uint32_t udp_cb_func (int32_t socket, const  NET_ADDR *addr, const uint8_t *buf, uint32_t len) {
	
  // Data received
  // Example
	// Analyse de ANGLE et DIST
  if ((buf[0] == 0x01) && (len == 2)) {

  }
 
  return (0);
}
 
// Send UDP data to destination client.
void send_udp_data (void) {
 
  if (udp_sock > 0) {

    // IPv4 address: 192.168.0.3
    NET_ADDR addr = { NET_ADDR_IP4, 5000, 192, 168, 0, 3 };
    uint8_t *sendbuf;
 
    sendbuf = netUDP_GetBuffer (2);
    sendbuf[0] = 0x10;  // Récupérer les valeurs d'un autre fichier 
    sendbuf[1] = 0x01;   //Récupérer les valeurs d'un autre fichier
 
    netUDP_Send (udp_sock, &addr, sendbuf, 2);
    
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
