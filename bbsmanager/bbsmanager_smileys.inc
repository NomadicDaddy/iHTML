<iDEFAULT NAME="SmileyConv" VALUE="1">

<iIF EXPR=':SmileyConv' ALIAS="Converter">

  <iREM -- Converts ASCII Smileys to Image Tags -- >

  <iREPLACE VAR="body" SRC="}:(" DST="<IMG SRC='/images/adminware/smiley/smiley07.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

  <iREPLACE VAR="body" SRC=":-)" DST="<IMG SRC='/images/adminware/smiley/smiley01.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=";-)" DST="<IMG SRC='/images/adminware/smiley/smiley02.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":-P" DST="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":-p" DST="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":-O" DST="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":-o" DST="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC="8-)" DST="<IMG SRC='/images/adminware/smiley/smiley05.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":-(" DST="<IMG SRC='/images/adminware/smiley/smiley06.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

  <iREPLACE VAR="body" SRC=":)" DST="<IMG SRC='/images/adminware/smiley/smiley01.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=";)" DST="<IMG SRC='/images/adminware/smiley/smiley02.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

  <iREPLACE VAR="body" SRC=":P" DST="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":p" DST="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

  <iREPLACE VAR="body" SRC=":O" DST="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":o" DST="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

  <iREPLACE VAR="body" SRC="8)" DST="<IMG SRC='/images/adminware/smiley/smiley05.gif' WIDTH=15 HEIGHT=15 BORDER=0>">
  <iREPLACE VAR="body" SRC=":(" DST="<IMG SRC='/images/adminware/smiley/smiley06.gif' WIDTH=15 HEIGHT=15 BORDER=0>">

<iELSE ALIAS="Converter">

  <iREM -- Converts Image Tags to ASCII Smileys (for email) -- >

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley05.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST="8)">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley06.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":(">

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":O">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":o">

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":P">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":p">

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley01.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":)">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley02.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=";)">

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley01.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-)">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley02.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=";-)">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-P">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley03.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-p">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-O">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley04.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-o">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley05.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST="8-)">
  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley06.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST=":-(">

  <iREPLACE VAR="Body" SRC="<IMG SRC='/images/adminware/smiley/smiley07.gif' WIDTH=15 HEIGHT=15 BORDER=0>" DST="}:(">

</iIF ALIAS="Converter">
