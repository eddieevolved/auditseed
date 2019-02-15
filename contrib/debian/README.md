
Debian
====================
This directory contains files used to package seedd/seed-qt
for Debian-based Linux systems. If you compile seedd/seed-qt yourself, there are some useful files here.

## seed: URI support ##


seed-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install seed-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your seedqt binary to `/usr/bin`
and the `../../share/pixmaps/seed128.png` to `/usr/share/pixmaps`

seed-qt.protocol (KDE)

