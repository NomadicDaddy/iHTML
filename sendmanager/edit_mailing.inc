<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="doUpdate"> ALIAS="doUpdate">

	<iSQLMORE ALIAS="loadDB" SQL="SELECT allowSelfSub, allowSelfUnsub, showUnsubLink, contentType FROM dbo.jobs (NOLOCK) WHERE id = :job ;">
	<iSQLFETCH ALIAS="loadDB">

	<iREM -- Use Specified To Address, if Given -- >
	<iIF NOTCOND=<iSTRCMP SRC=":sentTo" DST="">>
		<iSET sendTo = ":sentTo">
	<iELSE>
		<iSET sendTo = "<:SendToToken:>">
	</iIF>

	<iREM -- Use Specified Return-Path, if Given -- >
	<iIF NOTCOND=<iSTRCMP SRC=":returnPath" DST="">><iSET bounceTo = ":returnPath" errorsTo = `ERRORSTO=":returnPath"`></iIF>

	<iREM -- Add HTML-Encoded Mail, if Specified -- >
	<iIF NOTCOND=<iSTRCMP SRC=":loadDB_contentType" DST="text/plain">><iSET useHTML = "HTML=`:htmlbody<:UnSubToken:>`"></iIF>

	<iREM -- Allow Self-Subscription/Unsubscription? -- >
	<iSET subURL = "" unsubURL = "">
	<iIF EXPR=':loadDB_allowSelfSub'><iSET subURL = "LISTSUBURL=`http://adminware.com/sendmanager/subscribe.ihtml?jid=:job`"></iIF>
	<iIF EXPR=':loadDB_allowSelfUnsub'><iSET unsubURL = "LISTUNSUBURL=`http://adminware.com/sendmanager/unsubscribe.ihtml?jid=:job&rid=<:RecordToken:>&guid=<:GUIDToken:>`"></iIF>

	<iINCLUDE NAME="w:\ifuncs\iMSMail.ifunc">
	<iFUNCCALL ALIAS="iMSMail" 
		SENDTO=":sendTo" 
		SENDFROM=":sentFromName <:sentFromAddress>" 
		:errorsTo
		REPLYTO=":replyTo" 
		ORGANIZATION=":organization" 
		SUBJECT=":subject" 
		:subURL
		:unsubURL
		BODY=`:body<:UnSubToken:>` 
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

	<iREPLACE VAR="title" SRC="'" DST="''">
	<iREPLACE VAR="description" SRC="'" DST="''">
	<iREPLACE VAR="reference" SRC="'" DST="''">
	<iSTRLEFT SRC=":reference" NUM=254 OUTVAR="reference">
	<iREPLACE VAR="sentFromName" SRC="'" DST="''">
	<iREPLACE VAR="sentFromAddress" SRC="'" DST="''">
	<iREPLACE VAR="sentTo" SRC="'" DST="''">
	<iREPLACE VAR="replyTo" SRC="'" DST="''">
	<iREPLACE VAR="returnPath" SRC="'" DST="''">
	<iREPLACE VAR="organization" SRC="'" DST="''">
	<iREPLACE VAR="subject" SRC="'" DST="''">
	<iREPLACE VAR="body" SRC="'" DST="''">
	<iREPLACE VAR="htmlbody" SRC="'" DST="''">
	<iSET z="Mailing updated.">
	<iHTML DBNAME=":appConn" SQL=`
		UPDATE dbo.jobs
		SET title = ':title', description = ':description', reference = ':reference', sentTo = ':sentTo', sentFromName = ':sentFromName', sentFromAddress = ':sentFromAddress', replyTo = ':replyTo', returnPath = ':returnPath', organization = ':organization', subject = ':subject', body = ':body', htmlbody = ':htmlbody', mailSize = :mailSize
		WHERE id = :job ;
	` NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="statusMsg">
	<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="Update failed.">
	<iIF COND=<iSTRCMP SRC=":statusMsg" DST="Success"> ALIAS="setMsg"><iSET statusMsg = ":z"></iIF ALIAS="setMsg">
</iIF ALIAS="doUpdate">

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT title, description, reference, sentTo, sentFromName, sentFromAddress, replyTo, returnPath, organization, subject, body, htmlbody, contentType
	FROM dbo.jobs (NOLOCK)
	WHERE id = :job ;
">
<iSQLFETCH ALIAS="loadDB">

<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
function warnSentTo() {
	if (document.edit_mailing_form.sentTo.value.length == 0) {
		alert("NOTE:\n\nDo NOT change this unless you want every email that goes out to appear addressed to the same recipient (e.g. clients@whatever.com) instead of to the receipient.  \n\nOnce this field is NOT blank, all outgoing emails will appear to be addressed to the email address in this field.");
	}
}
function warnErrorsTo() {
	if (document.edit_mailing_form.returnPath.value.length == 0) {
		alert("WARNING:\n\nDo NOT change this unless you\'re sure you do not want the automated bounce-handling system to take care of bounced emails.\n\nOnce this field is NOT blank, the email address in this field will receive all bounced emails.");
	}
}
function checkForm(form) {
	if (form.title.value.length == 0) {
		alert("Please enter a title for this job.")
		form.title.focus()
		return false;
	}
	if (form.description.value.length == 0) {
		alert("Please enter a description for this job.")
		form.description.focus()
		return false;
	}
	if (form.sentFromAddress.value.length == 0) {
		alert("Please enter the address this email will be sent from.")
		form.sentFromAddress.focus()
		return false;
	}
	if (form.description.value.length == 0) {
		alert("Please enter a description for this job.")
		form.description.focus()
		return false;
	}
	if (form.reference.value.length == 0) {
		form.reference.value=form.organization.value+" -- "+form.title.value;
	}
	if (form.subject.value.length == 0) {
		alert("Please enter a subject for this email.")
		form.subject.focus()
		return false;
	}
	if (form.body.value.length == 0) {
		alert("Please enter a body for this email.")
		form.body.focus()
		return false;
	}
	<iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/html">>
	if (form.htmlbody.value.length == 0) {
		alert("Please enter an HTML body for this email.")
		form.htmlbody.focus()
		return false;
	}
	</iIF>
}
//--></SCRIPT>

<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="/js/dba_quickCheck.js"></SCRIPT>
<FORM METHOD=POST ACTION=':thisPage' NAME="edit_mailing_form" onSubmit="return checkForm(this)">
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Title')" onMouseOut="noHelp()">Job Title</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="title" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_title"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Description')" onMouseOut="noHelp()">Job Description</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><TEXTAREA NAME="description" COLS=60 ROWS=5 WRAP=SOFT>:loadDB_description</TEXTAREA></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Reference')" onMouseOut="noHelp()">Job Reference</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="reference" SIZE=50 MAXLENGTH=255 VALUE=":loadDB_reference"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Send To Address')" onMouseOut="noHelp()">Send To (Address)</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sentTo" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_sentTo" onFocus="warnSentTo()"  onChange="if (this.value != '') { qcEmail(this) }"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Send From Name')" onMouseOut="noHelp()">Send From (Name)</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sentFromName" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_sentFromName"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Send From Address')" onMouseOut="noHelp()">Send From (Address)</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sentFromAddress" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_sentFromAddress" onBlur="qcEmail(this)"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reply To')" onMouseOut="noHelp()">Reply To</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="replyTo" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_replyTo" onChange="if (this.value != '') { qcEmail(this) }"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Errors To')" onMouseOut="noHelp()">Errors To</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="returnPath" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_returnPath" onFocus="warnErrorsTo()" onChange="if (this.value != '') { qcEmail(this) }"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Organization')" onMouseOut="noHelp()">Organization</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="organization" SIZE=50 MAXLENGTH=50 VALUE=":loadDB_organization"></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Email Subject')" onMouseOut="noHelp()">Email Subject</A> &nbsp;</TD>
	<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="subject" SIZE=50 MAXLENGTH=75 VALUE=":loadDB_subject"></TD>
</TR>
<TR>
	<TD WIDTH="1%" VALIGN=TOP <iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/html">>ROWSPAN=2</iIF>>
		<A CLASS="tableHeading" HREF="javascript:void(0);" onMouseOver="return popUpHelp('Email Body')" onMouseOut="noHelp()">Email Body</A><BR><BR>
		<iSQL DBNAME=":appConn" SQL="SELECT fName FROM _fields (NOLOCK) WHERE parent='_job_:job' AND fName != 'id' AND fName != 'email' AND fName != 'guid' AND fName != 'tester' AND fName != 'addressee' AND fName != 'verified' AND fName != 'sent' AND fName != 'unsubscribed' AND fName != 'bounced' AND fName != 'company' AND fName != 'viewed' ;" ALIAS="cfs">
		<iSQLFETCH ALIAS="cfs">
		<iIF NOTCOND=:i_sqlempty>
			The following custom field(s) are defined:<BR><BR>
			<iWHILE NOTALIAS=i_sqlempty>
				&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<::cfs_fName:>'">&lt;::cfs_fName:&gt;</A><BR>
				<iSQLFETCH ALIAS="cfs">
			</iWHILE ALIAS=i_sqlempty>
		</iIF>
		<BR>
		<iSQL DBNAME=":appConn" SQL="SELECT linkToken FROM linkTracking (NOLOCK) WHERE job_id=:job ;" ALIAS="ltt">
		<iSQLFETCH ALIAS="ltt">
		<iIF NOTCOND=:i_sqlempty>
			The following link tracking token(s) are defined:<BR><BR>
			<iWHILE NOTALIAS=i_sqlempty>
				&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:Link:ltt_linkToken:>'">&lt;:Link:ltt_linkToken:&gt;</A><BR>
				<iSQLFETCH ALIAS="ltt">
			</iWHILE ALIAS=i_sqlempty>
		</iIF>
		<BR>
		</iSQL ALIAS="ltt">
		The following system-generated fields are available:<BR><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:EmailToken:>'" onMouseOver="return popUpHelp('EmailToken')" onMouseOut="noHelp()">&lt;:EmailToken:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:AddresseeToken:>'" onMouseOver="return popUpHelp('AddresseeToken')" onMouseOut="noHelp()">&lt;:AddresseeToken:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:SendToToken:>'" onMouseOver="return popUpHelp('SendToToken')" onMouseOut="noHelp()">&lt;:SendToToken:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:CompanyToken:>'" onMouseOver="return popUpHelp('CompanyToken')" onMouseOut="noHelp()">&lt;:CompanyToken:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:UnSubLinkToken:>'" onMouseOver="return popUpHelp('UnSubLinkToken')" onMouseOut="noHelp()">&lt;:UnSubLinkToken:&gt;</A><BR>
		&nbsp; <A HREF="javascript:void(0);" onClick="edit_mailing_form.body.value = edit_mailing_form.body.value + '<:ViewTracker:>'" onMouseOver="return popUpHelp('ViewTracker')" onMouseOut="noHelp()">&lt;:ViewTracker:&gt;</A><BR>
		<BR>To use these in your email body, simply add &lt;: before and :&gt; after the field name (or click on one of them to paste it into your email).
		
	 &nbsp;</TD>
	<TD VALIGN=TOP><iSET columns=20><iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/html">> &nbsp; <B>Text Version</B><BR><iSET columns=10></iIF> &nbsp; <TEXTAREA NAME="body" COLS=60 ROWS=:columns WRAP=HARD>:loadDB_body</TEXTAREA></TD>
</TR>
<iIF COND=<iSTRCMP SRC=":loadDB_contentType" DST="text/html">>
	<TR><TD VALIGN=TOP STYLE="padding-left : 9px;"><B>HTML Version</B><BR> &nbsp; <TEXTAREA NAME="htmlbody" COLS=60 ROWS=10 WRAP=SOFT>:loadDB_htmlbody</TEXTAREA></TD></TR>
</iIF>
<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doUpdate" VALUE="Update"></TD></TR>

</TABLE>
</FORM>

</CENTER></TD></TR></TABLE>
