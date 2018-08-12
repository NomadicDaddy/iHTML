<iREM -- Check for Messages -- >

<iREM -- FROM DB -- >
<iSET maxMultiMsgs=50>

<iSQL DBNAME=":datasource" LOGIN=":loginname" SQL="SELECT id FROM dbo.:userTable (NOLOCK) WHERE :extUserField=':i_auth_user' ;" ESC=FALSE ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
<iIF NOTCOND=:i_sqlempty ALIAS="doCheck">

	<iSET user_id=":loadDB_id">

	<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/siteMessaging.js"></SCRIPT>

	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS total FROM dbo.siteMessaging (NOLOCK) WHERE to_id=:user_id AND (status=1 OR status=5) ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET total=":loadDB_total">

	<iIF EXPR=':total > :maxMultiMsgs' ALIAS="multipleMsgs">
		<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript">siteMessaging('Instant%20Message', :user_id, 0, 0);</SCRIPT>
	<iELSE ALIAS="multipleMsgs">
		<iSET prefsString="AND NOT EXISTS (SELECT p.user_id FROM dbo.prefsList p (NOLOCK) WHERE (p.user_id=@user_id AND p.other_id=u.id AND p.ignored=1))">
		<iSQLMORE ALIAS="loadDB" SQL="
			SELECT smsg.id, smsg.from_id, smsg.status
			FROM dbo.siteMessaging smsg (NOLOCK) INNER JOIN dbo.:userTable u (NOLOCK) ON smsg.from_id=u.id
			WHERE u.id!=:user_id AND smsg.to_id=:user_id AND (smsg.status=1 OR smsg.status=5)
			ORDER BY smsg.dateCreated ;
		">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
			<iEVAL EXPR="(:loadDB_status & 4) + 3" OUTVAR="loadDB_status">
			<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript">siteMessaging('Instant%20Message', :user_id, :loadDB_from_id, :loadDB_id);</SCRIPT>
			<iHTML DBNAME=":datasource" LOGIN=":loginname" SQL="UPDATE dbo.siteMessaging SET status=:loadDB_status WHERE id=:loadDB_id ;">
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>
	</iIF ALIAS="multipleMsgs">

</iIF ALIAS="doCheck">
</iSQL ALIAS="loadDB">
