# Simultation-of-Memory-Management

A program simulating the behaviour of a memory management system based on real reference traces. We simulate two virtual processes which are reading line by line the reference traces from their respective file.

The virtual memory is being built based on an inverted page table. When each virtual process reaches k + 1 page faults, a page replacement algorithm is used, specifically the FWF (Flush When Full) algorithm. 

All pages and frames have a size of 4 KB (4096 bytes). Events such as Page Faults, 
reading/writing from/to disk etc. are recorded and printed at the end of 
the program as statistics.
- - -
Makefile is used to compile the program.


Type `make` to compile and create the executable.

# Parameters and Running
Run with `./main -k <maxPF> -frames <#framesOfIPT> -q <quantum> -max <maxReferences>`

`-k`: the maximum number of page faults per virtual process before FWF (Flush When Full) algorithm is called

`-frames`: the number of frames the inverted page table should have (must be > 2*k)

`-q`: the "Round-robin (RR)" quantum

`-max`: the maximum number of references to read from the files

# Running Examples

![Example 1](https://1ksiqg.by3302.livefilestore.com/y3msFBr8PuigPXq6SWMYcR4GyZUiKbnT7MGb034508GlvgqtARlt4ZBfqoSPH68zmUbB-p8ZGKQ5Sj3x6DVCdulYwkHd6F9kJ8TbtPlSkU0YvdZFRFuS4ELabfxoj3ewWycE7-scPTGoZFaf6hovQ1o__FI9VnsPEUcUU1p0Ujh15I?width=821&height=216&cropmode=none)
![Example 2](https://1kuo4q.by3302.livefilestore.com/y3m9ooW3wSSsmcJwSaAqY-rmx5FrlUMCni89Zpe5yc88KpfvDtd8l4a8UWF7jwwBx4E6_V-c2-QcrUilFbGx9jS3UxLBbKTGP-BOGl1mjQ9102ZUpH7CjZnPPrSiUti1FaEf04c25LKkE7zMrJrgc1mFO3YQxrIJFIAcMTn-4MU7SE?width=821&height=157&cropmode=none)
![Example 3](https://1kspvg.by3302.livefilestore.com/y3moTVslh2gOcAEaXBwG8msL-9PwjTYQdulFKYoLdVwmWvM-3riVG9x5s60uQuYfwS6aiWI-QMuQgrgct43Cie9XtCtnb32a9KNrzywVUqNgyyQrbbqN85ueApWMSdswKADz5umXxp6mgzP3wTFLLf5KKKWifh0tXWMY-NWGcp_LKQ?width=821&height=157&cropmode=none)
![Example 4](https://1kspvg.by3302.livefilestore.com/y3moTVslh2gOcAEaXBwG8msL-9PwjTYQdulFKYoLdVwmWvM-3riVG9x5s60uQuYfwS6aiWI-QMuQgrgct43Cie9XtCtnb32a9KNrzywVUqNgyyQrbbqN85ueApWMSdswKADz5umXxp6mgzP3wTFLLf5KKKWifh0tXWMY-NWGcp_LKQ?width=821&height=157&cropmode=none)
