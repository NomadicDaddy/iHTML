<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iREM -- Set GUIDs -- >
<iIF EXPR='<iISDEF VAR="doSetGUID.x"> OR <iISDEF VAR="doSetGUID">' ALIAS="doSetGUID">

	<iSQL DBNAME=":appConn" SQL="SELECT 0 ;" ALIAS="updateRecord">
	<iSQLFETCH ALIAS="updateRecord">

	<iSET record=0 updateCount=0>

	<iSQLMORE SQL="SELECT COUNT(*) AS total FROM _job_:job (NOLOCK) WHERE guid IS NULL ;" ALIAS="loadDB">
	<iSQLFETCH ALIAS="loadDB">

	<iEVAL EXPR=':loadDB_total / 1000' PREC=0 OUTVAR="iterations">
	<iIF EXPR=':iterations=0'><iSET iterations=1></iIF>

	<iLOOP INITIAL=1 FINAL=:iterations ALIAS="steps">
		<iSQLMORE SQL="
			SELECT TOP 1000 id, email 
			FROM _job_:job (NOLOCK) 
			WHERE id > :record AND guid IS NULL 
			ORDER BY id ;
		" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
			<iSET record=':loadDB_id'>
			<iEVAL EXPR=':updateCount + 1' OUTVAR="updateCount">
			<iSET guid="">
			<iLOOP INITIAL=1 FINAL=4>
				<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=65 HIGH=90>>`>
				<iSTRCAT DST="guid" SRC=`<iRNDNUM LOW=0 HIGH=9>`>
				<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=97 HIGH=122>>`>
			</iLOOP>
			<iSQLMORE SQL="UPDATE _job_:job SET guid=':guid' WHERE id=:loadDB_id ;" ALIAS="updateRecord">
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>
	</iLOOP ALIAS="steps">

	</iSQL ALIAS="updateRecord">

	<TR><TD><BR><FONT SIZE="-1" FACE="Arial, sans-serif"><B>There were <iIF EXPR=':updateCount > 0'>:updateCount<iELSE>no</iIF> GUIDs to be set.</B></FONT></TD></TR>

<iELSE ALIAS="doSetGUID">

	<TR><TD><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Setting GUIDs is a slow process. &nbsp;It goes through the list of unset recipients and sets the GUID.<BR><BR>To proceed, click the button below.</B><BR><BR></FONT></TD></TR>
	<TR><TD ALIGN=CENTER><FONT SIZE="-1" FACE="Arial, sans-serif">
		<FORM METHOD=POST ACTION=':thisPage'>
		<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
		<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
		<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
		<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
		<INPUT TYPE=SUBMIT NAME="doSetGUID" VALUE="Proceed" onClick="alert('Please be patient.  Depending on database size, this could take several minutes.')">
		</FORM>
	</FONT></TD></TR>

</iIF ALIAS="doSetGUID">

</TABLE>
