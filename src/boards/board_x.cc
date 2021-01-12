/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2015-2020  Luis Claudio Gambôa Lopes

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

//include files
#include"../picsimlab1.h"
#include"../picsimlab4.h" //Oscilloscope
#include"../picsimlab5.h" //Spare Parts
#include"board_x.h"

/* ids of inputs of input map*/
enum
{
 I_ICSP, //ICSP connector
 I_PWR, //Power button
 I_RST, //Reset button
 I_D0, //RD0 push button
 I_D1 //RD1 switch
};

/* ids of outputs of output map*/
enum
{
 O_SD1, //switch position (On/Off)
 O_LD0, //LED on RD0 push button
 O_LD1, //LED on RD1 switch
 O_LPWR, //Power LED
 O_RB0, //LED on RB0 output
 O_RB1 //LED on RB1 output
};
//return the input ids numbers of names used in input map

unsigned short
cboard_x::get_in_id(char * name)
{
 if (strcmp (name, "PG_ICSP") == 0)return I_ICSP;
 if (strcmp (name, "SW_PWR") == 0)return I_PWR;
 if (strcmp (name, "PB_RST") == 0)return I_RST;
 if (strcmp (name, "PB_D0") == 0)return I_D0;
 if (strcmp (name, "SW_D1") == 0)return I_D1;

 printf ("Error input '%s' don't have a valid id! \n", name);
 return -1;
}

//return the output ids numbers of names used in output map

unsigned short
cboard_x::get_out_id(char * name)
{

 if (strcmp (name, "SW_D1") == 0)return O_SD1;
 if (strcmp (name, "LD_LD0") == 0)return O_LD0;
 if (strcmp (name, "LD_LD1") == 0)return O_LD1;
 if (strcmp (name, "LD_LPWR") == 0)return O_LPWR;
 if (strcmp (name, "LD_RB1") == 0)return O_RB1;
 if (strcmp (name, "LD_RB0") == 0)return O_RB0;

 printf ("Error output '%s' don't have a valid id! \n", name);
 return 1;
}

//Constructor called once on board creation 

cboard_x::cboard_x(void)
{
 Proc = "PIC18F4550"; //default microcontroller if none defined in preferences
 ReadMaps (); //Read input and output board maps

 //controls properties and creation
 //scroll1
 scroll1 = new CScroll ();
 scroll1->SetFOwner (&Window1);
 scroll1->SetName (lxT ("scroll1_px"));
 scroll1->SetX (12);
 scroll1->SetY (273 - 160);
 scroll1->SetWidth (140);
 scroll1->SetHeight (22);
 scroll1->SetEnable (1);
 scroll1->SetVisible (1);
 scroll1->SetRange (100);
 scroll1->SetPosition (50);
 scroll1->SetType (4);
 Window1.CreateChild (scroll1);
 //gauge1
 gauge1 = new CGauge ();
 gauge1->SetFOwner (&Window1);
 gauge1->SetName (lxT ("gauge1_px"));
 gauge1->SetX (13);
 gauge1->SetY (382 - 160);
 gauge1->SetWidth (140);
 gauge1->SetHeight (20);
 gauge1->SetEnable (1);
 gauge1->SetVisible (1);
 gauge1->SetRange (100);
 gauge1->SetValue (0);
 gauge1->SetType (4);
 Window1.CreateChild (gauge1);
 //gauge2
 gauge2 = new CGauge ();
 gauge2->SetFOwner (&Window1);
 gauge2->SetName (lxT ("gauge2_px"));
 gauge2->SetX (12);
 gauge2->SetY (330 - 160);
 gauge2->SetWidth (140);
 gauge2->SetHeight (20);
 gauge2->SetEnable (1);
 gauge2->SetVisible (1);
 gauge2->SetRange (100);
 gauge2->SetValue (0);
 gauge2->SetType (4);
 Window1.CreateChild (gauge2);
 //label1
 label1 = new CLabel ();
 label1->SetFOwner (&Window1);
 label1->SetName (lxT ("label1_px"));
 label1->SetX (12);
 label1->SetY (249 - 160);
 label1->SetWidth (60);
 label1->SetHeight (20);
 label1->SetEnable (1);
 label1->SetVisible (1);
 label1->SetText (lxT ("AN0"));
 label1->SetAlign (1);
 Window1.CreateChild (label1);
 //label2
 label2 = new CLabel ();
 label2->SetFOwner (&Window1);
 label2->SetName (lxT ("label2_px"));
 label2->SetX (12);
 label2->SetY (306 - 160);
 label2->SetWidth (60);
 label2->SetHeight (20);
 label2->SetEnable (1);
 label2->SetVisible (1);
 label2->SetText (lxT ("RB0"));
 label2->SetAlign (1);
 Window1.CreateChild (label2);
 //label3
 label3 = new CLabel ();
 label3->SetFOwner (&Window1);
 label3->SetName (lxT ("label3_px"));
 label3->SetX (13);
 label3->SetY (357 - 160);
 label3->SetWidth (60);
 label3->SetHeight (20);
 label3->SetEnable (1);
 label3->SetVisible (1);
 label3->SetText (lxT ("RB1"));
 label3->SetAlign (1);
 Window1.CreateChild (label3);
}

//Destructor called once on board destruction 

cboard_x::~cboard_x(void)
{
 //controls destruction 
 Window1.DestroyChild (scroll1);
 Window1.DestroyChild (gauge1);
 Window1.DestroyChild (gauge2);
 Window1.DestroyChild (label1);
 Window1.DestroyChild (label2);
 Window1.DestroyChild (label3);
}

//Reset board status

void
cboard_x::Reset(void)
{
 pic_reset (1);

 p_BT1 = 1; //set push button  in default state (high) 

 //write button state to pic pin 19 (RD0)
 pic_set_pin (19, p_BT1);
 //write switch state to pic pin 20 (RD1)
 pic_set_pin (20, p_BT2);


 //verify serial port state and refresh status bar  
#ifndef _WIN_
 if (pic.serial[0].serialfd > 0)
#else
 if (pic.serial[0].serialfd != INVALID_HANDLE_VALUE)
#endif
  Window1.statusbar1.SetField (2, lxT ("Serial: ") +
                               lxString::FromAscii (SERIALDEVICE) + lxT (":") + itoa (pic.serial[0].serialbaud) + lxT ("(") +
                               lxString ().Format ("%4.1f", fabs ((100.0 * pic.serial[0].serialexbaud - 100.0 *
                                                                 pic.serial[0].serialbaud) / pic.serial[0].serialexbaud)) + lxT ("%)"));
 else
  Window1.statusbar1.SetField (2, lxT ("Serial: ") +
                               lxString::FromAscii (SERIALDEVICE) + lxT (" (ERROR)"));

 if (use_spare)Window5.Reset ();
}

//Called ever 1s to refresh status

void
cboard_x::RefreshStatus(void)
{
 //verify serial port state and refresh status bar   
#ifndef _WIN_
 if (pic.serial[0].serialfd > 0)
#else
 if (pic.serial[0].serialfd != INVALID_HANDLE_VALUE)
#endif
  Window1.statusbar1.SetField (2, lxT ("Serial: ") +
                               lxString::FromAscii (SERIALDEVICE) + lxT (":") + itoa (pic.serial[0].serialbaud) + lxT ("(") +
                               lxString ().Format ("%4.1f", fabs ((100.0 * pic.serial[0].serialexbaud - 100.0 *
                                                                 pic.serial[0].serialbaud) / pic.serial[0].serialexbaud)) + lxT ("%)"));
 else
  Window1.statusbar1.SetField (2, lxT ("Serial: ") +
                               lxString::FromAscii (SERIALDEVICE) + lxT (" (ERROR)"));

}

//Called to save board preferences in configuration file

void
cboard_x::WritePreferences(void)
{
 //write selected microcontroller of board_x to preferences
 Window1.saveprefs (lxT ("X_proc"), Proc);
 //write switch state of board_x to preferences 
 Window1.saveprefs (lxT ("X_bt2"), lxString ().Format ("%i", p_BT2));
 //write microcontroller clock to preferences
 Window1.saveprefs (lxT ("X_clock"), lxString ().Format ("%2.1f", Window1.GetClock()));
}

//Called whe configuration file load  preferences 

void
cboard_x::ReadPreferences(char *name, char *value)
{
 //read switch state of board_x of preferences 
 if (!strcmp (name, "X_bt2"))
  {
   if (value[0] == '0')
    p_BT2 = 0;
   else
    p_BT2 = 1;
  }
 //read microcontroller of preferences
 if (!strcmp (name, "X_proc"))
  {
   Proc = value;
  }
 //read microcontroller clock
 if (!strcmp (name, "X_clock"))
 {
  Window1.SetClock (atof(value));
 }
}


//Event on the board

void
cboard_x::EvKeyPress(uint key, uint mask)
{
 //if keyboard key 1 is pressed then activate button (state=0)   
 if (key == '1')
  {
   p_BT1 = 0;
  }

 //if keyboard key 2 is pressed then toggle switch state   
 if (key == '2')
  {
   p_BT2 ^= 1;
  }

}

//Event on the board

void
cboard_x::EvKeyRelease(uint key, uint mask)
{
 //if keyboard key 1 is pressed then deactivate button (state=1)     
 if (key == '1')
  {
   p_BT1 = 1;
  }

}

//Event on the board

void
cboard_x::EvMouseButtonPress(uint button, uint x, uint y, uint state)
{

 int i;

 //search for the input area which owner the event    
 for (i = 0; i < inputc; i++)
  {
   if (((input[i].x1 <= x)&&(input[i].x2 >= x))&&((input[i].y1 <= y)&&
                                                  (input[i].y2 >= y)))
    {

     switch (input[i].id)
      {
       //if event is over I_ISCP area then load hex file  
      case I_ICSP:
       Window1.menu1_File_LoadHex_EvMenuActive (NULL);
       break;
       //if event is over I_PWR area then toggle board on/off
      case I_PWR:
       if (Window1.Get_mcupwr ()) //if on turn off
        {
         Window1.Set_mcurun (0);
         Window1.Set_mcupwr (0);
         Reset ();
         p_BT1 = 1;
         Window1.statusbar1.SetField (0, lxT ("Stoped"));
        }
       else //if off turn on
        {
         Window1.Set_mcupwr (1);
         Window1.Set_mcurun (1);
         Reset ();
         Window1.statusbar1.SetField (0, lxT ("Running..."));
        }
       break;
       //if event is over I_RST area then turn off and reset
      case I_RST:
       if (Window1.Get_mcupwr () && pic_reset (-1))//if powered
        {
         Window1.Set_mcupwr (0);
         Window1.Set_mcurst (1);
        }
       p_MCLR = 0;
       break;
       //if event is over I_D0 area then activate button (state=0) 
      case I_D0:
       p_BT1 = 0;
       break;
       //if event is over I_D1 area then toggle switch state   
      case I_D1:
       p_BT2 ^= 1;
       break;
      }
    }
  }

}

//Event on the board

void
cboard_x::EvMouseButtonRelease(uint button, uint x, uint y, uint state)
{
 int i;

 //search for the input area which owner the event  
 for (i = 0; i < inputc; i++)
  {
   if (((input[i].x1 <= x)&&(input[i].x2 >= x))&&((input[i].y1 <= y)&&
                                                  (input[i].y2 >= y)))
    {
     switch (input[i].id)
      {
       //if event is over I_RST area then turn on  
      case I_RST:
       if (Window1.Get_mcurst ())//if powered
        {
         Window1.Set_mcupwr (1);
         Window1.Set_mcurst (0);

         if (pic_reset (-1))
          {
           Reset ();
          }
        }
       p_MCLR = 1;
       break;
       //if event is over I_D0 area then deactivate button (state=1) 
      case I_D0:
       p_BT1 = 1;
       break;
      }
    }
  }

}


//Called ever 100ms to draw board
//This is the critical code for simulator running speed

void
cboard_x::Draw(CDraw *draw, double scale)
{
 int i;

 draw->Canvas.Init (scale, scale); //initialize draw context

 //board_x draw 
 for (i = 0; i < outputc; i++) //run over all outputs
  {
   if (!output[i].r)//if output shape is a rectangle
    {
     if (output[i].id == O_SD1)//if output is switch
      {
       //draw a background white rectangle   
       draw->Canvas.SetBgColor (255, 255, 255);
       draw->Canvas.Rectangle (1, output[i].x1, output[i].y1,
                               output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);

       if (!p_BT2) //draw switch off
        {
         //draw a grey rectangle  
         draw->Canvas.SetBgColor (70, 70, 70);
         draw->Canvas.Rectangle (1, output[i].x1, output[i].y1 +
                                 ((int) ((output[i].y2 - output[i].y1)*0.35)), output[i].x2 - output[i].x1,
                                 (int) ((output[i].y2 - output[i].y1)*0.65));
        }
       else //draw switch on
        {
         //draw a grey rectangle  
         draw->Canvas.SetBgColor (70, 70, 70);
         draw->Canvas.Rectangle (1, output[i].x1,
                                 output[i].y1, output[i].x2 - output[i].x1,
                                 (int) ((output[i].y2 - output[i].y1)*0.65));
        }
      }
    }
   else //if output shape is a circle
    {

     draw->Canvas.SetFgColor (0, 0, 0); //black

     switch (output[i].id)//search for color of output
      {
      case O_LD0: //White using pin 19 mean value (RD0)
       draw->Canvas.SetColor (pic.pins[18].oavalue, pic.pins[18].oavalue, pic.pins[18].oavalue);
       break;
      case O_LD1: //Yelllow using pin 20 mean value (RD1)
       draw->Canvas.SetColor (pic.pins[19].oavalue, pic.pins[19].oavalue, 0);
       break;
      case O_LPWR: //Blue using mcupwr value
       draw->Canvas.SetColor (0, 0, 225 * Window1.Get_mcupwr () + 30);
       break;
      case O_RB0: //Green using pin 33 mean value (RB0)
       draw->Canvas.SetColor (0, pic.pins[32].oavalue, 0);
       break;
      case O_RB1: //Red using pin 34 mean value (RB1)
       draw->Canvas.SetColor (pic.pins[33].oavalue, 0, 0);
       break;
      }

     //draw a circle
     draw->Canvas.Circle (1, output[i].x1, output[i].y1, output[i].r);
    }

  }

 //end draw
 draw->Canvas.End ();
 draw->Update ();

 //RB0 mean value to gauge1
 gauge1->SetValue (0.4444 * (pic.pins[33].oavalue - 30));
 //RB1 mean value to gauge2
 gauge2->SetValue (0.44444 * (pic.pins[32].oavalue - 30));

}

void
cboard_x::Run_CPU(void)
{
 int i;
 int j;
 unsigned char pi;
 const picpin * pins;
 unsigned int alm[40];

 int JUMPSTEPS = Window1.GetJUMPSTEPS (); //number of steps skipped
 long int NSTEPJ = Window1.GetNSTEPJ (); //number of steps in 100ms


 //reset pins mean value
 memset (alm, 0, 40 * sizeof (unsigned int));

 //read pic.pins to a local variable to speed up 
 pins = pic.pins;

 //Spare parts window pre process
 if (use_spare)Window5.PreProcess ();

 j = JUMPSTEPS; //step counter
 if (Window1.Get_mcupwr ()) //if powered
  for (i = 0; i < Window1.GetNSTEP (); i++) //repeat for number of steps in 100ms
   {

    if (j >= JUMPSTEPS)//if number of step is bigger than steps to skip 
     {
      pic_set_pin (pic.mclr, p_MCLR);
      pic_set_pin (19, p_BT1); //Set pin 19 (RD0) with button state 
      pic_set_pin (20, p_BT2); //Set pin 20 (RD1) with switch state 
     }

    //verify if a breakpoint is reached if not run one instruction 
    if (!mplabxd_testbp ())pic_step ();
    //Oscilloscope window process
    if (use_oscope)Window4.SetSample ();
    //Spare parts window process
    if (use_spare)Window5.Process ();

    //increment mean value counter if pin is high 
    if (j < pic.PINCOUNT)
     alm[j] += pins[j].value;

    if (j >= JUMPSTEPS)//if number of step is bigger than steps to skip 
     {

      //set analog pin 2 (AN0) with value from scroll  
      pic_set_apin (2, ((5.0 * (scroll1->GetPosition ())) /
                        (scroll1->GetRange () - 1)));

      j = -1; //reset counter
     }
    j++; //counter increment
   }

 //calculate mean value
 for (pi = 0; pi < pic.PINCOUNT; pi++)
  {
   pic.pins[pi].oavalue = (int) (((225.0 * alm[pi]) / NSTEPJ) + 30);
  }
 
 //Spare parts window pre post process
 if (use_spare)Window5.PostProcess ();

}

//Register the board in PICSimLab
board_init("X", cboard_x); 

