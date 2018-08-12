<iWATCHDOG TIMEOUT=999>

<iSET dbConn=":appConn" targetTable="_job_:job">

<iCASE ALIAS="goSub" VALUE="deleteRecipients">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS recipientCount FROM :targetTable (NOLOCK) :do ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_recipientCount recipients deleted.">
	<iSQLMORE ALIAS="loadDB" SQL="DELETE FROM :targetTable :do ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="resetSent">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS flagCount FROM :targetTable (NOLOCK) WHERE sent=1 ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_flagCount 'sent' flags reset.">
	<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET sent=0 WHERE sent=1 ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="resetDelivered">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS flagCount FROM :targetTable (NOLOCK) WHERE delivered=1 ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_flagCount 'delivered' flags reset.">
	<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET delivered=0 WHERE delivered=1 ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="resetBounced">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS flagCount FROM :targetTable (NOLOCK) WHERE bounced=1 ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_flagCount 'bounced' flags reset.">
	<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET bounced=0 WHERE bounced=1 ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="resetUnsubscribed">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS flagCount FROM :targetTable (NOLOCK) WHERE unsubscribed=1 ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_flagCount 'unsubscribed' flags reset.">
	<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET unsubscribed=0 WHERE unsubscribed=1 ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="resetViewed">
	<iSQLMORE ALIAS="loadDB" SQL="SELECT COUNT(*) AS flagCount FROM :targetTable (NOLOCK) WHERE viewed=1 ;">
	<iSQLFETCH ALIAS="loadDB">
	<iSET statusMsg=":loadDB_flagCount 'viewed' flags reset.">
	<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET viewed=0 WHERE viewed=1 ;">
	<iSQLFETCH ALIAS="loadDB">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="importRecipients">
	<iCASE ALIAS="status" VALUE="0">
		<iSET fucfg="w:\sendmanager\fileuploader.cfg">
		<iINCLUDE NAME="w:\fileuploader\fileuploader.inc">
	</iCASE ALIAS="status">
	<iCASE ALIAS="status" VALUE="1">
		<iSET statusMsg="Upload failed: :errMsg">
	</iCASE ALIAS="status">
	<iCASE ALIAS="status" VALUE="2">
		<iSET statusMsg=":size bytes uploaded successfully. Import results are shown above.">

<iREMBLOCK>
		<iSET importFile=":i_path">
		<iREPLACE VAR="importFile" SRC=":i_currentpage" DST="\import_:job">
		<iSTRCAT DST="importFile" SRC=".csv">
</iREMBLOCK>

		<iSET importFile="x:\adminware.com\htdocs\import_:job">
		<iSTRCAT DST="importFile" SRC=".csv">

		<iSET eof=FALSE curLine=0>
		<iINCLUDE NAME="w:\ifuncs\checkEmail.ifunc">
		<P ALIGN=LEFT><B>Import Results:</B><BR><BR><CODE>

<iREMBLOCK>
What I would probably do is load the entire file and then do a 
iREGEX... on it to find the number of CRLF characters.

	<iREGEXLIST SRC=`<iFILE NAME=":importFile" OP=READ>` LISTNAME="crList" REGEX="\r" MAX=999999 FLAGS="NB">
	<iLISTGET NAME="crList" OP=COUNT> carriage returns found.<BR>
	<iREGEXLIST SRC=`<iFILE NAME=":importFile" OP=READ>` LISTNAME="lfList" REGEX="\n" MAX=999999 FLAGS="NB">
	<iLISTGET NAME="lfList" OP=COUNT> line feeds found.<BR>
	<iREGEXLIST SRC=`<iFILE NAME=":importFile" OP=READ>` LISTNAME="crlfList" REGEX="\r\n" MAX=999999 FLAGS="NB">
	<iLISTGET NAME="crlfList" OP=COUNT> CR/LF pairs found.<BR><BR>
</iREMBLOCK>

		<iWHILE NOTALIAS=eof>
			<iSET emailValid=0 guid="">
			<iEVAL EXPR=':curLine+1' OUTVAR="curLine">
			<iREADLINE NAME=":importFile" INDEX=:curLine OUTVAR="theLine" EHANDLE=INLINE>
			<iIF COND=<iSTRCMP SRC=":i_error" DST="920"> ALIAS="eofCheck">
				<iSET eof=TRUE>
			<iELSE ALIAS="eofCheck">
				<iIF EXPR='<iSTRIN SRC=":theLine" DST="email"> AND :curLine=1' ALIAS="skipHeader">
					Skipped header.
				<iELSE ALIAS="skipHeader">
					<iLISTCREATE NAME="upsertValues" DELIM="" SRC="theLine" TYPE=VARIABLE>
					<iLISTGET NAME="upsertValues" OP=COUNT DELIM="" OUTVAR="colCount">
					<iIF EXPR=':colCount = 1' ALIAS="justOne">
						<iLISTGET NAME="upsertValues" OP=GETAT INDEX=1 DELIM="" OUTVAR="newEmail">
						<iSTRLWR SRC=":newEmail" OUTVAR="newEmail">
						<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM :targetTable (NOLOCK) WHERE email=':newEmail' ;">
						<iSQLFETCH ALIAS="loadDB">
						<iIF COND=<iISDIGIT SRC=":loadDB_id"> ALIAS="emailExists">
							No update made for &lt;:newEmail&gt;.
						<iELSE ALIAS="emailExists">
							<iFUNCCALL ALIAS="checkEmail" EMAIL=":newEmail" OUTVAR="emailValid">
							<iLOOP INITIAL=1 FINAL=4>
								<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=65 HIGH=90>>`>
								<iSTRCAT DST="guid" SRC=`<iRNDNUM LOW=0 HIGH=9>`>
								<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=97 HIGH=122>>`>
							</iLOOP>
							<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO :targetTable (email, verified, guid) VALUES (':newEmail', :emailValid, ':guid') ;">
							<iSQLFETCH ALIAS="loadDB">
							<B>New recipient, &lt;:newEmail&gt;, inserted into database.</B>
						</iIF ALIAS="emailExists">
					<iELSE ALIAS="justOne">
						<iLISTGET NAME="upsertValues" OP=GETAT INDEX=1 DELIM="" OUTVAR="newRecipient">
						<iLISTGET NAME="upsertValues" OP=GETAT INDEX=2 DELIM="" OUTVAR="newEmail">
						<iSTRLWR SRC=":newEmail" OUTVAR="newEmail">
						<iIF EXPR=':colCount > 2' ALIAS="otherCols">
							<iLISTGET NAME="upsertValues" OP=GETAT INDEX=3 DELIM="" OUTVAR="newCompany">
						</iIF ALIAS="otherCols">
						<iSQLMORE ALIAS="loadDB" SQL="SELECT id FROM :targetTable (NOLOCK) WHERE email=':newEmail' ;">
						<iSQLFETCH ALIAS="loadDB">
						<iIF COND=<iISDIGIT SRC=":loadDB_id"> ALIAS="emailExists">
							<iSET existingEmail=":loadDB_id">
							<iSQLMORE ALIAS="loadDB" SQL="SELECT addressee FROM :targetTable (NOLOCK) WHERE id=:existingEmail ;">
							<iSQLFETCH ALIAS="loadDB">
							<iSET curAddressee=":loadDB_addressee">
							<iIF COND=<iSTRCMP SRC=":newRecipient" DST=":curAddressee"> ALIAS="nochange">
								No update made for :newRecipient &lt;:newEmail&gt;.
							<iELSE ALIAS="nochange">
								<iIF EXPR=':colCount > 2' ALIAS="otherCols">
									<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET addressee=':newRecipient', company=':newCompany' WHERE id=:existingEmail ;">
								<iELSE ALIAS="otherCols">
									<iSQLMORE ALIAS="loadDB" SQL="UPDATE :targetTable SET addressee=':newRecipient' WHERE id=:existingEmail ;">
								</iIF ALIAS="otherCols">
								<iSQLFETCH ALIAS="loadDB">
								<B>Renamed recipient with email address of ':newEmail' to ':newRecipient'.</B>
							</iIF ALIAS="nochange">
						<iELSE ALIAS="emailExists">
							<iFUNCCALL ALIAS="checkEmail" EMAIL=":newEmail" OUTVAR="emailValid">
							<iLOOP INITIAL=1 FINAL=4>
								<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=65 HIGH=90>>`>
								<iSTRCAT DST="guid" SRC=`<iRNDNUM LOW=0 HIGH=9>`>
								<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=97 HIGH=122>>`>
							</iLOOP>
							<iIF EXPR=':colCount > 2' ALIAS="otherCols">
								<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO :targetTable (addressee, email, verified, company, guid) VALUES (':newRecipient', ':newEmail', :emailValid, ':newCompany', ':guid') ;">
							<iELSE ALIAS="otherCols">
								<iSQLMORE ALIAS="loadDB" SQL="INSERT INTO :targetTable (addressee, email, verified, guid) VALUES (':newRecipient', ':newEmail', :emailValid, ':guid') ;">
							</iIF ALIAS="otherCols">
							<iSQLFETCH ALIAS="loadDB">
							<B>New recipient, :newRecipient &lt;:newEmail&gt;, inserted into database.</B>
						</iIF ALIAS="emailExists">
					</iIF ALIAS="justOne">
					<iUNDEFINE upsertValues>
				</iIF ALIAS="skipHeader">
				<BR>
			</iIF ALIAS="eofCheck">
		</iWHILE ALIAS=eof>
		</CODE></P>
	</iCASE ALIAS="status">
</iCASE ALIAS="goSub">

<iCASE ALIAS="goSub" VALUE="exportRecipients">

<iREMBLOCK>
	<iSET exportFile=":i_path">
	<iREPLACE VAR="exportFile" SRC=":i_currentpage" DST="\export_:job">
	<iSTRCAT DST="exportFile" SRC=".csv">
</iREMBLOCK>

	<iSET exportFile="x:\adminware.com\htdocs\export_:job">
	<iSTRCAT DST="exportFile" SRC=".csv">

	<iINCLUDE NAME="w:\dbalchemist\custom_field_array.inc">

	<iSET customFieldTitles="">
	<iLOOP INITIAL=1 FINAL=:customFieldCount ALIAS="customFieldLoop">
		<iLISTGET NAME="customFieldArray" OP=GETAT INDEX=:customFieldLoop DELIM="" OUTVAR="curField">
		<iSTRCAT DST="customFieldTitles" SRC=`,":curField"`>
	</iLOOP ALIAS="customFieldLoop">
	<iIF COND=:customFieldCount ALIAS="noCustomFields"><iSET customFields=",:customFields"></iIF ALIAS="noCustomFields">

	<iINCLUDE NAME="w:\ifuncs\exportToCSV.ifunc">
	<iFUNCCALL ALIAS="exportToCSV" DBCONN=":dbConn" TABLE=":targetTable" FILENAME=":exportFile" TITLES=`"Recipient's Name","Email Address","Unsubscribed","Bounced","Sent","Valid","Undelivery Reason":customFieldTitles` COLUMNS="addressee,email,unsubscribed,bounced,sent,verified,undeliveryReason:customFields">
	<iSTRRIGHT SRC=":exportFile" NUM=<iEVAL EXPR='<iSTRIN SRC=`<iSTRREV SRC=":exportFile">` DST="\"> - 1'> OUTVAR="nameOnly">
	<iADDHEADER SRC='Content-Disposition: other; filename=":nameOnly"'>
	<iDOWNLOAD TYPE="text/comma-seperated-values" DELETEFILE=TRUE DISPOSITION=":nameOnly" FILE=":nameOnly">
</iCASE ALIAS="goSub">

<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="deleteRecipients">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Delete Recipients')" onMouseOut="noHelp()">Delete Recipients:</A> &nbsp;</TD>
	<TD>
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="do" VALUE="" CHECKED> All &nbsp;
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="do" VALUE="WHERE bounced=1"> Bounced &nbsp;
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="do" VALUE="WHERE unsubscribed=1"> Unsubscribed &nbsp;
		<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="do" VALUE="WHERE verified=0"> Invalid &nbsp;
	</TD>
	<TD WIDTH="1%" NOWRAP ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="resetSent">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Sent')" onMouseOut="noHelp()">Reset 'Sent' Flag:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="resetDelivered">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Delivered')" onMouseOut="noHelp()">Reset 'Delivered' Flag:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="resetBounced">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Bounced')" onMouseOut="noHelp()">Reset 'Bounced' Flag:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="resetUnsubscribed">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Unsubscribed')" onMouseOut="noHelp()">Reset 'Unsubscribed' Flag:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="resetViewed">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Reset Viewed')" onMouseOut="noHelp()">Reset 'Viewed' Flag:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!" onClick="if (!(confirm('Are you sure?'))) {return false}"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ENCTYPE="multipart/form-data" ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="importRecipients">
	<INPUT TYPE=HIDDEN NAME="status" VALUE="0">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Import Recipients')" onMouseOut="noHelp()">Import Recipients from File:</A> &nbsp;</TD>
	<TD><INPUT TYPE=FILE NAME="filename" SIZE=50></TD>
	<TD WIDTH="1%" NOWRAP ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!"></A></TD>
	</FORM>
</TR>
<TR>
	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<INPUT TYPE=HIDDEN NAME="goSub" VALUE="exportRecipients">
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Export Recipients')" onMouseOut="noHelp()">Export Recipients to File:</A> &nbsp;</TD>
	<TD WIDTH="1%" NOWRAP COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT VALUE="Go!"></A></TD>
	</FORM>
</TR>
</TABLE>
