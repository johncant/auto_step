<h1>An pulseaudio + GNU autotools example.</h1>
<p>This is an example of autotools, combined with an example of pulseaudio's simple API</p>
<h2>Demo for simple GNU autotools usage</h2>
<p>The GNU autotools look really intimidating, but are more straightforward than they look at first. I've done my best to document how I generated this repo. You might as well use them to help other people compile your code.</p>
<p>Generated autotools installation with acmkdir according to autotools manual. On Ubuntu 12.10 I had to install the autotoolset from source. Required shar-utils pkg. This project requires the headers for pulseaudio.</p>
<p>Modified files used in autotools demo:</p>
<pre>
# Used by automake
Makefile.am
configure.ac
src/Makefile.am

# Admin - You don't need to edit these, but they should be used for admin
NEWS
README.in
README
THANKS
AUTHORS
ChangeLog # I guess you'd create this from `git log` if the project got serious
README.md # This file

# Code
src/auto\_step.cc
</pre>
<p>To regenerate the ./configure script after changing one of the Makefile.am(s) or configure.ac, execute `./reconf`. The project should now be ready for use (i.e. build with `./configure` then `make`)</p>


<h2>Demo for pulseaudio simple API</h2>

<p>pa\_simple = connection to pulseaudio server.</p>

<p>PA\_SAMPLE\_S16NE = Flag which makes the server accept an array of signed 16 bit integers. NE = native endian, so you don't need to worry about endianness (fine if you only need local sound)</p>

<p>The rate of 44100Hz literally means "play a sample 41000 times a second."</p>

<p>Take a look in src/auto\_step.cc . It plays a 2 second long sine wave at 440 Hz.</p>
