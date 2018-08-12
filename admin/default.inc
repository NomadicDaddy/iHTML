<iSQLMORE ALIAS="loadDB" SQL="EXEC getClientParent ':i_auth_user' ;">
<iSQLFETCH ALIAS="loadDB">
<iSET client_id=":loadDB_id" clientName=":loadDB_clientName" appAccess=":loadDB_access">
<iURLENCODE SRC=":clientName" OUTVAR="client">

<TABLE WIDTH="100%" BORDER=0>
<TR><TD COLSPAN=3>You are logged in as <B>:clientName</B> and have access to the following adminware programs and services:</TD></TR>
<TR><TD COLSPAN=3>&nbsp;</TD></TR>

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT a.id, a.appVersion, a.appDir, a.appWelcome 
	FROM apps a (NOLOCK) INNER JOIN jobs j (NOLOCK) ON a.id=j.app_id INNER JOIN clients c (NOLOCK) ON j.client_id=c.id 
	WHERE c.id=:client_id 
	ORDER BY a.id ;
">
<iSQLFETCH ALIAS="loadDB">
<iWHILE NOTALIAS=i_sqlempty>
	<TR>
		<TD CLASS="tableHeading" VALIGN=TOP NOWRAP STYLE="padding-left : 9px;"><A HREF=":thisPage?awpid=:loadDB_id&client_id=:client_id" onMouseOver="status='Login to :loadDB_appVersion'; return true;" onMouseOut="status='';">:loadDB_appVersion</TD>
		<TD NOWRAP STYLE="padding-left : 9px;">&nbsp; </TD>
		<TD VALIGN=TOP>:loadDB_appWelcome</TD>
	</TR>
	<TR><TD COLSPAN=3>&nbsp;</TD></TR>
	<iSQLFETCH ALIAS="loadDB">
</iWHILE ALIAS=i_sqlempty>

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT c.id AS client_id, c.userid, c.password, c.clientName, c.access, c.active, a.id, a.appVersion, a.appDir, a.appWelcome 
	FROM apps a (NOLOCK) INNER JOIN jobs j (NOLOCK) ON a.id=j.app_id INNER JOIN clients c (NOLOCK) ON j.client_id=c.id 
	WHERE c.parent=:client_id 
	ORDER BY c.id, a.id ;
">
<iSQLFETCH ALIAS="loadDB" EMPTY="sub_empty">
<iIF NOTCOND=:sub_empty ALIAS="subClients">
	<TR><TD COLSPAN=3>&nbsp;</TD></TR>
	<TR><TD COLSPAN=3>You also have designated administrator access to the following accounts:</TD></TR>
	<TR><TD COLSPAN=3>&nbsp;</TD></TR>
	<iSET prevClient="">
	<iWHILE NOTALIAS=sub_empty>
		<iURLENCODE SRC=":clientName [:loadDB_clientName]" OUTVAR="client">

		<iIF NOTCOND=<iSTRCMP SRC=":prevClient" DST=":loadDB_client_id"> ALIAS="sameClient">
			<TR><TD COLSPAN=3>&nbsp;</TD></TR>
			<TR>
				<TD NOWRAP>:loadDB_clientName (:loadDB_userid: :loadDB_access)</TD>
		<iELSE ALIAS="sameClient">
				<TD>&nbsp;</TD>
		</iIF ALIAS="sameClient">

				<TD NOWRAP STYLE="padding-left : 9px;">&nbsp; </TD>
				<TD CLASS="tableHeading"><A HREF=":thisPage?awpid=:loadDB_id&client_id=:loadDB_client_id" onMouseOver="status='Login to :loadDB_appVersion'; return true;" onMouseOut="status='';">:loadDB_appVersion</TD>
			</TR>

		<iSET prevClient=":loadDB_client_id">

		<iSQL DBNAME="adminware" LOGIN="adminware/zzz" SQL="
			SELECT c.id AS client_id, c.userid, c.password, c.clientName, c.access, c.active, a.id, a.appVersion, a.appDir, a.appWelcome 
			FROM apps a (NOLOCK) INNER JOIN jobs j (NOLOCK) ON a.id=j.app_id INNER JOIN clients c (NOLOCK) ON j.client_id=c.id 
			WHERE c.parent=:loadDB_client_id
			ORDER BY c.id, a.id ;
		" ALIAS="loadSubSub">
		<iSQLFETCH ALIAS="loadSubSub">
		<iIF NOTCOND=:i_sqlempty ALIAS="subSubClients">
			<iSET prevSubClient="">
			<iWHILE NOTALIAS=i_sqlempty>
				<iURLENCODE SRC=":clientName [:loadSubSub_clientName]" OUTVAR="client">

				<iIF NOTCOND=<iSTRCMP SRC=":prevSubClient" DST=":loadSubSub_client_id"> ALIAS="sameClient">
					<TR>
						<TD NOWRAP><IMG SRC="/images/adminware/whitebar.gif" ALT="" WIDTH=10 HEIGHT=1 ALIGN=CENTER HSPACE=5>:loadSubSub_clientName (:loadSubSub_userid: :loadSubSub_access)</TD>
				<iELSE ALIAS="sameClient">
						<TD>&nbsp;</TD>
				</iIF ALIAS="sameClient">

						<TD NOWRAP STYLE="padding-left : 9px;">&nbsp; </TD>
						<TD CLASS="tableHeading"><A HREF=":thisPage?awpid=:loadSubSub_id&client_id=:loadSubSub_client_id" onMouseOver="status='Login to :loadSubSub_appVersion'; return true;" onMouseOut="status='';">:loadSubSub_appVersion</TD>
					</TR>

				<iSET prevSubClient=":loadSubSub_client_id">

				<iSQLFETCH ALIAS="loadSubSub">
			</iWHILE ALIAS=i_sqlempty>
		</iIF ALIAS="subSubClients">
		</iSQL ALIAS="loadSubSub">

		<iSQLFETCH ALIAS="loadDB" EMPTY="sub_empty">
	</iWHILE ALIAS=sub_empty>

</iIF ALIAS="subClients">

</TABLE>
