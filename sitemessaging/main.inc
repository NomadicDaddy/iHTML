<iREMBLOCK>

Status Codes:

0 & 4: Deleted
1 & 5: New (for popup if online)
2 & 6: New (for storage)
3 & 7: Read
4 - 7: Deleted (from sender's outbox)

inbox : Check for status 1 messages and change to status 2
other : Check for status 1 messages and popup

</iREMBLOCK>

<iDEFAULT NAME="netBase" VALUE="w:">
<iDEFAULT NAME="step" VALUE="1">
<iDEFAULT NAME="box" VALUE="Inbox">
<iDEFAULT NAME="canCompose" VALUE="1">

<iSET system_id=1>
<iSET maxMsgSize=7999>
<iSET fontFace="Arial,Helvetica">

<iIF EXPR='NOT :canCompose AND <iSTRCMP SRC=":step" DST="3">' ALIAS="noCompose">
	<iSET step=1>
</iIF ALIAS="noCompose">

<iREM -- STEP 4: Send Message -- >
<iCASE ALIAS="step" VALUE="4">

	<iDEFAULT NAME="msgid" VALUE="0">
	<iIF COND=":msgid" ALIAS="isReply">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT replied FROM dbo.siteMessaging (NOLOCK) WHERE id=:msgid ;">
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		<iIF NOTCOND=":loadDB_empty" ALIAS="foundOrginator">
			<iIF NOTCOND=":loadDB_replied" ALIAS="notRepliedTo">
				<iSQLMORE ALIAS="loadDB" SQL="UPDATE dbo.siteMessaging SET replied=1 WHERE id=:msgid ;">
			</iIF ALIAS="notRepliedTo">
		</iIF ALIAS="foundOrginator">
	</iIF ALIAS="isReply">

	<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM dbo.:userTable (NOLOCK) WHERE :extUserField=':sentto' ;" ESC=FALSE>
	<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
	<iIF COND=":loadDB_empty" ALIAS="invalidUsername">
		<iSET msg="Invalid username.">
	<iELSE ALIAS="invalidUsername">

		<iSET toSelfString="Talking to yourself again, eh?">
		<iSET toSystemString="Talking to a computer?  Slow day, huh?">

		<iSET fromid=:user_id toid=:loadDB_id parseMessage=0>

		<iIF COND=<iSTRCMP SRC=":toid" DST=":user_id"> ALIAS="easterEgg">
			<iSET parseMessage=1 fromid=:system_id defaultMessage=":toSelfString" status=5>
		</iIF ALIAS="easterEgg">

		<iIF COND=<iSTRCMP SRC=":toid" DST=":system_id"> ALIAS="easterEgg">
			<iSET parseMessage=1 fromid=:system_id toid=:user_id defaultMessage=":toSystemString" status=5>
		</iIF ALIAS="easterEgg">

		<iIF COND=":parseMessage" ALIAS="parseMessage">
			<iSET modified=0>
			<iSTRLWR SRC=":message" OUTVAR="message">
			<iSWITCH ALIAS="message">
				<iREM -- Hard-coded Keyword Check -- >
<iREMBLOCK>
				<iCASE ALIAS="message" VALUE="help">
					<iSET message="Send any of these keywords...<BR>COIN, BIBLE, DICE, JOKE, RIDDLE or QUOTE.<BR><BR>Easter eggs can sometimes be found outside the season ;-)" modified=1>
				</iCASE ALIAS="message">
</iREMBLOCK>
				<iCASE ALIAS="message" VALUE="easter egg">
					<iSET message="That's right.  There are 5 of them - go find them!  The first to find each easter egg gets a big silver cookie!" modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="rabbit">
					<iSET message="That's right!  Rabbits deliver easter eggs and you've just found one.  Send the code 'EASTER EGG: I'M THE RABBIT' to the administrator.  If you're the first to find it, you've won a big silver cookie." modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="i give up">
					<iSET message="Why? You've just found an easter egg. If you keep going, send the code 'EASTER EGG: I GAVE UP, BUT NOW I'M BACK' to the administrator.  If you're the first to find it, you've won a big silver cookie." modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="1984">
					<iSET message="A quite bizarre Sci-Fi book by George Orwell.  You should read it, after you've sent the code 'EASTER EGG: BIG BROTHER SAW ME' to the administrator.  If you're the first to find it, you've won a big silver cookie." modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="orange">
					<iSET message="A strange word, indeed!  You've just found an easter egg.  Send code 'EASTER EGG: NOTHING RHYMES WITH ORANGE' to the administrator.  If you're the first to find it, you've won a big silver cookie." modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="yellow">
					<iSET message="A strange word, indeed!  You've just found an easter egg.  Send code 'EASTER EGG: NOTHING RHYMES WITH ORANGE' to the administrator.  If you're the first to find it, you've won a big silver cookie." modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="fuck">
					<iSET message="Go wash your mouth!" modified=1>
				</iCASE ALIAS="message">
				<iCASE ALIAS="message" VALUE="fuck you">
					<iSET message="Go wash your mouth!" modified=1>
				</iCASE ALIAS="message">
			</iSWITCH ALIAS="message">
			<iIF NOTCOND=":modified" ALIAS="checkKeywords">
<iREMBLOCK>
				<iSQLMORE SQL="SELECT id FROM dbo.autoresponder_types (NOLOCK) WHERE keyword=':message' ;" ALIAS="loadDB" ESC=TRUE>
				<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
				<iIF NOTCOND=":loadDB_empty" ALIAS="keywordExists">
					<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS responses FROM dbo.autoresponder_responses (NOLOCK) WHERE type=:loadDB_id ;">
					<iSQLFETCH ALIAS="loadDB">
					<iRNDNUM LOW="1" HIGH=":loadDB_responses" SEED=<iTICKS> OUTVAR="responseIdx">
					<iSQL :datasource ALIAS="z" SQL="SELECT data FROM dbo.autoresponder_responses (NOLOCK) WHERE type=:loadDB_id ;" INDEXED=TRUE>
						<iSQLFETCH ALIAS="z" INDEX=":responseIdx">
					 	<iSET message=":z_data">
					</iSQL ALIAS="z">
				<iELSE ALIAS="keywordExists">
					<iSET message=":defaultMessage"> 
				</iIF ALIAS="keywordExists">
</iREMBLOCK>
					<iSET message=":defaultMessage"> 
			</iIF ALIAS="checkKeywords">
		</iIF ALIAS="parseMessage">

		<iDEFAULT NAME="status" VALUE="1">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM dbo.siteMessaging (NOLOCK) WHERE from_id=:fromid AND to_id=:toid AND message=':message' AND status=:status ;">
		<iSQLFETCH ALIAS="loadDB">
		<iIF COND=:i_sqlempty ALIAS="isNew">
			<iIF EXPR='<iSTRLEN SRC=":message"> > :maxMsgSize'><iSTRLEFT SRC=":message" NUM=:maxMsgSize OUTVAR="message"></iIF>
			<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO dbo.siteMessaging (to_id, from_id, message, status, replied) VALUES (:toid, :fromid, ':message', :status, 0) ;">
		</iIF ALIAS="isNew">

		<iIF COND=<iSTRCMP SRC=":toid" DST=":user_id"> ALIAS="redir"><iREDIR URL=":i_script_name?box=Inbox"></iIF ALIAS="redir">
		<iSET step=1 message="" msg="Your message has been sent.&nbsp; You can view sent items from your Outbox.">
	</iIF ALIAS="invalidUsername">

</iCASE ALIAS="step">

<iREM -- STEP 3: Compose Message -- >
<iCASE ALIAS="step" VALUE="3">
	<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
	function checkLength(formObj) {
		if(formObj.message.value.length > :maxMsgSize){
			formObj.message.value = formObj.message.value.substr(0, :maxMsgSize);
			alert("Messages cannot be longer than :maxMsgSize characters.");
		}
	}
	function formCheck(form) {
		if (form.sentto.value.length == 0) {
			alert("You must enter a username to send to.")
			form.sentto.focus()
			return false;
		}
		if (form.message.value.length == 0) {
			alert("You must enter a message to send.")
			form.message.focus()
			return false;
		}
	}
	//--></SCRIPT>
	<iDEFAULT NAME="message" VALUE="">
	<FORM METHOD=POST ACTION=':i_script_name' onSubmit="return formCheck(this)">
	<INPUT TYPE=HIDDEN NAME="step" VALUE="4">
	<INPUT TYPE=HIDDEN NAME="box" VALUE=":box">
	<TABLE WIDTH="100%" BORDER=0>
	<TR>
		<TD ALIGN=RIGHT><FONT FACE=":fontFace" SIZE="-1"><B>To:</B></FONT></TD>
		<TD><FONT FACE=":fontFace" SIZE="-1"><INPUT TYPE=TEXT NAME="sentto" SIZE=20 MAXLENGTH=75></FONT></TD>
	</TR>
	<TR><TD COLSPAN=2>&nbsp;</TD></TR>
	<TR>
		<TD ALIGN=RIGHT><FONT FACE=":fontFace" SIZE="-1"><B>Subject:</B></FONT></TD>
		<TD><FONT FACE=":fontFace" SIZE="-1"><INPUT TYPE=TEXT NAME="subject" SIZE=20 MAXLENGTH=75></FONT></TD>
	</TR>
	<TR>
		<TD ALIGN=RIGHT VALIGN=TOP><FONT FACE=":fontFace" SIZE="-1"><B>Message:</B></FONT></TD>
		<TD><FONT FACE=":fontFace" SIZE="-1"><TEXTAREA NAME="message" ROWS=5 COLS=51 WRAP=SOFT onKeyUp="checkLength(this.form)">:message</TEXTAREA></FONT></TD>
	</TR>
	<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Send"></TD></TR>
	</TABLE>
	</FORM>
</iCASE ALIAS="step">

<iREM -- STEP 2: Delete Message -- >
<iCASE ALIAS="step" VALUE="2">
	<iDEFAULT NAME="deleteAll" VALUE="0">
	<iIF COND=:deleteAll ALIAS="deleteAllItems">
		<iSET msgid=":allItemIDs">
	</iIF ALIAS="deleteAllItems">
	<iLISTCREATE NAME="deleteList" TYPE=VARIABLE DELIM="" SEP="," SRC="msgid">
	<iLISTGET NAME="deleteList" OP=COUNT OUTVAR="deleteCount">
	<iLOOP INITIAL=1 FINAL=:deleteCount ALIAS="deleteLoop">
		<iLISTGET OP=GETAT INDEX=":deleteLoop" DELIM="" SEP="," NAME="deleteList" OUTVAR="deleteItem">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT to_id, from_id, status FROM dbo.siteMessaging (NOLOCK) WHERE id=:deleteItem ;">
		<iSQLFETCH ALIAS="loadDB">
		<iIF NOTCOND=":i_sqlempty" ALIAS="foundMessage">
			<iIF EXPR=":loadDB_to_id EQ :user_id" ALIAS="isRecipient">
				<iEVAL EXPR=":loadDB_status & 4" OUTVAR="loadDB_status">
			</iIF ALIAS="isRecipient">
			<iIF EXPR=":loadDB_from_id EQ :user_id" ALIAS="isSender">
				<iEVAL EXPR="(:loadDB_status & 3) + 4" OUTVAR="loadDB_status">
			</iIF ALIAS="isSender">
			<iSQLMORE ALIAS="loadDB" SQL="UPDATE dbo.siteMessaging SET status=:loadDB_status WHERE id=:deleteItem AND (to_id=:user_id OR from_id=:user_id) ;">
		</iIF ALIAS="foundMessage">
	</iLOOP ALIAS="deleteLoop">
	<iSET step=1>
</iCASE ALIAS="step">

<iREM -- Display Status Message -- >
<iIF COND=<iISDEF VAR="msg">><FONT FACE=":fontFace" SIZE="-1" COLOR="#FF0000">:msg</FONT><P></iIF>

<iREM -- STEP 1: In/Out Boxes -- >
<iCASE ALIAS="step" VALUE="1">

	<iDEFAULT NAME="showGroup" VALUE="">
	<iDEFAULT NAME="maxItems" VALUE="5">
	<iDEFAULT NAME="viewFrom" VALUE="1">
	<iEVAL EXPR=':viewFrom + :maxItems - 1' OUTVAR="viewTo">
	<iSET curPointer=:viewFrom curCount=0 showCount=0 curGroup="">

	<iSET prefString="AND NOT EXISTS (SELECT p.user_id FROM prefsList p (NOLOCK) WHERE (p.user_id=:user_id AND p.other_id=u.id AND p.ignored=1))">
	<iIF COND=<iSTRICMP SRC=":box" DST="inbox"> ALIAS="whichBox">
		<iSET joinOn="smsg.from_id=u.id">
		<iSET criteria="u.id!=:user_id AND smsg.to_id=:user_id AND smsg.status!=0 AND smsg.status!=4">
		<iIF COND=:canCompose ALIAS="showComposeLink">
			<iSET noMsgString=`You have no messages waiting for you.&nbsp; Click on <A HREF=":i_script_name?step=3" onMouseOver="status='Compose Message'; return true;" onMouseOut="status='';">Compose</A> to send one.`>
		<iELSE ALIAS="showComposeLink">
			<iSET noMsgString=`You have no messages waiting for you.`>
		</iIF ALIAS="showComposeLink">
		<iSET unreadString="a new message since your last check">
		<iSET senderString="From">
		<iSET isUnread=":loadDB_status = 2">
	<iELSE ALIAS="whichBox">
		<iSET joinOn="smsg.to_id=u.id">
		<iSET criteria="smsg.from_id=:user_id AND (smsg.status < 4)">
		<iIF COND=:canCompose ALIAS="showComposeLink">
			<iSET noMsgString=`You have no messages in your outbox.&nbsp; Click on <A HREF=":i_script_name?step=3" onMouseOver="status='Compose Message'; return true;" onMouseOut="status='';">Compose</A> to send one.`>
		<iELSE ALIAS="showComposeLink">
			<iSET noMsgString=`You have no messages in your outbox.`>
		</iIF ALIAS="showComposeLink">
		<iSET unreadString="the user has not read your message yet">
		<iSET senderString="To">
		<iSET isUnread=":loadDB_status = 2 OR :loadDB_status = 1">
	</iIF ALIAS="whichBox">
	<iIF NOTCOND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="showGroup">
		<iSTRCAT DST="criteria" SRC=" AND group_id=:showGroup">
	</iIF ALIAS="showGroup">

	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(smsg.id) AS total FROM dbo.siteMessaging smsg (NOLOCK) INNER JOIN dbo.:userTable u (NOLOCK) ON :joinOn WHERE :criteria ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET totalRecords=":loadDB_total">

	<iIF NOTCOND=<iISDEF VAR="userDisplay"> ALIAS="useDisplayFields">
		<iSET userDisplay="">
		<iLOOP INITIAL=1 FINAL=:displayFields>
			<iSTRCAT DST="userDisplay" SRC=`CAST(u.<iEQ VALUE=":displayField:i_loop" EVAL=TRUE> AS varchar(255)) + ' ' + `>
		</iLOOP>
		<iSTRLEFT SRC=":userDisplay" NUM=<iEVAL EXPR='<iSTRLEN SRC=":userDisplay"> - 9'> OUTVAR="userDisplay">
	</iIF ALIAS="useDisplayFields">

	<iDEFAULT NAME="userDisplayExtraJoinTable" VALUE="">

	<iSET allItemIDs="">
	<iSQLMORE ALIAS="loadDB" SQL="
		SELECT smsg.id
		FROM dbo.siteMessaging smsg (NOLOCK)
			INNER JOIN dbo.:userTable u (NOLOCK) ON :joinOn
		WHERE :criteria ;
	" ESC=FALSE>
	<iSQLFETCH ALIAS="loadDB">
	<iWHILE NOTALIAS=i_sqlempty>
		<iSTRCAT DST="allItemIDs" SRC=":loadDB_id,">
		<iSQLFETCH ALIAS="loadDB">
	</iWHILE ALIAS=i_sqlempty>
	<iSTRLEFT SRC=":allItemIDs" NUM=<iEVAL EXPR='<iSTRLEN SRC=":allItemIDs"> - 1'> OUTVAR="allItemIDs">

	<iDEFAULT NAME="smsgSort" VALUE="smsg.dateCreated DESC, smsg.status">

	<iSQLMORE ALIAS="loadDB" SQL="
		SELECT smsg.id, u.:extUserField, :userDisplay AS display, smsg.from_id, smsg.dateCreated, smsg.group_id, smsg.status, smsg.subject, smsg.message, smsg.attachment
		FROM dbo.siteMessaging smsg (NOLOCK)
			INNER JOIN dbo.:userTable u (NOLOCK) ON :joinOn
			:userDisplayExtraJoinTable
		WHERE :criteria
		ORDER BY :smsgSort ;
	" ESC=FALSE INDEXED=TRUE>
	<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty" INDEX=":viewFrom">

	<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/boxChecker.js"></SCRIPT>
	<FORM METHOD=POST ACTION=':i_script_name'>
	<INPUT TYPE=HIDDEN NAME="step" VALUE="2">
	<INPUT TYPE=HIDDEN NAME="box" VALUE=":box">
	<INPUT TYPE=HIDDEN NAME="deleteAll" VALUE="0">
	<INPUT TYPE=HIDDEN NAME="allItemIDs" VALUE=":allItemIDs">
	<TABLE WIDTH="100%" BORDER=1>
	<iIF ALIAS="nomsg" COND=":loadDB_empty">
		<TR><TD>&nbsp;</TD><TD COLSPAN=4><FONT FACE=":fontFace" SIZE="-1">:noMsgString</FONT></TD></TR>
	<iELSE ALIAS="nomsg">

		<iIF COND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="notGroup">
			<iSET colSpan=4>
		<iELSE ALIAS="notGroup">
			<TR><TD COLSPAN=4><FONT FACE=":fontFace" SIZE="-1">
				<TABLE BORDER=1 WIDTH="100%" CELLSPACING=0 CELLPADDING=5 BGCOLOR="#FFFFCC"><TR BGCOLOR="#FFFFCC"><TD><FONT FACE=":fontFace" SIZE="-1">
				<iIF NOTCOND=<iSTRCMP SRC=":loadDB_subject" DST="">><U><B><I>:loadDB_subject</I></B></U><BR></iIF>:loadDB_message
				<iIF NOTCOND=<iSTRCMP SRC=":loadDB_attachment" DST="">>
					<iURLENCODE SRC=":loadDB_attachment" OUTVAR="safeAttachment">
					<BR><BR>Attachment: <A HREF="smsgfiles/:safeAttachment">:loadDB_attachment</A>
				</iIF>
				</FONT></TD></TR></TABLE>
			</FONT></TD>
			<iSET colSpan=3>
		</iIF ALIAS="notGroup">

		<TR>
			<TD COLSPAN=:colSpan><FONT FACE=":fontFace" SIZE="-1"><FONT FACE=":fontFace" COLOR="#FF0000">*</FONT> indicates :unreadString.</FONT></TD>
			<TD ALIGN=CENTER>
				<INPUT TYPE=BUTTON VALUE="Select All" onClick="this.value=boxChecker(this.form.msgid)">
				<INPUT TYPE=BUTTON VALUE="Delete All" onClick="if (confirm('Are you sure?')) {this.form.deleteAll.value=1; this.form.submit()} else {javascript:null}">
			</TD>
		</TR>
		<TR>
			<TD>&nbsp;</TD>
			<iIF COND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="notGroup">
				<TD><FONT FACE=":fontFace" SIZE="+1">Date</FONT></TD>
			<iELSE ALIAS="notGroup">
				<TD WIDTH="1%"><FONT FACE=":fontFace" SIZE="+1">Date</FONT></TD>
			</iIF ALIAS="notGroup">
			<TD><FONT FACE=":fontFace" SIZE="+1">:senderString</FONT></TD>
			<iIF COND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="notGroup">
				<TD><FONT FACE=":fontFace" SIZE="+1">Message</FONT></TD>
			</iIF ALIAS="notGroup">
			<TD ALIGN=CENTER><INPUT TYPE=BUTTON VALUE="Delete Checked" onClick="if (confirm('Are you sure?')) {this.form.submit()} else {javascript:null}"></TD>
		</TR>
		<iWHILE NOTALIAS="loadDB_empty">
			<iEVAL EXPR=':curCount + 1' PREC=0 OUTVAR="curCount">
			<iIF EXPR='(<iSTRCMP SRC=":loadDB_group_id" DST="0"> OR NOT <iSTRCMP SRC=":curGroup" DST=":loadDB_group_id">) OR NOT <iSTRCMP SRC=":showGroup" DST="">' ALIAS="groupMarker">
				<TR>
					<TD WIDTH=10 VALIGN=TOP><FONT FACE=":fontFace" SIZE="-1">
						<iIF EXPR=':isUnread AND NOT <iSTRCMP SRC=":loadDB_group_id" DST="0">' ALIAS="unread">
							<FONT FACE=":fontFace" COLOR="#FF0000">*</FONT>
						<iELSE ALIAS="unread">
							&nbsp;
						</iIF ALIAS="unread">
					</FONT></TD>

<iIF COND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="notGroup">
	<iSET colWidth="WIDTH=85">
<iELSE ALIAS="notGroup">
	<iSET colWidth="NOWRAP">
</iIF ALIAS="notGroup">

					<TD :colWidth VALIGN=TOP><FONT FACE=":fontFace" SIZE="-1"><iDATETIME DATE='<iSTRSPAN SRC=":loadDB_dateCreated" FIRST=6 NUM=2>-<iSTRSPAN SRC=":loadDB_dateCreated" FIRST=9 NUM=2>-<iSTRSPAN SRC=":loadDB_dateCreated" FIRST=1 NUM=4>' TIME='<iSTRSPAN SRC=":loadDB_dateCreated" FIRST=12 NUM=8>' FMT="%b %d, %Y"></FONT></TD>
					<iIF COND=<iSTRCMP SRC=":showGroup" DST=""> ALIAS="notGroup">
						<TD WIDTH=100 VALIGN=TOP><FONT FACE=":fontFace" SIZE="-1">
							<iIF NOTCOND=<iSTRCMP SRC=":loadDB_group_id" DST="0"> ALIAS="isGroup">
								<A HREF=":i_script_name?step=2&box=:box&showGroup=:loadDB_group_id" onMouseOver="status='Show Group Status'; return true;" onMouseOut="status='';">Group</A>
							<iELSE ALIAS="isGroup">
								<A HREF="javascript:siteMessaging('Send%20Message', :user_id, :loadDB_from_id, :loadDB_id);" onMouseOver="status='Reply'; return true;" onMouseOut="status='';"><iEQ VALUE=":loadDB_display" EVAL=TRUE></A>
							</iIF ALIAS="isGroup">
						</FONT></TD>
						<TD>
							<TABLE BORDER=1 WIDTH="100%" CELLSPACING=0 CELLPADDING=5 BGCOLOR="#FFFFCC"><TR BGCOLOR="#FFFFCC"><TD><FONT FACE=":fontFace" SIZE="-1">
							<iIF NOTCOND=<iSTRCMP SRC=":loadDB_subject" DST="">><U><B><I>:loadDB_subject</I></B></U><BR></iIF>:loadDB_message
							<iIF NOTCOND=<iSTRCMP SRC=":loadDB_attachment" DST="">>
								<iURLENCODE SRC=":loadDB_attachment" OUTVAR="safeAttachment">
								<BR><BR>Attachment: <A HREF="smsgfiles/:safeAttachment">:loadDB_attachment</A>
							</iIF>
							</FONT></TD></TR></TABLE>
						</TD>
					<iELSE ALIAS="notGroup">
						<TD NOWRAP VALIGN=TOP><FONT FACE=":fontFace" SIZE="-1"><A HREF="javascript:siteMessaging('Send%20Message', :user_id, :loadDB_from_id, :loadDB_id);" onMouseOver="status='Reply'; return true;" onMouseOut="status='';"><iEQ VALUE=":loadDB_display" EVAL=TRUE></A></FONT></TD>
					</iIF ALIAS="notGroup">
					<TD WIDTH=55 VALIGN=TOP ALIGN=CENTER><INPUT TYPE=CHECKBOX NAME="msgid" VALUE=":loadDB_id"></TD>
				</TR>
			<iELSE ALIAS="groupMarker">
				<iEVAL EXPR=':totalRecords - 1' PREC=0 OUTVAR="totalRecords">
			</iIF ALIAS="groupMarker">
			<iSET curGroup=:loadDB_group_id>
			<iIF EXPR='NOT :curCount GT :maxItems - 1 AND :curCount LTE :totalRecords'>
				<iEVAL EXPR=':viewFrom + :curCount' OUTVAR="viewNow">
				<iEVAL EXPR=':curPointer + 1' OUTVAR="curPointer">
				<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty" INDEX=":viewNow">
			<iELSE>
				<iSET loadDB_empty=TRUE>
			</iIF>
		</iWHILE ALIAS="loadDB_empty">
		<TR><TD COLSPAN=5 ALIGN=RIGHT><BR><FONT FACE=":fontFace" SIZE="-1">You have <B>:totalRecords</B> messages in your <B>:box</B>.&nbsp; You are viewing message<iIF EXPR=':totalRecords > 1'>s <B>:viewFrom</B> to <B>:viewTo</B><iELSE> 1</iIF>.</FONT></TD></TR>
	</iIF ALIAS="nomsg">
	</TABLE>
	</FORM>
	<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=3><TR><TD ALIGN=CENTER>
	<iINCLUDE NAME=":netBase\shared\dba_prevnext.inc">
	</TD></TR></TABLE>

</iCASE ALIAS="step">
