# Ticket To Ride Path Finder

As a project for my Algorithms class, I decided to make a program that would find the shortest path between any two stations in the Ticket To Ride board game.  Not only does the program find the shortest path for you, it will also tell you how many and what colors you will need in order to link the different stations together.  

Here is what the [United States](https://cf.geekdo-images.com/images/pic38674.jpg) board game looks like.

###Compiling and Running.

In order to run the program simply clone the repository to your system and compile the source code.

  `gcc Dijkstra.c`
  
The program will use `US_Colors.csv`, `US_Station_Names.csv`, and `US_Weights.csv`.  Make sure to keep these in the same directory as the executable (or change the paths to them in the source code if you choose to move them).

###Adding New Boards.

Ticket To Ride has expansions that include other boards to play on.  If you want to create new `.csv` files of these boards, I included in the repository the Excel spreadsheet used to make the United States `.csv` files.  When I created the files for the United States board I listed the stations in alphabetical order and that is also how they are represented in the Weights and Colors `.csv`.  Make sure to keep these consistent. 

If you do make files for the other boards please let me know!  I would love to include them in the repo.
