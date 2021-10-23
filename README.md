# piston

Simple program to figure out best combination of two pvc pipes and o-rings to make a water piston with parts available at Home Depot.

I want to make a piston for a water pump. I need an two pvc pipes and some o-rings. The inside pipe is called the piston. The outside pipe is called the shell. The piston has to fit inside the shell.
The o-ring has to fit inside the shell. The o-ring can't be too small or water will squeeze past it. It can't be too big for the shell either or it will deform. The o-ring has to fit over the piston but it can only stretch so much. The piston will have a trough cut into it in which the o-ring will sit. The o-ring can't be any less than half-buried in the piston or it will be pulled out. The piston can't be cut any deeper than half its thickness to make sure it doesn't break. The piston can't be as wide as the o-ring or the o-ring won't contact the shell.

I made a list of every rubber o-ring available on the Home Depot website. I did the same thing with all their pvc pipes.

This program finds combos of all the pipes and o-rings to find the ones that best fit each other. It starts with an error tolerance of zero and if no solutions are found, it'll allow an error tolerance that's a little higher. When solutions are found, with a particular error tolerance, we're done.
