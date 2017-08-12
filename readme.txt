~~~~~~~~~~~~~~~~~~~~
Artifical Intelligence Project
~~~~~~~~~~~~~~~~~~~~
=======================================================================================================================================================
1. HOW TO START THE GAME
------------------------
- Run the .exes in the AI Project folder.
- To compile, open the Bootstrap.sln and set the start-up project to 2017_07_17_AIPractise_stoy
	- There is a limitation of Bootstrap which is that it may not compile if the total directory length is too long. To avoid this, drag the Bootstrap
	folder to something more direct like C:/Bootstrap.
        - Occasionally it may throw up a MSVCRT default lib error OR insufficient permissions to write this file, to fix this rebuild the solution.

=======================================================================================================================================================
2. GAME FEATURES
----------------
- NPCs use 3 different Decision Making Techniques that use custom classes and structures:
	- Each NPC uses a Finite State Machine to transition between states. 
	startup and shutdown multiple behavioural states, as well as transition between behaviours via external logic within the NPC.
	- Each NPC interfaces with a Blackboard in order to determine the best course of action for the current frame.
	- Utility AI decision making for the states, each state has a utility score and every update the best state will be set by the NPC's Finite State Machine.

- A* grid path-finding that allows for custom lambdas to be passed in to calculate the H score
	- Ability for multiple NPCs to plan out and follow paths with minimal lag.

- 5 Steering Behaviours used by NPCs
	- Seek/Flee
	- Follow Path
	- Wander
	- Collision Avoidance against circles, rectangles and triangles.
	- Arrival

- Steering forces are scaled with automatic weighted combination, a factor determined by the scale of all other active behaviours.


NOT DONE:
- Multiple steering behaviours working in unison that take into account weight calculations
- Multiple entities that use path-finding on the grid at the same time (nav-mesh at this point is highly unlikely), and that doesn't run ungodly slow.

=======================================================================================================================================================
3. REPOSITORY LINKS
--------------------
AI Project: https://github.com/DarthDementous/Bootstrap_AI_Practise
=======================================================================================================================================================