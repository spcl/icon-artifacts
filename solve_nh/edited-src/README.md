A snapshot of the "fake" `solve_nh` that is:
- Built on the AST at some convenient stage in the fparser pipeline (without function signature changes).
- Self contained with renamed module.
- Types that matter for the interfaces are put back from the original.
- Numerically validated (w.r.t. the output files present in the snapshot for step 1 and 9).
- Has the supporting serializaiton module files (i.e., serde.f90 and ti.f90).
- Has the supporting changes in the original file to route the call to the fake.
- The fake itself is cut into 5 pieces that works around the MPI calls.
