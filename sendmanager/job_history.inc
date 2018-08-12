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

<iSET isFirst=1 pTotal=0 pActive=0 pViewed=0 pBounced=0 pUnsubscribed=0 pInvalid=0>

<iSQLMORE SQL="SELECT * FROM transactions (NOLOCK) WHERE job_id=:job ORDER BY runDate;" ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
<iWHILE NOTALIAS=i_sqlempty>
	<iIF NOTCOND=<iSTRCMP SRC=":loadDB_reference" DST=""> ALIAS="showReference">
		<TR>
			<TD>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD COLSPAN=6 CLASS="awHeading1">&nbsp; :loadDB_reference</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD>&nbsp;</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">
				<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
				<TD>&nbsp;</TD>
			</iIF ALIAS="showCharge">
		</TR>
	</iIF ALIAS="showReference">
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
	<iIF NOTCOND=:isFirst ALIAS="notFirst">
		<TR>
			<TD STYLE="padding-left : 9px;">(change since last)</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_total - :pTotal'></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_active - :pActive'></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_viewed - :pViewed'></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_bounced - :pBounced'></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_unsubscribed - :pUnsubscribed'></TD>
			<TD ALIGN=RIGHT><iEVAL EXPR=':loadDB_invalid - :pInvalid'> &nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD ALIGN=RIGHT>&nbsp;</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">
				<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
				<TD ALIGN=RIGHT>&nbsp;</TD>
			</iIF ALIAS="showCharge">
		</TR>
	<iELSE ALIAS="notFirst">
		<TR>
			<TD STYLE="padding-left : 9px;">(baseline)</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD COLSPAN=6>&nbsp;</TD>
			<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
			<TD>&nbsp;</TD>
			<iIF EXPR=':showCharges' ALIAS="showCharge">
				<TD WIDTH=1><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=1 HEIGHT=20></TD>
				<TD>&nbsp;</TD>
			</iIF ALIAS="showCharge">
		</TR>
	</iIF ALIAS="notFirst">
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
	<iSET isFirst=0 pTotal=:loadDB_total pActive=:loadDB_active pViewed=:loadDB_viewed pBounced=:loadDB_bounced pUnsubscribed=:loadDB_unsubscribed pInvalid=:loadDB_invalid>
	<iSQLFETCH ALIAS="loadDB">
</iWHILE ALIAS=i_sqlempty>

<TR><TD COLSPAN=:colSpan><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=100% HEIGHT=1></TD></TR>
</TABLE>

<iREM -- Show Clipboard Copy Option if Browser Supported -- >
<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/copyData.js"></SCRIPT>
