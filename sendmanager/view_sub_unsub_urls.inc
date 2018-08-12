<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="doUpdate"> ALIAS="doUpdate">
	<iREPLACE VAR="euHeader" SRC="'" DST="''">
	<iREPLACE VAR="euFooter" SRC="'" DST="''">
	<iREPLACE VAR="euTemplate" SRC="'" DST="''">
	<iSET z="Subscribe/Unsubscribe URLs updated.">

	<iIF COND=<iSTRLEN SRC=`:euTemplate`> ALIAS="useTemplate">
		<iSET euHeader="" euFooter="">
		<iIF NOTCOND=<iSTRIN SRC=`:euTemplate` DST="<:form>"> ALIAS="addFormToken">
			<iSET euTemplate=`:euTemplate<BR><:form>`>
		</iIF ALIAS="addFormToken">
	</iIF ALIAS="useTemplate">

	<iHTML DBNAME=":appConn" SQL=`UPDATE dbo.jobs SET euHeader=':euHeader', euFooter=':euFooter', euTemplate=':euTemplate' WHERE id=:job ;` NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="statusMsg">
	<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="Update failed. ">
	<iIF COND=<iSTRCMP SRC=":statusMsg" DST="Success"> ALIAS="setMsg"><iSET statusMsg=":z"></iIF ALIAS="setMsg">
</iIF ALIAS="doUpdate">

<iSQLMORE ALIAS="loadDB" SQL="SELECT euHeader, euFooter, euTemplate FROM jobs (NOLOCK) WHERE id=:job ;">
<iSQLFETCH ALIAS="loadDB">

<FORM METHOD=POST ACTION=':thisPage' NAME="enduser_form">
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR><TD COLSPAN=2>For clients who wish to subscribe or unsubscribe themselves, the following URLs are provided:<BR><BR></TD></TR>
<TR>
	<TD CLASS="tableHeading"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Self-Subscribe URL')" onMouseOut="noHelp()">Self-Subscribe URL</A></TD>
	<TD><A HREF="http://adminware.com/sendmanager/subscribe.ihtml?jid=:job" TARGET="_blank" onMouseOver="return popUpHelp('Jump to Self-Subscribe URL')" onMouseOut="noHelp()">http://adminware.com/sendmanager/subscribe.ihtml?jid=:job</A></TD>
</TR>
<TR><TD COLSPAN=2><BR></TD></TR>
<TR>
	<TD CLASS="tableHeading"><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Self-Unsubscribe URL')" onMouseOut="noHelp()">Self-Unsubscribe URL</A></TD>
	<TD><A HREF="http://adminware.com/sendmanager/unsubscribe.ihtml?jid=:job" TARGET="_blank" onMouseOver="return popUpHelp('Jump to Self-Unsubscribe URL')" onMouseOut="noHelp()">http://adminware.com/sendmanager/unsubscribe.ihtml?jid=:job</A></TD>
</TR>
<TR>
	<TD COLSPAN=2><BR>

		<P>Recipients of this job's mailings will receive a system-generated,
		personalized unsubscribe URL with each mailing for their convenience.</P>

		<P>To customize the look-and-feel of this area, you may cut-and-paste a header
		and footer below OR a complete template.&nbsp; Be sure to use absolute
		references to any graphics or links used.&nbsp; If a template is used, the
		following system-generated tokens are available, but you must at least use the
		<:form> token.</P>

		&nbsp; <A HREF="javascript:void(0);" onClick="enduser_form.euTemplate.value = enduser_form.euTemplate.value + '<:title:>'" onMouseOver="return popUpHelp('JobTitle')" onMouseOut="noHelp()">&lt;:title:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="enduser_form.euTemplate.value = enduser_form.euTemplate.value + '<:description:>'" onMouseOver="return popUpHelp('JobDescription')" onMouseOut="noHelp()">&lt;:description:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="enduser_form.euTemplate.value = enduser_form.euTemplate.value + '<:form:>'" onMouseOver="return popUpHelp('Form')" onMouseOut="noHelp()">&lt;:form:&gt;</A><BR><BR>
	</TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('End-User Area Header')" onMouseOut="noHelp()">End-User Area Header</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><TEXTAREA NAME="euHeader" COLS=51 ROWS=5 WRAP=SOFT TABINDEX=1>:loadDB_euHeader</TEXTAREA></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('End-User Area Footer')" onMouseOut="noHelp()">End-User Area Footer</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><TEXTAREA NAME="euFooter" COLS=51 ROWS=5 WRAP=SOFT TABINDEX=2>:loadDB_euFooter</TEXTAREA></TD>
</TR>
<TR><TD COLSPAN=2><P><B>OR</B></P></TD></TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('End-User Area Template')" onMouseOut="noHelp()">End-User Area Template</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><TEXTAREA NAME="euTemplate" COLS=51 ROWS=10 WRAP=SOFT TABINDEX=3>:loadDB_euTemplate</TEXTAREA></TD>
</TR>
<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doUpdate" VALUE="Update"></TD></TR>
</TABLE>
</FORM>
