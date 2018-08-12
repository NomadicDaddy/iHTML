<iREM -- Need to Fix Editor -- >
<iIF COND=<iSTRCMP SRC=":go" DST="editpost"> ALIAS="EditPost"><BR>
	<iIF COND=<iISDEF VAR="Confirmed"> ALIAS="YesDoIt">
		<iREM -- Escape Quotes in Body -- >
		<iREPLACE VAR="Body" SRC="'" DST="''">
		<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL=`UPDATE :Messages SET Body=':Body' WHERE MsgID=:msgid ;` NOOUTPUT="Message #<B>:msgid</B> has been updated." FAILURE="UPDATE ERROR: :i_sqlerrortext" OUTVAR="msg">
		<iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
	<iELSE ALIAS="YesDoIt">
		<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Body FROM :Messages :IfSQL WHERE MsgID = :msgid ;" OUTPUT=":1" OUTVAR="Body">
		<FORM METHOD=POST ACTION=':i_script_name#:msgid'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
		<FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><TEXTAREA NAME="Body" WRAP=SOFT ROWS=15 COLS=58>:Body</TEXTAREA></FONT><BR><BR>
		<INPUT TYPE=HIDDEN NAME="ID" VALUE=":id"><INPUT TYPE=HIDDEN NAME="msgid" VALUE=":msgid"><INPUT TYPE=HIDDEN NAME="go" VALUE="editpost"><INPUT TYPE=HIDDEN NAME="Confirmed" VALUE="1">
		<INPUT TYPE=SUBMIT VALUE=" Save Changes ">
		</FORM>
	</iIF ALIAS="YesDoIt">
</iIF ALIAS="EditPost">

<iIF COND=<iSTRCMP SRC=":go" DST="delpost"> ALIAS="DeletePost"><BR>
	<iIF COND=<iISDEF VAR="Confirmed"> ALIAS="YesDoIt">
		<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="DELETE FROM :Messages WHERE MsgID=:msgid ;" NOOUTPUT="Message #<B>:msgid</B> has been <B>deleted</B>." FAILURE="DELETE ERROR: :i_sqlerrortext" OUTVAR="msg">
		<iREPLACE VAR="msg" SRC=":IsSQLError" DST="Delete failed.">
		<FONT COLOR="#FF0000">:msg</FONT>
	<iELSE ALIAS="YesDoIt">
		<FONT COLOR="#FF0000">Are you sure you want to delete message #<B>:id</B>?</FONT>
		&nbsp;<A HREF=":i_script_name?go=delpost&id=:id&msgid=:msgid&Confirmed=1:mLinksA">Yes</A>&nbsp;<A HREF=':i_script_name' onClick="window.history.go(-1);">No</A>
	</iIF ALIAS="YesDoIt"><BR><BR>
</iIF ALIAS="DeletePost">

<iREM -- Get View Profile String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT CfgVal FROM _Config :IfSQL WHERE CfgVar='VIEWPROFILE' ;" OUTPUT=":1" NOOUTPUT="" FAILURE="" OUTVAR="ViewProfile">

<iREM -- Check for Old Imported BBS Data -- >
<iDEFAULT NAME="LoadDB_UseOld" VALUE="0"><iSET OldSQL=""><iIF EXPR=':LoadDB_UseOld OR :LoadDB_AllowNonAuth'><iSET OldSQL=", Poster_NonAuth"></iIF>

<iREM -- Get 'User Not Found' String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT cfgVal FROM _config :IfSQL WHERE cfgVar='NOTFOUND' ;" OUTPUT=":1" NOOUTPUT="Anonymous" FAILURE="Anonymous" OUTVAR="userNotFound">

<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Closed FROM :Threads :IfSQL WHERE TID=:id ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="IsClosed">
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Name FROM :Threads :IfSQL WHERE TID=:id ;" OUTPUT=":1" NOOUTPUT="ERROR" FAILURE=":i_sqlerrortext" OUTVAR="Name">
<iREPLACE VAR="Name" SRC=":IsSQLError" DST="Update failed.">
<TR WIDTH="100%"><TD COLSPAN=2>(Click <A HREF=':i_script_name' onClick="window.history.go(-1);">here</A> or your browser's BACK button to return to the topic list.)<BR><BR><H2>:Name</H2><B>Replies to Topic:</B><BR><BR></TD></TR>

<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT MsgID, Poster, Posted :OldSQL FROM :Messages :IfSQL WHERE Thread=:id ORDER BY MsgID ;" ALIAS="yyy"><iSQLFETCH ALIAS="yyy">

	<TR><TD WIDTH=100><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B><U>From:&nbsp;</U></B></FONT></TD>
			<TD WIDTH=100><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B><U>Date:&nbsp;</U></B></FONT></TD></TR>
	<iWHILE NOTALIAS=i_sqlempty>
		<iCRDATE ODBC=":yyy_Posted" FMT=":LoadDB_DateFormat" OUTVAR="PMDate">
		<iCRDATE ODBC=":yyy_Posted" FMT="%m/%d/%y" OUTVAR="PMDateD">
		<iCRTIME ODBC=":yyy_Posted" FMT="%H:%M:%S" OUTVAR="PMDateT">
		<iDATEDIFF DATE1=":LastVisitD" DATE2=":PMDateD" OUTVAR="DiffD">
		<iTIMEDIFF TIME1=":LastVisitT" TIME2=":PMDateT" OUTVAR="DiffT">

		<iREM -- Get Current User's Name -- >
		<iIF EXPR='(:LoadDB_UseOld OR :LoadDB_AllowNonAuth) AND <iSTRCMP SRC=":yyy_Poster" DST="">' ALIAS="UseOldNonAuth">
			<iSET CurUserName=":yyy_Poster_NonAuth">
		<iELSE ALIAS="UseOldNonAuth">
			<iSET CurUserName=""><iDEFAULT NAME="LoadDB_UserNameFields" VALUE="1">
			<iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
				<iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
				<iSTRCAT DST="CurUserName" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :yyy_Poster ;" OUTPUT=":1" NOOUTPUT=":userNotFound" FAILURE=":userNotFound" EVAL=TRUE> '>
			</iLOOP>
		</iIF ALIAS="UseOldNonAuth">

		<TR><TD WIDTH=300><A HREF="#:yyy_MsgID"><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">:CurUserName</FONT></A><iIF EXPR=':DiffD LT 0 OR (:DiffD = 0 AND :DiffT LT 0) AND NOT :NoNew' ALIAS="IsNew"> &nbsp; :LoadDB_NewIndicator</iIF ALIAS="IsNew"></TD>
				<TD WIDTH=200><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">:yyy_Posted</FONT></TD></TR>
		<iSQLFETCH ALIAS="yyy">
	</iWHILE ALIAS=i_sqlempty> 

	<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM :Messages :IfSQL WHERE Thread=:id ORDER BY MsgID ;" ALIAS="zzview"><iSQLFETCH ALIAS="zzview">

		<iWHILE NOTALIAS=i_sqlempty>
			<iCRDATE ODBC=":zzview_Posted" FMT=":LoadDB_DateFormat" OUTVAR="PMDate">
			<iCRDATE ODBC=":zzview_Posted" FMT="%m/%d/%y" OUTVAR="PMDateD">
			<iCRTIME ODBC=":zzview_Posted" FMT="%H:%M:%S" OUTVAR="PMDateT">
			<iDATEDIFF DATE1=":LastVisitD" DATE2=":PMDateD" OUTVAR="DiffD">
			<iTIMEDIFF TIME1=":LastVisitT" TIME2=":PMDateT" OUTVAR="DiffT">
			<iSET LastThread=":zzview_MsgID">

			<iREM -- Get Current User's Name -- >
			<iIF EXPR='(:LoadDB_UseOld OR :LoadDB_AllowNonAuth) AND <iSTRCMP SRC=":zzview_Poster" DST="">' ALIAS="UseOldNonAuth">
				<iSET CurUserName=":zzview_Poster_NonAuth">
			<iELSE ALIAS="UseOldNonAuth">
				<iSET CurUserName=""><iDEFAULT NAME="LoadDB_UserNameFields" VALUE="1">
				<iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
					<iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
					<iSTRCAT DST="CurUserName" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :zzview_Poster ;" OUTPUT=":1" NOOUTPUT=":userNotFound" FAILURE=":userNotFound" EVAL=TRUE> '>
				</iLOOP>
			</iIF ALIAS="UseOldNonAuth">

			<TR WIDTH="100%"><TD COLSPAN=2><HR NOSHADE><iEQ NAME="msgbody" VALUE=":zzview_Body">
<iREMBLOCK>
			<iIF EXPR=':LoadDB_StripHTML' ALIAS="Strip"><iREPLACE VAR="msgbody" SRC="<" DST=""><iREPLACE VAR="msgbody" SRC=">" DST=""></iIF ALIAS="Strip">
</iREMBLOCK>
			<iREPLACE VAR="msgbody" SRC=":i$crlf" DST="<P>">
			<FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">
			<iIF EXPR=<iSTRSPAN SRC=":PrivString" FIRST=1 NUM=1> ALIAS="CanEdit"><FONT SIZE="-2"><A HREF=":i_script_name?go=editpost&id=:id&msgid=:zzview_MsgID:mLinksA">Edit</A> </FONT></iIF ALIAS="CanEdit">
			<iIF EXPR=<iSTRSPAN SRC=":PrivString" FIRST=2 NUM=1> ALIAS="CanDel"><FONT SIZE="-2"><A HREF=":i_script_name?go=delpost&id=:id&msgid=:zzview_MsgID:mLinksA">Del</A> </FONT></iIF ALIAS="CanDel">
			<A NAME=":zzview_MsgID"><B>From:</B></A> :CurUserName
			<iIF EXPR='<iSTRSPAN SRC=":PrefString" FIRST=2 NUM=1> AND NOT <iSTRCMP SRC=":ViewProfile" DST=""> AND NOT <iSTRIN SRC=":curUserName" DST=":userNotFound">' ALIAS="ShowProf"><FONT SIZE="-2"> &nbsp; <A HREF='<iEQ VALUE=":ViewProfile" EVAL=TRUE>' TARGET="_blank">View Profile</A></FONT></iIF ALIAS="ShowProf">
			<iIF EXPR=':DiffD LT 0 OR (:DiffD = 0 AND :DiffT LT 0) AND NOT :NoNew' ALIAS="IsNew"> &nbsp; :LoadDB_NewIndicator</iIF ALIAS="IsNew"><BR>
			<B>Date:</B> :zzview_Posted<BR>
			<P>:msgbody</P>
			</FONT>
			</TD></TR>
			<iSQLFETCH ALIAS="zzview">
		</iWHILE ALIAS=i_sqlempty>

	</iSQL ALIAS="zzview">

</iSQL ALIAS="yyy">

<TR WIDTH="100%"><TD COLSPAN=2><HR NOSHADE>(Click <A HREF=':i_script_name' onClick="window.history.go(-1);">here</A> or your browser's BACK button to return to the topic list.)

<iIF NOTCOND=<iSTRCMP SRC=":IsClosed" DST="1"> ALIAS="NotClosed">
	<BR><BR><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B>:LoadDB_NewReplyText</B></FONT>

	<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
	<TR><TD COLSPAN=2>
		<iREM -- Post New Reply -- >
		<FORM METHOD=POST ACTION=':i_script_name#:LastThread'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
		<iIF EXPR=':LoadDB_AllowNonAuth AND (<iSTRIN SRC=":bbs_un" DST="Anonymous"> OR <iSTRIN SRC=":bbs_un" DST="Unauthenticated">)' ALIAS="AllowNonAuth">
			<FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor">From: &nbsp; <INPUT TYPE=TEXT NAME="NonAuthFrom" SIZE=35></FONT><BR><BR>
		</iIF ALIAS="AllowNonAuth">
		<FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><TEXTAREA NAME="Body" WRAP=SOFT ROWS=15 COLS=58></TEXTAREA></FONT><BR><BR>
		<INPUT TYPE=HIDDEN NAME="ID" VALUE=":id"><INPUT TYPE=HIDDEN NAME="IP" VALUE=":i_ip">
		<INPUT TYPE=HIDDEN NAME="go" VALUE="reply"><INPUT TYPE=HIDDEN NAME="Thread" VALUE=":id">
		<INPUT TYPE=HIDDEN NAME="LastThread" VALUE=":LastThread">
		<INPUT TYPE=SUBMIT NAME="ReplyOnly" VALUE=" Post Reply "> &nbsp; <INPUT TYPE=SUBMIT NAME="ReplyRefresh" VALUE=" Post Reply / Refresh Thread ">
		</FORM>
	</TD></TR>
	<TR><TD>
		<iREM -- Refresh Thread Only -- >
		<FORM METHOD=POST ACTION=':i_script_name#:LastThread'>
		<INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
		<INPUT TYPE=HIDDEN NAME="go" VALUE="view">
		<INPUT TYPE=HIDDEN NAME="ID" VALUE=":id">
		<INPUT TYPE=SUBMIT VALUE=" Refresh Thread Only "> &nbsp; 
		</FORM>
		</TD><TD>
		<iREM -- Back to List -- >
		<FORM METHOD=POST ACTION=':i_script_name'>
		<INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
		<INPUT TYPE=HIDDEN NAME="go" VALUE="list">
		<INPUT TYPE=SUBMIT VALUE=" Goto Thread List ">
		</FORM>
	</TD></TR>
	</TABLE>
<iELSE ALIAS="NotClosed">
	<BR><BR><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B>This topic has been closed.</B></FONT>
</iIF ALIAS="NotClosed">

</TD></TR>
