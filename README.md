# Simultation-of-Memory-Management
- - -
A program simulating the behavior of a memory management system based on real reference traces. We simulate two virtual processes which are reading line by line the reference traces from their respective file.

The virtual memory is being built based on an inverted page table. When each virtual process reaches k + 1 page faults, a page replacement algorithm is used, specifically the FWF (Flush When Full) algorithm. 

All pages and frames have a size of 4 KB (4096 bytes). Events such as Page Faults, 
reading/writing from/to disk etc. are recorded and printed at the end of 
the program as statistics.
- - -
Makefile is used to compile the program.


Type `make` to compile and create the executable.

#Parameters and Running
Run with `./main -k <maxPF> -frames <#framesOfIPT> -q <quantum> -max <maxReferences>`

`-k`: the maximum number of page faults per virtual process before FWF (Flush When Full) algorithm is called

`-frames`: the number of frames the inverted page table should have (must be > 2*k)

`-q`: the "Round-robin (RR)" quantum

`-max`: the maximum number of references to read from the files
