seanh's dwm
===========

This is my "fork" of [dwm](http://dwm.suckless.org/) that contains my dwm
configuration, config files for other programs that I use with dwm, etc
(I haven't actually made any changes to the dwm code).

[This custom seanh branch](https://github.com/seanh/dwm/tree/seanh) is
currently branched off the [6.1](https://github.com/seanh/dwm/releases/tag/6.1)
tag (dwm version 6.1). You can see a
[comparison of my custom branch to dwm 6.1](https://github.com/seanh/dwm/compare/6.1...seanh).


Features
--------

- [Terminus font](http://terminus-font.sourceforge.net/)

- Keyboard shortcuts and the status area are bound to [scripts](bin) that you
  can modify the without having to restart dwm.

- The media keys on your keyboard are bound to scripts.

  For example the volume up key will call [dwm_volume_up](bin/dwm_volume_up),
  which calls PulseAudio to increase the volume.

  Volume down, toggle mute and open calculator, file browser and email also
  work. 

  See [config.h](config.h) for the full list of media keys that I bound, and
  how to bind more of them, and see `/usr/include/X11/XF86keysym.h` for the
  full list of media key names.

  I only bound the media keys that my keyboard has, and some of the scripts
  they're bound to don't exist because I don't have a good command to use for
  the key.

- <kbd>Left Super</kbd> launches a [custom dmenu script](bin/dwm_custom_dmenu)
  that shows the commands from your `~/.dmenu-path` file.

  `~/.dmenu-path` should be a file containing one command per line, like this:

        gedit
        gnome-terminal
        google-chrome
        google-chrome 'https://www.fastmail.com/calendar/'
        nautilus --no-desktop
        nautilus --no-desktop ~/Desktop
        gnome-terminal -e ipython

  This dmenu also appears from the bottom of the screen and uses dmenu's
  vertical layout. When some of the menu items are long this fits more items
  on screen at once and makes it easier to see where one item ends and the next
  begins.

  Most of the time I find it faster and easier to use a dmenu that contains
  only the commands that I use often, and this custom dmenu can also contain
  commands with arguments not just executables.

  When I need it, dwm's default dmenu that shows all executables on your path
  still works as well, although the keyboard shortcut has changed from
  <kbd>Alt+p</kbd> to <kbd>Left Super+p</kbd>.

  The cost of using dmenu like this is that you have to maintain the
  `/.dmenu-path` file yourself. If I find myself going to the default dmenu for
  a particular item frequently then I'll add it to the custom dmenu with a
  quick `echo something >> ~/.dmenu-path`.

  **Tip**: if a command is too long to read easily, or it's not obvious enough
  from the command itself what it does, then I write a one-line script that
  just calls this command, give the script a nice short filename, add it to my
  PATH, and append it to `~/.dmenu-path`. You can now use the script from the
  command line as well as from dmenu.


- Date and time, [volume](bin/dwm_volume), and
  [dropbox status](bin/dwm_dropbox_status) in dwm's status text area.

  This is done by a [dwm_status](bin/dwm_status) script.
  The [dwm_status_loop](bin/dwm_status_loop) script is called at startup
  (by [dwm_start](bin/dwm_start)) and it calls `dwm_status` once per minute.

  The reason for using a separate script to contain the loop is that you can
  edit `dwm_status` and the status area will begin using the new version without
  restarting dwm. You can also test your changes by running `dwm_status` manually
  to update the status area immediately instead of waiting until the minute is
  over.

  Even though `dwm_status_loop` only updates the status once per minute,
  other scripts can call `dwm_status` to update it immediately.
  For example `dwm_volume_up` does this to reflect volume changes in the status
  area immediately when you use it to change the volume.

- System notifications in dwm's status bar, using
  [dunst](https://github.com/knopwob/dunst), [configured](dunst/dunstrc) to
  match dwm's style.

- 12 tags instead of the default 9.

  <kbd>F1</kbd> - <kbd>F12</kbd> are used to change tags instead of the default
  <kbd>Alt+1</kbd> - <kbd>Alt+9</kbd>.

  The keyboard shortcut to select all tags at once (<kbd>Alt+0</kbd>) is
  removed (you can still do it by pressing
  <kbd>Alt+F1</kbd> - <kbd>Alt+F12</kbd> in sequence).

- Keyboard shortcuts use the <kbd>Left Super</kbd> (Windows) key instead of
  <kbd>Alt</kbd>.

  This prevents some keyboard shortcuts from clashing with application
  shortcuts. For example <kbd>Alt+b</kbd> opens the bookmarks menu in Firefox,
  <kbd>Alt+f</kbd> opens the file menu in many apps.

- Ignore size hints from windows - no gaps around tiled terminal windows.

- [dwm_start](bin/dwm_start) is called on login and launches Dropbox etc.


Installation
------------

These instructions have been tested on Ubuntu 16.04.1.


### Enable Software Sources

Enable the "Community-maintained free and open-source software (universe)"
and "Source code" software sources. There are checkboxes for these in Ubuntu
Software Center, for example. Or edit your `/etc/apt/sources.list` file.


### Install Packages

This installs the packages that are needed to compile dwm from source and the
fonts and helper programs that are used with dwm:

    sudo apt-get install git dmenu dunst xfonts-terminus libxft-dev
    sudo apt-get build-dep dwm


### Install My dwm Fork

    git clone 'https://github.com/seanh/dwm.git' ~/Projects/dwm
    cd ~/Projects/dwm
    sudo make clean install


### Link to the Dunst Config

    mkdir -p ~/.config
    ln -s ~/Projects/dwm/dunst ~/.config/dunst


### Add my dwm Executables to your PATH

Add [~/Projects/dwm/bin](bin) to your `PATH`:

    echo 'PATH="$HOME/Projects/dwm/bin:$PATH"' >> ~/.profile

I do mean edit `~/.profile` and not your bash, zsh or whatever startup file.
My scripts use `sh`.


### Add the Desktop Entry Specification

[~/Projects/dwm/dwm.desktop](dwm.desktop) is a Desktop Entry Specification file,
it's a copy of the `/usr/share/xsessions/dwm.desktop` file that ships with
the `dwm` Debian package. This is what adds the dwm option to your login
screen. You need to make a symlink to it:

    sudo ln -s ~/Projects/dwm/dwm.desktop /usr/share/xsessions/dwm.desktop


### Login to dwm

Logout, choose the dwm session from the login screen, login, and everything
should be working :)


Keyboard Shortcuts
------------------

<kbd>Right Super</kbd> launch the custom dmenu.

To add items to this menu add commands to `~/.dmenu-path`, one command per
line.

This can also be launched with <kbd>Left Super+o</kbd> (the key next to the
default dmenu keyboard shortcut) because not all keyboards have a
<kbd>Right Super</kbd> key.

<kbd>Left Super+p</kbd> launch the default dmenu

<kbd>F1-F12</kbd> go to tag 1-12

<kbd>Alt+F1-F12</kbd> toggle tag 1-12 into/out of view

<kbd>Left Super+F1-F12</kbd> move the focused window to tag 1-12

<kbd>Left Super+Alt+F1-F12</kbd> toggle tag 1-12 onto/off of the focused window

<kbd>Left Super+b</kbd> hide/show dwm's status bar

<kbd>Left Super+t</kbd> change to tiled layout

<kbd>Left Super+f</kbd> change to floating layout

<kbd>Left Super+m</kbd> change to monocle layout

<kbd>Left Super+Space</kbd> toggle between the current and previous layout

<kbd>Left Super+Shift+Space</kbd> toggle the focused window into and out of
floating mode

<kbd>Left Super+n</kbd> run the [dwm_terminal](bin/dwm_terminal) script
(by default: launches gnome-terminal).

<kbd>Left Super+Shift+Enter</kbd> launch dwm's default terminal
(`st`, note that you need to install st separately for this to work)

<kbd>Left Super+j</kbd> and <kbd>Left Super+k</kbd> move the focus to the
next/prev window

<kbd>Left Super+i</kbd> and <kbd>Left Super+d</kbd> increment and decrement
the number of windows in the  master area

<kbd>Left Super+h</kbd> and <kbd>Left Super+l</kbd> increase and decrease the
width of the master area

<kbd>Left Super+Enter</kbd> move the focused window into or out of the master
area

<kbd>Left Super+Tab</kbd> toggle between the current and previous views

<kbd>Left Super+Shift+c</kbd> close the focused window

<kbd>Left Super+Shift+q</kbd> quit dwm (logout)

<kbd>Left Super+,</kbd> focus the previous screen

<kbd>Left Super+.</kbd> focus the next screen

<kbd>Left Super+Shift+,</kbd> send the focused window to the previous screen

<kbd>Left Super+Shift+.</kbd> send the focused window to the next screen
