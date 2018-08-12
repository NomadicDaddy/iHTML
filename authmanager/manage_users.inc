<iSQL DBNAME=":dsn" SQL="SELECT 0 ;" ALIAS="loadDB">
<iSET job=":Area">
<iINCLUDE NAME="w:\shared\field_array.inc">
</iSQL ALIAS="loadDB">

<iREM -- Delete User -- >
<iIF EXPR='<iISDEF VAR="DoDelete.x"> OR <iISDEF VAR="DoDelete">' ALIAS="DoDelete">
  <iHTML DBNAME=':dsn' SQL='DELETE FROM :AreaName :IfSQL WHERE zID = :ID ;' NOOUTPUT="User deleted." FAILURE=" :i_sqlerrortext" OUTVAR="msg">
  <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Delete failed.">
  <iIF COND=<iISDEF VAR="ViewFrom2">><iEVAL EXPR=':ViewFrom2 - 1' OUTVAR="ViewFrom"><iELSE><iEVAL EXPR=':ViewFrom - 1' OUTVAR="ViewFrom"></iIF>
</iIF ALIAS="DoDelete">

<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="DoUpdate"> ALIAS="DoUpdate">
  <iSET sqlstring="UPDATE :AreaName SET ">
  <iLOOP INITIAL=1 FINAL=":fcount"><iEQ NAME="insertme" VALUE=":sV_:i_loop" EVAL=TRUE><iREPLACE VAR="insertme" SRC="'" DST="''"><iIF EXPR=':i_loop GT 1'><iSET sqlstring=`:sqlstring, <iEQ VALUE=":sF_:i_loop" EVAL=TRUE> = ':insertme'`><iELSE><iSET sqlstring=`:sqlstring <iEQ VALUE=":sF_:i_loop" EVAL=TRUE> = ':insertme'`></iIF></iLOOP>
  <iSET sqlstring=`:sqlstring :IfSQL WHERE zID = :ID ;` z="User updated.">
  <iHTML DBNAME=':dsn' SQL=`:sqlstring` ESC=FALSE NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="msg">
  <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
  <iIF COND=<iSTRCMP SRC=":msg" DST="Success"> ALIAS="SetMsg"><iSET msg=":z"></iIF ALIAS="SetMsg">
  <iIF EXPR='<iISDEF VAR="fumsg"> AND NOT <iSTRCMP SRC=":fumsg" DST="">' ALIAS="SetMsg"><iSET msg=":z :fumsg"></iIF ALIAS="SetMsg">
</iIF ALIAS="DoUpdate">

<iREM -- Show Status Message -- >
<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><CENTER><FONT COLOR="#FF5500" SIZE="+1">:msg</FONT></CENTER><BR></iIF ALIAS="ShowMsg">
<iSET DemoDSN="adminware_authmanager"><iIF COND=<iSTRCMP SRC=":dsn" DST=":DemoDSN"> ALIAS="IsDemo"><iSET demo=1></iIF ALIAS="IsDemo">

<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iSQL DBNAME=":dsn" SQL="SELECT * FROM _Areas WHERE ID = :Area ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">

<iREM -- Edit User -- >
<iIF EXPR='<iISDEF VAR="DoEdit.x"> OR <iISDEF VAR="DoEdit">' ALIAS="DoEdit">

  <iSQL DBNAME=":dsn" SQL="SELECT * FROM :AreaName WHERE zID=:ID ;" ALIAS="GetUser"><iSQLFETCH ALIAS="GetUser">
    <FORM METHOD=POST ACTION=:i_script_name>
    <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
    <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=HIDDEN NAME="ID" VALUE=":GetUser_zID"><INPUT TYPE=HIDDEN NAME="AreaName" VALUE=":AreaName"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE=":ViewFrom2">
    <iEQ VALUE=:GetUser_z:xUserName EVAL=TRUE OUTVAR="CurUserName"><iEQ VALUE=:GetUser_z:xPassword EVAL=TRUE OUTVAR="CurPassword">
    <INPUT TYPE=HIDDEN NAME="sF_:xUserNameID" VALUE="z:xUserName"><INPUT TYPE=HIDDEN NAME="sF_:xPasswordID" VALUE="z:xPassword">
    <TR><TD WIDTH=1% NOWRAP><B><U>ID</U></B></TD><TD NOWRAP STYLE="padding-left : 9px;">:GetUser_zID</TD></TR>
    <TR><TD WIDTH=1% NOWRAP><B><U>UserName</U></B><iIF NOTCOND=<iSTRCMP SRC=":xUserName" DST="UserName">> (:xUserName)</iIF></TD><TD NOWRAP STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sV_:xUserNameID" SIZE='<iEVAL EXPR=':xUserNameLen+2'>' MAXLENGTH=':xUserNameLen' VALUE=":CurUserName"></TD></TR>
    <TR><TD WIDTH=1% NOWRAP><B><U>Password</U></B><iIF NOTCOND=<iSTRCMP SRC=":xPassword" DST="Password">> (:xPassword)</iIF></TD><TD NOWRAP STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sV_:xPasswordID" SIZE='<iEVAL EXPR=':xPasswordLen+2'>' MAXLENGTH=':xPasswordLen' VALUE=":CurPassword"></TD></TR>

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
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=:InputRows COLS=51><iEQ VALUE=":GetUser_:NextField" EVAL=TRUE></TEXTAREA>
            <iELSEIF EXPR=':FieldSize = 0' ALIAS="FieldSizer">
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=5 COLS=51><iEQ VALUE=":GetUser_:NextField" EVAL=TRUE></TEXTAREA>
            <iELSE ALIAS="FieldSizer">
              <iEQ VALUE=":GetUser_:NextField" EVAL=TRUE OUTVAR="UserArea">
              <INPUT TYPE=TEXT NAME='sV_:FDO' SIZE='<iEVAL EXPR=':FieldSize+2'>' MAXLENGTH=':FieldSize' VALUE=":UserArea">
            </iIF ALIAS="FieldSizer">
          </FONT></TD></TR>
      </iIF ALIAS="UFields">
    </iLOOP ALIAS="FDO">
    <TR><TD COLSPAN=2 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="DoUpdate" VALUE="Update"><INPUT TYPE=SUBMIT NAME="DoDelete" VALUE="Delete"></TD></TR>
    </FORM>
  </iSQL ALIAS="GetUser">

  </TABLE>

  <iREM -- Display Back Button -- >
  <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="msg" VALUE=""><INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><TR><TD ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Back" VALUE="Go Back"></TD></TR></FORM>

<iELSE ALIAS="DoEdit">

  <iIF NOTCOND=<iSTRCMP SRC=":xUserName" DST="UserName">><iSET DxUserName=" (:xUserName)"><iELSE><iSET DxUserName=""></iIF>
  <iIF NOTCOND=<iSTRCMP SRC=":xPassword" DST="Password">><iSET DxPassword=" (:xPassword)"><iELSE><iSET DxPassword=""></iIF>

  <iREM -- ViewFrom = where to start, ViewTo = where to stop -- >
  <iDEFAULT NAME="ViewFrom" VALUE="1"><iSET ViewTo=<iEVAL EXPR=':ViewFrom + :MaxItems - 1'>><iSET CurPointer=:ViewFrom CurCount=0>

  <iDEFAULT NAME="SortBy" VALUE="zID"><iSET SortStr="ORDER BY :SortBy">

  <iDEFAULT NAME="SearchBy" VALUE=""><iDEFAULT NAME="SearchFor" VALUE="">
  <iIF NOTCOND=<iSTRCMP SRC=":SearchBy" DST=""> ALIAS="Searching">
    <iREPLACE VAR="SearchFor" SRC="'" DST="''">
    <iSET SearchStr="WHERE z:SearchBy LIKE '%:SearchFor%'">
  <iELSE ALIAS="Searching">
    <iSET SearchStr="">
  </iIF ALIAS="Searching">

  <iHTML DBNAME=":dsn" SQL="SELECT COUNT (*) FROM :AreaName ;" OUTPUT=":1" NOOUTPUT="0" OUTVAR="MaxUsers">
  <iHTML DBNAME=":dsn" SQL="SELECT COUNT (*) FROM :AreaName :SearchStr ;" ESC=FALSE OUTPUT=":1" NOOUTPUT="0" OUTVAR="TotalUsers">

<iREMBLOCK>
MaxUsers = ':MaxUsers'<BR>
TotalUsers = ':TotalUsers'<BR>
ViewFrom = ':ViewFrom'<BR>
ViewTo = ':ViewTo'<BR>
CurCount = ':CurCount'<BR>
CurPointer = ':CurPointer'<BR>
SortBy = ':SortBy'<BR>
SearchBy = ':SearchBy'<BR>
SearchFor = ':SearchFor'<BR>
SQLStr = 'SELECT * FROM :AreaName :SearchStr :SortStr ;'<BR>
</iREMBLOCK>

  <iIF EXPR=':TotalUsers' ALIAS="AreUsers">
    <TR BGCOLOR="#EEEEEE">
      <TD NOWRAP WIDTH=1%><B><iIF COND=<iSTRCMP SRC=":SortBy" DST="zID"> ALIAS="Sorted"><U>#</U><iELSE ALIAS="Sorted"><A HREF=:i_script_name?dsn=:dsn&UserName=:UserName&Password=:Password&go=Manage%20Existing%20Users&Config=:Config&Area=:Area&ViewFrom=1&SearchBy=:SearchBy&SearchFor=:SearchFor&Login=>#</A></iIF ALIAS="Sorted"></B></TD>
      <TD NOWRAP><B><iIF COND=<iSTRCMP SRC=":SortBy" DST="z:xUserName"> ALIAS="Sorted"><U>UserName</U><iELSE ALIAS="Sorted"><A HREF=:i_script_name?dsn=:dsn&UserName=:UserName&Password=:Password&go=Manage%20Existing%20Users&Config=:Config&Area=:Area&ViewFrom=1&SortBy=z:xUserName&SearchBy=:SearchBy&SearchFor=:SearchFor&Login=>UserName</A></iIF ALIAS="Sorted"></B>:DxUserName</TD>
      <TD NOWRAP><B><iIF COND=<iSTRCMP SRC=":SortBy" DST="z:xPassword"> ALIAS="Sorted"><U>Password</U><iELSE ALIAS="Sorted"><A HREF=:i_script_name?dsn=:dsn&UserName=:UserName&Password=:Password&go=Manage%20Existing%20Users&Config=:Config&Area=:Area&ViewFrom=1&SortBy=z:xPassword&SearchBy=:SearchBy&SearchFor=:SearchFor&Login=>Password</A></iIF ALIAS="Sorted"></B>:DxPassword</TD>
    <TD COLSPAN=2>&nbsp;</TD></TR>

    <iSQL DBNAME=":dsn" SQL="SELECT * FROM :AreaName :SearchStr :SortStr ;" ALIAS="GetUsers" ESC=FALSE INDEXED=TRUE><iSQLFETCH ALIAS="GetUsers" INDEX=":ViewFrom">
      <iWHILE NOTALIAS="i_sqlempty">
        <iSET CurCount=<iMATH A=:CurCount B=1 O="+">>
        <FORM METHOD=POST ACTION=:i_script_name>
        <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
        <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="ID" VALUE=":GetUsers_zID"><INPUT TYPE=HIDDEN NAME="ViewFrom2" VALUE=":ViewFrom">
        <iEQ VALUE=:GetUsers_z:xUserName EVAL=TRUE OUTVAR="CurUserName"><iEQ VALUE=:GetUsers_z:xPassword EVAL=TRUE OUTVAR="CurPassword">
        <iSET OtherFields="">
        <iLOOP INITIAL=1 FINAL=":fcount" ALIAS="FDO">
          <iEQ NAME="NextField" VALUE=":FName_:FDO" EVAL=TRUE><iEQ NAME="FieldType" VALUE=":FType_:FDO" EVAL=TRUE><iEQ NAME="FieldSize" VALUE=":FSize_:FDO" EVAL=TRUE>
          <iSTRRIGHT SRC=":NextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':NextField'> - 1'> OUTVAR="ViewField">
          <iEQ NAME="ThisStr" VALUE=:GetUsers_:NextField EVAL=TRUE><iSTRCAT DST="OtherFields" SRC="<B>:ViewField</B>: :ThisStr<BR>">
        </iLOOP ALIAS="FDO">
        <TR BGCOLOR="#EEEEEE">
          <TD NOWRAP WIDTH=1% VALIGN=TOP onMouseOver="hilite(':CurCount');" onMouseOut="unlite(':CurCount');" ID=ROW:CurCount><FONT FACE="Verdana, Helvetica, Arial" SIZE="2">:CurPointer</FONT></TD>
          <TD NOWRAP VALIGN=TOP onMouseOver="hilite(':CurCount');" onMouseOut="unlite(':CurCount');" ID=ROW:CurCount><FONT FACE="Verdana, Helvetica, Arial" SIZE="2">
            <A HREF=:i_script_name?dsn=:dsn&UserName=:UserName&Password=:Password&go=Manage%20Existing%20Users&Config=:Config&Area=:Area&ID=:GetUsers_zID&DoEdit.x=1&ViewFrom2=:ViewFrom&ViewFrom=:ViewFrom&SortBy=:SortBy&SearchBy=:SearchBy&SearchFor=:SearchFor&Login= onMouseOver="dcs(':OtherFields');" onMouseOut="nd()">:CurUserName</A>
          </FONT></TD>
          <TD NOWRAP VALIGN=TOP onMouseOver="hilite(':CurCount');" onMouseOut="unlite(':CurCount');" ID=ROW:CurCount><FONT FACE="Verdana, Helvetica, Arial" SIZE="2">:CurPassword</FONT></TD>
          <TD WIDTH=1% onMouseOver="hilite(':CurCount');" onMouseOut="unlite(':CurCount');" ID=ROW:CurCount><INPUT TYPE=IMAGE NAME="DoEdit" SRC="/images/adminware/btn_edit.gif" ALT="Edit" WIDTH=23 HEIGHT=11 VALUE="Edit" BORDER=0></TD>
          <TD WIDTH=1% onMouseOver="hilite(':CurCount');" onMouseOut="unlite(':CurCount');" ID=ROW:CurCount><INPUT TYPE=IMAGE NAME="DoDelete" SRC="/images/adminware/btn_del.gif" ALT="Delete" WIDTH=23 HEIGHT=11 VALUE="Delete" BORDER=0></TD>
        </TR>
        </FORM>

        <iIF EXPR='NOT :CurCount GT :MaxItems - 1 AND :CurCount LTE :TotalUsers'>
          <iSET ViewNow=<iEVAL EXPR=':ViewFrom + :CurCount'> CurPointer=<iMATH A=:CurPointer B=1 O="+">>
          <iSQLFETCH ALIAS="GetUsers" INDEX=":ViewNow">
        <iELSE>
          <iSET i_sqlempty=TRUE>
        </iIF>

      </iWHILE ALIAS="i_sqlempty">
    </iSQL ALIAS="GetUsers">

  <iELSE ALIAS="AreUsers">
    <TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2><TR><TD ALIGN=CENTER COLSPAN=4><BR><BLOCKQUOTE><FONT COLOR="#FF0000">There
    <iIF COND=<iISDEF VAR="SearchBy"> ALIAS="Searching">were no matching users found<iELSE ALIAS="Searching">are no active users</iIF ALIAS="Searching">
    in the <B>:AreaName Area</B> at this time.</FONT></BLOCKQUOTE></TD></TR></TABLE>
  </iIF ALIAS="AreUsers">

  </TABLE>

  <iIF EXPR=':MaxItems NE 9999' ALIAS="PrevNext"><BR><TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2><TR>

    <iIF EXPR='NOT :ViewFrom = 1'>
      <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":LoadDB_ID"><INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="Config" VALUE="Go!">
      <TD><P><INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE="1"><INPUT TYPE=SUBMIT VALUE="&lt;&lt;"></P></TD></FORM>
    </iIF>

    <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":LoadDB_ID"><INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="Config" VALUE="Go!">
    <TD><P>
      <iSET PrevSet=<iEVAL EXPR=':ViewFrom - :MaxItems'> NextSet=<iEVAL EXPR=':ViewTo + 1'>>
      <iIF EXPR=':PrevSet GT 0'>
        <iSET ButTxt=`Previous :MaxItems Users (:PrevSet-<iEVAL EXPR=':PrevSet + :MaxItems - 1'>)`>
        <INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE=":PrevSet"><INPUT TYPE=SUBMIT VALUE=":ButTxt">
      <iELSEIF EXPR=':ViewFrom LT :MaxItems AND :ViewFrom NE 1'>
        <iSET ButTxt=`Previous <iEVAL EXPR=':ViewFrom - 1'> Users (1-:MaxItems)`>
        <INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE="1"><INPUT TYPE=SUBMIT VALUE=":ButTxt">
      </iIF>
    </P></TD>
    </FORM>

    <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":LoadDB_ID"><INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="Config" VALUE="Go!">
    <TD><P>
      <iIF EXPR=':NextSet LT :TotalUsers'>
        <iIF EXPR='(:TotalUsers - :NextSet) GT :MaxItems' ALIAS="GetNumInSet">
          <iSET NumInSet=:MaxItems>
        <iELSE ALIAS="GetNumInSet">
          <iSET NumInSet=<iEVAL EXPR=':TotalUsers - :NextSet + 1'>>
        </iIF ALIAS="GetNumInSet">
        <iSET ButTxt=`Next :NumInSet Users (:NextSet-<iEVAL EXPR=':NextSet + :NumInSet - 1'>)`>
        <INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE=":NextSet"><INPUT TYPE=SUBMIT VALUE=":ButTxt">
      </iIF>
    </P></TD>
    </FORM>

    <iEVAL EXPR=':TotalUsers - :MaxItems + 1' OUTVAR="zEnd">
    <iIF EXPR=':ViewTo NE :TotalUsers AND :ViewTO LT :TotalUsers'>
      <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":LoadDB_ID"><INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="Config" VALUE="Go!">
      <TD><P><INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE=":zEnd"><INPUT TYPE=SUBMIT VALUE="&gt;&gt;"></P></TD></FORM>
    </iIF>

  </TR></TABLE>
  <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2><TR>

    <FORM METHOD=POST ACTION=:i_script_name>
    <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
    <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy">
    <TD>Search by </TD><TD><SELECT NAME="SearchBy"><iLOOP INITIAL=1 FINAL=":fcount" ALIAS="FDO"><OPTION><iSTRRIGHT SRC=`<iEQ VALUE=":FName_:FDO" EVAL=TRUE>` NUM=<iEVAL EXPR='<iSTRLEN SRC='<iEQ VALUE=":FName_:FDO" EVAL=TRUE>'> - 1'>></OPTION></iLOOP ALIAS="FDO"></SELECT></TD>
    <TD> for </TD><TD><P><INPUT TYPE=TEXT NAME="SearchFor" SIZE=10 MAXLENGTH=255> <INPUT TYPE=SUBMIT VALUE="Go!"></P></TD>
    </FORM>

    <TD>&nbsp;</TD>

    <TD>Jump to User #: </TD>
    <TD><P>
      <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=TEXT NAME="ViewFrom" SIZE=<iEVAL EXPR='<iSTRLEN SRC=":MaxUsers">+2'> MAXLENGTH=<iSTRLEN SRC=":MaxUsers"> onBlur="()">
      <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
      <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=HIDDEN NAME="SearchBy" VALUE=":SearchBy"><INPUT TYPE=HIDDEN NAME="SearchFor" VALUE=":SearchFor"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=SUBMIT VALUE="Go!">
      </FORM>
    </P></TD>

    <TD>&nbsp;</TD>

    <TD><P>
      <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="ViewFrom" VALUE="1">
      <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
      <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Existing Users"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":Area"><INPUT TYPE=HIDDEN NAME="SortBy" VALUE=":SortBy"><INPUT TYPE=SUBMIT VALUE="View All">
      </FORM>
    </P></TD>

  </TR></TABLE></iIF ALIAS="PrevNext">

  <iREM -- Display Back Button -- >
  <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="msg" VALUE=""><TR><TD ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Back" VALUE="Go Back"></TD></TR></FORM>

</iIF ALIAS="DoEdit">

</iSQL ALIAS="LoadDB">

</CENTER></TD></TR></TABLE>
