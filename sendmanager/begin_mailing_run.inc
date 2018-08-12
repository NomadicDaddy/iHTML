<iIF COND=<iISDEF VAR="resetSent"> ALIAS="resetFlags">
	<iHTML DBNAME=":appConn" SQL="UPDATE dbo._job_:job SET sent = 0 WHERE sent = 1 ;" OUTPUT=":1" NOOUTPUT="Sent flags reset." FAILURE="ERROR: :i_sqlerrortext" OUTVAR="statusMsg">
	<iSET step = 1>
</iIF ALIAS="resetFlags">

<iDEFAULT NAME="step" VALUE="1">

<iCASE ALIAS="step" VALUE="1">

	<iHTML DBNAME=":appConn" SQL="SELECT locked FROM dbo.jobs (NOLOCK) WHERE client_id = :client_id ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="isLocked">
	<iHTML DBNAME=":appConn" SQL="SELECT suspended FROM dbo.jobs (NOLOCK) WHERE client_id = :client_id ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="isSuspended">

	<iIF EXPR='NOT :isLocked AND NOT :isSuspended' ALIAS="jobActive">
		<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) FROM dbo._job_:job (NOLOCK) WHERE unsubscribed = 0 AND bounced = 0 AND sent = 0 AND verified = 1 ;" OUTPUT=":1" OUTVAR="pieces">
		<TABLE BORDER=0 CELLSPACING=3 CELLPADDING=2>
		<FORM METHOD=POST ACTION=':thisPage'>
		<INPUT TYPE=HIDDEN NAME="step" VALUE="2">
		<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
		<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
		<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
		<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
		<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
		<INPUT TYPE=HIDDEN NAME="pieces" VALUE=":pieces">
		<iIF EXPR=':pieces > 0' ALIAS="doSend">
			<TR>
				<TD CLASS="tableHeading">Mail Run Prepared:</TD>
				<TD>:pieces Pieces to be Sent</TD>
			</TR>
			<TR><TD CLASS="tableHeading" COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="startProcessing" VALUE="Proceed"></TD></TR>
		<iELSE ALIAS="doSend">
			<TR><TD COLSPAN=2>There are no recipients ready to send to.</TD></TR>
			<TR>
				<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Sent')" onMouseOut="noHelp()">Reset all 'Sent' flags now?</A> &nbsp;</TD>
				<TD><INPUT TYPE=SUBMIT NAME="resetSent" VALUE="Proceed"></TD>
			</TR>
		</iIF ALIAS="doSend">
		</FORM>
		</TABLE>
	<iELSE ALIAS="jobActive">
		<P>This job is locked or suspended.&nbsp; Please contact support for more information.</P>
	</iIF ALIAS="jobActive">

</iCASE ALIAS="step">

<iCASE ALIAS="step" VALUE="2">

	<iREM -- Add to queue -- >
	<iHTML DBNAME=":appConn" SQL="UPDATE dbo.jobs SET inProgress = 1, sendArchive = 1 WHERE id = :job ;">
	<iHTML DBNAME=":appConn" SQL="INSERT INTO queue (job_id, type, totalRecords) VALUES (:job, 1, :pieces) ;">

	<iREM -- Redirect to Job List -- >
	<iREDIR URL=":thisPage?awpid=:awpid&client_id=:client_id&showMenu=Job%20List&refreshAfter=60">

</iCASE ALIAS="step">
