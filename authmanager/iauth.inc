<iREMBLOCK>
adminware AuthManager v1.23.171.1 Authentication Module
Copyright � 1999-2002 adminware, llc
Uses InFusion Authenticator, Copyright � 1999 On-Line Data Solutions, Inc.
</iREMBLOCK>

<iINCLUDE NAME="#iauth.cfg"><iSET pass=0 abort=0 status="Failed ()">

realm=:auth_realm

Server-Side:  ':cfauser/:cfapass'
Cookie-Based: ':ck_usr/:ck_pwd'

<iIF EXPR=':auth_onlyrefs AND NOT (:auth_svr AND :auth_bypass) AND NOT <iSTRIN SRC=":i_referer" DST=":auth_allowrefs"> AND NOT <iSTRIN SRC=":i_referer" DST="">' ALIAS="CheckPoint">
-- Bad Referrer --
	<iSET pass=0 status="Failed (Bad Referrer)">
<iELSEIF EXPR='NOT :auth_cookies AND <iSTRCMP SRC=":cfauser" DST=""> AND <iSTRCMP SRC=":cfapass" DST="">' ALIAS="CheckPoint">
-- Not using Cookies and no Server-Side Auth Info --
	<iSET pass=0 status="Not using Cookies and no Server-Side Auth Info" log_on=0>
<iELSE ALIAS="CheckPoint">

	<iIF EXPR=':auth_cookies AND <iISDEF VAR="ck_usr"> AND <iISDEF VAR="ck_pwd"> AND NOT <iSTRIN SRC=":ck_usr" DST="ck_usr"> AND NOT <iSTRIN SRC=":ck_pwd" DST="ck_pwd">'>
-- Cookies Valid --
		<iREPLACE VAR="ck_usr" SRC="+" DST=" "><iREPLACE VAR="ck_pwd" SRC="+" DST=" "><iEQ NAME="cfauser" VALUE=":ck_usr"><iEQ NAME="cfapass" VALUE=":ck_pwd">
	</iIF>

	<iSET ChkAct=""><iIF NOTCOND=<iSTRCMP SRC=":auth_active" DST="">><iSET ChkAct=", :auth_active"></iIF>
	<iSET UFQual=""><iIF NOTCOND=<iSTRCMP SRC=":auth_utype" DST="Numeric">><iSET UFQual="'"></iIF>

	<iSET IfSQL=""><iIF COND=<iSTRCMP SRC=":auth_dbmode" DST="SQL">><iSET IfSQL="(NOLOCK)"></iIF>
	<iREPLACE VAR="cfauser" SRC="'" DST="''">
	<iSQL LOGIN=":auth_dsnup" DBNAME=":auth_dsn" SQL="SELECT :auth_pwd :ChkAct FROM :auth_table :IfSQL WHERE :auth_usr=:UFQual:cfauser:UFQual ;" ALIAS="getuser" ESC=FALSE>
	<iSQLFETCH ALIAS="getuser">

SQL = SELECT :auth_pwd :ChkAct FROM :auth_table :IfSQL WHERE :auth_usr = :UFQual:cfauser:UFQual ;

	<iIF COND=:i_sqlempty>
-- No Match --
		<iSET pass=0 status="Failed (Username Mismatch)">
	</iIF>

	<iWHILE NOTALIAS=i_sqlempty>

		<iIF EXPR=':auth_case' ALIAS="CaseSense">
			<iIF COND=<iSTRCMP SRC=":cfapass" DST=':getuser_:auth_pwd'>><iSET pass=1 status="Passed"><iEQ NAME="i_auth_id" VALUE=":getuser_:auth_pwd" EVAL=TRUE><iELSE><iSET status="Failed (Password Mismatch)"></iIF>
		<iELSE ALIAS="CaseSense">
			<iIF COND=<iSTRICMP SRC=":cfapass" DST=':getuser_:auth_pwd'>><iSET pass=1 status="Passed"><iEQ NAME="i_auth_id" VALUE=":getuser_:auth_pwd" EVAL=TRUE><iELSE><iSET status="Failed (Password Mismatch)"></iIF>
		</iIF ALIAS="CaseSense">

		<iIF EXPR=':pass AND NOT <iSTRCMP SRC=":ChkAct" DST=""> AND NOT <iSTRCMP SRC=":auth_activeind" DST=':getuser_:auth_active'>'><iSET pass=0 status="Failed (Inactive)"></iIF>

		<iSQLFETCH ALIAS="getuser">
	</iWHILE ALIAS=i_sqlempty>
	</iSQL ALIAS="getuser">

</iIF ALIAS="CheckPoint">

Status = :status

<iSTRIN SRC=":CFAREQURL" DST="." OUTVAR="DotPos"><iIF EXPR=':DotPos'><iSTRRIGHT SRC=":CFAREQURL" NUM=<iEVAL EXPR='<iSTRLEN SRC=":CFAREQURL">-:DotPos'> OUTVAR="CurExt"><iELSE><iSET CurExt=""></iIF>

<iIF EXPR=':log_on AND (<iSTRCMP SRC=":log_filter" DST=""> OR <iSTRCMP SRC=":CurExt" DST=""> OR <iSTRIN SRC=":log_filter" DST=":CurExt">)' ALIAS="DoLogging">
-- Logging On --

	<iSET LogIt=0><iDATETIME OUTVAR="GetDate">
	<iIF NOTCOND=<iISDEF VAR="ck_lastauth"> ALIAS="FirstAuth">
-- First Auth, Logging Access --
		<iCOOKIE NAME="ck_lastauth" VALUE=":GetDate" PATH="/"><iSET LogIt=1>
	<iELSEIF EXPR='<iDATEDIFF DATE1=":ck_lastauth" DATE2=":GetDate"> NE 0 OR (<iDATEDIFF DATE1=":ck_lastauth" DATE2=":GetDate">=0 AND <iTIMEDIFF TIME1=":ck_lastauth" TIME2=":GetDate" RESULT=MIN> GT :log_session)' ALIAS="FirstAuth">
TimeCheck: <iDATEDIFF DATE1=":ck_lastauth" DATE2=":GetDate"> NE 0 OR (<iDATEDIFF DATE1=":ck_lastauth" DATE2=":GetDate">=0 AND <iTIMEDIFF TIME1=":ck_lastauth" TIME2=":GetDate" RESULT=MIN> GT :log_session)
-- Session Timeout, Logging Access --
		<iCOOKIE NAME="ck_lastauth" VALUE=":GetDate" PATH="/"><iSET LogIt=1>
	</iIF ALIAS="FirstAuth">

	<iDEFAULT NAME="log_success" VALUE="1">
	<iIF EXPR=':LogIt AND (NOT :pass OR (:pass AND :log_success)' ALIAS="Log">
		<iIF NOTCOND=<iSTRCMP SRC=":log_filename" DST=""> ALIAS="Log2File">
-- Logging to :log_filename --
			<iSET LogPass=""><iIF EXPR=':log_goodpwds'><iSET LogPass=":cfapass"></iIF>
			<iFILE NAME=':log_filename' DATA=`<iDATETIME> | :i_ip | :cfauser | :LogPass | :CFAREQURL | :status:i$crlf` OP=APPEND MODE=TEXT>
		</iIF ALIAS="Log2File">
		<iIF NOTCOND=<iSTRCMP SRC=":log_dsn" DST=""> ALIAS="Log2DB">
-- Logging to :log_dsn --
			<iSET LogSQL1="INSERT INTO :log_table (" LogSQL2=") VALUES (">
			<iIF NOTCOND=<iSTRCMP SRC=":log_date" DST="">><iSTRCAT DST="LogSQL1" SRC=" :log_date,"><iSTRCAT DST="LogSQL2" SRC=" ':GetDate',"></iIF>
			<iIF NOTCOND=<iSTRCMP SRC=":log_ip" DST="">><iSTRCAT DST="LogSQL1" SRC=" :log_ip,"><iSTRCAT DST="LogSQL2" SRC=" ':i_ip',"></iIF>
			<iIF NOTCOND=<iSTRCMP SRC=":log_usr" DST="">><iSTRCAT DST="LogSQL1" SRC=" :log_usr,"><iSTRCAT DST="LogSQL2" SRC=" ':cfauser',"></iIF>
			<iIF EXPR='<iSTRCMP SRC=":log_pwd" DST=""> AND :log_goodpwds'><iSTRCAT DST="LogSQL1" SRC=" :log_pwd,"><iSTRCAT DST="LogSQL2" SRC=" ':cfapass',"></iIF>
			<iIF NOTCOND=<iSTRCMP SRC=":log_requrl" DST="">><iSTRCAT DST="LogSQL1" SRC=" :log_requrl,"><iSTRCAT DST="LogSQL2" SRC=" ':CFAREQURL',"></iIF>
			<iIF NOTCOND=<iSTRCMP SRC=":log_status" DST="">><iSTRCAT DST="LogSQL1" SRC=" :log_status,"><iSTRCAT DST="LogSQL2" SRC=" ':status',"></iIF>
			<iSTRLEFT SRC=":LogSQL1" NUM=<iEVAL EXPR='<iSTRLEN SRC=":LogSQL1">-1'> OUTVAR="LogSQL1">
			<iSTRLEFT SRC=":LogSQL2" NUM=<iEVAL EXPR='<iSTRLEN SRC=":LogSQL2">-1'> OUTVAR="LogSQL2">
			<iHTML LOGIN=":log_dsnup" DBNAME=":log_dsn" SQL=":LogSQL1:LogSQL2) ;" ESC=FALSE FAILURE="ERROR: :i_sqlerrortext">
		</iIF ALIAS="Log2DB">
	<iELSE ALIAS="Log">
-- Still in Session, Not Logging Access --
	</iIF ALIAS="Log">

</iIF ALIAS="DoLogging">

<iIF EXPR=':pass' ALIAS="Final">
-- DB Auth Passed --
	<iIF EXPR=':auth_setcookies'><iCOOKIE NAME="ck_zzz" VALUE="foo" PATH="/"><iCOOKIE NAME="ck_usr" VALUE=":cfauser" PATH="/"><iCOOKIE NAME="ck_pwd" VALUE=":cfapass" PATH="/"></iIF>
	alias=:auth_alias
	result=auth_accept
<iELSEIF EXPR=':auth_svr' ALIAS="Final">
-- DB Auth Failed, Attempting Server-Side --
	result=auth_server
<iELSE ALIAS="Final">
	result=auth_reject
</iIF ALIAS="Final">
