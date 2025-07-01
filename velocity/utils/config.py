use_cache = True
instrument = False
cleanup = False
reduction = True
import os
release = os.getenv('_RELEASE', '0').lower() in ('1', 'true', 'yes')
verbose = False
tile = False
remainder_loop = False
fix_out_val_0 = False
layout_transform = False
rm_syncs = True