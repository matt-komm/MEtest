ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c      written by the UFO converter
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

C     Parameters that should not be recomputed event by event.
C     
      IF(READLHA) THEN

        G = 2 * DSQRT(AS*PI)  ! for the first init

        CONJG__CKM1X1 = 1.000000D+00

        CONJG__CKM3X3 = 1.000000D+00

        CKM3X3 = 1.000000D+00

        COMPLEXI = (0.000000D+00,1.000000D+00)

        MZ__EXP__2 = MZ**2

        MZ__EXP__4 = MZ**4

        SQRT__2 = SQRT(2.000000D+00)

        MH__EXP__2 = MH**2

        AEW = 1.000000D+00/AEWM1

        MW = SQRT(MZ__EXP__2/2.000000D+00+SQRT(MZ__EXP__4/4.000000D
     $   +00-(AEW*PI*MZ__EXP__2)/(GF*SQRT__2)))

        SQRT__AEW = SQRT(AEW)

        EE = 2.000000D+00*SQRT__AEW*SQRT(PI)

        MW__EXP__2 = MW**2

        SW2 = 1.000000D+00-MW__EXP__2/MZ__EXP__2

        CW = SQRT(1.000000D+00-SW2)

        SQRT__SW2 = SQRT(SW2)

        SW = SQRT__SW2

        G1 = EE/CW

        GW = EE/SW

        VEV = (2.000000D+00*MW*SW)/EE

        VEV__EXP__2 = VEV**2

        LAM = MH__EXP__2/(2.000000D+00*VEV__EXP__2)

        YB = (YMB*SQRT__2)/VEV

        YT = (YMT*SQRT__2)/VEV

        YTAU = (YMTAU*SQRT__2)/VEV

        MUH = SQRT(LAM*VEV__EXP__2)

        I1X33 = YB*CONJG__CKM3X3

        I2X33 = YT*CONJG__CKM3X3

        I3X33 = CKM3X3*YT

        I4X33 = CKM3X3*YB

        EE__EXP__2 = EE**2

        SW__EXP__2 = SW**2

        CW__EXP__2 = CW**2

      ENDIF
C     
C     Parameters that should be recomputed at an event by even basis.
C     
      AS = G**2/4/PI

      SQRT__AS = SQRT(AS)

      G__EXP__2 = G**2

C     
C     Definition of the EW coupling used in the write out of aqed
C     
      GAL(1) = 3.5449077018110318 / DSQRT(AEWM1)
      GAL(2) = 1D0

