#!bin/bash/

VAR1=/lhcb/LHCb/Collision11/SEMILEPTONIC.DST/00041838/0000/00041838_00000631_1.semileptonic.dst

lhcb-proxy-init
SetupLHCbDirac
dirac-dms-get-file $VAR1

