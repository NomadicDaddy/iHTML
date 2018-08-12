<iSQL DBNAME=":dsn" SQL="SELECT 0 ;" ALIAS="loadDB">
<iSET job=":Area">
<iINCLUDE NAME="w:\shared\field_array.inc">
</iSQL ALIAS="loadDB">

<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="DoAdd"> ALIAS="DoAdd">
  <iSET sqlstring="INSERT INTO :AreaName">
  <iLOOP INITIAL=1 FINAL=":fcount"><iIF EXPR=':i_loop GT 1'><iSET sqlstring=`:sqlstring, <iEQ VALUE=":sF_:i_loop" EVAL=TRUE>`><iELSE><iSET sqlstring=`:sqlstring (<iEQ VALUE=":sF_:i_loop" EVAL=TRUE>`></iIF></iLOOP>
  <iSET sqlstring=":sqlstring) VALUES">
  <iLOOP INITIAL=1 FINAL=":fcount">
    <iEQ NAME="insertme" VALUE=":sV_:i_loop" EVAL=TRUE><iREPLACE VAR="insertme" SRC="'" DST="''">
    <iEQ NAME="FieldType" VALUE=":FType_:i_loop" EVAL=TRUE><iIF NOTCOND=<iSTRCMP SRC=":FieldType" DST="Numeric">><iSET insertme="':insertme'"></iIF>
    <iIF EXPR=':i_loop GT 1'><iSET sqlstring=`:sqlstring, :insertme`><iELSE><iSET sqlstring=`:sqlstring (:insertme`></iIF>
  </iLOOP>
  <iSET sqlstring=`:sqlstring) :IfSQL ;` z="User added.">
  <iHTML DBNAME=':dsn' SQL=`:sqlstring` ESC=FALSE NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="msg">
  <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
  <iIF COND=<iSTRCMP SRC=":msg" DST="Success"> ALIAS="SetMsg"><iSET msg=":z"></iIF ALIAS="SetMsg">
  <iIF EXPR='<iISDEF VAR="fumsg"> AND NOT <iSTRCMP SRC=":fumsg" DST="">' ALIAS="SetMsg"><iSET msg=":z :fumsg"></iIF ALIAS="SetMsg">
</iIF ALIAS="DoAdd">

<iREM -- Show Status Message -- >
<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><CENTER><FONT COLOR="#FF5500" SIZE="+1">:msg</FONT></CENTER><BR></iIF ALIAS="ShowMsg">
<iSET DemoDSN="adminware_authmanager"><iIF COND=<iSTRCMP SRC=":dsn" DST=":DemoDSN"> ALIAS="IsDemo"><iSET demo=1></iIF ALIAS="IsDemo">

<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iSQL DBNAME=":dsn" SQL="SELECT * FROM _Areas WHERE ID = :Area ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">

<FORM METHOD=POST ACTION=:i_script_name>
<INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
<INPUT TYPE=HIDDEN NAME="go" VALUE="Add a User"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=HIDDEN NAME="AreaName" VALUE=":AreaName">
<INPUT TYPE=HIDDEN NAME="sF_:xUserNameID" VALUE="z:xUserName"><INPUT TYPE=HIDDEN NAME="sF_:xPasswordID" VALUE="z:xPassword">
<TR><TD WIDTH=1% NOWRAP><B><U>UserName</U></B><iIF NOTCOND=<iSTRCMP SRC=":xUserName" DST="UserName">> (:xUserName)</iIF></TD><TD NOWRAP STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sV_:xUserNameID" SIZE='<iEVAL EXPR=':xUserNameLen+2'>' MAXLENGTH=':xUserNameLen' VALUE=""></TD></TR>
<TR><TD WIDTH=1% NOWRAP><B><U>Password</U></B><iIF NOTCOND=<iSTRCMP SRC=":xPassword" DST="Password">> (:xPassword)</iIF></TD><TD NOWRAP STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sV_:xPasswordID" SIZE='<iEVAL EXPR=':xPasswordLen+2'>' MAXLENGTH=':xPasswordLen' VALUE=""></TD></TR>

<iLOOP INITIAL=1 FINAL=":fcount" ALIAS="FDO">
  <iREM -- Get Field Settings -- >
  <iEQ NAME="NextField" VALUE=":FName_:FDO" EVAL=TRUE><iEQ NAME="FieldType" VALUE=":FType_:FDO" EVAL=TRUE><iEQ NAME="FieldSize" VALUE=":FSize_:FDO" EVAL=TRUE>
  <iIF EXPR='NOT <iSTRCMP SRC=":FieldType" DST="UserName"> AND NOT <iSTRCMP SRC=":FieldType" DST="Password">' ALIAS="UFields">
    <iREM -- Remove 'z' Prefix for Display Purposes -- >
    <iSTRRIGHT SRC=":NextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':NextField'> - 1'> OUTVAR="ViewField">
    <INPUT TYPE=HIDDEN NAME="sF_:FDO" VALUE=<iEQ VALUE=":NextField" EVAL=TRUE>>
      <TR><TD WIDTH=1% NOWRAP><B><U>:ViewField</U></B></TD>
      <TD NOWRAP STYLE="padding-left : 9px;"><FONT SIZE="-1">
        <iIF EXPR=':FieldSize GT 50' ALIAS="FieldSizer">
          <iEVAL EXPR=':FieldSize / 51' OUTVAR="InputRows">
          <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=:InputRows COLS=51></TEXTAREA>
        <iELSEIF EXPR=':FieldSize = 0' ALIAS="FieldSizer">
          <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=5 COLS=51></TEXTAREA>
        <iELSE ALIAS="FieldSizer">
          <INPUT TYPE=TEXT NAME='sV_:FDO' SIZE='<iEVAL EXPR=':FieldSize+2'>' MAXLENGTH=':FieldSize' VALUE="">
        </iIF ALIAS="FieldSizer">
      </FONT></TD></TR>
  </iIF ALIAS="UFields">
</iLOOP ALIAS="FDO">
<TR><TD COLSPAN=2 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="DoAdd" VALUE="Add"></TD></TR>
</FORM>

</TABLE>

<iREM -- Display Back Button -- >
<FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="msg" VALUE=""><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><TR><TD ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Back" VALUE="Go Back"></TD></TR></FORM>

</iSQL ALIAS="LoadDB">

</CENTER></TD></TR></TABLE>
