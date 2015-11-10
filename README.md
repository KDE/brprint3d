This is the README file for the development version of BRPrint3d

Please check the ReleaseNotes.txt for details about new features and
changes since last release

BRPrint3d can be found at http://projects.kde.org/brprint3d

License: GPLv2

You can get the sources to the latest development version from the git
repository, configured :

git.kde.org:brprint3d

Basic Usage:
============

Install and start from the desktop, or you can run it locally from the
build directory:

On Linux:

$ ./brprint3d

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