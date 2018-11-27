# Spin to Win

This project is for a conference I'm hosting a booth for. I have a trivia game I've created, and I've built an LED matrix with
some controls as a way for the user to select categories and win prizes.

I've done a live stream for the creation of this project from beginning to end, that can be found here [https://www.youtube.com/watch?v=JJy1pkgHZBc&list=PLz6ht8wE2VSujYsN-sqULnGspK5Ppp12D]()

The project consists of:
- a 8 * 20 matrix of ws2818b led's
- 2 60mm big dome LED's with 1NC1NO switches
- 2 1k potentiometers
- AC to DC regulated power supply (5v up to 30A)
- microcontroller (teensy 3.6 or Arduino Due)

### YouTube Videos

I live streamed most of this build.  The video of the completed animation and controls can be found here: https://www.youtube.com/watch?v=JsFyjuAizuk

For the complete build check out my [#HHHWorkshop playlist](https://www.youtube.com/playlist?list=PLz6ht8wE2VSujYsN-sqULnGspK5Ppp12D)

### Pin Information

In a 8 strip matrix, with strips having pixel 1 on the far right, and the first strip being at the top.

To verify the strip order, run the `src/id_strips.cpp` sketch.

```
# teensy 3.6 pins (Using Teensy Port Manipulation, PORT D)

Pin 2  - strip 1
Pin 14 - strip 2
Pin 7  - strip 3
Pin 8  - strip 4
Pin 6  - strip 5
Pin 20 - strip 6
Pin 21 - strip 7
Pin 5  - strip 8

# Arduino Due (Using Port Manipulation, PORT D)
Pin 25  - strip 1
Pin 26 - strip 2
Pin 27  - strip 3
Pin 28  - strip 4
Pin 14  - strip 5
Pin 15 - strip 6
Pin 29 - strip 7
Pin 11  - strip 8
```
