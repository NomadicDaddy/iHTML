
<iDEFAULT NAME="showFields" VALUE="logDate, token, record_id">
<iDEFAULT NAME="token" VALUE="">
<iDEFAULT NAME="record_id" VALUE="">
<iDEFAULT NAME="startDate" VALUE=`<iDATETIME FMT="%m/%d/%Y %H:%M %p" ADJUST="-3600">`>
<iDEFAULT NAME="endDate" VALUE=`<iDATETIME FMT="%m/%d/%Y %H:%M %p">`>
<iDEFAULT NAME="sortBy1" VALUE="logDate">
<iDEFAULT NAME="sortBy2" VALUE="">
<iDEFAULT NAME="sortBy3" VALUE="">

<iSQLMORE ALIAS="loadDB" SQL="SELECT MIN(DATEPART([year], logDate)) AS firstYear, MAX(DATEPART([year], logDate)) AS lastYear FROM linkTrackingLog (NOLOCK) WHERE job_id=:job ;">
<iSQLFETCH ALIAS="loadDB">

<iSET fields="">
<iSTRSPAN SRC=":appConn" FIRST=<iEVAL EXPR=`<iSTRIN SRC=":appConn" DST="DATABASE="> + 9`> NUM=<iEVAL EXPR=`<iSTRLEN SRC=":appConn"> - (<iSTRIN SRC=":appConn" DST="DATABASE="> + 9)`> OUTVAR="dbQualifier">
<iSQLCOLUMNS DBNAME=":appConn" TABLE="linkTrackingLog" QUALIFIER=":dbQualifier" ALIAS="getCols">
<iSQLFETCH ALIAS="getCols">
	<iWHILE NOTALIAS=i_sqlempty>
		<iIF NOTCOND=<iSTRCMP SRC=":getCols_COLUMN_NAME" DST="job_id">><iSET fields=":fields,:getCols_COLUMN_NAME"></iIF>
		<iSQLFETCH ALIAS="getCols">
	</iWHILE ALIAS=i_sqlempty>
</iSQL ALIAS="getCols">
<iSTRRIGHT SRC=":fields" NUM=<iEVAL EXPR='<iSTRLEN SRC=":fields"> - 1'> OUTVAR="fields">
<iLISTCREATE NAME="fieldArray" DELIM="" SRC="fields" TYPE=VARIABLE>
<iLISTGET NAME="fieldArray" OP=COUNT DELIM="" OUTVAR="fieldCount">

<FORM METHOD=POST NAME="logSearch" ACTION=':thisPage'>
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH="100%" BORDER=1 CELLSPACING=0 CELLPADDING=2>
<TR>
	<TD VALIGN=TOP>
		Fields Shown:<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" VALUE="logDate" <iIF COND=<iSTRIN SRC=":showFields" DST="logDate">>CHECKED</iIF>> Date/Time<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" VALUE="ipAddress" <iIF COND=<iSTRIN SRC=":showFields" DST="ipAddress">>CHECKED</iIF>> IP Address<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" VALUE="token" <iIF COND=<iSTRIN SRC=":showFields" DST="token">>CHECKED</iIF>> Token<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" VALUE="record_id" <iIF COND=<iSTRIN SRC=":showFields" DST="record_id">>CHECKED</iIF>> Record ID<BR>
	</TD>
	<TD VALIGN=TOP>
		Criteria:<BR>
		<TABLE BORDER=0>
		<TR><TD>Token contains </TD><TD><INPUT TYPE=TEXT NAME="token" VALUE=":token"></TD></TR>
		<TR><TD>Record ID is </TD><TD><INPUT TYPE=TEXT NAME="record_id" VALUE=":record_id"></TD></TR>
		</TABLE>
	</TD>
	<TD VALIGN=TOP>
<iREMBLOCK>
		<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><iINCLUDE NAME="x:\adminware.com\htdocs\js\awCalendarPop.js" PARSE=FALSE></SCRIPT>
</iREMBLOCK>
		<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/awCalendarPop.js"></SCRIPT>
		Date/Time Range:<BR>
		From:<BR>
		<INPUT TYPE=TEXT NAME="startDate" VALUE=":startDate" SIZE=19 MAXLENGTH=19 CALENDAR="range" ALLOW="2" FIRSTDAY="0" DATEFORMAT="1" TIMEFORMAT="2" FIRST="01/01/:loadDB_firstYear" LAST="12/31/:loadDB_lastYear" POPUPWIDTH="190" POPUPHEIGHT="220" STYLESHEET="http://adminware.com/style/adminware/awCalendarPop.css">
		<IMG SRC="/images/adminware/calendar.gif" ALT="Calendar" WIDTH=31 HEIGHT=25 BORDER=0 ALIGN=CENTER onClick="popDate('document.logSearch.startDate');"><BR>
		To:<BR>
		<INPUT TYPE=TEXT NAME="endDate" VALUE=":endDate" SIZE=19 MAXLENGTH=19 CALENDAR="range" ALLOW="2" FIRSTDAY="0" DATEFORMAT="1" TIMEFORMAT="2" FIRST="01/01/:loadDB_firstYear" LAST="12/31/:loadDB_lastYear" POPUPWIDTH="190" POPUPHEIGHT="220" STYLESHEET="http://adminware.com/style/adminware/awCalendarPop.css">
		<IMG SRC="/images/adminware/calendar.gif" ALT="Calendar" WIDTH=31 HEIGHT=25 BORDER=0 ALIGN=CENTER onClick="popDate('document.logSearch.endDate');"><BR>
	</TD>
	<TD VALIGN=TOP>
		Sort By:<BR>
		<TABLE BORDER=0>
		<TR><TD>1st: </TD>
		<TD><SELECT NAME="sortBy1">
		<OPTION VALUE="" <iIF COND=<iSTRCMP SRC=":sortBy1" DST="">>SELECTED</iIF>>-</OPTION>
		<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
			<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
			<OPTION VALUE=":curField" <iIF COND=<iSTRICMP SRC=":curField" DST=":sortBy1">>SELECTED</iIF>>:curField</OPTION>
		</iLOOP ALIAS="fieldLoop">
		</SELECT></TD></TR>
		<TR><TD>2nd: </TD>
		<TD><SELECT NAME="sortBy2">
		<OPTION VALUE="" <iIF COND=<iSTRCMP SRC=":sortBy2" DST="">>SELECTED</iIF>>-</OPTION>
		<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
			<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
			<OPTION VALUE=":curField" <iIF COND=<iSTRICMP SRC=":curField" DST=":sortBy2">>SELECTED</iIF>>:curField</OPTION>
		</iLOOP ALIAS="fieldLoop">
		</SELECT></TD></TR>
		<TR><TD>3rd: </TD>
		<TD><SELECT NAME="sortBy3">
		<OPTION VALUE="" <iIF COND=<iSTRCMP SRC=":sortBy3" DST="">>SELECTED</iIF>>-</OPTION>
		<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
			<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
			<OPTION VALUE=":curField" <iIF COND=<iSTRICMP SRC=":curField" DST=":sortBy3">>SELECTED</iIF>>:curField</OPTION>
		</iLOOP ALIAS="fieldLoop">
		</SELECT></TD></TR>
		</TABLE>
	</TD>
</TR>
</TABLE>
<TABLE WIDTH="100%" BORDER=0><TR><TD ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Update Report"></TD></TR></TABLE>
</FORM>

<iSET criteria="">
<iIF NOTCOND=<iSTRCMP SRC=":token" DST="">><iREPLACE VAR="token" SRC="'" DST="''"><iSTRCAT DST="criteria" SRC="AND token LIKE '%:token%'"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":record_id" DST="">><iSTRKEEP SRC=":record_id" KEEP="0123456789" OUTVAR="record_id"><iSTRCAT DST="criteria" SRC="AND record_id=:record_id"></iIF>
<iSTRRIGHT SRC=":criteria" NUM=<iEVAL EXPR='<iSTRLEN SRC=":criteria"> - 4'> OUTVAR="criteria">
<iIF NOTCOND=<iSTRCMP SRC=":criteria" DST="">><iSET criteria="AND :criteria"></iIF>

<iSET sortBy="">
<iIF NOTCOND=<iSTRCMP SRC=":sortBy1" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy1"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":sortBy2" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy2"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":sortBy3" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy3"></iIF>
<iSTRRIGHT SRC=":sortBy" NUM=<iEVAL EXPR='<iSTRLEN SRC=":sortBy"> - 2'> OUTVAR="sortBy">
<iIF NOTCOND=<iSTRCMP SRC=":sortBy" DST="">><iSET sortBy="ORDER BY :sortBy"></iIF>

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT :showFields, j.addressee, j.email
	FROM linkTrackingLog l (NOLOCK) INNER JOIN _job_:job j (NOLOCK) ON l.record_id=j.id
	WHERE job_id=:job AND logDate >= ':startDate' AND ':endDate' >= logDate :criteria :sortBy ;
" ESC=FALSE>
<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">

<iIF NOTCOND=:loadDB_empty ALIAS="hasLogs">
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=3 CELLPADDING=2>
	<TR>
		<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
			<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
			<iIF COND=<iSTRIN SRC=":showFields" DST=":curField"> ALIAS="showColumn">
				<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>&nbsp; 
					<iCASE ALIAS="curField" VALUE="logDate"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Date/Time')" onMouseOut="noHelp()">Date/Time</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="ipAddress"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('IP Address')" onMouseOut="noHelp()">IP Address</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="token"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Token')" onMouseOut="noHelp()">Token</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="record_id"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('RecordID')" onMouseOut="noHelp()">Record ID</A></iCASE ALIAS="curField">
				</TD>
			</iIF ALIAS="showColumn">
		</iLOOP ALIAS="fieldLoop">
	</TR>
	<iWHILE NOTALIAS=loadDB_empty>
		<TR BGCOLOR="#A0B8C8" CLASS="highlightRow">
			<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
				<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
				<iIF COND=<iSTRIN SRC=":showFields" DST=":curField"> ALIAS="showColumn">
					<TD CLASS="inHighlight" NOWRAP><iEQ VALUE=":loadDB_:curField" EVAL=TRUE></TD>
				</iIF ALIAS="showColumn">
			</iLOOP ALIAS="fieldLoop">
			<TD>:loadDB_addressee (:loadDB_email)</TD>
		</TR>
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
	</iWHILE ALIAS=loadDB_empty>
	</TABLE>
<iELSE ALIAS="hasLogs">
	There are no log entries for this area matching the above criteria.
</iIF ALIAS="hasLogs">
