<iREM -- Add Tracked Link -- >
<iIF COND=<iISDEF VAR="doAdd"> ALIAS="doAdd">
	<iIF EXPR='<iSTRCMP SRC=":linkToken" DST=""> OR <iSTRCMP SRC=":linkTarget" DST="">' ALIAS="isBlank">
		<iSET statusMsg="Neither the tracked link nor the token name can be blank.">
	<iELSE ALIAS="isBlank">
		<iSTRKEEP SRC=":linkToken" KEEP="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" OUTVAR="linkToken">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT linkTarget FROM linkTracking (NOLOCK) WHERE job_id=:job AND linkTarget=':linkTarget' ;">
		<iSQLFETCH ALIAS="loadDB">
		<iIF COND=:i_sqlempty ALIAS="exists">
			<iSQLMORE ALIAS="loadDB" SQL="SELECT linkToken FROM linkTracking (NOLOCK) WHERE job_id=:job AND linkToken=':linkToken' ;">
			<iSQLFETCH ALIAS="loadDB">
			<iIF COND=:i_sqlempty ALIAS="exists2">
				<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO linkTracking (job_id, linkToken, linkTarget) VALUES (:job, ':linkToken', ':linkTarget') ;">
				<iSET statusMsg="Added new tracked link.">
			<iELSE ALIAS="exists2">
				<iSET statusMsg="There is already a tracked link with that token name.&nbsp; You cannot use it twice.">
			</iIF ALIAS="exists2">
		<iELSE ALIAS="exists">
			<iSET statusMsg="There is already a tracked link with that URL.&nbsp; You cannot use it twice.">
		</iIF ALIAS="exists">
	</iIF ALIAS="isBlank">
</iIF ALIAS="doAdd">

<iREM -- Delete Tracked Link -- >
<iIF EXPR='<iISDEF VAR="doDelete.x"> OR <iISDEF VAR="doDelete">' ALIAS="doDelete">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT linkTarget FROM linkTracking (NOLOCK) WHERE job_id=:job AND linkTarget=':linkTarget' ;">
	<iSQLFETCH ALIAS="loadDB">
	<iIF NOTCOND=:i_sqlempty ALIAS="exists">
		<iHTML DBNAME=":appConn" SQL="DELETE FROM linkTracking WHERE job_id=:job AND linkTarget=':linkTarget' ;" NOOUTPUT="Tracked link deleted." FAILURE="Failed to delete tracked link: :i_sqlerrortext" OUTVAR="statusMsg">
	<iELSE ALIAS="exists">
		<iSET statusMsg="That does not exist (and therefore cannot be deleted).">
	</iIF ALIAS="exists">
</iIF ALIAS="doDelete">

<iREM -- Show Current Tracked Links -- >
<iSQLMORE ALIAS="loadDB" SQL="SELECT linkToken, linkTarget, hits FROM linkTracking (NOLOCK) WHERE job_id=:job ;">
<iSQLFETCH ALIAS="loadDB">
<iIF NOTCOND=:i_sqlempty ALIAS="areLinks">
	<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
	<TR>
		<TD CLASS="tableHeading"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Tracked Link Token')" onMouseOut="noHelp()">Token</A></TD>
		<TD CLASS="tableHeading"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Tracked Link Target')" onMouseOut="noHelp()">Target URL</A></TD>
		<TD CLASS="tableHeading" ALIGN=CENTER><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Tracked Link Hits')" onMouseOut="noHelp()">Current Hits</A></TD>
		<TD WIDTH="1%">&nbsp;</TD>
	</TR>
	<iWHILE NOTALIAS=i_sqlempty>
		<FORM METHOD=POST ACTION=':thisPage'>
		<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
		<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
		<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
		<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
		<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
		<INPUT TYPE=HIDDEN NAME="linkTarget" VALUE=":loadDB_linkTarget">
		<TR>
			<TD>:loadDB_linkToken</TD>
			<TD>:loadDB_linkTarget</TD>
			<TD ALIGN=CENTER>:loadDB_hits</TD>
			<TD WIDTH="1%"><INPUT TYPE=IMAGE NAME="doDelete" SRC="/images/adminware/btn_del.gif" ALT="Delete" WIDTH=23 HEIGHT=11 VALUE="Delete" BORDER=0 onMouseOver="return popUpHelp('Delete Button')" onMouseOut="noHelp()" onClick="if (!(confirm('Are you sure?'))) {return false}"></TD>
		</TR>
		</FORM>
		<iSQLFETCH ALIAS="loadDB">
	</iWHILE ALIAS=i_sqlempty>
	</TABLE>
<iELSE ALIAS="areLinks">
	<DIV CLASS="noticeText">The are no tracked links setup currently.&nbsp; Use the form below to add one.</DIV>
</iIF ALIAS="areLinks">

<FORM METHOD=POST ACTION=':thisPage'>
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Tracked Link Token')" onMouseOut="noHelp()">Token</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="linkToken" SIZE=15 MAXLENGTH=15></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Tracked Link Target')" onMouseOut="noHelp()">Target URL</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="linkTarget" SIZE=50 MAXLENGTH=150></TD>
</TR>
<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doAdd" VALUE="Add New Tracked Link"></TD></TR>
</TABLE>
</CENTER></TD></TR></TABLE>
</FORM>
