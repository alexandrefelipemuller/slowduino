                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 4.2.0 #13081 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module globals
                              6 	.optsdcc -mhc08
                              7 	
                              8 	.area HOME    (CODE)
                              9 	.area GSINIT0 (CODE)
                             10 	.area GSINIT  (CODE)
                             11 	.area GSFINAL (CODE)
                             12 	.area CSEG    (CODE)
                             13 	.area XINIT   (CODE)
                             14 	.area CONST   (CODE)
                             15 	.area DSEG    (PAG)
                             16 	.area OSEG    (PAG, OVR)
                             17 	.area XSEG
                             18 	.area XISEG
                             19 ;--------------------------------------------------------
                             20 ; Public variables in this module
                             21 ;--------------------------------------------------------
                             22 	.globl _configPage2
                             23 	.globl _configPage1
                             24 	.globl _currentStatus
                             25 ;--------------------------------------------------------
                             26 ; ram data
                             27 ;--------------------------------------------------------
                             28 	.area DSEG    (PAG)
                             29 ;--------------------------------------------------------
                             30 ; overlayable items in ram
                             31 ;--------------------------------------------------------
                             32 ;--------------------------------------------------------
                             33 ; absolute ram data
                             34 ;--------------------------------------------------------
                             35 	.area IABS    (ABS)
                             36 	.area IABS    (ABS)
                             37 ;--------------------------------------------------------
                             38 ; absolute external ram data
                             39 ;--------------------------------------------------------
                             40 	.area XABS    (ABS)
                             41 ;--------------------------------------------------------
                             42 ; external initialized ram data
                             43 ;--------------------------------------------------------
                             44 	.area XISEG
                             45 ;--------------------------------------------------------
                             46 ; extended address mode data
                             47 ;--------------------------------------------------------
                             48 	.area XSEG
   00BA                      49 _currentStatus::
   00BA                      50 	.ds 61
   00F7                      51 _configPage1::
   00F7                      52 	.ds 34
   0119                      53 _configPage2::
   0119                      54 	.ds 64
                             55 ;--------------------------------------------------------
                             56 ; global & static initialisations
                             57 ;--------------------------------------------------------
                             58 	.area HOME    (CODE)
                             59 	.area GSINIT  (CODE)
                             60 	.area GSFINAL (CODE)
                             61 	.area GSINIT  (CODE)
                             62 ;--------------------------------------------------------
                             63 ; Home
                             64 ;--------------------------------------------------------
                             65 	.area HOME    (CODE)
                             66 	.area HOME    (CODE)
                             67 ;--------------------------------------------------------
                             68 ; code
                             69 ;--------------------------------------------------------
                             70 	.area CSEG    (CODE)
                             71 	.area CSEG    (CODE)
                             72 	.area CONST   (CODE)
                             73 	.area XINIT   (CODE)
                             74 	.area CABS    (ABS,CODE)
