# Snake-with-arduino-on-a-VGA-screen
a simple version of the game snake, programmed on an arduino mega and displayed on a monitor that supports a VGA connection

# disclaimer
for this code to work you need to have installed the library VGAX by sandro maffiodo https://github.com/smaffer/vgax
and use at least an arduino mega in terms of memory

# credits
Sandro Maffiodo VGAX library 
https://github.com/smaffer/vgax

# info 
you can find the connection schemes and info on how to use the VGA into the link above
this version does not present a victory or defeat screen, it just restarts again once you either touch the tail or a wall;
this version also presents a lot of delay in the imput registrations as i think the way i structured the game does not let me 
use a millis function because i need to use the integrated function VGA.delay to let arduino focus on the visualization on 
the screen, as arduino does not read lines of code and simultaneusly draws pixels onto screen,but i was pretty lazy in the 
optimization as my goal was learning how to use the VGA for another project.

to play it you simply need 4 esternally connected buttons of some sort and a VGA compatible screen;

# working principle

this program works by memorizing the coordinates on screen of the points where the snake changed direction, and then 
cancelling everything from the tail to it; in the meantime every cicle a new pixel, which is the head pixel, appears in the 
direction the snake was mooving, giving the idea of motion;
i had to do this because for some reason by putting a decent size matrix inside of the function vga.draw(); completely filled the memory 
i choose a pretty slow slithering pace, but to make the game faster just reduce the delays scattered in the code.





