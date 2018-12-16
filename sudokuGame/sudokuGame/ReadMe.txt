========================================================================
    CONSOLE APPLICATION : sudokuGame Project Overview
========================================================================


/////////////////////////////////////////////////////////////////////////////
Group Members: Kevin Harlley

For my solution I created a sudoku class that would gain objects from the 
last saved solution if there was one. If there was no saved game available
the game would randomly initialize a number of valid numbers according to
the value of the variable initialNumbers.
When implementing my code and testing for errors I realized that the game
 was not producing truly random numbers as they were just getting repeated. 
 I realized this was I was using rand incorrectly.
After fixing this it was initially hard to input variables because they would 
not allow the appropriate game pieces to be initialized.