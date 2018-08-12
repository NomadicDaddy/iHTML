<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iREM -- Verify Addresses -- >
<iIF EXPR='<iISDEF VAR="doVerify.x"> OR <iISDEF VAR="doVerify">' ALIAS="doVerify">

	<iINCLUDE NAME="w:\ifuncs\checkEmail.ifunc">

	<TR><TD><FONT SIZE="-1" FACE="Arial, sans-serif"><B>The following email addresses are invalid and have been marked as invalid:</B><BR><BR></FONT></TD></TR>

	<iSQL DBNAME=":appConn" SQL="SELECT 0 ;" ALIAS="updateRecord">
	<iSQLFETCH ALIAS="updateRecord">

	<iSET record=0 badCount=0>

	<iSQLMORE SQL="SELECT COUNT(*) AS total FROM _job_:job (NOLOCK) WHERE verified IS NULL OR verified=0 ;" ALIAS="loadDB">
	<iSQLFETCH ALIAS="loadDB">

	<iEVAL EXPR=':loadDB_total / 1000' PREC=0 OUTVAR="iterations">
	<iIF EXPR=':iterations=0'><iSET iterations=1></iIF>
	<iLOOP INITIAL=1 FINAL=:iterations ALIAS="steps">
		<iSQLMORE SQL="
			SELECT TOP 1000 id, email 
			FROM _job_:job (NOLOCK) 
			WHERE id > :record AND verified IS NULL OR verified=0
			ORDER BY id ;
		" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
			<iSET record=':loadDB_id'>
			<iIF NOTCOND=<iFUNCCALL ALIAS="checkEmail" EMAIL=":loadDB_email"> ALIAS="notValid">
				<TR><TD STYLE="padding-left : 9px;">:loadDB_email</TD></TR>
				<iEVAL EXPR=':badCount + 1' OUTVAR="badCount">
				<iSQLMORE SQL="UPDATE _job_:job SET verified=0 WHERE id=:loadDB_id ;" ALIAS="updateRecord">
			<iELSE ALIAS="notValid">
				<iSQLMORE SQL="UPDATE _job_:job SET verified=1 WHERE id=:loadDB_id ;" ALIAS="updateRecord">
			</iIF ALIAS="notValid">
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>
	</iLOOP ALIAS="steps">

	</iSQL ALIAS="updateRecord">

	<TR><TD><BR><FONT SIZE="-1" FACE="Arial, sans-serif"><B>There were <iIF EXPR=':badCount > 0'>:badCount<iELSE>no</iIF> invalid email addresses.</B></FONT></TD></TR>

<iELSE ALIAS="doVerify">

	<TR><TD><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Address verification is a slow process. &nbsp;It goes through the list of unverified recipients and verifies that the addresses are syntactically valid. &nbsp;If an address if found to be invalid, it will be marked as such.<BR><BR>To proceed, click the button below.</B><BR><BR></FONT></TD></TR>
	<TR><TD ALIGN=CENTER><FONT SIZE="-1" FACE="Arial, sans-serif">
		<FORM METHOD=POST ACTION=':thisPage'>
		<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
		<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
		<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
		<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
		<INPUT TYPE=SUBMIT NAME="doVerify" VALUE="Proceed with Verification Process" onClick="alert('Please be patient.  Depending on database size, this could take several minutes.')">
		</FORM>
	</FONT></TD></TR>

</iIF ALIAS="doVerify">

</TABLE>
