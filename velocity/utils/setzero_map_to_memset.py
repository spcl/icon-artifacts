# Copyright 2019-2025 ETH Zurich and the DaCe authors. All rights reserved.
from typing import Any, Dict, Optional, Set
import warnings
import dace

@properties.make_properties
@transformation.explicit_cf_compatible
class SetZeroMapToMemset(ppl.Pass):
    def modifies(self) -> ppl.Modifies:
        return ppl.Modifies.AccessNodes | ppl.Modifies.Memlets | ppl.Modifies.Scopes

    def should_reapply(self, modified: ppl.Modifies) -> bool:
        return False

    def depends_on(self):
        return {}

    def apply_pass(self, sdfg: SDFG, pipeline_results: Dict[str, Any]) -> Optional[int]:
        # If a map is found that writes to an array
        pass