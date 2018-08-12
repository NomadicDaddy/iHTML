<iREM -- Show Charges -- >
<iIF EXPR=':appAccess>2' ALIAS="checkAccess">
	<iSET showCharges=1 colSpan=12>
<iELSE ALIAS="checkAccess">
	<iSET showCharges=0 colSpan=10>
</iIF ALIAS="checkAccess">

<TABLE ID="copyTable" WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=0>

<TR><TD COLSPAN=:colSpan><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=100% HEIGHT=1></TD></TR>
<TR>
	<TD>&nbsp;</TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD CLASS="tableHeading" ALIGN=CENTER COLSPAN=6>Recipients</TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD>&nbsp;</TD>
	<iIF EXPR=':showCharges' ALIAS="showCharge">
		<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
		<TD>&nbsp;</TD>
	</iIF ALIAS="showCharge">
</TR>
<TR>
	<TD CLASS="tableHeading"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Date/Time')" onMouseOut="noHelp()">Date/Time</A></TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Total Field')" onMouseOut="noHelp()">Total</A></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Active Field')" onMouseOut="noHelp()">Active</A></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Viewed Field')" onMouseOut="noHelp()">Viewed</A></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Bounced Field')" onMouseOut="noHelp()">Bounced</A></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Unsubscribed Field')" onMouseOut="noHelp()">Unsubscribed</A></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Invalid Field')" onMouseOut="noHelp()">Invalid</A> &nbsp;</TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('OverSize Field')" onMouseOut="noHelp()">OverSize</A> &nbsp;</TD>
	<iIF EXPR=':showCharges' ALIAS="showCharge">
		<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
		<TD CLASS="tableHeading" ALIGN=RIGHT><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Run Charge')" onMouseOut="noHelp()">Run Charge</A></TD>
	</iIF ALIAS="showCharge">
</TR>
<TR><TD COLSPAN=:colSpan><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=100% HEIGHT=1></TD></TR>

<iSET curJob="">

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT j.title AS jobTitle, t.*
	FROM transactions t (NOLOCK) INNER JOIN jobs j (NOLOCK) ON t.job_id=j.id
	WHERE j.client_id=:client_id
	ORDER BY j.title, t.runDate ;
">
<iSQLFETCH ALIAS="loadDB">
<iWHILE NOTALIAS=i_sqlempty>

	<iIF NOTCOND=<iSTRCMP SRC=":curJob" DST=":loadDB_job_id"> ALIAS="jobHeader">
		<iIF NOTCOND=<iSTRCMP SRC=":curJob" DST=""> ALIAS="isJob">
			<iHTML DBNAME=":appConn" SQL="SELECT SUM(runCharge) FROM transactions (NOLOCK) WHERE job_id=:curJob ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="totalCharges">
			<iIF EXPR=':showCharges AND :totalCharges > 0' ALIAS="showCharge">
				<TR>
					<TD ALIGN=RIGHT>Job Total &nbsp;</TD>
					<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
					<TD ALIGN=CENTER COLSPAN=6>&nbsp;</TD>
					<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
					<TD>&nbsp;</TD>
					<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
					<TD ALIGN=RIGHT>$ <iEVAL EXPR=':totalCharges' PREC=2></TD>
				</TR>
			</iIF ALIAS="showCharge">
		</iIF ALIAS="isJob">
		<TR>
			<TD>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=CENTER COLSPAN=6>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD>&nbsp;</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">
				<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
				<TD>&nbsp;</TD>
			</iIF ALIAS="showCharge">
		</TR>
		<TR>
			<TD CLASS="tableHeading">:loadDB_jobTitle</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=CENTER COLSPAN=6>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD>&nbsp;</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">
				<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
				<TD>&nbsp;</TD>
			</iIF ALIAS="showCharge">
		</TR>
	</iIF ALIAS="jobHeader">

	<TR>
		<TD><iCRDATETIME ODBC=":loadDB_runDate" FMT="%m/%d/%Y %I:%M %p"></TD>
		<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
		<TD ALIGN=RIGHT>:loadDB_total</TD>
		<TD ALIGN=RIGHT>:loadDB_active</TD>
		<TD ALIGN=RIGHT>:loadDB_viewed</TD>
		<TD ALIGN=RIGHT>:loadDB_bounced</TD>
		<TD ALIGN=RIGHT>:loadDB_unsubscribed</TD>
		<TD ALIGN=RIGHT>:loadDB_invalid &nbsp;</TD>
		<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
		<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_overSize' PREC=2> &nbsp;</TD>
		<iIF EXPR=':showCharges' ALIAS="showCharge">
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=RIGHT>$ <iEVAL EXPR=':loadDB_runCharge' PREC=2></TD>
		</iIF ALIAS="showCharge">
	</TR>
	<iSET curJob=":loadDB_job_id">
	<iSQLFETCH ALIAS="loadDB">
</iWHILE ALIAS=i_sqlempty>

<iIF NOTCOND=<iSTRCMP SRC=":curJob" DST=""> ALIAS="isJob">
	<iHTML DBNAME=":appConn" SQL="SELECT SUM(runCharge) FROM transactions (NOLOCK) WHERE job_id=:curJob ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="totalCharges">
	<iIF EXPR=':showCharges AND :totalCharges > 0' ALIAS="showCharge">
		<TR>
			<TD ALIGN=RIGHT>Job Total &nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=CENTER COLSPAN=6>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=RIGHT>$ <iEVAL EXPR=':totalCharges' PREC=2></TD>
		</TR>
	</iIF ALIAS="showCharge">
</iIF ALIAS="isJob">
<TR>
	<TD>&nbsp;</TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD ALIGN=CENTER COLSPAN=6>&nbsp;</TD>
	<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
	<TD>&nbsp;</TD>
	<iIF EXPR=':showCharges' ALIAS="showCharge">
		<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
		<TD>&nbsp;</TD>
	</iIF ALIAS="showCharge">
</TR>

<TR><TD COLSPAN=:colSpan><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=100% HEIGHT=1></TD></TR>
</TABLE>

<iREM -- Show Clipboard Copy Option if Browser Supported -- >
<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/copyData.js"></SCRIPT>
