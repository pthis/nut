/* solis.h -  Microsol Solis UPS hardware

   Copyright (C) 2004  Silvino B. Magalhaes    <sbm2yk@gmail.com>
                 2019  Roberto Panerai Velloso <rvelloso@gmail.com>


   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

   2004/10/10 - Version 0.10 - Initial release
   2004/10/20 - Version 0.20 - add Battery information in driver
   2004/10/26 - Version 0.30 - add commands and test shutdown
   2004/10/30 - Version 0.40 - add model data structs
   2004/11/22 - Version 0.50 - add internal e external shutdown programming
   2005/06/16 - Version 0.60 - save external shutdown programming to ups,
                               support new cables and Solaris compilation
   2015/09/19 - Version 0.63 - patch for correct reading for Microsol Back-Ups BZ1200-BR

*/

#ifndef INCLUDED_SOLIS_H
#define INCLUDED_SOLIS_H

typedef int bool_t;

/* autonomy constants */

const static int bext[5] = {14,18,28,18,1};
const static int nompow[5] = { 1000,1500,2000,3000,1200 };
const static int inds[6] = { 0,0,1,2,3,4 };
const static double InVolt_offset = 30.;
#define PACKET_SIZE 25
const static int packet_size = PACKET_SIZE;

const static struct {
         int maxi;              /* power internals */
         int minc[21];          /* power minimal index */
         int maxc[21];          /* power maximus index */
         int mm[21][39];        /* autonomy time [minutes] */
} auton[5] =
{{ 7,
   { 139,139,142,141,141,141,141,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } ,
   { 176,174,172,172,170,170,170,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } ,
   {
     { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,7,8,10,11,12,15,17,19,22,25,28,31,35,40,43,47,52,59,64,68,75,75 },
     { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,5,5,6,7,8,9,10,11,12,13,15,18,20,21,24,28,30,32,33,33,34,34,34,34 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,2,3,3,4,4,5,5,6,7,8,9,10,11,12,13,15,17,19,21,22,23,23,23,23,23,23 },
     { 1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,4,5,6,7,7,8,9,19,11,12,13,14,16,18,20,20,20,20,20,20 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,5,5,6,6,6,7,7,8,8,10,11,12,13,14,14,14,14,14,14,14,14 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,3,4,4,5,6,6,6,7,7,8,9,10,11,12,12,12,12,12,12,12,12,12,12 },
     { 1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,4,4,5,5,6,6,6,7,7,8,9,10,10,10,10,10,10,10,10,10,10,10,10,10 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   },},
 { 10,
   { 141,141,141,141,141,141,141,141,141,141,0,0,0,0,0,0,0,0,0,0,0 } ,
   { 177,177,177,172,173,172,172,172,172,172,0,0,0,0,0,0,0,0,0,0,0 } ,
   {
     { 1,1,1,1,1,1,1,1,1,2,2,3,3,5,6,7,9,10,12,15,16,18,22,25,27,30,36,42,45,48,55,60,64,70,78, 84,90,97,104 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,3,2,3,4,5,6,7,8,10,12,13,14,16,19,22,25,28,30,35,38,42,46,52,55, 58,60,62 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,4,5,7,9,10,12,13,16,20,21,23,26,28,30,34,35,37,38,39,40 ,40,40 },
     { 1,1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,4,5,6,7,8,9,10,11,13,14,16,18,21,22,24,27,27,27,27,27,27 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,2,3,3,4,4,4,4,4,5,6,7,8,9,10,11,12,14,15,16,19,20,22,23,23,23,23,23 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,3,4,4,4,4,5,6,7,8,9,10,11,12,13,14,16,17,18,18,18,18,18,18 },
     { 1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,3,4,4,4,4,4,5,7,7,7,8,9,10,11,12,14,14,14,14,14,14,14 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,4,4,5,6,7,7,8,8,9,10,11,12,13,13,13,13,13,13,13,13 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,4,4,4,4,4,5,6,7,7,8,9,10,10,11,11,12,12,12,12,12,12 },
     { 1,1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,4,5,6,6,7,7,8,8,8,9,9,10,10,10,10,10,10,10,10 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   },},
 { 13,
   { 141,141,141,141,141,141,141,141,141,141,141,141,141,0,0,0,0,0,0,0,0 } ,
   { 177,177,177,172,173,172,172,172,172,172,172,172,172,0,0,0,0,0,0,0,0 } ,
   {
     { 1,1,1,1,1,1,2,2,2,3,4,5,5,8,10,11,13,15,18,22,24,28,34,40,43,48,56,65,70,76,85,93,100,110,122,132,141,152,162 },
     { 1,1,1,1,1,1,1,2,2,2,3,3,3,4,5,6,8,9,10,12,15,18,20,22,25,30,35,40,44,48,54,60,65,73,80,85,92,94,95 },
     { 1,1,1,1,1,1,1,2,2,3,3,3,4,4,4,5,5,6,8,10,14,16,18,20,24,30,32,36,40,44,48,52,54,58,59,60 ,62,62,62 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,5,6,8,9,10,12,13,15,17,20,22,24,28,32,35,38,42,42,42,42,42,42 },
     { 1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,7,8,10,11,12,14,15,17,18,21,24,26,29,32,34,36,36,36,36,36 },
     { 1,1,1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,7,8,9,10,12,13,15,16,18,20,22,24,26,28,28,28,28,28,28 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,4,5,5,6,6,7,8,9,10,11,13,14,15,17,19,21,22,22,22,22,22,22 },
     { 1,1,1,1,1,1,1,2,2,2,3,3,3,3,4,4,5,5,6,6,7,8,8,9,10,11,12,14,15,17,18,19,20,20,20,20,20,20,20 },
     { 1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,4,4,5,6,6,7,7,8,9,10,11,12,13,15,15,16,16,16,16,16,16,16,16 },
     { 1,1,1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,6,7,8,9,9,10,11,12,12,12,13,13,14,14,14,14,14,14,14,14 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,4,4,5,5,6,7,7,8,9,10,10,10,11,11,12,12,12,12,12,12,12,12 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,4,4,5,5,6,6,7,7,8,8,8,9,9,10,10,10,10,10,10,10,10 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,4,4,4,5,5,6,6,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   },},
 { 21,
   { 141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141 } ,
   { 177,175,173,171,169,169,168,168,167,167,166,165,164,162,160,160,160,160,159,158,157 } ,
   {
     { 1,1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,14,16,19,22,24,27,30,33,37,42,44,50,55,60,65,70,75 ,80,88,93,95,100 },
     { 1,1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,18,20,22,25,27,31,35,38,42,46,50,55,61,66,71 ,76,83,89,89,89 },
     { 1,1,1,1,2,2,3,3,4,5,6,7,8,8,9,10,11,12,13,15,18,19,22,24,26,30,33,38,40,45,50,55,60,66,70,70,70,70,70 },
     { 1,1,1,1,1,1,2,2,3,4,5,6,7,7,8,9,10,10,11,13,16,17,19,21,23,25,28,34,36,39,45,50,55,55,55,55,55,55,55 },
     { 1,1,1,1,1,1,2,2,3,4,4,5,6,6,7,8,8,9,10,12,14,15,17,18,20,21,25,28,30,34,39,39,39,39,39,39,39,39,39 },
     { 1,1,1,1,1,1,2,2,3,4,4,4,5,5,6,7,8,8,9,10,12,13,15,16,18,19,22,25,26,28,30,30,30,30,30,30,30,30,30 },
     { 1,1,1,1,1,1,2,2,2,3,3,3,4,4,5,6,7,7,8,9,11,12,13,14,17,17,20,22,24,26,26,26,26,26,26,26,26,26,26 },
     { 1,1,1,1,1,1,2,2,2,3,3,3,4,4,5,5,6,7,7,8,10,11,12,13,15,16,18,20,22,23,23,23,23,23,23,23,23,23,23 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,6,7,7,9,10,11,13,14,15,16,18,19,19,19,19,19,19,19,19,19,19,19 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,2,3,4,4,5,6,7,7,8,10,11,13,14,15,15,16,17,17,17,17,17,17,17,17,17,17,17 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,2,3,4,4,5,6,7,7,8,9,10,11,13,14,13,14,14,14,14,14,14,14,14,14,14,14,14 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,5,6,6,7,8,9,10,12,13,12,13,13,13,13,13,13,13,13,13,13,13,13 },
     { 1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,5,6,6,7,8,8,9,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,5,6,6,7,7,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,5,6,6,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,5,6,6,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,5,6,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 },
     { 1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,5,6,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
     { 1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 },
   },},
 { 21,
   { 141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141 } ,
   { 177,175,173,171,169,169,168,168,167,167,166,165,164,162,160,160,160,160,159,158,157 } ,
   {
     { 1,1,1,2,5,5,8,11,14,16,19,22,36,40,44,48,52,56,64,76,88,96,145,162,
       178,199,226,237,270,297,324,351,378,405,432,475,502,513,540 },
     { 1,1,1,2,3,5,8,11,14,16,19,22,36,40,44,48,52,56,60,72,80,88,135,145,
       167,189,205,226,248,270,297,329,356,383,410,448,480,480,480 },
     { 1,1,1,2,3,5,6,8,11,14,16,19,32,32,36,40,44,48,52,60,72,76,118,129,
       140,162,178,205,216,243,270,297,324,356,378,378,378,378,378 },
     { 1,1,1,2,3,4,5,6,8,11,14,16,28,28,32,36,40,40,44,52,64,68,102,
       113,124,135,151,183,194,210,243,270,297,297,297,297,297,297,297 },
     { 1,1,1,2,3,4,5,6,8,11,11,14,24,24,28,32,32,36,40,48,56,60,91,
       97,108,113,135,151,162,183,210,210,210,210,210,210,210,210,210 },
     { 1,1,1,2,3,4,5,6,8,11,11,11,20,20,24,28,32,32,36,40,48,52,81,
       86,97,102,118,135,140,151,162,162,162,162,162,162,162,162,162 },
     { 1,1,1,2,3,4,5,6,7,8,8,8,16,16,20,24,28,28,32,36,44,48,70,75,
       91,91,108,118,129,140,140,140,140,140,140,140,140,140,140 },
     { 1,1,1,2,2,3,4,5,5,8,8,8,16,16,20,20,24,28,28,32,40,44,64,70,
       81,86,97,108,118,124,124,124,124,124,124,124,124,124,124 },
     { 1,1,1,2,2,3,3,4,4,5,5,6,12,12,16,16,20,24,28,28,36,40,59,
       70,75,81,86,97,102,102,102,102,102,102,102,102,102,102,102 },
     { 1,1,1,2,2,3,3,4,4,5,5,8,10,12,16,16,20,24,28,28,32,40,
       59,70,75,81,81,86,91,91,91,91,91,91,91,91,91,91,91 },
     { 1,1,1,2,2,3,3,4,4,5,6,8,10,12,16,16,20,24,28,28,32,36,54,
       59,70,75,70,75,75,75,75,75,75,75,75,75,75,75,75 },
     { 1,1,2,2,2,2,2,2,2,5,6,8,10,12,16,18,20,22,24,26,28,36,48,
       54,60,65,70,70,70,70,70,70,70,70,70,70,70,70,70 },
     { 1,1,1,2,2,3,3,4,4,5,6,8,10,12,15,16,18,20,22,24,28,32,43,
       48,58,64,64,64,64,64,64,64,64,64,64,64,64,64,64 },
     { 1,1,1,2,2,3,3,4,4,4,5,6,8,10,12,16,20,24,26,28,30,32,42,
       48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48 },
     { 1,1,1,2,2,3,3,4,4,4,5,6,8,10,12,15,18,20,24,28,30,32,32,
       32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 },
     { 1,1,1,2,2,3,3,4,4,4,5,6,8,10,12,16,18,22,24,28,30,32,32,
       32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 },
     { 1,1,1,2,2,3,3,4,4,4,5,6,8,10,12,16,18,20,22,24,28,32,32,
       32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 },
     { 1,1,1,2,2,3,3,4,4,4,5,6,8,10,12,16,18,20,22,24,28,32,32,
       32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 },
     { 1,1,1,2,2,3,3,4,5,5,6,8,10,12,14,16,18,20,22,24,28,28,28,
       28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 },
     { 1,1,1,2,2,3,3,4,4,5,5,6,8,10,12,16,18,20,22,24,24,24,24,
       24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },
     { 1,1,1,2,2,3,3,3,4,5,5,6,8,10,12,15,16,18,20,20,20,20,20,
       20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 }
   },},
};

/* -----------------------------------------------------------
 * Solis constants for data ajustment
 * ----------------------------------------------------------- */

const static struct {
  double m_infreq;
  double m_appp_offset;
  double m_involt193[2];
  double m_involt194[2];
  double m_incurr[2];
  double m_battvolt[2];
  double m_outvolt_s[2][2];
  double m_outvolt_i[2][2];
  double m_outcurr_s[2][2];
  double m_outcurr_i[2][2];
  double m_utilp_s[2][2];
  double m_utilp_i[2][2];
  double m_appp_s[2][2];
  double m_appp_i[2][2];
} ctab[6] =
{
  { 101620.0, 25.0,
    { 1.141, 13.0 },
    { 1.141, 13.0 },
    { 22.2, 800.0 },
    { 1.0/7.19, 0.0 },
    { { 1.45, 13.0 },{ 1.4, 17.0 } },
    { { 1.45, 13.0 },{ 1.4, 17.0 } },
    { { 1.0/20.5, 0.15 }, { 1.0/20.5, 0.15 } },
    { { 1.0/20.5, 0.15 }, { 1.0/20.5, 0.15 } },
    { { 1.0/12.8, 16.0 }, { 1.0/12.3, 15.0 } },
    { { 1.0/12.8, 16.0 }, { 1.0/12.3, 15.0 } },
    { { 1.0/13.46, 16.7 }, { 1.0/12.9, 19.0 } },
    { { 1.0/13.46, 16.7 }, { 1.0/12.9, 19.0 } }
  },
  { 101715.0, 28.0,
    { 1.141, 12.0 },
    { 2.5, -250.0 },
    { 22.2, 800.0 },
    { 1.0/7.19, 0.6},
    { { 1.44, 13.0 }, { 1.4, 18.0 } },
    { { 2.9, 13.0 }, { 3.15, 2.0 } },
    { { 1.0/21.75, 0.15 }, { 1.0/21.75, 0.15 } },
    { { 1.0/49.0, 0.1 }, { 1.0/49.0, 0.1 } },
    { { 1.0/12.87, 15.6 }, { 1.0/12.2, 13.0 } },
    { { 1.0/14.5, 20.0 }, { 1.0/14.0, 25.0 } },
    { { 1.0/13.5, 16.0 }, { 1.0/12.9, 17.0 } },
    { { 1.0/15.4, 22.0 }, { 1.0/14.5, 22.0 } }
  },
  { 101620.0, 35.0,
    { 1.141, 13.0 },
    { 2.5, -250.0 },
    { 22.2, 800.0 },
    { 1.0/7.0, 0.0 },
    { { 1.375, 16.0 }, { 1.41, 16.0 } },
    { { 2.8, 20.0 }, { 2.9, 18.0 } },
    { { 1.0/16.5, 0.1 }, { 1.0/16.8, 0.0 } },
    { { 1.0/32.5, 0.0 }, { 1.0/32.5, 0.0 } },
    { { 1.0/10.2, 11.0 }, { 1.0/9.4, 15.0 } },
    { { 1.0/10.1, 26.0 }, { 1.0/9.4, 30.0 } },
    { { 1.0/10.2, 11.0 }, { 1.0/9.4, 15.0 } },
    { { 1.0/10.6, 26.0 }, { 1.0/9.8, 30.0 } }
  },
  { 101700.0, 40.0,
    { 1.141, 13.0 },
    { 2.5, -250.0 },
    { 35.0, 800.0 },
    { 1.0/7.19, 1.1 },
    { { 1.45, 11.8 }, { 1.65, 0.0 } },
    { { 2.93, 13.0 }, { 3.0, 12.0 } },
    { { 1.0/12.2, 0.32 }, { 1.0/12.2, 0.32 } },
    { { 1.0/23.2, 0.2 }, { 1.0/23.2, 0.20 } },
    { { 1.0/7.0, 16.5 }, { 1.0/6.85, 13.0 } },
    { { 1.0/7.15, 30.0 }, { 1.0/6.87, 23.0 } },
    { { 1.0/7.45, 28.0 }, { 1.0/7.25, 18.2 } },
    { { 1.0/7.55, 37.0 }, { 1.0/7.25, 29.0 } }
  },
  { 101800.0, 56.0,
    { 1.127, 12.0 },
    { 2.5, -250.0 },
    { 35.0, 1000.0 },
    { 1.0/3.52, 0.0 },
    { { 1.41, 13.0 }, { 1.4, 17.0 } },
    { { 2.73, 25.0 }, { 2.73, 30.0 } },
    { { 1.0/8.15, 0.25 }, { 1.0/8.15, 0.25 } },
    { { 1.0/16.0, 0.4 }, { 1.0/15.0, 0.4 } },
    { { 1.0/4.87, 19.0 }, { 1.0/4.55, 17.0 } },
    { { 1.0/4.78, 52.0 }, { 1.0/4.55, 55.0 } },
    { { 1.0/5.15, 29.0 }, { 1.0/4.8, 26.0 } },
    { { 1.0/4.78, 52.0 }, { 1.0/4.55, 55.0 } }
  },

  /*STAY1200_USB

  double m_infreq;
  double m_appp_offset;
  double m_involt193[2];
  double m_involt194[2];
  double m_incurr[2];
  double m_battvolt[2];
  double m_outvolt_s[2][2];
  double m_outvolt_i[2][2];
  double m_outcurr_s[2][2];
  double m_outcurr_i[2][2];
  double m_utilp_s[2][2];
  double m_utilp_i[2][2];
  double m_appp_s[2][2];
  double m_appp_i[2][2];


   */
  { 101800.0, //m_infreq
    56.0, //m_appp_offset
    { 1.64, 9.34 },// m_involt193 - ok
    { 2.5, -250.0 }, //m_involt194
    { 35.0, 1000.0 }, //m_incurr
    { 0.1551, 0.2525 }, //m_battvolt
    { { 1.41, 13.0 }, { 1.4, 17.0 } }, //m_outvolt_s
    { { 2.73, 25.0 }, { 2.73, 30.0 } }, //m_outvolt_i
    { { 1.0/8.15, 0.25 }, { 1.0/8.15, 0.25 } }, //m_outcurr_s
    { { 1.0/16.0, 0.4 }, { 1.0/15.0, 0.4 } }, //m_outcurr_i
    { { 1.0/4.87, 19.0 }, { 1.0/4.55, 17.0 } }, //m_utilp_s
    { { 1.0/4.78, 52.0 }, { 1.0/4.55, 55.0 } }, //m_utilp_i
    { { 1.0/5.15, 29.0 }, { 1.0/4.8, 26.0 } },  //m__app_s
    { { 1.0/4.78, 52.0 }, { 1.0/4.55, 55.0 } } //m_app_i
  }
};

/* Date, time and programming group */
static int const BASE_YEAR = 1998;
static int Day, Month, Year;
static int isprogram = 0, progshut = 0, prgups = 0;
static int dian=0, mesn=0, anon=0, weekn=0;
static int dhour, dmin, lhour, lmin, ihour,imin, isec, hourshut, minshut;
static unsigned char DaysOnWeek=0, DaysOffWeek=0, DaysStd = 0;
static char seman[4];

/* buffers */
static unsigned char RecPack[PACKET_SIZE];
static unsigned char ConfigPack[12];

/*
unsigned char MibData[161];
unsigned char DumpPack[242];
*/

/* Identification */
static const char *Model;
static int SolisModel, imodel;
static int InputValue, Out220;

/* Status group */
static unsigned char InputStatus,OutputStatus, BattStatus;
/* Events group */
static unsigned char SourceEvents, OutputEvents, BattEvents;

/* logical */
static bool_t detected = 0;
static bool_t SourceFail, SourceLast, FailureFlag, SourceReturn, SuperHeat;
static bool_t SuperHeatLast, OverCharge, OverChargeLast, LowBatt;
static bool_t CriticBatt, CriticBattLast, Flag_inversor, InversorOn, InversorOnLast;

/* Input group */
static double InVoltage, InCurrent, InFreq;
static double InDownLim, InUpLim, NomInVolt;
/* Output group */
static double OutVoltage, OutCurrent, OutFreq, OutDownLim, OutUpLim, NomOutVolt;
/* Battery group */
static int Autonomy, BattExtension, maxauto;
static double BattVoltage, Temperature, batcharge;
/* Power group */
static double AppPower, UtilPower, upscharge;
static int ChargePowerFactor, NominalPower, UpsPowerFactor;

static void print_info(void);
static int  is_today( unsigned char, int );
static void autonomy_calc( int );
static void scan_received_pack(void);
static void comm_receive(const unsigned char*,  int );
static void get_base_info(void);
static void get_update_info(void);

#endif /* INCLUDED_SOLIS_H */
