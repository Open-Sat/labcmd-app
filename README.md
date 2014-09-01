labcmd-app
==========

Command ingest application designed for lab environments using UDP

This is non-flight code intended for use in a prototype or lab environment. This app receives
commands over a UDP port and sends the commands on teh software bus. This application follows
the object-based application design pattern.  

It currently uses the expat XML parser.  Using expat is an exploritory exercise first in using
text-based tables that are managed by the applications themselves and second using XML as the
format.
