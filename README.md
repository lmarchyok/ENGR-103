# ENGR-103

LIGHT GAME

- Inputs: Button A, Button B
- Outputs: Sound outputs, Light outputs

Game details:

User must input correct sequence of A and B button presses, corresponding with the color pattern shown in the sequence of lights on the circuitboard. There are three levels, which increase in difficulty by giving the user an increasingly short window of time to view the pattern before they must input it. 
Each level first announces the level using text to speech, then displays the pattern, then waits for 10 left or right button presses before displaying level and total running score, before moving on to the next. At the end of level 3, the user is greeted with a choice to play again, or terminate the program. 
Level score is calculated by number of correct buttons pressed out of ten divided by ten, multiplied by 20000 divided by the time taken to reach 10 button presses in milliseconds, all multiplied by constant of 100. Total score over all levels currently passed is tracked as well.
