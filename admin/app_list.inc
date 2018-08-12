<TABLE WIDTH="100%" BORDER=0>

<iSQLMORE ALIAS="loadDB" SQL="SELECT id, appVersion, appDir, appWelcome FROM apps (NOLOCK) WHERE id>2 ORDER BY id ;">
<iSQLFETCH ALIAS="loadDB">
<iWHILE NOTALIAS=i_sqlempty>
	<TR>
		<TD CLASS="tableHeading" VALIGN=TOP NOWRAP STYLE="padding-left : 9px;"><A HREF="javascript:void(0);" onMouseOver="status='Info for :loadDB_appVersion'; return true;" onMouseOut="status='';">:loadDB_appVersion</A></TD>
		<TD STYLE="padding-left : 9px;">&nbsp; </TD>
		<TD VALIGN=TOP>:loadDB_appWelcome</TD>
	</TR>
	<TR><TD COLSPAN=3>&nbsp;</TD></TR>
	<iSQLFETCH ALIAS="loadDB">
</iWHILE ALIAS=i_sqlempty>

</TABLE>
