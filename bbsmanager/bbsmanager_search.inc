<iREM -- Get 'User Not Found' String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT cfgVal FROM _config :IfSQL WHERE cfgVar='NOTFOUND' ;" OUTPUT=":1" NOOUTPUT="Anonymous" FAILURE="Anonymous" OUTVAR="userNotFound">

<iSET tTID=":Threads" tName=":Threads" tOriginator=":Threads" tClosed=":Threads" mMsgID=":Messages" mPosted=":Messages" mThread=":Messages" mBody=":Messages" mPoster=":Messages">
<iSTRCAT DST="tTID" SRC=".TID"><iSTRCAT DST="tName" SRC=".Name"><iSTRCAT DST="tOriginator" SRC=".Originator"><iSTRCAT DST="tClosed" SRC=".Closed">
<iSTRCAT DST="mMsgID" SRC=".MsgID"><iSTRCAT DST="mPosted" SRC=".Posted"><iSTRCAT DST="mThread" SRC=".Thread"><iSTRCAT DST="mBody" SRC=".Body"><iSTRCAT DST="mPoster" SRC=".Poster">

<iIF NOTCOND=<iISDEF VAR="DoSearch"> ALIAS="ShowForm">

  <BODY onUnload="if (PopUp != null) { PopUp.close() }">

  <SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/bbsmanager/search.js"></SCRIPT>

  <CENTER><BR><TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
    <FORM NAME="SearchForm" METHOD=POST ACTION=':i_script_name' onSubmit="return FormCheck(this);"><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un"><INPUT TYPE=HIDDEN NAME="go" VALUE="search"><INPUT TYPE=HIDDEN NAME="DoSearch" VALUE="1">

    <TR><TD COLSPAN=2><B><U>Search This Board</U></B></TD></TR>
    <TR><TD>Search By</TD><TD><SELECT NAME="SearchBy"><OPTION VALUE=":tName">Topics</OPTION><OPTION VALUE=":mBody">Bodies</OPTION><OPTION VALUE=":mPoster">Users</OPTION></SELECT></TD></TR>
    <TR><TD>Search For</TD><TD><INPUT TYPE=TEXT NAME="SearchFor" SIZE=20></TD></TR>
    <TR><TD>Date Range</TD><TD><SELECT NAME="Age">
      <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Age, Description FROM _Ages :IfSQL ORDER BY Age ;" ALIAS="Ages"><iSQLFETCH ALIAS="Ages">
        <iWHILE NOTALIAS=i_sqlempty>
          <OPTION VALUE=":Ages_Age" <iIF EXPR=':Age = :Ages_Age'>SELECTED</iIF>>:Ages_Description</OPTION>
          <iSQLFETCH ALIAS="Ages">
        </iWHILE ALIAS=i_sqlempty>
      </iSQL ALIAS="Ages">
      </SELECT>
    </TD></TR>
    <TR><TD># of Results</TD><TD><SELECT NAME="Results"><OPTION VALUE="10">Up to 10</OPTION><OPTION VALUE="25">Up to 25</OPTION><OPTION VALUE="50">Up to 50</OPTION></SELECT></TD></TR>

  </TABLE><BR><INPUT TYPE=SUBMIT VALUE="Go!"> &nbsp; <INPUT TYPE=BUTTON VALUE="Return to BBS" onClick="self.location=':i_script_name:mLinksQ';"></FORM></CENTER>

<iELSE ALIAS="ShowForm">

  <iCASE ALIAS="SearchBy" VALUE=":mPoster">
    <iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT TOP 1 :LoadDB_UserID FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserName2=':SearchFor' ;" OUTPUT=":1" NOOUTPUT="" FAILURE="" OUTVAR="SearchSQL" ESC=FALSE EVAL=TRUE>
    <iIF COND=<iSTRCMP SRC=":SearchSQL" DST="">><iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT TOP 1 :LoadDB_UserID FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserName1=':SearchFor' ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" OUTVAR="SearchSQL" ESC=FALSE EVAL=TRUE></iIF>
    <iSET SearchDesc="<B>posted by</B>">
  </iCASE ALIAS="SearchBy" VALUE=":mPoster">

  <iCASE ALIAS="SearchBy" VALUE=":mBody">
    <iSET SearchDesc="with <B>bodies</B> containing" SearchSQL=":SearchFor">
  </iCASE ALIAS="SearchBy" VALUE=":mBody">

  <iCASE ALIAS="SearchBy" VALUE=":tName">
    <iSET SearchDesc="with <B>topics</B> containing" SearchSQL=":SearchFor">
  </iCASE ALIAS="SearchBy" VALUE=":tName">

  <iEVAL EXPR=':Age*-86400' OUTVAR="AdjAge"><iDATETIME ADJUST=":AdjAge" OUTVAR="dte"><iDATETIME OUTVAR="dts">
  <iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Description FROM _Ages :IfSQL WHERE Age=:Age ;" OUTPUT=":1" OUTVAR="AgeDesc">

  <CENTER><BR><TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>

    <TR><TD COLSPAN=3><B><U>Search Results</U></B></TD></TR>
    <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT TOP :Results :tTID as ThreadID, :tName as ThreadName, Count(:mMsgID) AS MessageCount, Max(:mPosted) AS LastMessage FROM :Messages, :Threads WHERE :tTID = :mThread AND :SearchBy LIKE '%:SearchSQL%' GROUP BY :tTID, :tName HAVING Max(:mPosted) BETWEEN ':dte' AND ':dts' ORDER BY Max(:mPosted) DESC ;" ALIAS="ShowMsgs"><iSQLFETCH ALIAS="ShowMsgs">

      <iIF COND=:i_sqlempty ALIAS="NoResults">
        <TR><TD COLSPAN=3>No results for threads containing messages :SearchDesc <B>':SearchFor'</B> in the last <B>:AgeDesc</B>:<BR><BR></TD></TR>
      <iELSE ALIAS="NoResults">
        <TR><TD COLSPAN=3>Threads containing messages :SearchDesc <B>':SearchFor'</B> in the last <B>:AgeDesc</B>:<BR><BR></TD></TR>
        <TR><TD ALIGN=LEFT VALIGN=BOTTOM><B>Topic Name</B></TD><TD ALIGN=CENTER VALIGN=TOP><B>Matches in Topic</B></TD><TD ALIGN=CENTER VALIGN=BOTTOM><B>&nbsp; &nbsp; Last Message</B></TD></TR>
        <iWHILE NOTALIAS=i_sqlempty>
      
          <TR>
            <TD ALIGN=LEFT VALIGN=BOTTOM><A HREF=":i_script_name?go=view&id=:ShowMsgs_ThreadID:mLinksA">:ShowMsgs_ThreadName</A></TD>
            <TD ALIGN=CENTER>&nbsp;:ShowMsgs_MessageCount</TD>
            <TD ALIGN=CENTER>&nbsp;&nbsp;&nbsp;&nbsp; :ShowMsgs_LastMessage</TD>
          </TR>

          <iSQLFETCH ALIAS="ShowMsgs">
        </iWHILE ALIAS=i_sqlempty>
      </iIF ALIAS="NoResults">

    </iSQL ALIAS="ShowMsgs">

  </TABLE><BR><INPUT TYPE=BUTTON VALUE="Perform Another Search" onClick="self.location=':i_script_name?go=search:mLinksA';"> &nbsp; <INPUT TYPE=BUTTON VALUE="Return to BBS" onClick="self.location=':i_script_name:mLinksQ';"></CENTER>

</iIF ALIAS="ShowForm">
