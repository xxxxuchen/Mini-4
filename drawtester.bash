#!/bin/bash
echo " "
echo -e ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
echo -e "...Start Testing..........and Drawing Some Nice Figures............\n"
echo -e ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"

if [[ ! -f asciidraw.c ]]
then
	echo "Error cannot locate asciidraw.c"
	exit 1
fi

gcc -o asciidraw asciidraw.c -lm
rc=$?

if [[ $rc -ne 0 ]]
then
	echo "There were errors/warnings from gcc. rc = $rc"
	exit $rc
fi

echo " --- test case 0 >> test the loop of accepting commands and wrong usages (invalid commands) --- "
echo '
./asciidraw <<ENDOFCMDS
LINE 10,20 25,30
DISPLAY
CHA $
GRID 40 30
LINE 10,20 25,30
GRID 20 20
LIN 10,20 25,30
CIR 10,10 5
CHA #
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
LINE 10,20 25,30
DISPLAY
CHA $
GRID 40 30
LINE 10,20 25,30
GRID 20 20
LIN 10,20 25,30
CIR 10,10 5
CHA #
END
ENDOFCMDS

echo " --- test case 1 >> test DISPLAY command, checking initial status of canvas and number indexing --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 14 22
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 14 22
DISPLAY
END
ENDOFCMDS

echo " --- test case 2 >> draw simple lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 15,20
CHAR @
LINE 1,1 18,5
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 15,20
CHAR @
LINE 1,1 18,5
DISPLAY
END
ENDOFCMDS

echo " --- test case 3 >> draw simple lines and test different orders of coordinates (x1 > x2 or x1 < x2,etc.)--- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 25,30 10,20
CHAR +
LINE 10,20 5,30
CHAR &
LINE 10,20 20,5
CHAR @
LINE 0,5 10,20
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 25,30 10,20
CHAR +
LINE 10,20 5,30
CHAR &
LINE 10,20 20,5
CHAR @
LINE 0,5 10,20
DISPLAY
END
ENDOFCMDS

echo " --- test case 4 >> draw vertical lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,5 10,30
CHAR +
LINE 20,10 20,2
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,5 10,30
CHAR +
LINE 20,10 20,2
DISPLAY
END
ENDOFCMDS

echo " --- test case 5 >> draw horizontal lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,15 30,15
CHAR +
LINE 25,30 5,30
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,15 30,15
CHAR +
LINE 25,30 5,30
DISPLAY
END
ENDOFCMDS

echo " --- test case 6 >> draw simple rectangles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
RECTANGLE 2,7 8,3
CHAR #
RECTANGLE 5,20 20,10
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
RECTANGLE 2,7 8,3
CHAR #
RECTANGLE 5,20 20,10
DISPLAY
END
ENDOFCMDS

echo " --- test case 7 >> draw simple circles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
CIRCLE 20,20 6
CHAR @
CIRCLE 15,15 10
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 50
CIRCLE 20,20 6
CHAR @
CIRCLE 15,15 10
DISPLAY
END
ENDOFCMDS

echo " --- test case 8 >> draw truncating lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 1,1 10,60
CHAR #
LINE 15,20 90,20
CHAR &
LINE 39,25 39,50
CHAR +
LINE 30,5 100,5
LINE 100,100 200,200
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 1,1 10,60
CHAR #
LINE 15,20 90,20
CHAR &
LINE 39,25 39,50
CHAR +
LINE 30,5 100,5
LINE 100,100 200,200
DISPLAY
END
ENDOFCMDS

echo " --- test case 9 >> draw truncating rectangles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 25,45 30,35
RECTANGLE 35,10 50,5
RECTANGLE 4000,3000 4500,2500
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 25,45 30,35
RECTANGLE 35,10 50,5
RECTANGLE 4000,3000 4500,2500
DISPLAY
END
ENDOFCMDS

echo " --- test case 10 >> draw truncating circles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
CIRCLE 0,0 10
CHAR @
CIRCLE 35,20 6
CHAR &
CIRCLE 25,35 7
CHAR #
CIRCLE 3,10 5
CIRCLE 4000,3000 4500,2500
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 40
CIRCLE 0,0 10
CHAR @
CIRCLE 35,20 6
CHAR &
CIRCLE 25,35 7
CHAR #
CIRCLE 3,10 5
CIRCLE 4000,3000 5
DISPLAY
END
ENDOFCMDS

echo " --- test case 11 >> draw multiple shapes, switching characters, etc --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS

