<!iHTML CACHE=FALSE><iINCLUDE NAME="incs\header.inc">

<iDEFAULT name="message" VALUE="quote">
<iREM iEQ NAME="usermessage" VALUE=":message" COOKIE="TRUE">
<iSET parseMessage="1" defaultMessage="You should not see this unless you typed anything but a keyword.">

<iIF COND=<iISDEF VAR="mode"> ALIAS="editDb">
	<iSWITCH ALIAS="mode">
		<iCASE ALIAS="mode" VALUE="changek">
			<iEQ NAME="cat_id" VALUE=":new_cat_id" COOKIE="TRUE">
		</iCASE ALIAS="mode">
		<iCASE ALIAS="mode" VALUE="addk">
			<iHTML :datasource SQL="INSERT INTO autoresponder_types (keyword) VALUES (':keyword');" ESC="TRUE">
		</iCASE ALIAS="mode">
		<iCASE ALIAS="mode" VALUE="editk">
			<iHTML :datasource SQL="UPDATE autoresponder_types SET keyword=':keyword' WHERE id=:id ;" ESC="TRUE">
		</iCASE ALIAS="mode">
		<iCASE ALIAS="mode" VALUE="add">
			<iHTML :datasource SQL="INSERT INTO autoresponder_responses (type, data) VALUES (:type, ':data');" ESC="TRUE">
		</iCASE ALIAS="mode">
		<iCASE ALIAS="mode" VALUE="edit">
			<iHTML :datasource SQL="UPDATE autoresponder_responses SET data=':data' WHERE id=:id ;" ESC="TRUE">
		</iCASE ALIAS="mode">
	</iSWITCH ALIAS="mode">
</iIF ALIAS="editDb">



<iREMBLOCK>
	<iDEFAULT NAME="lgid" VALUE="0">
	<iIF COND=":lgId" ALIAS="isReply">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT repliedTo FROM luvGrams (NOLOCK) WHERE id=:lgid">
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		<iIF NOTCOND=":loadDB_empty" ALIAS="foundOrginator">
			<iIF NOTCOND=":loadDB_repliedTo" ALIAS="notRepliedTo">
				<iSQLMORE SQL="UPDATE dbo.siteMessagings SET repliedTo="1" WHERE id=:lgid">
				<iSET freeReply="1">
			</iIF ALIAS="notRepliedTo">
		</iIF ALIAS="foundOrginator">
	</iIF ALIAS="isReply">
	<iDEFAULT NAME="freeReply" VALUE="0">

	<iSQLMORE ALIAS="loadDB" SQL="SELECT luvGramSent FROM users (NOLOCK) WHERE id=:uid">
	<iSQLFETCH ALIAS="loadDB">

	<iIF EXPR=":access = 1 AND :freeReply=0" ALIAS="checkMaxLuvGrams">
		<iIF EXPR=":loadDB_luvGramSent GE 5" ALIAS="maxReached">
			<iSET maxReached="1">
		</iIF ALIAS="maxReached">
	</iIF ALIAS="checkMaxLuvGrams">
			 
	<iDEFAULT NAME="maxReached" VALUE="0">
			
	<iIF NOTCOND=":maxReached" ALIAS="allowLuvGram">
		<iEVAL EXPR=":loadDB_luvGramSent + 1 - :freeReply" OUTVAR="loadDB_luvGramSent">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM users (NOLOCK) WHERE username=':sentto'">
		<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		<iIF COND=":loadDB_empty" ALIAS="invalidUsername">
			<iSET msg="Invalid username.">
			<iSET step=1>
		<iELSE ALIAS="invalidUsername">
			<iSET fromid=':uid' parseMessage="0">
			<iIF EXPR=":loadDB_id EQ :uid" ALIAS="EasterEgg">
				<iSET parseMessage=1 fromid=:system_id defaultMessage="You ain't gonna get a date by talking to yourself, you know!" status=5>
			</iIF ALIAS="EasterEgg">
			<iIF EXPR=":loadDB_id EQ :system_id" ALIAS="EasterEgg">
				<iSET parseMessage=1 fromid=:system_id loadDB_id=:uid defaultMessage="You ain't gonna get any date by chatting with a computer, you know!" status=5>
			</iIF ALIAS="EasterEgg">
</iREMBLOCK>

			<iIF COND=":parseMessage" ALIAS="parseMessage">
				<iSET modified=0>
				<iSTRLWR SRC=":message" OUTVAR="message">
				<iSWITCH ALIAS="message">
					<iREM This is where we can check for hardcoded keywords>
					<iCASE ALIAS="message" VALUE="help">
						<iSET message="Send any of these keywords...<BR>QUOTE - Famous (?) quotes<BR>JOKE - Get a laugh<BR><BR>Easter eggs can sometimes be found outside the season ;-)" modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="easter egg">
						<iSET message="That's rigth. There are 5 of them - go find them! The first to find each easter egg gets a 3 months FREE advanced membership!" modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="rabbit">
						<iSET message="That's right! Rabbits deliver easter eggs, and you've just found one. Send the code 'EASTER EGG: I'M THE RABBIT' to Admin. If you're the first to find it, you've won a free 3 month advanced membership." modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="i give up">
						<iSET message="Why? You've just found an easter egg. If you keep going, send the code 'EASTER EGG: I GAVE UP, BUT NOW I'M BACK' to Admin. If you're the first to find it, you've won a free 3 month advanced membership." modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="1984">
						<iSET message="A quite bissarre Sci-fi book by George Orwell. You should read it, after you've sent the code 'EASTER EGG: BIG BROTHER SAW ME' to Admin. If you're the first to find it, you've won a free 3 month advanced membership." modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="orange">
						<iSET message="A strange word, indeed! You've just found an easter egg. Send code 'EASTER EGG: NOTHING RHYMES WITH ORANGE' to Admin. If you're the first to find it, you've won a free 3 month advanced membership." modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="yellow">
						<iSET message="A strange word, indeed! You've just found an easter egg. Send code 'EASTER EGG: NOTHING RHYMES WITH ORANGE' to Admin. If you're the first to find it, you've won a free 3 month advanced membership." modified=1>
					</iCASE ALIAS="message">
					
					<iCASE ALIAS="message" VALUE="fuck">
						<iSET message="Go wash your mouth!!" modified=1>
					</iCASE ALIAS="message">
					<iCASE ALIAS="message" VALUE="fuck you">
						<iSET message="Go wash your mouth!!" modified=1>
					</iCASE ALIAS="message">
					<iREM Etc, and so on... blah blah!>
				</iSWITCH ALIAS="message">
				<iIF NOTCOND=":modified" ALIAS="checkKeywords">
					<iSQLMORE SQL="SELECT id FROM autoresponder_types (NOLOCK) WHERE keyword=':message' ;" ALIAS="loadDB" ESC="TRUE">
					<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
					<iIF NOTCOND=":loadDB_empty" ALIAS="keywordExists">
						<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS responses FROM autoresponder_responses (NOLOCK) WHERE type=:loadDB_id ;">
						<iSQLFETCH ALIAS="loadDB">
						<iRNDNUM LOW="1" HIGH=":loadDB_responses" SEED=<iTICKS> OUTVAR="responseIdx">
						<iSQL :datasource ALIAS="z" SQL="SELECT data FROM autoresponder_responses (NOLOCK) WHERE type=:loadDB_id ;" INDEXED="TRUE">
							<iSQLFETCH ALIAS="z" INDEX=":responseIdx">
						 	<iSET message=":z_data">
						</iSQL ALIAS="z">
					<iELSE ALIAS="keywordExists">
						<iSET message=":defaultMessage"> 
					</iIF ALIAS="keywordExists">
				</iIF ALIAS="checkKeywords">
			</iIF ALIAS="parseMessage">
<iREMBLOCK>
			<iDEFAULT NAME="status" VALUE="1">
			
			<iSQLMORE ALIAS="loadDB" SQL="UPDATE users SET luvgramsent=:loadDB_luvgramsent WHERE id = :uid ;"> 
			<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO dbo.siteMessaging (to_id, from_id, message, status, datecreated) VALUES (:loadDB_id, :fromid, ':message', :status ,getDate()) ;">
</iREMBLOCK>
			
			This is the message string that would have been written to the db:<P>
			:message<P>

			Test any of the keywords (try HELP).<BR>
			
			<FORM METHOD=POST ACTION=':i_script_name'>
				<INPUT TYPE="TEXT" VALUE="quote" NAME="message">
				<INPUT TYPE="SUBMIT">
			</FORM>
			
<HR>
<H1>Edit database:</H1>

<FORM METHOD=POST ACTION=':i_script_name'>
	<INPUT TYPE="HIDDEN" NAME="mode" VALUE="addk">
	<B>Add keyword:</B><BR><INPUT TYPE="TEXT" NAME="keyword" STYLE="width:500px">
	<INPUT TYPE="SUBMIT" VALUE="Save">
</FORM>


<FORM METHOD=POST ACTION=':i_script_name'>
	<INPUT TYPE="HIDDEN" NAME="mode" VALUE="changek">
	<B>Select a keyword/category to edit:</B><SELECT NAME="new_cat_id"> 
	<iSQLMORE ALIAS="loadDB" SQL="SELECT id, keyword FROM autoresponder_types (NOLOCK) ;">
	<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		<iDEFAULT NAME="cat_id" VALUE=":loadDB_id">
		<iWHILE NOTALIAS="loadDB_empty">
			<iIF EXPR=":cat_id EQ :loadDB_id" ALIAS="setName">
				<iSET catName=":loadDB_keyword">
			</iIF ALIAS="setName">
			<OPTION VALUE=":loadDB_id" <iIF EXPR=":loadDB_id EQ :cat_id" ALIAS="setThis">SELECTED</iIF ALIAS="setThis">>:loadDB_keyword
			<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
		</iWHILE ALIAS="loadDB_empty">
		</SELECT>
	<INPUT TYPE="SUBMIT" VALUE="Select">
</FORM>

<FORM METHOD=POST ACTION=':i_script_name'>
	<INPUT TYPE="HIDDEN" NAME="mode" VALUE="editk">
	<INPUT TYPE="HIDDEN" NAME="id" VALUE=":cat_id">
	<B>Edit:</B><BR>
	<INPUT TYPE="TEXT" NAME="keyword" VALUE=":catName" STYLE="width:500px" MAXLENGTH="255">
	<INPUT TYPE="SUBMIT" VALUE="Save">
</FORM>
		
<H3>Data:</H3>

<FORM METHOD=POST ACTION=':i_script_name'>
	<INPUT TYPE="HIDDEN" NAME="mode" VALUE="add">
	<INPUT TYPE="HIDDEN" NAME="type" VALUE=":cat_id">
	<B>Add Data:</B><BR>
	<INPUT TYPE="TEXT" NAME="data" STYLE="width:500px">
	<INPUT TYPE="SUBMIT" VALUE="Save">
</FORM>

<B>Edit Data:</B>
<iSQLMORE ALIAS="loadDB" SQL="SELECT id, data FROM autoresponder_responses (NOLOCK) WHERE type=:cat_id ;">
<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
<iWHILE NOTALIAS="loadDB_empty">
	<iREPLACE SRC='"' DST="&quot;" VAR="loadDB_data">
	<FORM METHOD=POST ACTION=':i_script_name'>
		<INPUT TYPE="HIDDEN" NAME="mode" VALUE="edit">
		<INPUT TYPE="HIDDEN" NAME="id" VALUE=":loadDB_id">
		<INPUT TYPE="TEXT" NAME="data" VALUE=":loadDB_data" STYLE="width:500px" MAXLENGTH="255">
		<INPUT TYPE="SUBMIT" VALUE="Save">
	</FORM>
	<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">
</iWHILE ALIAS="loadDB_empty">
		
<iINCLUDE NAME="..\..\incs\footer_members.inc">
