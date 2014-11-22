This file implements an algorithm possibly linked to the patent
SURF.
This file is made available for the exclusive aim of serving as
scientific tool to verify the soundness and completeness of the
algorithm description. Compilation, execution and redistribution
of this file may violate patents rights in certain countries.
The situation being different for every country and changing
over time, it is your responsibility to determine which patent
rights restrictions apply to you before you compile, use,
modify, or redistribute this file. A patent lawyer is qualified
to make this determination.
If and only if they don't conflict with any patent terms, you
can benefit from the following license terms attached to this
file.

This program is provided for research and education only: you can
use and/or modify it for these purposes, but you are not allowed
to redistribute this work or derivative works in source or
executable form. A license must be obtained from the patent right
holders for any other use.


SURF for IPOL

This software is divided into 3 bins that can compute SURF descriptors, SURF matches and display them on images.

The article reference can be found on IPOL.

Last update: —— (3rd release)
Main changes:
* normalization of the Hessian
* cleaner code
* bin file is separated into 3 files

1) Compilation
Do make in command line.

2) Usage
Cd in /bin folder. For detecting keypoints:

extract_surf ../examples/gobelet.png k1.txt
extract_surf ../examples/gobelet2.png k1.txt

For matching:

match_surf k1.txt k2.txt matches.txt

And for display:

display_surf k1.txt k2.txt matches.txt ../examples/gobelet.png ../examples/gobelet2.png descriptor.png matches.png

3) Copyrights

ORSA has not to be reviewed. ORSA and libMatch are not production of the author. If you are the owner and want your copyright to appear, please send us an email.

4) Contact
If you see any bugs or have any comments, please send an email to the authors.

Authors :
E Oyallon edouard.oyallon@ens.fr
J Rabin julien.rabin@unicaen.fr