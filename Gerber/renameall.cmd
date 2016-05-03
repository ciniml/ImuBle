@ECHO OFF
SET TARGET=IMUBLE
MOVE /Y %TARGET%.drl           %TARGET%.txt
MOVE /Y %TARGET%-NPTH.drl      %TARGET%-NPTH.txt
MOVE /Y %TARGET%-F_Cu.gtl      %TARGET%.gtl
MOVE /Y %TARGET%-B_Cu.gbl      %TARGET%.gbl
MOVE /Y %TARGET%-F_Mask.gts    %TARGET%.gts
MOVE /Y %TARGET%-B_Mask.gbs    %TARGET%.gbs
MOVE /Y %TARGET%-F_SilkS.gto   %TARGET%.gto
MOVE /Y %TARGET%-B_SilkS.gbo   %TARGET%.gbo
MOVE /Y %TARGET%-Edge_Cuts.gm1 %TARGET%.gml

