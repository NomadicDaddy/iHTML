<iREMBLOCK>
adminware BBSManager
Copyright © 1999-2002 adminware, inc.  All rights reserved.
</iREMBLOCK>

<iSET AWPV="BBS Manager v1.40.358.1" demoDSN="adminware_bbsmanager" demo=0 notifyTo="pbeazley@onvix.com" notifyFrom="bbsmanager@adminware.com" fBase="w:\bbsmanager">

<iDEFAULT NAME="login" VALUE="/">

<iSET showErrors=0><iINCLUDE NAME="w:\ifuncs\errorHandler.inc">
<iINCLUDE NAME="w:\shared\config.inc">

<iREM -- Check for Bad Cookie or KillCookie -- >
<iIF EXPR='<iISDEF VAR="killCookie"> OR <iSTRCMP SRC=":ck_usr" DST=""> OR <iSTRCMP SRC=":ck_usr" DST="Anonymous">'>
	<iCOOKIE NAME="ck_usr" VALUE="" EXPIRES=-200 DISCARD=TRUE PATH="/">
	<iSET msg="Bad cookie removed and reset.">
</iIF>

<iREM -- Get Auth Method and UserName -- >
<iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT id FROM _boards :IfSQL WHERE name=':show' AND active=1 ;" OUTPUT=":1" NOOUTPUT="0" OUTVAR="ActiveBoard">
<iSET AuthedBy="Unauthenticated" bbs_un="Anonymous" mLinksA="" mLinksQ="">
<iIF EXPR='NOT <iSTRCMP SRC=":ck_usr" DST=""> AND <iISDEF VAR="ck_usr">' ALIAS="C1"><iSET AuthedBy="Cookie" bbs_un=":ck_usr"></iIF ALIAS="C1">
<iIF EXPR='NOT <iSTRCMP SRC=":username" DST=""> AND <iISDEF VAR="username">' ALIAS="C2"><iSET AuthedBy="Pass-Thru" bbs_un=":username"></iIF ALIAS="C2">
<iIF EXPR='NOT <iSTRCMP SRC=":i_auth_user" DST=""> AND <iISDEF VAR="i_auth_user">' ALIAS="C3"><iSET AuthedBy="Server-Side" bbs_un=":i_auth_user"></iIF ALIAS="C3">
<iIF EXPR='NOT <iSTRCMP SRC=":bbs_un" DST="Anonymous"> AND NOT <iISDEF VAR="ck_usr">' ALIAS="C4"><iCOOKIE NAME="ck_usr" VALUE=":bbs_un" PATH="/"></iIF ALIAS="C4">
<iIF NOTCOND=<iSTRCMP SRC=":bbs_un" DST="Anonymous"> ALIAS="GetUN"><iSET mLinksA="&username=:bbs_un" mLinksQ="?username=:bbs_un"></iIF ALIAS="GetUN">

<iDEFAULT NAME="show" VALUE="main"><iSET threads=":show" messages=":show"><iSTRCAT DST="Threads" SRC="_threads"><iSTRCAT DST="Messages" SRC="_messages">
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT id FROM _boards :IfSQL WHERE name=':show' ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="board">

<iIF EXPR=':board > 0' ALIAS="goodBoard1">
	<iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT id FROM _boards :IfSQL WHERE name=':show' AND active=1 ;" OUTPUT=":1" NOOUTPUT="0" OUTVAR="activeBoard">
	<iIF EXPR=':activeBoard' ALIAS="goodBoard2">
		<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM _boards :IfSQL WHERE id=:activeBoard ;" ALIAS="loadDB"><iSQLFETCH ALIAS="loadDB">

			<iREM -- Get User Logged In -->
			<iIF NOTCOND=<iSTRCMP SRC=":bbs_un" DST="Anonymous"> ALIAS="GetUN">
				<iSET AFQual=""><iIF NOTCOND=<iSTRCMP SRC=":loadDB_AuthType" DST="Numeric">><iSET AFQual="'"></iIF>
				<iSET UserLoggedIn=""><iDEFAULT NAME="loadDB_UserNameFields" VALUE="1">
				<iLOOP INITIAL="1" FINAL=":loadDB_UserNameFields">
					<iEQ NAME="tmp" VALUE=":loadDB_UserName:i_loop" EVAL=TRUE>
					<iSTRCAT DST="UserLoggedIn" SRC='<iHTML LOGIN=":loadDB_UserLP" DBNAME=":loadDB_UserDSN" SQL="SELECT :tmp FROM :loadDB_UserTable :IfUSQL WHERE :loadDB_AuthField = :AFQual:bbs_un:AFQual ;" OUTPUT=":1" NOOUTPUT="Anonymous (NOP)" FAILURE="Anonymous (Error)" ESC=FALSE EVAL=TRUE> '>
				</iLOOP>

				<iIF NOTCOND=<iSTRCMP SRC=":loadDB_uActiveField" DST=""> ALIAS="checkActive">
					<iHTML LOGIN=":loadDB_UserLP" DBNAME=":loadDB_UserDSN" SQL="SELECT :loadDB_uActiveField FROM :loadDB_UserTable :IfUSQL WHERE :loadDB_AuthField = :AFQual:bbs_un:AFQual ;" OUTPUT=":1" NOOUTPUT="NOP" FAILURE=":i_sqlerrortext" ESC=FALSE OUTVAR="uActiveCheck">
					<iIF NOTCOND=<iSTRCMP SRC=":uActiveCheck" DST=":loadDB_uActiveOn"> ALIAS="Inactive"><iSET AuthedBy="Unauthenticated" bbs_un="Anonymous" UserLoggedIn="" mLinksA="" mLinksQ=""></iIF ALIAS="Inactive">
				</iIF ALIAS="checkActive">

		<iREM -- Remove Extra Space at End if Present -- >

			<iELSE ALIAS="GetUN">
				<iSET UserLoggedIn="Anonymous">
			</iIF ALIAS="GetUN">

			<iREM -- Get User Privs & Prefs -- >
			<iINCLUDE NAME=":FBase\bbsmanager_privsprefs.inc">

			<iREM -- Use Alternate DisplayName if Specified -- >
			<iSET DisplayName=':show'><iIF NOTCOND=<iSTRCMP SRC=":loadDB_DisplayName" DST=""> ALIAS="AltName"><iSET DisplayName=`:loadDB_DisplayName`></iIF ALIAS="AltName">

			<iREM -- Are there new items? -- >
			<iSET NoNew=0>
			<iIF COND=<iISDEF VAR="ck_lastvisit"> ALIAS="NewItems">

		<iREM -- Ignore Cookie -- >
		<iSET ck_lastvisit="2000-06-18 02:11:12">

				<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT MAX(Posted) FROM :Messages :IfSQL ;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="MaxDate">

				<iIF NOTCOND=<iSTRCMP SRC=":MaxDate" DST="NA"> ALIAS="AnyNew">
					<iCRDATE ODBC=":ck_lastvisit" FMT="%m/%d/%y" OUTVAR="LastVisitD">
					<iCRTIME ODBC=":ck_lastvisit" FMT="%H:%M:%S" OUTVAR="LastVisitT">
					<iCRDATE ODBC=":MaxDate" FMT="%m/%d/%y" OUTVAR="MaxDateD">
					<iCRTIME ODBC=":MaxDate" FMT="%H:%M:%S" OUTVAR="MaxDateT">
					<iDATEDIFF DATE1=":LastVisitD" DATE2=":MaxDateD" OUTVAR="DiffD">
					<iTIMEDIFF TIME1=":LastVisitT" TIME2=":MaxDateT" OUTVAR="DiffT">
					<iIF EXPR=':DiffD LT 0 OR (:DiffD = 0 AND :DiffT LT 0)' ALIAS="Y"><iSET NoNew=1></iIF ALIAS="Y">
					<iSET LastVisit=":ck_lastvisit">
				<iELSE ALIAS="AnyNew">
					<iDATE FMT="%m/%d/%y" OUTVAR="LastVisitD">
					<iTIME FMT="%H:%M:%S" OUTVAR="LastVisitT">
					<iDATETIME FMT="%Y-%m-%d %H:%M:%S" OUTVAR="LastVisit"><iCOOKIE NAME="ck_lastvisit" VALUE=":LastVisit" PATH="/">
				</iIF ALIAS="AnyNew">

			<iELSE ALIAS="NewItems">
				<iDATE FMT="%m/%d/%y" OUTVAR="LastVisitD">
				<iTIME FMT="%H:%M:%S" OUTVAR="LastVisitT">
				<iDATETIME FMT="%Y-%m-%d %H:%M:%S" OUTVAR="LastVisit"><iSET NoNew=1>
			</iIF ALIAS="NewItems">

			<iIF EXPR=':NoNew' ALIAS="Reset"><iDATETIME FMT="%Y-%m-%d %H:%M:%S" OUTVAR="LastVisit"><iCOOKIE NAME="ck_lastvisit" VALUE=":LastVisit" PATH="/"></iIF ALIAS="Reset">

			<iIF EXPR='NOT :loadDB_HideHeader' ALIAS="HideHeader">
				<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":loadDB_BarColor"><TD><FONT FACE=":loadDB_BarTextFace" SIZE=":loadDB_BarTextSize" COLOR=":loadDB_BarTextColor"><B>:DisplayName</B></FONT></TD>
<iREMBLOCK>
					<TD ALIGN=RIGHT><FONT FACE=":loadDB_ListTextFace" SIZE=":loadDB_ListTextSize" COLOR=":loadDB_BarTextColor">Your last visit was on <B>:LastVisit</B>.
						<iIF EXPR=':NoNew' ALIAS="Nope">
							No new items have been posted.
						<iELSE ALIAS="Nope">
							Items posted since then have been marked new.
						</iIF ALIAS="Nope">
					</FONT></TD>
</iREMBLOCK>
				</TR></TABLE>
			</iIF ALIAS="HideHeader">
			<CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=1 CELLPADDING=1>

			<iREM -- What to do? -- >
			<iIF EXPR='<iSTRCMP SRC=":go" DST="Contact adminware Support">' ALIAS="GoSupport"><iINCLUDE NAME="w:\shared\support_request.inc"></iIF ALIAS="GoSupport">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="post"> OR <iSTRCMP SRC=":go" DST="reply">' ALIAS="GoPost"><iINCLUDE NAME=":FBase\bbsmanager_post.inc"></iIF ALIAS="GoPost">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="prefs"> OR <iSTRCMP SRC=":go" DST="set">' ALIAS="GoPrefs"><iINCLUDE NAME=":FBase\bbsmanager_prefs.inc"></iIF ALIAS="GoPrefs">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="stats">' ALIAS="GoStats"><iINCLUDE NAME=":FBase\bbsmanager_stats.inc"></iIF ALIAS="GoStats">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="search">' ALIAS="GoSearch"><iINCLUDE NAME=":FBase\bbsmanager_search.inc"></iIF ALIAS="GoSearch">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="view"> OR <iSTRCMP SRC=":go" DST="editpost"> OR <iSTRCMP SRC=":go" DST="delpost">' ALIAS="GoView"><iINCLUDE NAME=":FBase\bbsmanager_view.inc"></iIF ALIAS="GoView">
			<iIF EXPR='<iSTRCMP SRC=":go" DST="list"> OR <iSTRCMP SRC=":go" DST="status"> OR <iSTRCMP SRC=":go" DST="delthread"> OR <iSTRCMP SRC=":go" DST="default"> OR NOT <iISDEF VAR="go">' ALIAS="GoList"><iINCLUDE NAME=":FBase\bbsmanager_list.inc"></iIF ALIAS="GoList">

			<iREM -- Default Msg -- >
			<iIF COND=<iSTRCMP SRC=":AdminIP" DST=":i_ip"> ALIAS="IsAdmin"><iSET ULIPre="<FONT COLOR='#FFFF00'>" ULIPost="</FONT>"><iELSE ALIAS="IsAdmin"><iSET ULIPre="" ULIPost=""></iIF ALIAS="IsAdmin">
			<iDEFAULT NAME="msg" VALUE="User Logged In:	:ULIPre:UserLoggedIn:ULIPost <FONT SIZE='-2'>(via :AuthedBy)</FONT>">

			</TABLE></CENTER><BR>
			<iIF EXPR='NOT :loadDB_HideFooter' ALIAS="HideFooter"><TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":loadDB_BarColor"><TD>&nbsp;<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>:msg</B></FONT></iIF ALIAS="ShowMsg"></TD><TD ALIGN=RIGHT><FONT FACE=":loadDB_BarTextFace" SIZE=":loadDB_BarTextSize" COLOR=":loadDB_BarTextColor"><B>:AWPV</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B>Copyright &copy; 1999-2000 adminware, inc.	All rights reserved.</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B><A HREF="http://adminware.com/" onMouseOver="status='adminware'; return true;" onMouseOut="status='';">http://adminware.com/</A></B></FONT></TD></TR></TABLE></iIF ALIAS="HideFooter">

		</iSQL ALIAS="loadDB">
	<iELSE ALIAS="goodBoard2">
	<CENTER><FONT COLOR="#FF0000"><B>That BBSManager Board (:dsn/:show) is not currently active.</B></FONT><BR><BR></CENTER>
	</iIF ALIAS="goodBoard2">
<iELSE ALIAS="goodBoard1">
	<CENTER><FONT COLOR="#FF0000"><B>There is no BBSManager Board with that name (:dsn/:show) currently setup.</B></FONT><BR>Check the name and try again or use the Administrative interface to create this BBSManager Board.<BR><BR></CENTER>
</iIF ALIAS="goodBoard1">

<iIF EXPR=':demo' ALIAS="IsDemo"><CENTER>
	<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Name FROM _Boards :IfSQL ;" ALIAS="Boards">
		<iSQLFETCH ALIAS="Boards">
		<iWHILE NOTALIAS=i_sqlempty>
			<A HREF=":i_script_name?Show=:Boards_Name">:Boards_Name</A>
			<iSQLFETCH ALIAS="Boards">
		</iWHILE ALIAS=i_sqlempty>
	</iSQL ALIAS="Boards">
	<BR><BR><A HREF=":i_script_name?Admin">Click here to view the BBSManager Administration Interface Demo.</A>
</CENTER></iIF ALIAS="IsDemo">
