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
#include <string.h>

extern float distance_cm();
extern void servo_set_angle (int);

int32_t udp_sock;                       // UDP socket handle


// Notify the user application about UDP socket events.
uint32_t udp_cb_func (int32_t socket, const NET_ADDR *addr, const uint8_t *buf, uint32_t len) {
  char cmd[len + 1]; // +1 pour le caractère de fin de chaîne
  uint8_t *sendbuf;
  uint32_t i, message;
  int angle,alpha;
  float d = distance_cm ();           // -1 si timeout

  // Copie du datagramme et présence de fin de chaine (\n ou \r)
  for (i = 0; i < len; i++) {
    if (buf[i] == '\n' || buf[i] == '\r') break;
    cmd[i] = (char)buf[i];  
  }
  cmd[i] = '\0';


  // Allocation du buffer d'envoi UDP
  sendbuf = netUDP_GetBuffer (64);
  if (sendbuf == NULL) return (0); // Si pas de buffer dispo, on ne répond pas


  // Traitement des commandes
  // Commande "ANGLE <valeur>"
  if (sscanf(cmd, "ANGLE %d", &angle) == 1) {
    if ((angle >= 0) && (angle <= 180)) {
			angle = alpha;
			servo_set_angle (angle);
      message = (uint32_t)sprintf((char *)sendbuf, "OK\n");
    }
    else {
      message = (uint32_t)sprintf((char *)sendbuf, "ERR VALEUR ANGLE NON VALABLE\n");
    }
  }
  // Commande "DIST"
  else if (strncmp(cmd, "DIST",4) == 0) {
    if (d < 0) {
      message = (uint32_t)sprintf((char *)sendbuf, "ERR DIST TIMEOUT \n"); 
    }
    else {
      message = (uint32_t)sprintf((char *)sendbuf, "%.1f\n", d); // Format avec 1 décimale
    }
  }
	 // Commande "SCAN"
  else if (strncmp(cmd, "SCAN", 4) == 0) {
    if ((alpha >= 0) && (alpha <= 180)) {
      message = (uint32_t)sprintf((char *)sendbuf, "%3d %.1f  END\n", alpha, d); // Message FINALE quand tout bon
    }
  }

  else {
    message = (uint32_t)sprintf((char *)sendbuf, "ERR\n");
  }

  // Réponse à l'expéditeur
  netUDP_Send (socket, addr, sendbuf, message); //(socket dans parametre fonction,longueur=message);
 
  return (0);
}
 
// Send UDP data to destination client.
void send_udp_data (void) {
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


