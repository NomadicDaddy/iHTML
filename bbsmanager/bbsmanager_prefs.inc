<iIF COND=<iSTRCMP SRC=":go" DST="set"> ALIAS="SetPrefs">

  <iSET PrefString=":Bit1:Bit2:Bit3:Bit4:Bit5">

  <iREM -- Escape Quotes/Convert Returns in Signature -- >
  <iREPLACE VAR="NewSignature" SRC=":i$crlf" DST="<BR>"><iSET Signature=":NewSignature"><iREPLACE VAR="NewSignature" SRC="'" DST="''">

  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT ID FROM _Members :IfSQL WHERE :EID = :EIDQual:bbs_un:EIDQual ;" ESC=FALSE OUTPUT="0" NOOUTPUT="1" FAILURE="1" OUTVAR="CreateIt">
  <iIF EXPR=':CreateIt' ALIAS="CreateMember">
    <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="INSERT INTO _Members (:EID, Privs, Prefs, Signature) VALUES (:EIDQual:bbs_un:EIDQual, ':PrivString', ':PrefString', ':NewSignature') ;" ESC=FALSE FAILURE="ERROR: :i_sqlerrortext" OUTVAR="msg">
  <iELSE ALIAS="CreateMember">
    <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="UPDATE _Members SET Prefs=':PrefString', Signature=':NewSignature' WHERE :EID = :EIDQual:bbs_un:EIDQual ;" ESC=FALSE NOOUTPUT="Your preferences have been saved." FAILURE="ERROR: :i_sqlerrortext" OUTVAR="msg">
  </iIF ALIAS="CreateMember">
  <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
</iIF ALIAS="SetPrefs">

<CENTER><BR><TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
  <FORM METHOD=POST ACTION=':i_script_name'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un"><INPUT TYPE=HIDDEN NAME="go" VALUE="set">

  <TR><TD COLSPAN=2><B><U>Your Thread Viewing Defaults</U></B></TD></TR>

  <TR><TD>Range of Messages to Show</TD>
      <TD><SELECT NAME="Bit1">
        <iSTRSPAN SRC=":PrefString" FIRST=1 NUM=1 OUTVAR="Bit1">
        <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT ID, Description FROM _Ages :IfSQL ORDER BY Age ;" ALIAS="Ages"><iSQLFETCH ALIAS="Ages">
          <iWHILE NOTALIAS=i_sqlempty>
            <OPTION VALUE=":Ages_ID" <iIF EXPR=':Bit1 = :Ages_ID'>SELECTED</iIF>>Show :Ages_Description</OPTION>
            <iSQLFETCH ALIAS="Ages">
          </iWHILE ALIAS=i_sqlempty>
        </iSQL ALIAS="Ages">
        </SELECT></TD></TR>

  <iIF NOTCOND=<iSTRCMP SRC=":ViewProfile" DST=""> ALIAS="ViewProf">
    <TR><TD>Show View Profile in Threads?</TD>
        <TD><INPUT TYPE=RADIO NAME="Bit2" VALUE=0 <iIF NOTCOND=<iSTRSPAN SRC=":PrefString" FIRST=2 NUM=1>>CHECKED</iIF>>No <INPUT TYPE=RADIO NAME="Bit2" VALUE=1 <iIF COND=<iSTRSPAN SRC=":PrefString" FIRST=2 NUM=1>>CHECKED</iIF>>Yes</TD></TR>
  <iELSE ALIAS="ViewProf">
    <INPUT TYPE=HIDDEN NAME="Bit2" VALUE=0">
  </iIF ALIAS="ViewProf">

  <TR><TD COLSPAN=2><BR></TD></TR>

  <TR><TD COLSPAN=2><B><U>Your Message Posting Defaults</U></B></TD></TR>

  <TR><TD>Message Preview</TD>
      <TD><INPUT TYPE=RADIO NAME="Bit3" VALUE=0 <iIF NOTCOND=<iSTRSPAN SRC=":PrefString" FIRST=3 NUM=1>>CHECKED</iIF>>Off <INPUT TYPE=RADIO NAME="Bit3" VALUE=1 <iIF COND=<iSTRSPAN SRC=":PrefString" FIRST=3 NUM=1>>CHECKED</iIF>>On</TD></TR>

  <TR><TD>Spell Checker</TD>
      <TD><INPUT TYPE=RADIO NAME="Bit4" VALUE=0 <iIF NOTCOND=<iSTRSPAN SRC=":PrefString" FIRST=4 NUM=1>>CHECKED</iIF>>Off <INPUT TYPE=RADIO NAME="Bit4" VALUE=1 <iIF COND=<iSTRSPAN SRC=":PrefString" FIRST=4 NUM=1>>CHECKED</iIF>>On</TD></TR>

  <TR><TD>Attach Signature</TD>
      <TD><INPUT TYPE=RADIO NAME="Bit5" VALUE=0 <iIF NOTCOND=<iSTRSPAN SRC=":PrefString" FIRST=5 NUM=1>>CHECKED</iIF>>Off <INPUT TYPE=RADIO NAME="Bit5" VALUE=1 <iIF COND=<iSTRSPAN SRC=":PrefString" FIRST=5 NUM=1>>CHECKED</iIF>>On</TD></TR>

  <TR><TD COLSPAN=2><BR></TD></TR>

  <TR><TD COLSPAN=2><B><U>Your Signature</U></B></TD></TR>

  <TR><TD COLSPAN=2><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><TEXTAREA NAME="NewSignature" WRAP=SOFT ROWS=5 COLS=50>:Signature</TEXTAREA></FONT></TD></TR>

</TABLE><BR><INPUT TYPE=SUBMIT VALUE="Update Preferences"> &nbsp; <INPUT TYPE=BUTTON VALUE="Return to BBS" onClick="self.location=':i_script_name:mLinksQ';"></FORM></CENTER>
