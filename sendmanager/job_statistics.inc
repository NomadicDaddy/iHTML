<TABLE ID="copyTable" WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<TR><TD COLSPAN=2>Campaign Statistics</TD></TR>
<TR><TD COLSPAN=2 HEIGHT=20>&nbsp;</TD></TR>

<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Total Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Total Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Bounced Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Bounced Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE bounced=1 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Unsubscribed Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Unsubscribed Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE unsubscribed=1 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Invalid Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Invalid Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE verified=0 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>

<TR><TD COLSPAN=2 HEIGHT=20>&nbsp;</TD></TR>
<TR><TD COLSPAN=2>Current Mailing Run Statistics</TD></TR>
<TR><TD COLSPAN=2 HEIGHT=20>&nbsp;</TD></TR>

<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Unsent Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Unsent Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND sent=0 AND verified=1 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Sent Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Sent Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND sent=1 AND verified=1 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Sent Pending Delivery')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Sent Pending Delivery</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND sent=1 AND verified=1 AND delivered=0 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>
<TR>
	<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Delivered Recipients')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Delivered Recipients</B></FONT></A></TD>
	<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
		<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND sent=1 AND verified=1 AND delivered=1 ;" ALIAS="loadDB">
		<iSQLFETCH ALIAS="loadDB">
		:loadDB_total
	</FONT></TD>
</TR>

<iSQLMORE SQL="SELECT body, htmlbody FROM dbo.jobs (NOLOCK) WHERE id = :job ;" ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
<iIF EXPR='<iSTRIN SRC=":loadDB_body" DST="<:ViewTracker"> OR <iSTRIN SRC=":loadDB_htmlbody" DST="<:ViewTracker">' ALIAS="usingViewTracker">
	<TR>
		<TD><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Viewed Current Mailing')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B>Viewed Current Mailing</B></FONT></A></TD>
		<TD ALIGN=RIGHT><FONT SIZE="-1" FACE="Arial, sans-serif">
			<iSQLMORE SQL="SELECT COUNT(*) AS total FROM dbo._job_:job (NOLOCK) WHERE viewed=1 ;" ALIAS="loadDB">
			<iSQLFETCH ALIAS="loadDB">
			:loadDB_total
		</FONT></TD>
	</TR>
</iIF ALIAS="usingViewTracker">

</TABLE>

<iREM -- Show Clipboard Copy Option if Browser Supported -- >
<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/copyData.js"></SCRIPT>
