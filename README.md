# RBE3001_nucleo_firmware

Welcome to the first RBE3001 lab session! This is going to be great!
Below you will find instructions to install and set up the firmware for the nucleo-f746zg board.

If you are working on one of the workstations in AK120, then you can skip the first section of this README, and go directly to section 2.

# 1. Set up udev rule (for private machines only)
## Driver and udev rule
The nucleo needs a udev rule installed in

/etc/udev/rules.d/81-neuronrobotics.rules

```
wget https://github.com/WPIRoboticsEngineering/RBE3001_nucleo_firmware/releases/download/0.0.6/81-neuronrobotics.rules
sudo cp 81-neuronrobotics.rules /etc/udev/rules.d/
sudo  udevadm control --reload-rules
sudo adduser $USER dialout 
```
Udev for nucleo source

## Toolchains 
```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt install gcc-arm-embedded automake libusb-1.0-0-dev putty libhidapi-dev python-pip libtool git
sudo pip install mbed-cli
git clone http://repo.or.cz/r/openocd.git
cd openocd
./bootstrap
./configure --enable-stlink --enable-ftdi --enable-cmsis-dap --prefix=/usr/local
make -j8
sudo make install

```

Log out and log back in to make the user permissions stick.


# 2. Configure git
## Generating a new SSH key
If you wish to be able to push changes to this repository without having to enter your username and password all the time,
you need to set up an SSH key with github. 
### 2.1 Create SSH key
Open Terminal

Paste the text below, substituting in your GitHub email address.

 `$ ssh-keygen -t rsa -b 4096 -C "your_email@example.com"`
 
This creates a new ssh key, using the provided email as a label.

 `> Generating public/private rsa key pair.`
 
When you're prompted to "Enter a file in which to save the key," press Enter. This accepts the default file location.

 `> Enter a file in which to save the key (/home/you/.ssh/id_rsa): [Press enter]`
 
At the prompt, DO NOT type a secure passphrase, hit enter to make it passwordless.

### 2.2 Add ssh key to GitHub

And then:  https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/

### 2.3 Configure the username
```
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@wpi.edu
```
To check which other users have been configured, you can run:
```
$ git config --list
 ```

# 3. Set up your Git Repository
## 3.1 Clone your private lab repository
Clone your private lab repository. **Note: The command below won't work! Use your own url, found on Github!**
```
git clone git@github.com:RBE300X-Lab/RBE3001_nucleo_firmwareXX.git
```
If your repository is empty, you may get a warning.

## 3.2 Set up your private lab repository **[DO ONLY ONCE PER TEAM]**
Note: Perform this **only if** you do not already have the nucleo firmware in your repository
1. `cd` into your repository you just created
```
cd [name of the repository you just cloned]
```
2. Set up a secondary remote server pointing to your repository
```
git remote add default-code https://github.com/WPIRoboticsEngineering/RBE3001_nucleo_firmware.git
```
You can confirm that the remote has been added by running the following command: 
```
git remote
```
3. Pull the code from your remote server. You should then see the code in your local repository
``` bash
git pull default-code master
```
4. Push your code to your main remote repository `origin`
```bash
git push origin
```

## 3.3 Pulling changes from your secondary remote repository **[Only if required]**
If you need to pull new changes from the default repostory, follow these instructions:
1. Make sure you have set up the correct secondary remote repository. Run the following code to check:
``` bash
git remote -v
```
You should see `origin` (your main server repo) and another pointing to the following url:
```bash
https://github.com/WPIRoboticsEngineering/RBE3001_nucleo_firmware.git
```
**If you do not see a second remote, or your second remote points to another url, follow the instructions under [Section 3.2 Part 2](##3.2-Set-up-your-private-lab-repository-**[DO-ONLY-ONCE-PER-TEAM]**)**

2. Run the following command to pull the new code from the secondary remote repository:
``` bash
git pull default-code master
```
Note: If your secondary remote is not named `default-code`, change it to the actual name

## 3.4 Ensure you have all of your submodules added and pulled
**Note: This needs to be done every time you clone the repository**
``` bash
git submodule init
git submodule update
```

# 4. Set up and test the firmware + toolchain

## 4.1 Install the required components using pip
``` bash
pip install --user --upgrade setuptools
```

## 4.2 Compile and Deploy the firmware
``` bash
mbed deploy
mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/ -f
```

If everything worked your terminal should look like: 

![](/img/terminal.png)

If an error message shows up at the end of the build process, check that the board is connected to the computer and try again.

# 5. Setting up Doxygen

```
doxygen doxy.doxygen
```
If successful a series of commands should scroll across the screen and once complete a docs folder should be generated comtaining an html folder.

# 6. Print statements

Now we are going to verify the communication between the computer and the NUCLEO firmware. To do so, we will use putty to listen on the serial port ttyACM0:
```
putty -serial /dev/ttyACM0
```
If successful, you should now see the following:

![](/img/serial.png)


# 7 Install Eclipse CDT (for private machines only)

## 7.1 Download
[Direct Download Link for Eclipse](https://www.eclipse.org/downloads/download.php?file=/oomph/epp/oxygen/R/eclipse-inst-linux64.tar.gz)

## 7.2 Install
Extract and run the installer. Select C/C++ version of eclipse and install it in the default location. 

`eclipse-inst`

![](/img/eclipse.png)

To launch eclipse, go to where you installed eclipse

if you installed in it in the deault location run:

```
cd ~/eclipse/cpp-oxygen/eclipse
./eclipse
```
Optionally you can make an eclipse launcher
```
mkdir -p ~/bin/
echo "[Desktop Entry]
Version=1.0
Type=Application
Name=Eclipse Arm Toolchain
Comment=
Exec=$HOME/eclipse/cpp-oxygen/eclipse/eclipse
Icon=$HOME/eclipse/cpp-oxygen/eclipse/icon.xpm
Path=
Terminal=false
StartupNotify=false" > ~/bin/EclipseARM.desktop
chmod +x ~/bin/EclipseARM.desktop
ln -s ~/bin/Eclipse.desktop ~/Desktop/EclipseARM.desktop
```

# 8. Configure your Eclipse

Start by opening eclipse


## 8.1 configure plugin

Create a workspace for you RBE3001 devlepmet. First, add the GNU ARM toolchain by clicking on the Help tab at the top of the screen and then clicking on the "Install New Software..." button within that tab. From there, add the following information:


Name: GNU ARM Eclipse Plug-ins

Location: `http://gnu-mcu-eclipse.netlify.com/v4-neon-updates`

Install plugins from that site. 

### NOTE
 
This step will take some time, be sure to wait for it to finish

Restart Eclipse after installing plugins.


## 8.2 Next Set up the toolchain path for MCU's

Window->Preferences->MCU->Global ARM Toolchain Paths->Toolchain folder:

`/usr/arm-none-eabi/bin/`

Apply and Close

## 8.3 Import project

Set up a new project using "Importing to Eclipse and Building" section from: 

From the File menu:
Import... ->C/C++ -> Existing Code as Makefile Project

Browse in Existing Code Location for your RBE3001_Nucleo_firmware (This should set the project name as well

Select ARM Cross GCC

Finish

## 8.4 Configure Build command

Then set the build command by right clicking on RBE3001_Nucleo_firmware

Select Properties->C/C++ Build

Builder Settings->Build Command:

`mbed-cli compile -j0 -t GCC_ARM -m nucleo_f746zg --source .  --source ./mbed-os/features/unsupported/USBDevice/USBDevice/  --source ./mbed-os/features/unsupported/USBDevice/USBHID/`

![](/img/Screenshot_2017-08-21_12-50-00.png)


Set the build command to push the firmware with '-f'

Properties->C/C++ Build->Behavior-> Build(Incremental Build)

Additionally, make sure `Buildon resource save (autobuild)` is unchecked

![](/img/Screenshot_2017-08-21_12-43-41.png)

## 8.5 Fix Compilation path

right click on RBE3001_Nucleo_firmware 

Properties->C/C++ Build ->Settings->Toolchains->Toolchain path

and make sure it says:

`/usr/arm-none-eabi/bin/`

Click apply and Save from this window. This writes the toolchain into the configuration and causes a re-index. THis step is nessissary. 

right click on RBE3001_Nucleo_firmware

Index-> Rebuild

Wait for the C/C++ indexer to complete and then you can begin working.

## 8.6 Click the green run button

The green button with hte white play symbol to compile and program the robot.

**Congratulations! You have completed the setup of the NUCLEO firmware!**


# 9. Core firmware maintainance and bug reporting
## 9.1 Upstream updates
If the course staff needs to update or repair any system code or the dependant libraries, then you will need to run:
```
git pull RBE-UPSTREAM master
git submodule init
git submodule update
cd lib/AS5050/
git pull origin master
cd ..
cd lib/MbedPwmServo/
git pull origin master
cd ..
cd lib/PID_Bowler/
git pull origin master
cd ..
cd lib/SimplePacketComs/
git pull origin master
cd ..
```

## 9.2 Reporting Issues with the template code

To report an issue with the template code it must consist of these exact elements:

A public fork of the template code from the current master with the error demonstrated with a unit test demonstration. Only the necessary code to demonstrate the bug. 9 times out of 10, when doing this you will find the bug or a faster workaround to unexpected behavior. If the bug can be demonstrated in isolation then move on to the next step. DO Not just copy your whole project over, make a new set of code demonstrating only the problem and nothing else. Each line must have a comment on the end explaining why it needs to be ther in order to demonstrate the bug. This will be visible in the github diff as each line having a comment after the end of the line. If you demonstration does not meet these criteria, the issue will wait until you commit updates making the repo meet them. 

An Issue posted here: https://github.com/WPIRoboticsEngineering/RBE3001_nucleo_firmware/issues and a link to the repository with the demonstration code. Simply describing a problem without the isolated demonstration code will cause the issue to be closed. The issue will be reviewed and a patch or response with happen as soon as the staff figures out whats wrong. If you would like to suggest a solution, feel free to send a Pull Request with a clean branch of the solution to the issue. Be sure to include the issue number, such as #1 , in all commits resolving this issue. 
