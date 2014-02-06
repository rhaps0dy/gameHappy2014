Description
===========

You jump around controlling RMS. The game features a level editor
for making your levels. Originally it was written in a couple days
as a gift to my cousin and it had his face (it's still buried in old
commits), and wished him Happy 2014.

Building
========

Just type 'make'. Make sure you have SDL, SDL\_image
and SDL\_mixer.

You can type 'make windows' to cross-compile for Windows.

If on FreeBSD, type 'make freebsd'.

Playing
=======

Use the arrow keys to jump and move

Level Editor
============

Create a vector graphics file with rectangles. Change directory
to 'resources', and run the 'feslevel.py' script like this:

```
python3.3 feslevel.py <path-to-svg-file>
```

the 'level' file will be updated with the geometry of the level
you made. Now you can play on it!
