Author: Juan Martinez
Course: CS 315
Assignment: Project 3

READ ME

WHAT IS IMPLEMENTED: I was able to implement the FCFS, STRACK, CLOOK, LOOK, PICKUP Queues and the FCFS, CLOOK, LOOK Disks.
     - QUEUES
		The user runs "make" and then must add an output file like so "./type_queue.x < inputFile.txt > outputFile.txt".
Otherwise it will output to the screen. There is already an input file provided but user can add one if they like.
"make clean" gets rid of the usual and the output file. The last request might be seen double because of a bug later explained in BUGS.

      - DISKS
		The user runs "make" and redirects and input file. There is already one provided but user can make their own.
After running the executable, two output files are created: One for the regualr disk report "TYPE_output.txt" and "TYPE_summary.txt".
Numbers might be off by a little since the bug about duplicates.

BUGS: So I had everything work in CLION app on my lap top. I ran strack disk on blue but I kept getting seg fault so I did not include
it in the directory. Some disks have the last request duplicated because, my guess, of std::cin. The queues had duplicates as well
when I just used while (!std::cin.eof()) but I later changed to ( while cin >> time ) and no more duplicates. So im guessing its an issue
with cin or input. The input file must not have a new line after last entry either. 
