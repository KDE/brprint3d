This is the README file for the development version of BRPrint3d

Please check the ReleaseNotes.txt for details about new features and
changes since last release

This version only have support to 3DPrinters with Repetier Firmware.

BRPrint3d can be found at http://projects.kde.org/brprint3d

License: GPLv3


Basic Usage:
============
Before compile BrPrint-3D, check if your libraries are the version
requireds:
Cmake Version 3.0 or Major
Qt Version 5.4 or Major
http://www.qt.io/download-open-source/#section-2
VTK Version 6 or Major
The VTK library you can found in this link:
www.vtk.org/download/
Bind VTK with Qt5
http://www.vtk.org/Wiki/VTK/Configure_and_Build#Configure_VTK_with_CMake
```sh
mkdir build-vtk && cd build-vtk
ccmake ../VTKSource
configure
VTK_Group_Qt=ON
configure
Qt_Version=5
generate and exit
make -j2
make install

```

On Linux:
Grab the source code from this repository using git and then
Run the following commands to install dependencies and to build the program:

In some distros the Br-Print3D will show a error: 'Arduino Serial couldn't open
serial port'.
This error is because the Arduino is mount with sudo permissions. We have two solutions for that:
-Runs Br-Print3D with sudo 
-Change The Rules of your serial ports
To change the rules, follow the steps:
```sh
cd /etc/udev/rules.d
sudo vim 999-BrRule.rules
KERNEL=="ttyACM[0-9]",MODE="0666"
```

If you're using Ubuntu or Debian:
The repositories dont have the VTK and Qt version that Br-Print3D requires. You will need to
download the source and compile. 

If you're using Fedora 22 or Major:
```sh
sudo dnf install qt5-devel qt5-qtbase-devel qt5-qttools-devel mesa-libGLU-devel mesa-libGL-devel
```
Compile steps:
```sh
git clone git.kde.org:brprint3d
mkdir build
cd build
cmake ..
make
./BRPrint
```
Help us:
========
-To find leek memories
-To find bugs or inconsistecies

Contributing:
=============

If you want to contribute code, please either send signed-off patches or
a pull request with signed-off commits.  If you don't sign off on them,
we will not accept them. This means adding a line that says
"Signed-off-by: Name <email>" at the end of each commit, indicating that
you wrote the code and have the right to pass it on as an open source
patch.

See: http://developercertificate.org/

Also, please write good git commit messages.  A good commit message
looks like this:

	Header line: explain the commit in one line (use the imperative)

	Body of commit message is a few lines of text, explaining things
	in more detail, possibly giving some background about the issue
	being fixed, etc etc.

	The body of the commit message can be several paragraphs, and
	please do proper word-wrap and keep columns shorter than about
	74 characters or so. That way "git log" will show things
	nicely even when it's indented.

	Make sure you explain your solution and why you're doing what you're
	doing, as opposed to describing what you're doing. Reviewers and your
	future self can read the patch, but might not understand why a
	particular solution was implemented.

	Reported-by: whoever-reported-it
	Signed-off-by: Your Name <youremail@yourhost.com>

where that header line really should be meaningful, and really should be
just one line.  That header line is what is shown by tools like gitk and
shortlog, and should summarize the change in one readable line of text,
independently of the longer explanation. Please use verbs in the
imperative in the commit message, as in "Fix bug that...", "Add
file/feature ...", or "Make BrPrint3d..."
