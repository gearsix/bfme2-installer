# ISO install wrapper - Lord of the Rings: Battle for Middle-Earth 2
**REQUIRES WINDOWS 10**
An install wrapper for Lord of the Rings: Battle for Middle-Earth 2 .iso files, it'll mount the .iso files, run the installer for you and apply the no cd crack so that you don't need to re-mount the .iso files everytime you run the game.

## Contents
1. [Disclaimer](##Disclaimer)
2. [Overview](##Overview)
3. [Requirements](##Requirements)
2. [Usage](##Usage)
3. [Compiling](##Compiling)
4. [Authors](##Authors)
5. [Changelog](##Changelog)

## Disclaimer
This project does not include any game files or serial keys.
You'll need to provide those yourself to use this.

## Overview
This is an install wrapper for the .iso files of Lord of the Rings: Battle for Middle-Earth 2 and it's expansion. It's written in C, except for the PowerShell scripts that to mount the .iso files (natively, which is the part that requires win10) and then runs the game installer on the disk.
I've also included a script that applies to no cd crack so that the .iso doesn't need to be mounted everytime you want to play.

I know the entire project seems a little unecessary, but I made it for some friends of mine that aren't tech-savvy enough to figure out how to mount .iso files, etc.

It would make more sense to have written the C portion of this in something like Python. If I ever need to re-purpose this for any other .iso files then I might rewrite it in Python and make it less usecase specific.

## Requirements
**For information on the game's system requirements, see docs/requirements.txt**

**Windows 10**
I insisted on using the native mounting feature added in Windows 10 because I like to try and stay minimal _(I also thought it was pretty cool that I was able to do this in PowerShell)_.
Obviously it also needs to be Windows because the .iso files have windows executable installers on and install windows versions of the game. I don't think Linux versions exist, but if you want to play it on Linux then this is useless because you'll need to do something with the game files (like run it in WINE or something).

## Usage
**For information on the game's system requirements, see docs/instructions.txt**

1. Add the _Battle for Middle-Earth 2 .iso_ to ```game_files/bfme2/```
2. Add the _Rise of the Witch-King .iso_ to ```game_files/rotwk/```
3. Run ```bfme2-installer.exe``` as an Administrator

What bfme2-installer does:
* Install
	1. Mounts the respective .iso (using Windows 10's native mounting feature)
	2. Runs the installer on the disc
	3. Dismounts the respective .iso file
* Apply crack
	1. Checks if the game is installed via the Registry (_HKLM:\SOFTWARE\WOW6432Node\Electronic Arts\*_) and data files directory (_$env:APPDATA+"\*\"_)
	2. Copies the crack file (no-cd crack) to the install directory
	3. Sets the options.ini file (found in the data files directory); this stops the game crashing on startup and sets the default resolution to 1920x1080.

## Compiling
Compiling is really simple, so I didn't bother with a Makefile or anything.
1. ```gcc src\bfme2-installer.c src\libs\* -o bfme2-installer.exe```
2. Done!

If you want to set an icon for the executable (as I have for the current release):
1. ```windres src\bfme2-installer.rc -o src\bfme2-installer.o```
2. ```gcc src\bfme2-installer.c src\libs\* src\bfme2-installer.o -o bfme2-installer.exe```
3. Done!

## Authors
* [Alexander Collins](https://www.github.com/GeaRSiX)
