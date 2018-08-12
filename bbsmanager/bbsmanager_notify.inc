<iREM -- If Reply, get Topic -- >
<iIF NOTCOND=<iISDEF VAR="Topic"> ALIAS="ThreadName">
	<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Name FROM :Threads :IfSQL WHERE TID = :Thread ;" OUTPUT=":1" OUTVAR="Topic">
</iIF ALIAS="ThreadName">

<iREM -- Un-Escape Quotes in Body -- >
<iREPLACE VAR="Body" SRC="''" DST="'">

<iREM -- Un-Convert Smileys -- >
<iDEFAULT NAME="LoadDB_ConvertSmileys" VALUE="1">
<iIF EXPR=':LoadDB_ConvertSmileys' ALIAS="Convert"><iSET SmileyConv=0><iINCLUDE NAME=":FBase\bbsmanager_smileys.inc"></iIF ALIAS="Convert">

<iREM -- Get UserName -- >
<iIF COND=<iISDEF VAR="NonAuthFrom"> ALIAS="IsNonAuth">
	<iSET WhoFrom=":NonAuthFrom" AuthedBy="Unauthenticated">
<iELSE ALIAS="IsNonAuth">
	<iSET WhoFrom=":bbs_un (User ID :PostedBy)">
</iIF ALIAS="IsNonAuth">

<iINCLUDE NAME="w:\ifuncs\iMSMail.ifunc">
<iFUNCCALL ALIAS="iMSMail" 
SENDTO="BBS Manager <:LoadDB_MgrToAddress>" 
SENDFROM=":LoadDB_MgrFromAddress" 
SUBJECT="BBS Post Notification" 
BODY=`A post has been made to the :DisplayName Bulletin Board.

Status:        :msg
Authed By:     :AuthedBy
Posted By:     :WhoFrom
Thread:        :Topic (Thread # :Thread)

Body:

:Body
` 
HOSTNAME="bbsmanager.com" 
SPOOLDIR=":loadDB_imsSpoolDir"
>
