/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Project 5
*/

FEATURES THAT WORK:

    Program is able to work with both the regular AND human-readable forms for the JSON input. To start, "main.cpp" uses
the compressed form for JSON input. User should run "make" and then "make run" to execute the program. A master output
HTML file called "artists.html" will be created displaying first the artist's name, their picture (if any), their profile
information, and then each of the albums and the album's picture (if any). Under each album, it will display the album's
tracks. It will also add each album's html output into the directory "html_albums". The files are named after the album's
id and .html at the end (ex: "12345.html").

    Then "make clean" can be ran to remove "artists.html" and other files. It does not remove the album files from
"html_albums", so if the user wants to check whether or not the human_readable forms create the same output, they will
have to first remove everything inside "html_albums" directory. The user can then edit "main.cpp" and use the
human readable forms by just editing the file names for each entity (ex: "./artists.json" -> "./artists_human_readable.json").
After that, run "make" and then "make run" and the same master HTML output will be created along with each album in "html_albums".


FEATURES THAT DO NOT WORK:

    HTML output is fine but is bland and is just plain old looking HTML.

POSSIBLE BUGS:

    Multiple albums look similar but each has its own unique "album_id" so they are technically different. On my mac, I
transferred the hmtl files using FileZilla onto my desktop, however when I tried to open with Chrome it would not work.
I then opened it with Safari and it worked perfectly. I am not sure what the issue is, pretty sure it is just my machine.
But if for some reason it does happen, you can check the contents of the HTML file in any text editor and see that it in
fact does produce the html output. It was working with google chrome and any other browser a while ago, like late November.
It works if I open google chrome, then on top menu bar, select: file -> Open File -> theHtmlFile.html .
