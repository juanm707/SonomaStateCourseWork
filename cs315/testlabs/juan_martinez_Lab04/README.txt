/*

  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 4
  
*/

FEATURES THAT WORK:

	 So in my Lab 04 directory, I have two other directories. One for the "tennis.cpp" file Dr. Kooshesh gave us called "Non_Object_Oriented"
and that one has a Makefile to use his program. The other directory is "Object_Oriented" which stores the object oriented portion of the lab.
It has a Makefile that was provided to us. I included two directories so the user can compare the output from both programs. The outputs are/should be the same
but just incase the user wanted to check I added them.

	 My output is the same or very similar to Dr. Kooshesh's output from "tennis.cpp". If I use the same seed
and probabilities that I would use on "tennis.cpp" on the Object Oriented part of this lab, the output is the same. It outputs the tie breaker,
if any, and the set numbers, and each score, and at the end it outputs which player won by how many sets.

FEATURES THAT DO NOT WORK:

	 I am not sure what does not work. I know putting probabilities 0 for both players causes an infinite loop or seg fault.
Other than that, I do not know any issues.

POSSIBLE BUGS:

	 I do not know of any possible bugs. Sometimes in the tie breaker, the scores are more than 10, sometimes 20, which makes sense
since to win you need at least 7 points and be ahead by two, so really it can go on for a long time.
