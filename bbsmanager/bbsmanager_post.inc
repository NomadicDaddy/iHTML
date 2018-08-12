<iEQ NAME=Date VALUE="<iDATETIME>" EVAL=TRUE>

<iIF NOTCOND=<iSTRCMP SRC=":AdminIP" DST=":i_ip"> ALIAS="NotAdmin">
	<iREM -- Strip HTML -- >
	<iIF EXPR=':LoadDB_StripHTML' ALIAS="Strip"><iREPLACE VAR="Body" SRC="<" DST="&lt;"><iREPLACE VAR="Body" SRC=">" DST="&gt;"></iIF ALIAS="Strip">
</iIF ALIAS="NotAdmin">

<iREM -- Convert Smileys -- >
<iDEFAULT NAME="LoadDB_ConvertSmileys" VALUE="1">
<iIF EXPR='<iSTRCMP SRC=":AdminIP" DST=":i_ip"> AND <iSTRIN SRC=":Body" DST="NOSMILEYS">' ALIAS="StopSmiling">
	<iREPLACE VAR="Body" SRC="NOSMILEYS" DST="">
<iELSEIF EXPR=':LoadDB_ConvertSmileys' ALIAS="StopSmiling">
	<iINCLUDE NAME=":FBase\bbsmanager_smileys.inc">
</iIF ALIAS="StopSmiling">

<iREM -- Tack on Signature -- >
<iIF EXPR='<iSTRSPAN SRC=":PrefString" FIRST=5 NUM=1> AND NOT <iSTRCMP SRC=":Signature" DST="">' ALIAS="AddSig"><iSTRCAT DST="Body" SRC=":Signature"></iIF ALIAS="AddSig">

<iREM -- Escape Quotes in Body -- >
<iREPLACE VAR="Body" SRC="'" DST="''">

<iREM -- Get User ID -- >
<iIF COND=<iISDEF VAR="NonAuthFrom"> ALIAS="IsNonAuth">
	<iSET PostedBy=0>
<iELSE ALIAS="IsNonAuth">
	<iSET IDQual=""><iIF NOTCOND=<iSTRCMP SRC=":LoadDB_AuthType" DST="Numeric">><iSET IDQual="'"></iIF>
	<iHTML DBNAME=':LoadDB_UserDSN' LOGIN=":LoadDB_UserLP" SQL="SELECT :LoadDB_UserID FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_AuthField = :IDQual:bbs_un:IDQual ;" OUTPUT=":1" NOOUTPUT="0" FAILURE=":i_sqlerrortext" ESC=FALSE OUTVAR="PostedBy">
</iIF ALIAS="IsNonAuth">

<iREM -- Get 'Can Post' Field -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT cfgVal FROM _config :IfSQL WHERE cfgVar='CANPOST' ;" OUTPUT=":1" NOOUTPUT="canPost" FAILURE="canPost" OUTVAR="canPost">
<iHTML DBNAME=':LoadDB_UserDSN' LOGIN=":LoadDB_UserLP" SQL="SELECT :canPost FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_AuthField = :IDQual:bbs_un:IDQual ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" ESC=FALSE OUTVAR="postAllowed">

<iREM -- Check/Handle Non-Authorized Posting -- >
<iIF EXPR='(NOT :PostedBy OR (NOT <iSTRCMP SRC=":postAllowed" DST="Y"> AND NOT <iSTRCMP SRC=":postAllowed" DST="1">) AND NOT :LoadDB_AllowNonAuth' ALIAS="Block"><iSET go="blocked"></iIF ALIAS="Block">

<iREM -- Set Notify -- >
<iSET notify=0><iIF EXPR='(<iSTRCMP SRC=":go" DST="post"> OR <iSTRCMP SRC=":go" DST="reply">) AND :LoadDB_NotifyOnPost' ALIAS="ChkNotify"><iSET notify=1></iIF ALIAS="ChkNotify">

<iREM -- Post Message -- >
<iIF COND=<iSTRCMP SRC=":go" DST="post"> ALIAS="Post">
	<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT MAX(TID) FROM :Threads :IfSQL WHERE Name = ':Topic' ;" OUTPUT=":1" NOOUTPUT="0" FAILURE=":i_sqlerrortext" EVAL=TRUE OUTVAR="Thread">
	<iREPLACE VAR="Thread" SRC=":IsSQLError" DST="Update failed.">
	<iIF EXPR=':Thread' ALIAS="IsReply">
		<iSET go="reply">
	<iELSE ALIAS="IsReply">
		<iIF EXPR='NOT <iSTRCMP SRC=":Body" DST=""> AND NOT <iSTRCMP SRC=":Body" DST=" "> AND NOT <iSTRCMP SRC=":Topic" DST=""> AND NOT <iSTRCMP SRC=":Topic" DST=" ">' ALIAS="GoPost">

			<iREM -- Escape Quotes in Topic -- >
			<iREPLACE VAR="Topic" SRC="'" DST="''">

			<iIF COND=<iISDEF VAR="NonAuthFrom"> ALIAS="IsNonAuth">
				<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Threads (Name, Originator_NonAuth) VALUES (':Topic', ':NonAuthFrom') ;` NOOUTPUT="1" FAILURE="THREAD ERROR: :i_sqlerrortext" OUTVAR="msg1">
			<iELSE ALIAS="IsNonAuth">
				<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Threads (Name, Originator) VALUES (':Topic', :PostedBy) ;` NOOUTPUT="1" FAILURE="THREAD ERROR: :i_sqlerrortext" OUTVAR="msg1">
			</iIF ALIAS="IsNonAuth">
			<iREPLACE VAR="msg1" SRC=":IsSQLError" DST="Update failed.">

			<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT TID FROM :Threads :IfSQL WHERE Name = ':Topic' ;" OUTPUT=":1" FAILURE=":i_sqlerrortext" EVAL=TRUE OUTVAR="Thread">
			<iREPLACE VAR="Thread" SRC=":IsSQLError" DST="Update failed.">

			<iIF COND=<iISDEF VAR="NonAuthFrom"> ALIAS="IsNonAuth">
				<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Messages (Thread, Poster_NonAuth, IP, Posted, Body) VALUES (:Thread, ':NonAuthFrom', ':IP', ':Date', ':Body') ;` NOOUTPUT="1" FAILURE="MESSAGE ERROR: :i_sqlerrortext" EVAL=TRUE OUTVAR="msg2">
			<iELSE ALIAS="IsNonAuth">
				<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Messages (Thread, Poster, IP, Posted, Body) VALUES (:Thread, :PostedBy, ':IP', ':Date', ':Body') ;` NOOUTPUT="1" FAILURE="MESSAGE ERROR: :i_sqlerrortext" EVAL=TRUE OUTVAR="msg2">
			</iIF ALIAS="IsNonAuth">
			<iREPLACE VAR="msg2" SRC=":IsSQLError" DST="Update failed.">

			<iIF EXPR='<iSTRCMP SRC=":msg2" DST="1"> AND <iSTRCMP SRC=":msg2" DST="1">' ALIAS="Success">
				<iSET msg="Your message was posted successfully.">
			<iELSE ALIAS="Success">
				<iSET msg=":msg1	:msg2">
			</iIF ALIAS="Success">
			<iIF EXPR=':notify' ALIAS="DoNotify"><iINCLUDE NAME=":FBase\bbsmanager_notify.inc"></iIF ALIAS="DoNotify">
			<iSET go="list" msg=":msg">
		<iELSE ALIAS="GoPost">
			<iSET go="list" msg="Neither your topic nor message can be blank.">
		</iIF ALIAS="GoPost">
	</iIF ALIAS="IsReply">
</iIF ALIAS="Post">

<iREM -- Reply to Message -- >
<iIF COND=<iSTRCMP SRC=":go" DST="reply"> ALIAS="Reply">
	<iIF EXPR='NOT <iSTRCMP SRC=":Body" DST=""> AND NOT <iSTRCMP SRC=":Body" DST=" ">' ALIAS="GoReply">

		<iIF COND=<iISDEF VAR="NonAuthFrom"> ALIAS="IsNonAuth">
			<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Messages (Thread, Poster_NonAuth, IP, Posted, Body) VALUES (:Thread, ':NonAuthFrom', ':IP', ':Date', ':Body') ;` NOOUTPUT="Your reply was posted successfully." FAILURE="REPLY ERROR: :i_sqlerrortext" EVAL=TRUE OUTVAR="msg">
		<iELSE ALIAS="IsNonAuth">
			<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL=`INSERT INTO :Messages (Thread, Poster, IP, Posted, Body) VALUES (:Thread, :PostedBy, ':IP', ':Date', ':Body') ;` NOOUTPUT="Your reply was posted successfully." FAILURE="REPLY ERROR: :i_sqlerrortext" EVAL=TRUE OUTVAR="msg">
		</iIF ALIAS="IsNonAuth">
		<iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">

		<iIF EXPR=':notify' ALIAS="DoNotify"><iINCLUDE NAME=":FBase\bbsmanager_notify.inc"></iIF ALIAS="DoNotify">
		<iSET go="list" id=":Thread" msg=":msg">
	<iELSE ALIAS="GoReply">
		<iSET go="list" msg="Your message cannot be blank.">
	</iIF ALIAS="GoReply">
</iIF ALIAS="Reply">

<iREM -- Check for Refresh Thread -- >
<iIF COND=<iISDEF VAR="ReplyRefresh"> ALIAS="Refresher"><iSET go="view"></iIF ALIAS="Refresher">

<iREM -- Not Authorized -- >
<iIF COND=<iSTRCMP SRC=":go" DST="blocked"> ALIAS="Blocked">
	<iSET go="list" msg="You are not authorized to post.	PostedBy=':PostedBy'	AllowNonAuth=:LoadDB_AllowNonAuth	:ck_usr :username :i_auth_user	DSN=:LoadDB_UserDSN SQL=SELECT :LoadDB_UserID FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_AuthField = ':bbs_un' ;">
</iIF ALIAS="Blocked">

<iREM -- All Other Cases -- >
<iDEFAULT NAME="go" VALUE="list">
