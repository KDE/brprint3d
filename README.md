This is the README file for the development version of Br-Print3D

Please check the ReleaseNotes.txt for details about new features and
changes since last release

This version is currently in developing
WE DO NOT HAVE ANY SUPPORT FOR PRINT FISNISH

License: GPLv3

Basic Usage:
============
Before compile BrPrint-3D, check if your libraries are the version
requireds:
Cmake Version 3.0 or Major
Qt Version 5.6 or Major
http://www.qt.io/download-open-source/#section-2

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

Compile steps:
```sh
sudo apt-get install git cmake g++ # On debian, Ubuntu, etc.
git clone https://github.com/KDE/brprint3d.git
cd brprint3d
mkdir build
cd build
cmake ..
make
./brprint3d
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
