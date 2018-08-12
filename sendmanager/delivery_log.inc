
<iDEFAULT NAME="showFields" VALUE="lastDelivered, email, id">
<iSET showFields="lastDelivered, email, id">
<iDEFAULT NAME="email" VALUE="">
<iDEFAULT NAME="id" VALUE="">
<iDEFAULT NAME="limitTo" VALUE="25">
<iDEFAULT NAME="startDate" VALUE=`<iDATETIME FMT="%m/%d/%Y %H:%M %p" ADJUST="-3600">`>
<iDEFAULT NAME="endDate" VALUE=`<iDATETIME FMT="%m/%d/%Y %H:%M %p" ADJUST="+120">`>
<iDEFAULT NAME="sortBy1" VALUE="lastDelivered">
<iDEFAULT NAME="sortBy2" VALUE="">
<iDEFAULT NAME="sortBy3" VALUE="">

<iSQLMORE ALIAS="loadDB" SQL="SELECT MIN(DATEPART([year], lastDelivered)) AS firstYear, MAX(DATEPART([year], lastDelivered)) AS lastYear FROM dbo._job_:job (NOLOCK) ;">
<iSQLFETCH ALIAS="loadDB">

<iSET fields="">
<iSTRSPAN SRC=":appConn" FIRST=<iEVAL EXPR=`<iSTRIN SRC=":appConn" DST="DATABASE="> + 9`> NUM=<iEVAL EXPR=`<iSTRLEN SRC=":appConn"> - (<iSTRIN SRC=":appConn" DST="DATABASE="> + 9)`> OUTVAR="dbQualifier">
<iSQLCOLUMNS DBNAME=":appConn" TABLE="_job_:job" QUALIFIER=":dbQualifier" ALIAS="getCols">
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
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" DISABLED VALUE="lastDelivered" <iIF COND=<iSTRIN SRC=":showFields" DST="lastDelivered">>CHECKED</iIF>> Date/Time<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" DISABLED VALUE="email" <iIF COND=<iSTRIN SRC=":showFields" DST="email">>CHECKED</iIF>> Email<BR>
		&nbsp; <INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="showFields" DISABLED VALUE="id" <iIF COND=<iSTRIN SRC=":showFields" DST="id">>CHECKED</iIF>> Record ID<BR>
	</TD>
	<TD VALIGN=TOP>
		Criteria:<BR>
		<TABLE BORDER=0>
		<TR><TD>Email contains </TD><TD><INPUT TYPE=TEXT NAME="email" VALUE=":email"></TD></TR>
		<TR><TD>Record ID is </TD><TD><INPUT TYPE=TEXT NAME="id" VALUE=":id"></TD></TR>
		<TR><TD>Delivered </TD><TD><INPUT CLASS="backgroundColor" TYPE=CHECKBOX NAME="delivered" VALUE="1" <iIF COND=<iSTRCMP SRC=":delivered" DST="1">>CHECKED</iIF>></TD></TR>
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
<TABLE WIDTH="100%" BORDER=0><TR><TD ALIGN=RIGHT>
	Record Limit: <INPUT TYPE=TEXT NAME="limitTo" VALUE=":limitTo" SIZE=2 MAXLENGTH=3>
	<INPUT TYPE=SUBMIT VALUE="Update Report"></TD></TR></TABLE>
</FORM>

<iSET criteria="">
<iIF NOTCOND=<iSTRCMP SRC=":email" DST="">><iREPLACE VAR="email" SRC="'" DST="''"><iSTRCAT DST="criteria" SRC=" AND email LIKE '%:email%'"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":id" DST="">><iSTRKEEP SRC=":id" KEEP="0123456789" OUTVAR="id"><iSTRCAT DST="criteria" SRC=" AND id=:id"></iIF>
<iDEFAULT NAME="delivered" VALUE="0">
<iSTRCAT DST="criteria" SRC=" AND delivered=:delivered">
<iSTRRIGHT SRC=":criteria" NUM=<iEVAL EXPR='<iSTRLEN SRC=":criteria"> - 4'> OUTVAR="criteria">
<iIF NOTCOND=<iSTRCMP SRC=":criteria" DST="">><iSET criteria=" AND :criteria"></iIF>

<iIF COND=:delivered>
	<iSET criteria="AND lastDelivered >= ':startDate' AND ':endDate' >= lastDelivered :criteria">
</iIF>

<iSET sortBy="">
<iIF NOTCOND=<iSTRCMP SRC=":sortBy1" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy1"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":sortBy2" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy2"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":sortBy3" DST="">><iSTRCAT DST="sortBy" SRC=", :sortBy3"></iIF>
<iSTRRIGHT SRC=":sortBy" NUM=<iEVAL EXPR='<iSTRLEN SRC=":sortBy"> - 2'> OUTVAR="sortBy">
<iIF NOTCOND=<iSTRCMP SRC=":sortBy" DST="">><iSET sortBy="ORDER BY :sortBy"></iIF>

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT TOP :limitTo :showFields, delivered, addressee
	FROM dbo._job_:job
	WHERE sent = 1 :criteria :sortBy ;
" ESC=FALSE>
<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">

<iIF NOTCOND=:loadDB_empty ALIAS="hasLogs">
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=3 CELLPADDING=2>
	<TR>
		<iLOOP INITIAL=1 FINAL=:fieldCount ALIAS="fieldLoop">
			<iLISTGET NAME="fieldArray" OP=GETAT INDEX=:fieldLoop DELIM="" OUTVAR="curField">
			<iIF COND=<iSTRIN SRC=":showFields" DST=":curField"> ALIAS="showColumn">
				<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>&nbsp; 
					<iCASE ALIAS="curField" VALUE="delivered"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Delivered')" onMouseOut="noHelp()">Delivered</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="addressee"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Addressee')" onMouseOut="noHelp()">Addressee</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="lastDelivered"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Date/Time')" onMouseOut="noHelp()">Date/Time</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="email"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Email')" onMouseOut="noHelp()">Email</A></iCASE ALIAS="curField">
					<iCASE ALIAS="curField" VALUE="id"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('RecordID')" onMouseOut="noHelp()">Record ID</A></iCASE ALIAS="curField">
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
