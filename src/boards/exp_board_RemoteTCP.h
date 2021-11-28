/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2015-2021  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef BOARD_RemoteTCP_H
#define	BOARD_RemoteTCP_H

#include<lxrad.h>

#include "exp_bsim_remote.h"

#define BOARD_RemoteTCP_Name "Remote TCP"

//new board class must be derived from board class defined in board.h
class cboard_RemoteTCP:public bsim_remote
{
   private:
      lxBitmap * micbmp; 
      lxFont font;
      void RegisterRemoteControl(void) override; 
   public:
      //Return the board name
      lxString GetName(void) override {return lxT(BOARD_RemoteTCP_Name); };
      lxString GetAboutInfo(void) override {return lxT("L.C. Gamboa \n <lcgamboa@yahoo.com>");}; 
      //Constructor called once on board creation 
      cboard_RemoteTCP(void);
      //Destructor called once on board destruction 
      ~cboard_RemoteTCP(void); 
      //Called ever 100ms to draw board
      void Draw(CDraw *draw) override;
      void Run_CPU(void) override;
      //Return a list of board supported microcontrollers
      lxString GetSupportedDevices(void) override {return lxT("Ripes,");};
      //Reset board status
      void Reset(void) override;
      //Event on the board
      void EvMouseButtonPress(uint button, uint x, uint y,uint state) override;
      //Event on the board
      void EvMouseButtonRelease(uint button, uint x, uint y,uint state) override;
      //Event on the board
      void EvKeyPress(uint key,uint mask) override;
      //Event on the board
      void EvKeyRelease(uint key, uint mask) override;      
      //Called ever 1s to refresh status
      void RefreshStatus(void) override;
      //Called to save board preferences in configuration file
      void WritePreferences(void) override;
      //Called whe configuration file load  preferences 
      void ReadPreferences(char *name,char *value) override;
      //return the input ids numbers of names used in input map
      unsigned short get_in_id(char * name) override;
      //return the output ids numbers of names used in output map
      unsigned short get_out_id(char * name) override;
      //initialization of processor
      int MInit(const char * processor, const char * fname, float freq) override;
      //Run one step
      void MStep(void) override;   
};

#endif	/* BOARD_RemoteTCP_H */
