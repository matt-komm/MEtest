      SUBROUTINE initmatrix()
      	
      INCLUDE "coupl.inc"
      INCLUDE "nexternal.inc" 
      REAL*8 PMASS(NEXTERNAL)
      INCLUDE "ngraphs.inc"
    
      call setpara('param_card.dat')
      include "pmass.inc"
      
      end
      
