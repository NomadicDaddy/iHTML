<iREMBLOCK>
adminware CopyManager (Public Module)
Copyright © 1998-2002 adminware, inc.  All rights reserved.
</iREMBLOCK>

<iSET AWPV="CopyManager v1.31.192.1" DemoDSN="adminware_copymanager" demo=0 AWPID="copymanager">

<iDEFAULT NAME="login" VALUE="/">

<iDEFAULT NAME="dsn" VALUE="">
<iIF COND=<iSTRCMP SRC=":dsn" DST="">><iSTOP></iIF>

<iSET showErrors=0><iINCLUDE NAME="d:\adminware.com\apps\ifuncs\errorHandler.inc">
<iINCLUDE NAME="d:\adminware.com\apps\shared\config.inc">

<iDEFAULT NAME="show" VALUE="News">
<iDEFAULT NAME="showAll" VALUE="0">
<iDEFAULT NAME="showColNums" VALUE="0">

<iSQL LOGIN=":login" DBNAME=":dsn" SQL="SELECT COUNT(*) AS pmCount FROM :show :nolock WHERE active=1 ;" ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
<iSET pm_entries=":loadDB_pmCount">
<iIF NOTCOND=<iISDIGIT SRC=":pm_entries">><iSET pm_entries=0></iIF>

<iSQLMORE SQL="SELECT id FROM _dbs :nolock WHERE name=':show' ;" ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
<iSET db=":loadDB_id">
<iIF NOTCOND=<iISDIGIT SRC=":db">><iSET db=0></iIF>

<iIF EXPR=':db GT 0' ALIAS="goodDB1">
	<iSQLMORE SQL="SELECT id FROM _dbs :nolock WHERE name=':Show' AND active=1 ;" ALIAS="loadDB">
	<iSQLFETCH ALIAS="loadDB">
	<iSET activeDB=":loadDB_id">
	<iIF NOTCOND=<iISDIGIT SRC=":activeDB">><iSET activeDB=0></iIF>

	<iIF EXPR=':activeDB GT 0 OR :showColNums' ALIAS="goodDB2">

		<iREM -- Create Field Array -- >
		<iSET fcount=0>
		<iSQLMORE SQL="SELECT * FROM _fields :nolock WHERE parent=:db ORDER BY id ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
			<iEVAL EXPR=':fCount + 1' OUTVAR="fCount">
			<iEQ NAME="fName_:fcount" VALUE="z:loadDB_fName" EVAL=TRUE>
			<iEQ NAME="fType_:fcount" VALUE=":loadDB_fType" EVAL=TRUE>
			<iEQ NAME="fPre_:fcount" VALUE=":loadDB_fPre" EVAL=TRUE>
			<iEQ NAME="fPost_:fcount" VALUE=":loadDB_fPost" EVAL=TRUE>
			<iEQ NAME="fSize_:fcount" VALUE=":loadDB_fSize" EVAL=TRUE>
			<iEQ NAME="fImgBorder_:fcount" VALUE=":loadDB_fImgBorder" EVAL=TRUE>
			<iEQ NAME="fImgAlign_:fcount" VALUE=":loadDB_fImgAlign" EVAL=TRUE>
			<iEQ NAME="fImgLinkToOnly_:fcount" VALUE=":loadDB_fImgLinkToOnly" EVAL=TRUE>
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>

		<iREM -- Setup List for Field Display Order & Count -- >
		<iSQLMORE SQL="SELECT fieldDisplayOrder FROM _dbs :nolock WHERE id=:db ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		<iSET fieldDisplayOrder=":loadDB_fieldDisplayOrder">
		<iIF COND=<iSTRCMP SRC=":fieldDisplayOrder" DST="">><iSET fieldDisplayOrder=0></iIF>
		<iLISTCREATE NAME="fieldOrder" DELIM="" SRC="fieldDisplayOrder" TYPE=VARIABLE>
		<iLISTGET NAME="fieldOrder" DELIM="" OP=COUNT OUTVAR="fDOCount">

		<iSQLMORE SQL="SELECT * FROM _dbs :nolock WHERE id=:db ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">

		<iREM -- Assign PageName -- >
		<iIF EXPR=':showColNums' ALIAS="page"><iSET pageName=":loadDB_liveURL"><iELSE ALIAS="page"><iSET pageName=":i_script_name"></iIF ALIAS="page">

		<iREM -- Use Alternate DisplayName if Specified -- >
		<iSET displayName=':show'><iIF NOTCOND=<iSTRCMP SRC=":loadDB_displayName" DST=""> ALIAS="altName"><iSET displayName=':loadDB_displayName'></iIF ALIAS="altName">

		<iDEFAULT NAME="displayStyle" VALUE="normal">

		<iCASE ALIAS="displayStyle" VALUE="normal">
			<iREM -- Are there new items? -- >
			<iSET noNew=0>
			<iIF COND=<iISDEF VAR="ck_lvisit"> ALIAS="newItems">
				<iSQLMORE SQL="SELECT MAX(posted) AS maxDate FROM :show :nolock WHERE active=1 ;" ALIAS="loadDB">
				<iSQLFETCH ALIAS="loadDB">
				<iSET maxDate=":loadDB_maxDate">
				<iIF COND=<iSTRCMP SRC=":maxDate" DST="">><iSET maxDate="NA"></iIF>
				<iIF NOTCOND=<iSTRCMP SRC=":maxDate" DST="NA"> ALIAS="anyNew">
					<iIF COND=<iSTRCMP SRC=":ck_lvisit" DST="-">>
						<iDATE ODBC=":ck_lvisit" FMT="%m/%d/%Y" OUTVAR="lastVisit">
					<iELSE>
						<iSET lastVisit=":ck_lvisit">
					</iIF>
					<iCRDATE ODBC=':maxDate' FMT='%m/%d/%Y' OUTVAR="maxDate">
					<iIF EXPR='<iSTRIN SRC=":ck_lvisit" DST="lastVisit"> OR <iSTRIN SRC=":ck_lvisit" DST="ck_lvisit">' ALIAS="badCookie">
						<iDATE FMT="%m/%d/%Y" OUTVAR="ck_lvisit">
					</iIF ALIAS="badCookie">
					<iIF EXPR='<iSTRIN SRC=":lastVisit" DST="lastVisit"> OR <iSTRIN SRC=":lastVisit" DST="ck_lvisit">' ALIAS="badCookie">
						<iDATE FMT="%m/%d/%Y" OUTVAR="lastVisit">
					</iIF ALIAS="badCookie">
					<iDATEDIFF DATE1=":lastVisit" DATE2=":MaxDate" OUTVAR="diff">
					<iIF EXPR=':diff LT 0' ALIAS="y"><iSET noNew=1></iIF ALIAS="y">
				</iIF ALIAS="anyNew">
			<iELSE ALIAS="newItems">
				<iDATE FMT="%m/%d/%Y" OUTVAR="lastVisit">
				<iSET noNew=1>
			</iIF ALIAS="newItems">
			<iCOOKIE NAME="ck_lvisit" VALUE=":lastVisit" PATH="/">
		</iCASE ALIAS="displayStyle">

		<iIF EXPR='NOT :loadDB_hideHeader' ALIAS="hideHeader">
			<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":loadDB_barColor"><TD><FONT FACE=":loadDB_barTextFace" SIZE=":loadDB_barTextSize" COLOR=":loadDB_barTextColor"><B>:displayName</B></FONT></TD>
			<iCASE ALIAS="displayStyle" VALUE="normal">
				<TD ALIGN=RIGHT><FONT FACE=":loadDB_listTextFace" SIZE=":loadDB_listTextSize" COLOR=":loadDB_barTextColor">Your last visit was on <B>:lastVisit</B>.	
					<iIF EXPR=':noNew' ALIAS="nope">
						No new items have been posted.
					<iELSE ALIAS="nope">
						Items posted since then have been marked new.
					</iIF ALIAS="nope">
				</FONT></TD>
			</iCASE ALIAS="displayStyle">
			</TR></TABLE>
		</iIF ALIAS="HideHeader">

		<BR><CENTER><TABLE <iIF NOTCOND=<iSTRCMP SRC=":loadDB_tableWidth" DST="">>WIDTH=:loadDB_tableWidth</iIF> <iIF NOTCOND=<iSTRCMP SRC=":loadDB_tableHeight" DST="">>HEIGHT=:loadDB_tableHeight</iIF> BORDER=<iIF NOTCOND=<iSTRCMP SRC=":loadDB_tableBorder" DST="">>:loadDB_tableBorder<iELSE>0</iIF> CELLSPACING=0 CELLPADDING=3>

		<iSET dtfmt=":loadDB_dateFormat"><iIF EXPR=':loadDB_showTime' ALIAS="showTime"><iSET dtfmt=":loadDB_dateFormat :loadDB_timeFormat"></iIF ALIAS="showTime">
		<iSET pMCount=0 whichRow=1 arcItems=0>

		<iCASE ALIAS="displayStyle" VALUE="calendar">

			<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
			var winW = 190;
			var winH = 240;
			if (document.all) {
				var pageW = document.body.scrollWidth;
				var pageH = document.body.scrollHeight;
			}
			else if (document.layers) {
				var pageW = self.document.width;
				var pageH = self.document.height;
			}
			else {
				var pageW = screen.width;
				var pageH = screen.height;
			}
			var winX = (pageW/2)-(winW/2);
			var winY = (pageH/2)-(winH/2);
			var winProps = ", width="+winW+", height="+winH+", left="+winX+", top="+winY;
			//--></SCRIPT>

			<iDATE FMT="%d" OUTVAR="currentDay">
			<iDATE FMT="%m" OUTVAR="currentMonth">
			<iDATE FMT="%Y" OUTVAR="currentYear">
			<iDEFAULT NAME="selectedDay" VALUE=":currentDay">
			<iDEFAULT NAME="selectedMonth" VALUE=":currentMonth">
			<iDEFAULT NAME="selectedYear" VALUE=":currentYear">
			<iDATEEXT DATE=":selectedMonth/1/:selectedYear" TYPE=DAYSINMONTH OUTVAR="daysInMonth">
			<iDATEEXT DATE=":selectedMonth/1/:selectedYear" TYPE=FIRSTDAYMONTH OUTVAR="firstDayMonth">
			<iIF EXPR=':selectedDay GT :daysInMonth'><iSET selectedDay=:daysInMonth></iIF>

			<iDEFAULT NAME="dayCellHeight" VALUE="75">

			<iSET prevYear=:selectedYear>
			<iEVAL EXPR=':selectedMonth - 1' OUTVAR="prevMonth">
			<iIF EXPR=':prevMonth = 0'>
				<iSET prevMonth=12>
				<iEVAL EXPR=':selectedYear - 1' OUTVAR="prevYear">
			</iIF>
			<iDATEEXT DATE=`:prevMonth/:selectedDay/:prevYear` TYPE=DAYSINMONTH OUTVAR="daysInPrevMonth">

			<iSET nextYear=:selectedYear>
			<iEVAL EXPR=':selectedMonth + 1' OUTVAR="nextMonth">
			<iIF EXPR=':nextMonth = 13'>
				<iSET nextMonth=1>
				<iEVAL EXPR=':selectedYear + 1' OUTVAR="nextYear">
			</iIF>

<iREMBLOCK>
			<!--
				currentDay = ':currentDay', currentMonth = ':currentMonth', currentYear = ':currentYear'
				selectedDay = ':selectedDay', selectedMonth = ':selectedMonth', selectedYear = ':selectedYear', daysInMonth = ':daysInMonth', firstDayMonth = ':firstDayMonth'
			-->
</iREMBLOCK>

			<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0><TR>
				<TD ALIGN=RIGHT VALIGN=CENTER HEIGHT=24><A HREF=':pageName?show=:show&dsn=:dsn&selectedMonth=:prevMonth&selectedYear=:prevYear'><IMG SRC="http://adminware.com/images/adminware/arrow_left.gif" ALT="<" WIDTH=24 HEIGHT=24 BORDER=0></A></TD>
				<TD ALIGN=CENTER VALIGN=CENTER HEIGHT=24 WIDTH="1%" NOWRAP><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor">&nbsp;<B><iCRDATE MONTH=:selectedMonth DAY=:selectedDay YEAR=:selectedYear FMT="%B, %Y"></B>&nbsp;</FONT></TD>
				<TD ALIGN=LEFT VALIGN=CENTER HEIGHT=24><A HREF=':pageName?show=:show&dsn=:dsn&selectedMonth=:nextMonth&selectedYear=:nextYear'><IMG SRC="http://adminware.com/images/adminware/arrow_right.gif" ALT=">" WIDTH=24 HEIGHT=24 BORDER=0></A></TD>
			</TR></TABLE><BR>
			<TABLE WIDTH="100%" BORDER=1 CELLSPACING=0 CELLPADDING=0 BORDERCOLOR="#000000">
			<TR BGCOLOR=":loadDB_rowColor2">
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Sunday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Monday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Tuesday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Wednesday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Thursday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Friday</B></FONT></TD>
				<TD WIDTH="14%" ALIGN=CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><B>Saturday</B></FONT></TD>
			</TR>
			<iSET coordinate=0>
			<iLOOP INITIAL=1 FINAL=6 ALIAS="calRows">
				<TR HEIGHT=:dayCellHeight>
					<iLOOP INITIAL=0 FINAL=6 ALIAS="calColumns">
						<iEVAL EXPR=':coordinate - :firstDayMonth + 1' PREC=0 OUTVAR="calDay">
						<TD <iIF EXPR=':coordinate LT :firstDayMonth OR :daysInMonth LT :calDay'>BGCOLOR="#CCCCCC"<iELSEIF EXPR=':selectedMonth = :currentMonth AND :selectedYear = :currentYear AND :calDay = :currentDay'>BGCOLOR="#FFFFCC"</iIF> VALIGN=TOP><FONT FACE=":loadDB_headTextFace" COLOR=":loadDB_headTextColor">
							<iIF EXPR=':calDay GT 0 AND :calDay LTE :daysInMonth' ALIAS="isDay">
								&nbsp;<B>:calDay</B>

								<iSQLMORE SQL="SELECT * FROM :show :nolock WHERE posted=':selectedYear-:selectedMonth-:calDay' ;" ALIAS="loadDB">
								<iSQLFETCH ALIAS="loadDB">
								<iIF NOTCOND=:i_sqlempty ALIAS="showEvent">
									<BR><CENTER><FONT FACE=":loadDB_bodyTextFace" SIZE=":loadDB_bodyTextSize" COLOR=":loadDB_bodyTextColor">
									<iWHILE NOTALIAS=i_sqlempty>
										<iIF COND=<iSTRCMP SRC=":loadDB_zBlurb" DST=""> ALIAS="noBlurb">
											:loadDB_zEvent
										<iELSE ALIAS="noBlurb">
											<iCRDATE MONTH=:selectedMonth DAY=:calDay YEAR=:selectedYear FMT="%B %d, %Y" OUTVAR="thisDayString">
											<iSET safeBlurb=":loadDB_zBlurb">
											<iREPLACE VAR="safeBlurb" SRC=`"` DST=`\"`>
											<iREPLACE VAR="safeBlurb" SRC=":i$crlf" DST="">
											<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
											function dynaPop:loadDB_id() {
												PopUp=window.open("", "Event", "scrollbars=auto, dependent=yes"+winProps);
												PopUp.opener=self;
												PopUp.document.write("<HTML><HEAD><TITLE>:loadDB_zEvent</TITLE></HEAD><BODY BGCOLOR=\"#FFFFCC\" TEXT=\"#000000\" STYLE=\"overflow:auto;\"><FONT FACE=\":loadDB_bodyTextFace\" SIZE=\":loadDB_bodyTextSize\" COLOR=\":loadDB_bodyTextColor\"><B><U>:thisDayString</U></B><BR><BR><B>:loadDB_zEvent</B><BR><BR>:safeBlurb<BR><P ALIGN=CENTER><A HREF=\"#\" onClick=\"window.close(self)\">Close Window</A></P></FONT></BODY></HTML>");
												PopUp.document.close();
											}
											//--></SCRIPT>
											<A HREF="javascript:dynaPop:loadDB_id();">:loadDB_zEvent</A>
										</iIF ALIAS="noBlurb">
										<BR>
										<iSQLFETCH ALIAS="loadDB">
									</iWHILE ALIAS=i_sqlempty>
									</FONT></CENTER>
								</iIF ALIAS="showEvent">

							<iELSE ALIAS="isDay">
								<iIF EXPR=':calDay LT 1' ALIAS="outsideMonth">
									<FONT SIZE="-1">&nbsp;<iEVAL EXPR=':daysInPrevMonth + :calDay'></FONT>
								<iELSE ALIAS="outsideMonth">
									<FONT SIZE="-1">&nbsp;<iEVAL EXPR=':calDay - :daysInMonth'></FONT>
								</iIF ALIAS="outsideMonth">
							</iIF ALIAS="isDay">
						</FONT></TD>

						<iEVAL EXPR=':coordinate + 1' OUTVAR="coordinate">
					</iLOOP ALIAS="calColumns">
				</TR>
			</iLOOP ALIAS="calRows">
			</TABLE>

		</iCASE ALIAS="displayStyle">

		<iCASE ALIAS="displayStyle" VALUE="normal">

			<iIF COND=<iISDIGIT SRC=":entry"> ALIAS="showEntry">

				<iSQLMORE SQL="SELECT * FROM :show :nolock WHERE id=:entry ;" ALIAS="loadDB">

			<iELSE ALIAS="ShowEntry">

				<iREM -- Establish Group Order -- >
				<iSET groupOrder="">
				<iIF EXPR=':loadDB_groupField GT 0' ALIAS="altGroup">
					<iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT fName FROM _fields :nolock WHERE id=:loadDB_groupField ;" OUTPUT="z:1," NOOUTPUT="" FAILURE="" OUTVAR="groupOrder">
				</iIF ALIAS="altGroup">

				<iREM -- Establish Sort Order -- >
				<iIF EXPR=':loadDB_sortField GT 0' ALIAS="altSort">
					<iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT fName FROM _fields :nolock WHERE id=:loadDB_sortField ;" OUTPUT="z:1" NOOUTPUT="" FAILURE="" OUTVAR="sortOrder">
				<iELSEIF EXPR=':loadDB_sortField = 0' ALIAS="altSort">
					<iSET sortOrder="id">
				<iELSE ALIAS="altSort">
					<iSET sortOrder="posted">
				</iIF ALIAS="altSort">

				<iREM -- Establish Sort Direction -- >
				<iSET dispOrder=";"><iIF EXPR=':loadDB_descending' ALIAS="descending"><iSET dispOrder="DESC ;"></iIF ALIAS="descending">
				<iSET groupSort=":groupOrder:sortOrder"><iIF COND=<iSTRCMP SRC=`<iSTRIPCHR SRC=":groupOrder" CHR=",">` DST=`<iSTRIPCHR SRC=":sortOrder" CHR=",">`>><iSET groupSort=":sortOrder"></iIF>

				<iSQLMORE SQL="SELECT * FROM :show :nolock WHERE active=1 ORDER BY :groupSort :dispOrder" ALIAS="loadDB">

			</iIF ALIAS="ShowEntry">

			<iREM -- Header Row -- >
			<iIF EXPR=':loadDB_showHeaderRow' ALIAS="headerRow">
				<TR>
					<iIF EXPR=':loadDB_showNewIndicator' ALIAS="showNI"><TD WIDTH=1%>&nbsp;</TD></iIF ALIAS="showNI">
					<iIF EXPR=':loadDB_showDate' ALIAS="showDate"><TD WIDTH=1%>&nbsp;</TD></iIF ALIAS="showDate">
					<iIF EXPR=':loadDB_fieldDisplayType' ALIAS="fDT">
						<iREM -- Display Fields in Preferred Order -- >
						<iLOOP INITIAL=1 FINAL=:fDOCount ALIAS="fDO">
							<iIF COND=<iSTRIN SRC=":loadDB_fieldDisplayOrder" DST=":fDO"> ALIAS="doDisplay">
								<TD><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor">
								<iLISTGET NAME="fieldOrder" OP=GETAT INDEX=":fDO" OUTVAR="next">
								<iREM -- Get Field Settings -- >
								<iEQ NAME="nextField" VALUE=":fName_:next" EVAL=TRUE><iEQ NAME="fieldType" VALUE=":fType_:next" EVAL=TRUE>
								<iREM -- Remove 'z' Prefix for Display Purposes -- >
								<iSTRRIGHT SRC=":nextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':nextField'> - 1'> OUTVAR="viewField">
								<B><U>:viewField</U></B>
								</FONT></TD>
							</iIF ALIAS="doDisplay">
						</iLOOP ALIAS="fDO">
					<iELSE ALIAS="FDT">
						<TD><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor">
						<iREM -- Display Fields in Preferred Order -- >
						<iLOOP INITIAL=1 FINAL=:fDOCount ALIAS="fDO">
							<iIF COND=<iSTRIN SRC=":loadDB_fieldDisplayOrder" DST=":fDO"> ALIAS="doDisplay">
								<iLISTGET NAME="fieldOrder" OP=GETAT INDEX=":fDO" OUTVAR="next">
								<iREM -- Get Field Settings -- >
								<iEQ NAME="nextField" VALUE=":fName_:next" EVAL=TRUE><iEQ NAME="fieldType" VALUE=":fType_:next" EVAL=TRUE>
								<iREM -- Remove 'z' Prefix for Display Purposes -- >
								<iSTRRIGHT SRC=":nextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':nextField'> - 1'> OUTVAR="viewField">
								<B><U>:viewField</U></B>
							</iIF ALIAS="DoDisplay">
						</iLOOP ALIAS="FDO">
						</FONT></TD>
					</iIF ALIAS="FDT">
				</TR>
			</iIF ALIAS="headerRow">

			<iSQLFETCH ALIAS="loadDB">
			<iWHILE NOTALIAS=i_sqlempty>
				<iEVAL EXPR=':pMCount + 1' OUTVAR="pMCount">
				<iCRDATE ODBC=':loadDB_posted' FMT='%m/%d/%Y' OUTVAR="pMDate">
				<iDATEDIFF DATE1=":lastVisit" DATE2=":PMDate" OUTVAR="diff">
				<iDEFAULT NAME="goLinkTo" VALUE="0">

				<iIF NOTCOND=:showAll>
					<iEVAL EXPR='(:diff GT -:loadDB_archiveCutoff) OR :loadDB_archiveCutoff=0 OR :showAll OR :goLinkTo' OUTVAR="showIt">
				<iELSE>
					<iEVAL EXPR='(:diff LT -:loadDB_archiveCutoff) AND NOT :loadDB_archiveCutoff=0 OR :goLinkTo' OUTVAR="showIt">
				</iIF>

				<iIF EXPR=':showIt' ALIAS="notArchived">

					<iREM -- Insert Row Pre-Separator if not First Row -- >
					<iIF EXPR=':pm_entries NE 1 AND NOT <iSTRCMP SRC=":loadDB_rPre" SRC="">' ALIAS="recPre">
						<TR><TD>&nbsp;</TD><TD COLSPAN=2>:loadDB_rPre</TD></TR>
					</iIF ALIAS="RecPre">

					<iREM -- Define Row Colors -- >
					<iSET rowColor="">
					<iIF EXPR=':loadDB_altRowColor' ALIAS="alternate">
						<iIF EXPR=':whichRow = 1 AND NOT <iSTRCMP SRC=":loadDB_rowColor1" DST="">' ALIAS="whichColor">
							<iSET rowColor="BGCOLOR=':loadDB_rowColor1'" whichRow=2>
						<iELSEIF EXPR=':whichRow = 2 AND NOT <iSTRCMP SRC=":loadDB_rowColor2" DST="">' ALIAS="whichColor">
							<iSET rowColor="BGCOLOR=':loadDB_rowColor2'" whichRow=1>
						</iIF ALIAS="whichColor">
					<iELSEIF NOTCOND=<iSTRCMP SRC=":loadDB_rowColor1" DST=""> ALIAS="alternate">
						<iSET rowColor="BGCOLOR=':loadDB_rowColor1'">
					</iIF ALIAS="alternate">
			 
					<iREM -- Output Items in the DB -- >
					<TR>
						<iIF EXPR=':loadDB_showNewIndicator' ALIAS="showNI"><TD WIDTH=1% VALIGN=TOP NOWRAP><iIF EXPR=':diff GTE 0 AND NOT :noNew' ALIAS="isNew">:loadDB_newIndicator</iIF ALIAS="isNew">&nbsp;</TD></iIF ALIAS="showNI">
						<iIF EXPR=':loadDB_showDate' ALIAS="showDate"><TD WIDTH=1% VALIGN=TOP NOWRAP><FONT FACE=":loadDB_bodyTextFace" SIZE=":loadDB_bodyTextSize" COLOR=":loadDB_bodyTextColor"><B><iCRDATE ODBC=':loadDB_posted' FMT=':dtfmt'></B></FONT>&nbsp;</TD></iIF ALIAS="showDate">

						<iIF EXPR=':loadDB_fieldDisplayType' ALIAS="fDT">

							<iREM -- Display Fields in Preferred Order -- >
							<iLOOP INITIAL=1 FINAL=:fDOCount ALIAS="fDO">
								<iIF COND=<iSTRIN SRC=":loadDB_fieldDisplayOrder" DST=":fDO"> ALIAS="doDisplay">
									<TD :RowColor><FONT FACE=":loadDB_bodyTextFace" SIZE=":loadDB_bodyTextSize" COLOR=":loadDB_bodyTextColor">
									<iLISTGET NAME="fieldOrder" OP=GETAT INDEX=":fDO" OUTVAR="next">
									<iREM -- Get Field Settings -- >
									<iEQ NAME="nextField" VALUE=":fName_:next" EVAL=TRUE><iEQ NAME="fieldType" VALUE=":fType_:next" EVAL=TRUE>
									<iREM -- Remove 'z' Prefix for Display Purposes -- >
									<iSTRRIGHT SRC=":nextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=":nextField"> - 1'> OUTVAR="viewField">
									<iIF EXPR=':loadDB_showTitles' ALIAS="showTitles"><B><U>:viewField:</U></B><BR></iIF ALIAS="showTitles">
									<iIF EXPR=':showColNums' ALIAS="colNums">(<B>#:next</B>)</iIF ALIAS="colNums">
									<iIF COND=<iISDEF VAR="debug"> ALIAS="debug">(<B>#:next :nextField</B>)</iIF ALIAS="debug">

									<iIF EXPR=':loadDB_linkToField = :next AND :goLinkTo = 0' ALIAS="linkTo">
										<A HREF=':pageName?show=:show&entry=:loadDB_id&goLinkTo=:next&dsn=:dsn'>:loadDB_linkToText</A>
									<iELSE ALIAS="linkTo">

										<iEQ NAME="nextFieldVal" VALUE=":loadDB_:nextField" EVAL=TRUE>
										<iIF EXPR='<iSTRCMP SRC=":fieldType" DST="Image"> AND NOT <iSTRCMP SRC=":nextFieldVal" DST="">' ALIAS="isImg">
											<iEQ NAME="imgLinkToOnly" VALUE=":fImgLinkToOnly_:next" EVAL=TRUE>
											<iIF EXPR='(:goLinkTo AND :imgLinkToOnly) OR NOT :imgLinkToOnly' ALIAS="showOnLinkTo">
												<iSET imgURL=":imagedir">
												<iREPLACE VAR="imgURL" SRC="d:\" DST="http://www.">
												<iREPLACE VAR="imgURL" SRC="d:\" DST="http://www.">
												<iREPLACE VAR="imgURL" SRC="htdocs\" DST="">
												<iREPLACE VAR="imgURL" SRC="\" DST="/">
												<iEQ NAME="imgBorder" VALUE=":fImgBorder_:next" EVAL=TRUE>
												<iEQ NAME="imgAlign" VALUE=":fImgAlign_:next" EVAL=TRUE>
												<IMG SRC=":imgURL/copymanager/:nextFieldVal" ALT="" BORDER=:imgBorder ALIGN=:imgAlign>
											</iIF ALIAS="showOnLinkTo">
										<iELSE ALIAS="isImg">
											<iEQ VALUE=":fPre_:next :loadDB_:nextField :fPost_:next" EVAL=TRUE>
										</iIF ALIAS="isImg">

										<iIF COND=<iSTRCMP SRC=':nextFieldVal' DST=""> ALIAS="blank">&nbsp;</iIF ALIAS="blank">

									</iIF ALIAS="linkTo">
									</FONT></TD>
								</iIF ALIAS="doDisplay">
							</iLOOP ALIAS="fDO">

						<iELSE ALIAS="fDT">

							<TD :rowColor><FONT FACE=":loadDB_bodyTextFace" SIZE=":loadDB_bodyTextSize" COLOR=":loadDB_bodyTextColor">
							<iREM -- Display Fields in Preferred Order -- >
							<iLOOP INITIAL=1 FINAL=:fDOCount ALIAS="fDO">
								<iIF COND=<iSTRIN SRC=":loadDB_fieldDisplayOrder" DST=":fDO"> ALIAS="doDisplay">
									<iLISTGET NAME="fieldOrder" OP=GETAT INDEX=":fDO" OUTVAR="next">
									<iREM -- Get Field Settings -- >
									<iEQ NAME="nextField" VALUE=":fName_:next" EVAL=TRUE><iEQ NAME="fieldType" VALUE=":fType_:next" EVAL=TRUE>
									<iREM -- Remove 'z' Prefix for Display Purposes -- >
									<iSTRRIGHT SRC=":nextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=":nextField"> - 1'> OUTVAR="ViewField">
									<iIF EXPR=':loadDB_showTitles' ALIAS="showTitles"><B><U>:viewField:</U></B><BR></iIF ALIAS="showTitles">
									<iIF EXPR=':showColNums' ALIAS="colNums">(<B>#:next</B>)</iIF ALIAS="colNums">
									<iIF COND=<iISDEF VAR="debug"> ALIAS="debug">(<B>#:next :nextField</B>)</iIF ALIAS="debug">
									<iIF EXPR=':loadDB_linkToField = :next AND :goLinkTo = 0' ALIAS="linkTo">
										<A HREF=':i_script_name?show=:show&entry=:loadDB_id&goLinkTo=:next&dsn=:dsn'>:loadDB_linkToText</A>
									<iELSE ALIAS="linkTo">
										<iEQ NAME="nextFieldVal" VALUE=":loadDB_:nextField" EVAL=TRUE>
										<iIF EXPR='<iSTRCMP SRC=":fieldType" DST="Image"> AND NOT <iSTRCMP SRC=":nextFieldVal" DST="">' ALIAS="isImg">
											<iEQ NAME="imgLinkToOnly" VALUE=":fImgLinkToOnly_:next" EVAL=TRUE>
											<iIF EXPR='(:goLinkTo AND :imgLinkToOnly) OR NOT :imgLinkToOnly' ALIAS="showOnLinkTo">
												<iSET imgURL=":imagedir">
												<iREPLACE VAR="imgURL" SRC="d:\" DST="http://www.">
												<iREPLACE VAR="imgURL" SRC="d:\" DST="http://www.">
												<iREPLACE VAR="imgURL" SRC="htdocs\" DST="">
												<iREPLACE VAR="imgURL" SRC="\" DST="/">
												<iEQ NAME="imgBorder" VALUE=":fImgBorder_:next" EVAL=TRUE>
												<iEQ NAME="imgAlign" VALUE=":fImgAlign_:next" EVAL=TRUE>
												<IMG SRC=":imgURL/copymanager/:nextFieldVal" ALT="" BORDER=:imgBorder ALIGN=:imgAlign>
											</iIF ALIAS="showOnLinkTo">
										<iELSE ALIAS="isImg">
											<iEQ VALUE=":fPre_:next :loadDB_:nextField :fPost_:next" EVAL=TRUE>
										</iIF ALIAS="isImg">
									</iIF ALIAS="linkTo">
								</iIF ALIAS="doDisplay">
							</iLOOP ALIAS="fDO">
							</FONT></TD>

						</iIF ALIAS="fDT">

					</TR>

					<iREM -- Show Back Button if ShowEntry -- >
					<iIF COND=<iISDIGIT SRC="entry"> ALIAS="showBack">
						<TR><TD COLSPAN=3 ALIGN=CENTER><A HREF="javascript:window.history.go(-1)">Go Back</A></TD></TR>
					</iIF ALIAS="showBack">

					<iREM -- Insert Row Post-Separator if not Last Row -- >
					<iIF EXPR=':pMCount LT :pm_entries AND NOT <iSTRCMP SRC=":loadDB_rPost" SRC="">' ALIAS="recPost">
						<TR><TD>&nbsp;</TD><TD COLSPAN=2>:loadDB_rPost</TD></TR>
					</iIF ALIAS="recPost">

				<iELSE ALIAS="NotArchived">
					<iEVAL EXPR=':arcItems + 1' OUTVAR="arcItems">
				</iIF ALIAS="NotArchived">

				<iSQLFETCH ALIAS="loadDB">
			</iWHILE ALIAS=i_sqlempty>

			</TD></TR></TABLE></CENTER><BR>

			<iIF EXPR=':arcItems GT 0 AND NOT :showAll' ALIAS="archived">
				<BR><CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><A HREF=':i_script_name?show=:show&showAll=1'>View Archived Entries</A> (:arcItems item<iIF EXPR=':arcItems GT 1' ALIAS="plural">s</iIF ALIAS="plural"> archived)</FONT></CENTER><BR>
			<iELSEIF EXPR=':arcItems GT 0 AND :showAll' ALIAS="archived">
				<BR><CENTER><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor"><A HREF=':i_script_name?show=:show&showAll=0'>View Active Entries</A></FONT></CENTER><BR>
			</iIF ALIAS="archived">

			<iIF EXPR=':pMCount = 0' ALIAS="noItems">
				<BR><CENTER><BLOCKQUOTE><FONT FACE=":loadDB_headTextFace" SIZE=":loadDB_headTextSize" COLOR=":loadDB_headTextColor">There are no active items in the <B>:show Database</B> at this time.</FONT></BLOCKQUOTE></CENTER><BR>
			</iIF ALIAS="noItems">

		</iCASE ALIAS="displayStyle">

		<iIF EXPR='NOT :loadDB_hideFooter' ALIAS="hideFooter"><TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":loadDB_barColor" ALIGN=RIGHT><TD COLSPAN=2><FONT FACE=":loadDB_barTextFace" SIZE=":loadDB_barTextSize" COLOR=":loadDB_barTextColor"><B>:AWPV</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B>Copyright &copy; 1998-2002 adminware, inc.  All rights reserved.</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B><A HREF="http://adminware.com/" onMouseOver="status='adminware'; return true;" onMouseOut="status='';">http://adminware.com/</A></B></FONT></TD></TR></TABLE></iIF ALIAS="hideFooter">

		</iSQL ALIAS="loadDB">

	<iELSE ALIAS="goodDB2">

		<CENTER><FONT COLOR="#FF0000"><B>That CopyManager Database is not currently active.</B></FONT><BR><BR></CENTER>

	</iIF ALIAS="goodDB2">

<iELSE ALIAS="goodDB1">

	<CENTER><FONT COLOR="#FF0000"><B>There is no CopyManager Database with that name currently setup.</B></FONT><BR>Check the name and try again or use the Administrative interface to create this CopyManager Database.<BR><BR></CENTER>

</iIF ALIAS="goodDB1">

<iREM -- Reset Variables for Multiple Instance on Page Handling -- >
<iREM -- OLD WAY: iSET fieldOrder="" fDO="" next="" entry="" goLinkTo="" -- >
<iUNDEFINE fieldOrder fDO next entry goLinkTo>

<iIF COND=<iISDEF VAR="debug"> ALIAS="debug"><BR><HR NOSHADE><iHEAPDUMP HEAP=LOCAL></iIF ALIAS="debug">
