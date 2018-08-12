<iSET total=0>

<iREM -- Open DB Connection -- >
<iSQL DBNAME="DRIVER=SQL Server;SERVER=PEPPERJACK;UID=adminware;PWD=zzz;DATABASE=aw_main;" SQL="SELECT 0 ;" ALIAS="clients">
<iSQLFETCH ALIAS="clients">

<iREM -- Iterate Jobs -- >
<iSQL DBNAME=":appConn" SQL="
	SELECT j.id, j.client_id, j.title, t.runDate, t.overSize, t.active, t.runCharge 
	FROM transactions t (NOLOCK) INNER JOIN jobs j (NOLOCK) ON t.job_id = j.id 
	WHERE runCharge > 0 AND j.id != 10 ;
" ALIAS="jobs">
<iSQLFETCH ALIAS="jobs">
<TABLE WIDTH="100%" BORDER=0>
<TR>
	<TD><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Client Name</U></B></FONT></TD>
	<TD ALIGN=CENTER><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Job ID</U></B></FONT></TD>
	<TD><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Job Title</U></B></FONT></TD>
	<TD><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Run Date</U></B></FONT></TD>
	<TD ALIGN=CENTER><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Pieces</U></B></FONT></TD>
	<TD ALIGN=RIGHT><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Size</U></B></FONT></TD>
	<TD ALIGN=RIGHT><FONT FACE="Arial, sans-serif" SIZE="-1"><B><U>Run Charge</U></B></FONT></TD>
</TR>
<iWHILE NOTALIAS=i_sqlempty>
	<iSQLMORE SQL="SELECT clientName FROM clients (NOLOCK) WHERE id=:jobs_client_id ;" ALIAS="clients">
	<iSQLFETCH ALIAS="clients">
	<iEVAL EXPR=':total + :jobs_runCharge' PREC=2 OUTVAR="total">
	<TR>
		<TD><FONT FACE="Arial, sans-serif" SIZE="-1">:clients_clientName</FONT></TD>
		<TD ALIGN=CENTER><FONT FACE="Arial, sans-serif" SIZE="-1">:jobs_id</FONT></TD>
		<TD><FONT FACE="Arial, sans-serif" SIZE="-1">:jobs_title</FONT></TD>
		<TD><FONT FACE="Arial, sans-serif" SIZE="-1"><iCRDATETIME ODBC=":jobs_runDate" FMT="%m/%d/%y %I:%M %p"></FONT></TD>
		<TD ALIGN=CENTER><FONT FACE="Arial, sans-serif" SIZE="-1">:jobs_active</FONT></TD>
		<TD ALIGN=RIGHT><FONT FACE="Arial, sans-serif" SIZE="-1"><iEVAL EXPR=':jobs_overSize + 1' PREC=2>K</FONT></TD>
		<TD ALIGN=RIGHT><FONT FACE="Arial, sans-serif" SIZE="-1">$ <iEVAL EXPR=':jobs_runCharge' PREC=2></FONT></TD>
	</TR>
	<iSQLFETCH ALIAS="jobs">
</iWHILE ALIAS=i_sqlempty>
<TR><TD ALIGN=RIGHT COLSPAN=7>&nbsp;</TD></TR>
<TR><TD ALIGN=RIGHT COLSPAN=7><FONT FACE="Arial, sans-serif" SIZE="-1"><B>$ <iEVAL EXPR=':total' PREC=2></B></FONT></TD></TR>
</TABLE>
</iSQL ALIAS="jobs">
