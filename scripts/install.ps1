#parameters
param([string]$TARGET)	#TARGET = target to install (bfme2 or rotwk)
#variables
$DIR_START = (Get-Item -Path ".\" -Verbose).FullName	#current directory
$TARGET_ISO = $DIR_START+'\game_files\'+$TARGET+'\disc1.iso'	#target iso file

"`t DO NOT CLOSE THISE WINDOW!"

#mount TARGET_ISO
"`t Mounting ISO file..."
$MOUNT = Mount-DiskImage $TARGET_ISO -PassThru
$DRIVE = ($MOUNT | Get-Volume).DriveLetter + ":\"	#get drive letter of MOUNT

#print serial keys for user
"`t Installing..."
#cd to DRIVE (installer searched for .dll filed in current directory)
cd $DRIVE
#run the installer
try
{
	Start-Process "AutoRun.exe" -Wait
}
catch [InvalidOperationException]
{
	"`t INSTALLATION ABORTED."
}

"`t Dismounting ISO file..."
#dismount TARGET_ISO
Dismount-DiskImage $TARGET_ISO

cd $DIR_START