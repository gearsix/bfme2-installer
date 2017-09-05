#parameters
param([string]$TARGET)	#target = target to install (bfme2 or rotwk)
#variables
$DIR_START = (Get-Item -Path ".\" -Verbose).FullName	#current directory

#check game is installed
if ($TARGET -eq 'bfme2')
{
	try
	{
		$DIR_INSTALL = (Get-ItemProperty "HKLM:\SOFTWARE\WOW6432Node\Electronic Arts\The Battle for Middle-earth II" -ErrorAction Stop)."Install Dir"
		$DIR_APPDATA = $env:APPDATA+"\My Battle for Middle-earth(tm) II Files\"
	}
	catch
	{
		"`t COULD NOT DETECT INSTALLATION"
		"`t ABORTING...`n"
		exit
	}
}
elseif ($target -eq 'rotwk')
{
	try
	{
		$DIR_INSTALL = (Get-ItemProperty "HKLM:\SOFTWARE\WOW6432Node\Electronic Arts\The Lord of the Rings, The Rise of the Witch-king" -ErrorAction Stop)."Install Dir"
		$DIR_APPDATA = $env:APPDATA+"\My The Lord of the Rings, The Rise of the Witch-king Files\"
	}
	catch
	{
		"`t COULD NOT DETECT INSTALLATION"
		"`t ABORTING...`n"
		exit
	}
}

"`t Uninstalling...`n"
#run uninstaller
cd $DIR_INSTALL
Start-Process 'eauninstall.exe' -Wait
cd $DIR_START

