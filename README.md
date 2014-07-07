devmgmt
=======

C++ ONVIF device discovery client.

Shell-based program for discovering ONVIF-compatible devices via service bradcast.  
Every discovered deviced is queried for its service URI and its stream URIs, if a username and password for the device is supplied.
Currently, all communication is done by traversing and concatenating prepared XML files, wich are wrapped and sent via boost sockets.

##Getting started

You will need QT Creator and the C++ boost libs installed for successful compilation of this project.
