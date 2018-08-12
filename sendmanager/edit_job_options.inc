<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="doUpdate"> ALIAS="doUpdate">

	<iSQLMORE ALIAS="loadDB" SQL="SELECT sentTo, sentFromName, sentFromAddress, replyTo, returnPath, organization, subject, body, htmlbody FROM jobs (NOLOCK) WHERE id=:job ;">
	<iSQLFETCH ALIAS="loadDB">

	<iREM -- Use Specified To Address, if Given -- >
	<iIF NOTCOND=<iSTRCMP SRC=":loadDB_sentTo" DST="">>
		<iSET sendTo=":loadDB_sentTo">
	<iELSE>
		<iSET sendTo="<:SendToToken:>">
	</iIF>

	<iREM -- Use Specified Return-Path, if Given -- >
	<iIF NOTCOND=<iSTRCMP SRC=":loadDB_returnPath" DST="">><iSET bounceTo=":loadDB_returnPath" errorsTo=`ERRORSTO=":loadDB_returnPath"`></iIF>

	<iREM -- Add HTML-Encoded Mail, if Specified -- >
	<iIF NOTCOND=<iSTRCMP SRC=":contentType" DST="text/plain">><iSET useHTML="HTML=`:loadDB_htmlbody<:UnSubToken:>`"></iIF>

	<iREM -- Allow Self-Subscription/Unsubscription? -- >
	<iSET subURL="" unsubURL="">
	<iIF EXPR=':allowSelfSub'><iSET subURL="LISTSUBURL=`http://adminware.com/sendmanager/subscribe.ihtml?jid=:job`"></iIF>
	<iIF EXPR=':allowSelfUnsub'><iSET unsubURL="LISTUNSUBURL=`http://adminware.com/sendmanager/unsubscribe.ihtml?jid=:job&rid=<:RecordToken:>&guid=<:GUIDToken:>`"></iIF>

	<iINCLUDE NAME="w:\ifuncs\iMSMail.ifunc">
	<iFUNCCALL ALIAS="iMSMail" 
	SENDTO=":sendTo" 
	SENDFROM=":loadDB_sentFromName <:loadDB_sentFromAddress>" 
	:errorsTo
	REPLYTO=":loadDB_replyTo" 
	ORGANIZATION=":loadDB_organization" 
	SUBJECT=":loadDB_subject" 
	:subURL
	:unsubURL
	BODY=`:loadDB_body<:UnSubToken:>` 
	:useHTML 
	HOSTNAME="sendmanager.com" 
	MAILER="adminware :appVersion <http://www.sendmanager.com/>" 
	CREATEMAILFILEONLY="YES" 
	GETMAILFILENAME="YES" 
	SPOOLDIR="z:\" 
	OUTVAR="MFN"
	>
	<iSTRCAT DST="MFN" SRC=".mbx">
	<iSTRLEN SRC=`<iFILE NAME="z:\:MFN" OP=READ>` OUTVAR="mailSize">
	<iEVAL EXPR=':mailSize + 200' OUTVAR="mailSize">
	<iFILE NAME="z:\:MFN" OP=DELETE>

	<iREPLACE VAR="contentType" SRC="'" DST="''">
	<iSET z="Job Options updated.">
	<iHTML DBNAME=":appConn" SQL=`UPDATE jobs SET allowSelfSub=:allowSelfSub, allowSelfUnsub=:allowSelfUnsub, showUnsubLink=:showUnsubLink, contentType=':contentType', mailSize=:mailSize WHERE id=:job ;` NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="statusMsg">
	<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="Update failed. ">
	<iIF COND=<iSTRCMP SRC=":statusMsg" DST="Success"> ALIAS="setMsg"><iSET statusMsg=":z"></iIF ALIAS="setMsg">
</iIF ALIAS="doUpdate">

<iSQLMORE ALIAS="loadDB" SQL="SELECT allowSelfSub, allowSelfUnsub, showUnsubLink, contentType FROM jobs (NOLOCK) WHERE id=:job ;">
<iSQLFETCH ALIAS="loadDB">

<FORM METHOD=POST ACTION=':thisPage'>
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR>
	<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Self-Subscribes')" onMouseOut="noHelp()">Allow Self-Subscribes?</A> &nbsp;</TD>
	<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="allowSelfSub" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_allowSelfSub" DST="1">>CHECKED</iIF>> Yes &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="allowSelfSub" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_allowSelfSub" DST="0">>CHECKED</iIF>> No</TD>
</TR>
<TR>
	<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Self-Unsubscribes')" onMouseOut="noHelp()">Allow Self-Unsubscribes?</A> &nbsp;</TD>
	<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="allowSelfUnsub" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_allowSelfUnsub" DST="1">>CHECKED</iIF>> Yes &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="allowSelfUnsub" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_allowSelfUnsub" DST="0">>CHECKED</iIF>> No</TD>
</TR>
<TR>
	<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('System-Generated Unsubscribe Link')" onMouseOut="noHelp()">Show System-Generated Unsubscribe Link?</A> &nbsp;</TD>
	<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="showUnsubLink" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_showUnsubLink" DST="1">>CHECKED</iIF>> Yes &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="showUnsubLink" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_showUnsubLink" DST="0">>CHECKED</iIF>> No</TD>
</TR>
<TR>
	<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Email Content Type')" onMouseOut="noHelp()">Email Content Type</A> &nbsp;</TD>
	<TD NOWRAP>
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="contentType" VALUE="text/plain" <iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/plain">>CHECKED</iIF>> Plain Text &nbsp;
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="contentType" VALUE="text/html" <iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/html">>CHECKED</iIF>> HTML
	</TD>
</TR>
<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doUpdate" VALUE="Update"></TD></TR>
</TABLE>
</FORM>
