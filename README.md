A machine that automatically winds copper coils to exact specifications.
Note you can find pics and a little video of the first winder in [pics/TheFirstWinder/](https://github.com/Rylangrayston/winder/tree/master/pics/TheFirstWinder).

There are lots of DIY coil winders out there, but this one is a bit different.

Originally built and coded by Rylan Grayston for the Peachy Printer project, which required the winding coils made of very fine (as small as 50 gage wire). Being that the wire is so fine, one cannot simply pull on it to unspool it; doing so would break it. The solution here is to motorize both the winding of the coil and the unwinding of the spool. The motors' speeds must be dynamically adjusted as to not break the very fine wire (finer than hair). Tension is set with a hanging mass and is very constant. The speed of the spool is governed by a variable resistor which senses when more wire is needed from the spool.

Another two variable resistors control the global speed of the whole winding process and the max speed of the spool coil. Lastly, a roller and an IR detector detect the amount of wire that has come off the spool, allowing the winder to stop at a predefined resistance, and print out in real-time the resistance of the coil as its being wound. 

How to use it:

Enter in the wire gage you're using and the desired resistance of your coil, then run the script. The script will cause the winder machine to automatically make the coil. Once complete, the script will print out all the info that it knows about the coil, including how many turns are in it!

Winder looks pretty ugly right now... but it works great!!

What is it made of:

```
code--> arduino--> stepper motor driver--> stepper motors--> spool
           |                                         |--> coil
           |<--varaibel risistor-more wire needed                                                                     
           |<-- variable resistor global speed
           |<--variable resistor-max spool speed
           |<-- IR sensor length of wire on coil
           |<--> computer runs code and prints info about the coil
```




In case winder isnt what you're looking for, here are some links to other coil winders. 

* [http://www.instructables.com/id/Coil-winder-with-automatic-counter/](http://www.instructables.com/id/Coil-winder-with-automatic-counter/)
* [http://youtu.be/1SwWuILlH4Q](http://youtu.be/1SwWuILlH4Q)
* [http://www.renovatedradios.com/articlePages/Winder2.pdf](http://www.renovatedradios.com/articlePages/Winder2.pdf)
* [http://www.theprojectasylum.com/electronicsprojects/automaticcoilwinder/automaticcoilwinder.html](http://www.theprojectasylum.com/electronicsprojects/automaticcoilwinder/automaticcoilwinder.html)
* [http://solomonsmusic.net/coil_winder.html](http://solomonsmusic.net/coil_winder.html)
* [http://www.thingiverse.com/thing:56493](http://www.thingiverse.com/thing:56493)




