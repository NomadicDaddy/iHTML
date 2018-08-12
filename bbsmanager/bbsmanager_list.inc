<iREM -- Check for Old Imported BBS Data -- >
<iDEFAULT NAME="LoadDB_UseOld" VALUE="0"><iSET OldSQL=""><iIF EXPR=':LoadDB_UseOld OR :LoadDB_AllowNonAuth'><iSET OldSQL=", :Threads"><iSTRCAT DST="OldSQL" SRC=".Originator_NonAuth"></iIF>

<iSET NewAge=<iDATE>><iIF EXPR=':IsSQL' ALIAS="IsSQL"><iDATETIME FMT="%Y-%m-%d %H:%M:%S" OUTVAR="NewAge"></iIF ALIAS="IsSQL">

<iSET tTID=":Threads" tName=":Threads" tOriginator=":Threads" tClosed=":Threads" mMsgID=":Messages" mPosted=":Messages" mThread=":Messages">
<iSTRCAT DST="tTID" SRC=".TID"><iSTRCAT DST="tName" SRC=".Name"><iSTRCAT DST="tOriginator" SRC=".Originator"><iSTRCAT DST="tClosed" SRC=".Closed">
<iSTRCAT DST="mMsgID" SRC=".MsgID"><iSTRCAT DST="mPosted" SRC=".Posted"><iSTRCAT DST="mThread" SRC=".Thread">

<iIF COND=<iSTRCMP SRC=":go" DST="status"> ALIAS="ChangeStatus"><BR>
	<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT :tName FROM :Threads :IfSQL WHERE :tTID = :id ;" OUTPUT=":1" OUTVAR="ztName">
	<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT :tClosed FROM :Threads :IfSQL WHERE :tTID = :id ;" OUTPUT=":1" OUTVAR="ztClosed">
	<iIF COND=<iISDEF VAR="Confirmed"> ALIAS="YesDoIt">
		<iIF COND=<iSTRCMP SRC=":ztClosed" DST="1">><iSET NSt="Open" NSn=0><iELSE><iSET NSt="Closed" NSn=1></iIF>
		<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="UPDATE :Threads SET Closed=:NSn WHERE TID=:id ;" NOOUTPUT="Thread #<B>:id</B> (<B>:ztName</B>) has been changed to <B>:NSt</B>." FAILURE="UPDATE ERROR: :i_sqlerrortext" OUTVAR="msg">
		<iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
	<iELSE ALIAS="YesDoIt">
		<iIF COND=<iSTRCMP SRC=":ztClosed" DST="1">><iSET NSt="open"><iELSE><iSET NSt="close"></iIF>
		<FONT COLOR="#FF0000">Are you sure you want to :NSt thread #<B>:id</B> (<B>:ztName</B>)?</FONT>
		&nbsp;<A HREF=":i_script_name?go=status&id=:id&Confirmed=1:mLinksA">Yes</A>&nbsp;<A HREF=':i_script_name' onClick="window.history.go(-1);">No</A>
	</iIF ALIAS="YesDoIt">
</iIF ALIAS="ChangeStatus">

<iIF COND=<iSTRCMP SRC=":go" DST="delthread"> ALIAS="DeleteThread"><BR>
	<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT :tName FROM :Threads :IfSQL WHERE :tTID = :id ;" OUTPUT=":1" OUTVAR="ztName">
	<iIF COND=<iISDEF VAR="Confirmed"> ALIAS="YesDoIt">
		<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="DELETE FROM :Threads WHERE TID=:id ;" NOOUTPUT="Thread #<B>:id</B> (<B>:ztName</B>) has been <B>deleted</B>." FAILURE="DELETE ERROR: :i_sqlerrortext" OUTVAR="msg">
		<iREPLACE VAR="msg" SRC=":IsSQLError" DST="Delete failed.">
	<iELSE ALIAS="YesDoIt">
		<FONT COLOR="#FF0000">Are you sure you want to delete thread #<B>:id</B> (<B>:ztName</B>)?</FONT>
		&nbsp;<A HREF=":i_script_name?go=delthread&id=:id&Confirmed=1:mLinksA">Yes</A>&nbsp;<A HREF=':i_script_name' onClick="window.history.go(-1);">No</A>
	</iIF ALIAS="YesDoIt">
</iIF ALIAS="DeleteThread">

<iREM -- Get Public Stats String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT CfgVal FROM _Config :IfSQL WHERE CfgVar='PUBLICSTATS' ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="PublicStats">

<iREM -- Get 'User Not Found' String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT cfgVal FROM _config :IfSQL WHERE cfgVar='NOTFOUND' ;" OUTPUT=":1" NOOUTPUT="Anonymous" FAILURE="Anonymous" OUTVAR="userNotFound">

<FORM METHOD=POST ACTION=':i_script_name'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
<TR><TD WIDTH=1%>&nbsp;</TD><TD COLSPAN=4 ALIGN=RIGHT><FONT FACE=":LoadDB_ListTextFont" SIZE="-1" COLOR=":LoadDB_ListTextColor">&nbsp; <A HREF=":i_script_name?go=search:mLinksA">Search</A><iIF EXPR=':PublicStats' ALIAS="ShowStats">&nbsp; <A HREF=":i_script_name?go=stats:mLinksA">Statistics</A></iIF ALIAS="ShowStats">&nbsp; <A HREF=":i_script_name?go=prefs:mLinksA">Preferences</A>&nbsp; <A HREF=":i_script_name?go=Contact%20adminware%20Support:mLinksA">Support</A></FONT></TD></TR>
<TR><TD WIDTH=1%>&nbsp;</TD><TD COLSPAN=2>&nbsp;<A HREF="#Post">Post New Topic</A></TD>

<TD COLSPAN=2 ALIGN=RIGHT WIDTH=1% NOWRAP>
	<SELECT NAME="Age" onChange="form.submit()">
	<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Age, Description FROM _Ages :IfSQL ORDER BY Age ;" ALIAS="Ages"><iSQLFETCH ALIAS="Ages">
		<iWHILE NOTALIAS=i_sqlempty>
			<OPTION VALUE=":Ages_Age" <iIF EXPR=':Age = :Ages_Age'>SELECTED</iIF>>Show :Ages_Description</OPTION>
			<iSQLFETCH ALIAS="Ages">
		</iWHILE ALIAS=i_sqlempty>
	</iSQL ALIAS="Ages">
	</SELECT> <INPUT TYPE=SUBMIT VALUE="Refresh">
</TD></TR></FORM>

<iIF EXPR=':IsSQL' ALIAS="IsSQL">
	<iEVAL EXPR=':Age*1440' OUTVAR="AgeInMin">
	<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT :tTID, :tName, :tOriginator, :tClosed, Count(:mMsgID) AS MessageCount, Max(:mPosted) AS LastMessage :OldSQL FROM :Threads, :Messages :IfSQL WHERE :tTID = :mThread GROUP BY :tTID, :tName, :tOriginator, :tClosed :OldSQL HAVING :AgeInMin > DATEDIFF(n, MAX(:mPosted), ':NewAge') ORDER BY MAX(:mPosted) DESC ;" ALIAS="zzlist">
<iELSE ALIAS="IsSQL">
	<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT :tTID, :tName, :tOriginator, :tClosed, Count(:mMsgID) AS MessageCount, Max(:mPosted) AS LastMessage :OldSQL FROM :Threads, :Messages :IfSQL WHERE :tTID = :mThread GROUP BY :tTID, :tName, :tOriginator, :tClosed :OldSQL HAVING MAX(:mPosted) > (#:NewAge#-:Age) ORDER BY MAX(:mPosted) DESC ;" ALIAS="zzlist">
</iIF ALIAS="IsSQL">
<iSQLFETCH ALIAS="zzlist">

	<iCASE ALIAS=i_sqlempty VALUE=FALSE>
		<TR BGCOLOR=":LoadDB_BarColor">
			<TD WIDTH=1% BGCOLOR="#FFFFFF">&nbsp;</TD>
			<TD NOWRAP><FONT FACE=":LoadDB_BarTextFace" SIZE=":LoadDB_BarTextSize" COLOR=":LoadDB_BarTextColor">Topic</FONT></TD>
<iREMBLOCK>
			<TD><FONT FACE=":LoadDB_BarTextFace" SIZE=":LoadDB_BarTextSize" COLOR=":LoadDB_BarTextColor">Originator</FONT></TD>
</iREMBLOCK>
			<TD WIDTH=1% ALIGN=CENTER NOWRAP><FONT FACE=":LoadDB_BarTextFace" SIZE=":LoadDB_BarTextSize" COLOR=":LoadDB_BarTextColor">Replies</FONT></TD>
			<TD WIDTH=1% ALIGN=RIGHT NOWRAP><FONT FACE=":LoadDB_BarTextFace" SIZE=":LoadDB_BarTextSize" COLOR=":LoadDB_BarTextColor">Last Message</FONT></TD>
		</TR>
	</iCASE ALIAS=i_sqlempty>
	<iCASE ALIAS=i_sqlempty VALUE=TRUE>
		<TR><TD COLSPAN=5 ALIGN=CENTER><BR><FONT FACE=":LoadDB_HeadTextFont" SIZE=":LoadDB_HeadTextSize" COLOR="#FF0000"><B>There are currently no topics in the selected date range.<BR>Choose a larger range or start a new topic one below.</B></FONT></TD></TR>
	</iCASE ALIAS=i_sqlempty>

	<iWHILE NOTALIAS=i_sqlempty>
		<iCRDATE ODBC=":zzlist_LastMessage" FMT=":LoadDB_DateFormat" OUTVAR="PMDate">
		<iCRDATE ODBC=":zzlist_LastMessage" FMT="%m/%d/%y" OUTVAR="PMDateD">
		<iCRTIME ODBC=":zzlist_LastMessage" FMT="%H:%M:%S" OUTVAR="PMDateT">
		<iDATEDIFF DATE1=":LastVisitD" DATE2=":PMDateD" OUTVAR="DiffD">
		<iTIMEDIFF TIME1=":LastVisitT" TIME2=":PMDateT" OUTVAR="DiffT">
		<iIF EXPR=':DiffD LT 0 OR (:DiffD = 0 AND :DiffT LT 0' ALIAS="Y"><iSET NoNew=1></iIF ALIAS="Y">
		<iEVAL EXPR=':zzlist_MessageCount - 1' OUTVAR="Replies">

		<iREM -- Get Current User's Name -- >
		<iIF EXPR='(:LoadDB_UseOld OR :LoadDB_AllowNonAuth) AND <iSTRCMP SRC=":zzlist_Originator" DST="">' ALIAS="UseOldNonAuth">
			<iSET CurUserName=":zzlist_Originator_NonAuth">
		<iELSE ALIAS="UseOldNonAuth">
			<iSET CurUserName=""><iDEFAULT NAME="LoadDB_UserNameFields" VALUE="1">
			<iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
				<iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
				<iSTRCAT DST="CurUserName" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :zzlist_Originator ;" OUTPUT=":1" NOOUTPUT=":userNotFound" FAILURE=":userNotFound" EVAL=TRUE> '>
			</iLOOP>
		</iIF ALIAS="UseOldNonAuth">

		<iREM -- Set Last Message Date -- >
		<iIF COND=<iSTRCMP SRC=":PMDateD" DST='<iDATE FMT="%m/%d/%y">'>><iSET LastMsgDate=":PMDateT"><iELSE><iSET LastMsgDate=":PMDateD"></iIF>

		<iREM -- Set IsClosed -- >
		<iIF COND=<iSTRCMP SRC=":zzlist_Closed" DST="1">><iSET IsClosed=` <FONT SIZE="-1">(closed)</FONT>`><iELSE><iSET IsClosed=""></iIF>

		<TR>
			<TD WIDTH=1% ALIGN=RIGHT NOWRAP>
				<iIF EXPR=<iSTRSPAN SRC=":PrivString" FIRST=3 NUM=1> ALIAS="CanStat"><FONT SIZE="-2"><A HREF=":i_script_name?go=status&id=:zzlist_TID:mLinksA">S</A> </FONT></iIF ALIAS="CanStat">
				<iIF EXPR=<iSTRSPAN SRC=":PrivString" FIRST=4 NUM=1> ALIAS="CanDel"><FONT SIZE="-2"><A HREF=":i_script_name?go=delthread&id=:zzlist_TID:mLinksA">D</A> </FONT></iIF ALIAS="CanDel">
				<iIF EXPR=":Replies > 0" ALIAS="HasReps"><A HREF=":i_script_name?go=view&id=:zzlist_TID:mLinksA"><IMG SRC="/images/adminware/plus.gif" ALT="[+]" WIDTH=10 HEIGHT=10 HSPACE=1 BORDER=0></A><iELSE ALIAS="HasReps"><IMG SRC="/images/adminware/space.gif" ALT="" WIDTH=10 HEIGHT=10 HSPACE=1 BORDER=0></iIF ALIAS="HasReps"></TD>
			<TD NOWRAP><FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor"><A HREF=":i_script_name?go=view&id=:zzlist_TID&replies=:Replies:mLinksA">:zzlist_Name</A> &nbsp;(<iSTRLEFT SRC=":CurUserName" NUM=<iEVAL EXPR=`<iSTRLEN SRC=":CurUserName">-1`>>)</FONT><iIF EXPR=':DiffD GTE 0 AND :DiffT GTE 0 AND NOT :NoNew' ALIAS="IsNew"> &nbsp; :LoadDB_NewIndicator</iIF ALIAS="IsNew">:IsClosed &nbsp; &nbsp;</TD>
<iREMBLOCK>
			<TD><FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor">:CurUserName &nbsp; &nbsp; </FONT></TD>
</iREMBLOCK>
			<TD WIDTH=1% ALIGN=CENTER NOWRAP><FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor">:Replies</FONT></TD>
			<TD WIDTH=1% ALIGN=RIGHT NOWRAP><FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor"> &nbsp; &nbsp; :LastMsgDate</FONT></TD>
		</TR>
		<iSQLFETCH ALIAS="zzlist">
	</iWHILE ALIAS=i_sqlempty>

	</TABLE><TABLE WIDTH=95% BORDER=0 CELLSPACING=1 CELLPADDING=1>

	<TR><TD WIDTH=1%>&nbsp;</TD><TD COLSPAN=4><HR NOSHADE><A NAME="Post"><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B>:LoadDB_NewPostText</B></FONT></A><BR><BR>

	<FORM METHOD=POST ACTION=':i_script_name'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
	<iIF EXPR=':LoadDB_AllowNonAuth AND (<iSTRIN SRC=":bbs_un" DST=":userNotFound"> OR <iSTRIN SRC=":bbs_un" DST="Unauthenticated">)' ALIAS="AllowNonAuth">
		<FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor">From: &nbsp; <INPUT TYPE=TEXT NAME="NonAuthFrom" SIZE=35></FONT><BR><BR>
	</iIF ALIAS="AllowNonAuth">
	<FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor">Topic: &nbsp; <INPUT TYPE=TEXT NAME="Topic" SIZE=35 MAXLENGTH=50></FONT><BR><BR>
	<FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><TEXTAREA NAME="Body" WRAP=SOFT ROWS=15 COLS=45></TEXTAREA></FONT><BR><BR>
	<INPUT TYPE=HIDDEN NAME="IP" VALUE=":i_ip"><INPUT TYPE=HIDDEN NAME="go" VALUE="post">
	<INPUT TYPE=SUBMIT VALUE=" Post Topic "></FORM></TD></TR>

</iSQL ALIAS="zzlist">
