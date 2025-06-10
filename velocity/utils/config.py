use_cache = True
instrument = False
cleanup = False
reduction = True
import os
_release =  os.getenv("RELEASE")
assert _release == "TRUE" or _release == "FALSE" or _release is None, "RELEASE environment variable must be set to TRUE or FALSE, or not set at all."
release = _release == "TRUE"
verbose = False
tile = False
remainder_loop = False
fix_out_val_0 = False
layout_transform = False
rm_syncs = True