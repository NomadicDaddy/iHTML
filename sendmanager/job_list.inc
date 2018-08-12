<iIF COND=<iISDEF VAR="refreshAfter">>
	<EMBED SRC="/images/cashregister.wav" HEIGHT=1 WIDTH=1 AUTOLOAD=TRUE AUTOSTART=TRUE HIDDEN=TRUE LOOP=0 CONTROLS=SMALLCONSOLE><BGSOUND SRC="/images/cashregister.wav" LOOP=0></EMBED>
</iIF>

<iDEFAULT NAME="step" VALUE="1">

<iREM -- Delete Job -- >
<iIF COND=<iSTRCMP SRC=":step" DST="2"> ALIAS="deleteJob">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM dbo.jobs WHERE id = :job AND client_id = :client_id ;">
	<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
	<iIF NOTCOND=:loadDB_empty ALIAS="authorized">
		<iSQLMORE ALIAS="loadDB" SQL="DELETE FROM dbo.jobs WHERE id=:job ;">
		<iSQLMORE ALIAS="loadDB" SQL="DELETE FROM dbo._fields WHERE parent='_job_:job' ;">
		<iSET index="dbo._job_:job"><iSTRCAT DST="index" SRC=".ix__job_:job">
		<iSQLMORE ALIAS="loadDB" SQL="DROP INDEX :index ;">
		<iSQLMORE ALIAS="loadDB" SQL="DROP TABLE dbo._job_:job ;">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS transactions FROM dbo.transactions (NOLOCK) WHERE job_id = :job ;">
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		<iIF COND=<iSTRCMP SRC=":loadDB_transactions" DST="1"> ALIAS="zeroTrans">
			<iSQLMORE ALIAS="loadDB" SQL="DELETE FROM dbo.transactions WHERE job_id=:job ;">
		</iIF ALIAS="zeroTrans">
	</iIF ALIAS="authorized">
	<DIV CLASS="errorText">Job ':jobTitle' has been deleted.</DIV>
</iIF ALIAS="deleteJob">

<iREM -- Show Charges -- >
<iIF EXPR=':appAccess>2' ALIAS="checkAccess">
	<iSET showCharges=1>
<iELSE ALIAS="checkAccess">
	<iSET showCharges=0>
</iIF ALIAS="checkAccess">

<iSQLMORE ALIAS="loadDB" SQL="SELECT * FROM jobs (NOLOCK) WHERE client_id = :client_id ;">
<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
<iIF NOTCOND=:loadDB_empty ALIAS="hasJobs">
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=3 CELLPADDING=2>
	<TR>
		<TD>&nbsp;</TD>
		<TD CLASS="tableHeading" COLSPAN=2 ALIGN=CENTER VALIGN=BOTTOM>:appUnits</TD>
		<TD COLSPAN=2>&nbsp;</TD>
	</TR>
	<TR>
		<TD CLASS="tableHeading">&nbsp; <A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Title')" onMouseOut="noHelp()">Job Title</A></TD>
		<TD CLASS="tableHeading" WIDTH="1%" ALIGN=CENTER><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Total Recipients')" onMouseOut="noHelp()">Total</A></TD>
		<TD CLASS="tableHeading" WIDTH="1%" ALIGN=CENTER><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Active Recipients')" onMouseOut="noHelp()">Active</A></TD>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>&nbsp; <A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Email Size')" onMouseOut="noHelp()">Email Size</A></TD>
		<iIF EXPR=':showCharges' ALIAS="showCharge">
			<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>&nbsp; <A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Run Charge')" onMouseOut="noHelp()">Run Charge</A></TD>
			<TD>&nbsp;</TD>
		</iIF ALIAS="showCharge">
	</TR>
	<iWHILE NOTALIAS=loadDB_empty>

		<iIF COND=":loadDB_inProgress" ALIAS="status"><iSET showCharges=0></iIF ALIAS="status">

		<iIF EXPR=':showCharges' ALIAS="showCharge">
			<FORM METHOD=POST ACTION=':thisPage'>
			<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
			<INPUT TYPE=HIDDEN NAME="step" VALUE="2">
			<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
			<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
			<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
			<INPUT TYPE=HIDDEN NAME="job" VALUE=":loadDB_id">
			<INPUT TYPE=HIDDEN NAME="jobTitle" VALUE=":loadDB_title">
		</iIF ALIAS="showCharge">
		<TR BGCOLOR="#A0B8C8" CLASS="highlightRow">
			<TD CLASS="inHighlight" VALIGN=TOP>&nbsp; 
				<iIF COND=":loadDB_inProgress" ALIAS="status">
					<A CLASS="inHighlight" HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job in Progress')" onMouseOut="noHelp()">:loadDB_title</A> <SPAN CLASS="awHeading1InHighlight">(in progress)</SPAN>
					<iHTML DBNAME=":appConn" SQL="SELECT type, runStart, totalRecords, sendCount FROM queue (NOLOCK) WHERE job_id=:loadDB_id ;" OUTPUT=":1,:2,:3,:4" NOOUTPUT="" FAILURE="" OUTVAR="progressData">
					<iIF NOTCOND=<iSTRCMP SRC=":progressData" DST=""> ALIAS="notFinished">
						<iLISTCREATE NAME="progressList" DELIM="" SRC="progressData" TYPE=VARIABLE>
						<iSET runType="Live"><iIF COND=<iSTRCMP SRC=`<iLISTGET NAME="progressList" OP=GETAT INDEX=1 DELIM="">` DST="0"> ALIAS="type"><iSET runType="Test"></iIF ALIAS="type">
						<iLISTGET NAME="progressList" OP=GETAT INDEX=2 DELIM="" OUTVAR="runStart">
						<iIF NOTCOND=<iSTRCMP SRC=":runStart" DST=""> ALIAS="started">
							<iCRDATETIME ODBC=`<iLISTGET NAME="progressList" OP=GETAT INDEX=2 DELIM="">` FMT="%m/%d/%y %H:%M" OUTVAR="runStart">
							<iSET runStart="began :runStart">
						<iELSE ALIAS="started">
							<iSET runStart="pending">
						</iIF ALIAS="started">
						<iLISTGET NAME="progressList" OP=GETAT INDEX=3 DELIM="" OUTVAR="totalRecords">
						<iLISTGET NAME="progressList" OP=GETAT INDEX=4 DELIM="" OUTVAR="sendCount">
						<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) AS total FROM dbo._job_:loadDB_id (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND sent=1 AND verified=1 AND delivered=0 ;" OUTPUT=":1" OUTVAR="pendingDelivery">
						<BR><SPAN CLASS="noticeTextInHighlight">&nbsp; :runType run :runStart.</SPAN>
						<BR><SPAN CLASS="noticeTextInHighlight">&nbsp; :sendCount of :totalRecords queued (<iEVAL EXPR=':totalRecords - :sendCount'> remaining), :pendingDelivery pending delivery.</SPAN>
						<iUNDEFINE progressList>
					</iIF ALIAS="notFinished">
				<iELSEIF COND=":loadDB_locked" ALIAS="status">
					<A CLASS="inHighlight" HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job is Locked')" onMouseOut="noHelp()">:loadDB_title</A> <SPAN CLASS="awHeading1InHighlight">(locked)</SPAN>
				<iELSEIF COND=":loadDB_suspended" ALIAS="status">
					<A CLASS="inHighlight" HREF=":thisPage?awpid=:awpid&client_id=:client_id&showMenu=Management&job=:loadDB_id" onMouseOver="return popUpHelp('Job is Suspended')" onMouseOut="noHelp()">:loadDB_title</A> <SPAN CLASS="awHeading1InHighlight">(suspended)</SPAN>
				<iELSE ALIAS="status">
					<A CLASS="inHighlight" HREF=":thisPage?awpid=:awpid&client_id=:client_id&showMenu=Management&job=:loadDB_id" onMouseOver="return popUpHelp('Manage Job')" onMouseOut="noHelp()">:loadDB_title</A>
				</iIF ALIAS="status">
			</TD>
			<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) FROM _job_:loadDB_id (NOLOCK) ;" OUTPUT=":1" FAILURE="0" OUTVAR="totalPieces">
			<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) FROM _job_:loadDB_id (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND verified=1 ;" OUTPUT=":1" FAILURE="0" OUTVAR="sendPieces">
			<iEVAL EXPR=':loadDB_mailSize/1024' PREC=2 OUTVAR="kilobytes">
			<TD CLASS="inHighlight" ALIGN=CENTER VALIGN=TOP>:totalPieces</TD>
			<TD CLASS="inHighlight" ALIGN=CENTER VALIGN=TOP>:sendPieces</TD>
			<TD CLASS="inHighlight" VALIGN=TOP NOWRAP>&nbsp; :loadDB_mailSize bytes (:kilobytes KB)</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">

				<iSET costLevel = ":loadDB_costLevel">

				<iREM -- Calculate Run Charge -- >
				<iINCLUDE NAME="w:\:appDir\jobCost.inc">

				<TD CLASS="inHighlight" ALIGN=RIGHT WIDTH="1%" VALIGN=TOP>&nbsp; <A CLASS="inHighlight" HREF=":thisPage?awpid=:awpid&client_id=:client_id&go=Run%20Charge%20Summary&showMenu=Job%20List&job=:loadDB_id" onMouseOver="return popUpHelp('Run Charge Summary')" onMouseOut="noHelp()">$ :runCharge</A></TD>
				<TD CLASS="inHighlight" WIDTH="15" VALIGN=TOP>
					<iIF COND=":loadDB_inProgress" ALIAS="status">
						<INPUT TYPE=IMAGE SRC="/images/adminware/delete_7788AA.gif" ALT="Delete" WIDTH=15 HEIGHT=16 VALUE="Delete" BORDER=0 onMouseOver="return popUpHelp('Job in Progress')" onMouseOut="noHelp()" onClick="return false">
					<iELSEIF COND=":loadDB_locked" ALIAS="status">
						<INPUT TYPE=IMAGE SRC="/images/adminware/delete_7788AA.gif" ALT="Delete" WIDTH=15 HEIGHT=16 VALUE="Delete" BORDER=0 onMouseOver="return popUpHelp('Job is Locked')" onMouseOut="noHelp()" onClick="return false">
					<iELSE ALIAS="status">
						<iSET safeJobTitle=":loadDB_title">
						<iREPLACE VAR="safeJobTitle" SRC="'" DST="\'">
						<INPUT TYPE=IMAGE SRC="/images/adminware/delete_7788AA.gif" ALT="Delete" WIDTH=15 HEIGHT=16 VALUE="Delete" BORDER=0 onMouseOver="return popUpHelp('Delete Job')" onMouseOut="noHelp()" onClick="if (!(confirm('Are you sure you want to delete \':safeJobTitle\'?\n\nAll settings and recipients for this job will be lost!'))) {return false}">
					</iIF ALIAS="status">
				</TD>
			</iIF ALIAS="showCharge">
		</TR>
		<iIF EXPR=':showCharges' ALIAS="showCharge">
			</FORM>
		</iIF ALIAS="showCharge">
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
	</iWHILE ALIAS=loadDB_empty>
	</TABLE>
<iELSE ALIAS="hasJobs">
	There are no jobs setup at this time.&nbsp; <A HREF=":thisPage?awpid=:awpid&client_id=:client_id&go=Add%20New%20Job&showMenu=Job%20List" onMouseOver="status='Add New Job'; return true;" onMouseOut="status='';">Click here</A> to create a new job.
</iIF ALIAS="hasJobs">
