Sharp Wizard games
==================

A small collection of horrible games that, as a teenager, I made and distributed for my electronic organizer, the Sharp Wizard OZ-7xx series. Some of them are in BASIC, which was sanctioned by Sharp's provided SDK. The marginally more interesting games are written in C and compiled to Z80 assembly. The Wizard had a Z80 processor, so Alex Pruss wrote a C SDK for it, and people ran with it. There were even a few native assembly games!

Following is the list of games, in the rough order that they were written:

BASIC games:
 - Password -- Guess the word to get to the next one. THRILLING. Includes three different versions.
 - Star Trek: The Mission of Choice -- I don't even remember.
 - Star Trek Trivia -- Trust me, it's accurate. At least, it was at the time.

C/assembly games:
 - OZ Clay Pigeons -- Try to hit a clay pigeon by firing at the right time. Semi-addictive. Inspired by my old friend Danny's suggestion!
 - Monopoly -- Yup, it's Monopoly. Missing some feature of the game (was it the Chance and Community Chest cards?) because I ran out of available memory.
 - Falldown -- This was a popular game on the TI-83, so I tried to write my own version. It's not as fancy, but it's almost as addictive.
 - WizBattleship -- Fully-functional for hotseat two-player (it will even blank the screen while you hand your organizer to your friend). I was going to add an AI but never got around to it.

The .wzd files are directly installable to your OZ-7xx series Wizard. I only ever tested them on the OZ-730, so use at your own risk.

The source code for the C/assembly games is under src/ in this repository. It's some of the first code I ever wrote, so don't expect much. :-) If for some reason, you want the code for the BASIC games, you can use one of the decompiler tools out there. I really don't know where I put it, and it's not worth looking at, anyway!

You can get the HiTech C SDK (and other cool Wizard-related things) here: http://www.lh.co.nz/ozdev/

Please use caution when running any C/assembly programs on the Wizard, as there
have been reported situations where an organizer has been unintentionally
damaged. If your organizer is damaged, you are solely responsible.
