<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="submitted"> ALIAS="doSave">
	<iREPLACE VAR="postSub" SRC="'" DST="''">
	<iREPLACE VAR="postUnsub" SRC="'" DST="''">
	<iREPLACE VAR="postBounce" SRC="'" DST="''">
	<iREPLACE VAR="postSQLDSN" SRC="'" DST="''">
	<iREPLACE VAR="postSQLUP" SRC="'" DST="''">
	<iREPLACE VAR="postURLUP" SRC="'" DST="''">
	<iSET z="Post processing settings updated.">
	<iHTML DBNAME=":appConn" SQL=`UPDATE jobs SET postSubType=:postSubType, postUnsubType=:postUnsubType, postBounceType=:postBounceType, postSub=':postSub', postUnsub=':postUnsub', postBounce=':postBounce', postSQLDSN=':postSQLDSN', postSQLUP=':postSQLUP', postURLUP=':postURLUP' WHERE id=:job ;` NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="statusMsg">
	<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="Update failed.">
	<iIF COND=<iSTRCMP SRC=":statusMsg" DST="Success"> ALIAS="setMsg"><iSET statusMsg=":z"></iIF ALIAS="setMsg">
</iIF ALIAS="doSave">

<iSQLMORE ALIAS="load" SQL="SELECT isLocal FROM clients (NOLOCK) WHERE id=:client_id ;">
<iSQLFETCH ALIAS="load">
<iIF NOTCOND=:i_sqlempty>
	<iSET isLocal=:load_isLocal>
<iELSE>
	<iSET isLocal=0>
</iIF>

<iSQLMORE ALIAS="loadDB" SQL="SELECT allowSelfSub, allowSelfUnsub, postSubType, postUnsubType, postBounceType, postBounce, postSub, postUnsub, postBounce, postSQLDSN, postSQLUP, postURLUP FROM jobs (NOLOCK) WHERE id=:job ;">
<iSQLFETCH ALIAS="loadDB">

<FORM METHOD=POST ACTION=':thisPage'>
<INPUT TYPE=HIDDEN NAME="submitted" VALUE="1">
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<TR><TD COLSPAN=2><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Post Processing Types')" onMouseOut="noHelp()"><FONT SIZE="-1" FACE="Arial, sans-serif"><B><U>Available Post Processing Types</U></B></FONT></A><BR><BR></TD></TR>
<TR>
	<TD CLASS="tableHeading" VALIGN=TOP NOWRAP>URL Processing &nbsp;</TD>
	<TD>
		The username and password should be in the format <B>username:<iREM>password</B>, if required to access the URL
		provided.&nbsp; The URL run will receive the email address as the only argument in the variable 'email'.<BR><BR>
		For example, if the URL you enter is <I>http://www.yourdomain.com/postunsub.ihtml</I> and the email address being
		unsubscribed is <I>bob@saget.com</I>, the end result would be:&nbsp; <B>http://www.yourdomain.com/postunsub.ihtml?email=bob@saget.com</B>
	</TD>
</TR>
<iIF EXPR=':isLocal' ALIAS="showSQL">
	<TR><TD COLSPAN=2>&nbsp;</TD></TR>
	<TR>
		<TD CLASS="tableHeading" VALIGN=TOP NOWRAP><B>SQL Processing</B> &nbsp;</TD>
		<TD>
			The username and password should be in the format <B>username/password</B>.&nbsp; Within your SQL, the email
			address will be available as :<iREM>email.<BR><BR>
			For example, if your SQL is <I>UPDATE myTable SET unsub=1 WHERE email=':email'</I> and the email address being
			unsubscribed is <I>bob@saget.com</I>, the end result would be:&nbsp; <B>UPDATE myTable SET unsub=1 WHERE email='bob@saget.com'</B>
		</TD>
	</TR>
</iIF ALIAS="showSQL">
<TR><TD COLSPAN=2>&nbsp;</TD></TR>

<TR><TD CLASS="tableHeading" COLSPAN=2><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Post Subscribe')" onMouseOut="noHelp()">Post Subscription Processing</A> &nbsp;</TD></TR>
<iIF EXPR=':loadDB_allowSelfSub' ALIAS="showSub">
	<TR>
		<TD CLASS="tableHeading" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postSubType" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_postSubType" DST="0">>CHECKED</iIF> onClick='this.form.submit()'> URL &nbsp;</TD>
		<TD><iIF COND=<iSTRCMP SRC=":loadDB_postSubType" DST="0">>
			<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
			<TR>
				<TD>URL: </TD>
				<TD><INPUT TYPE=TEXT NAME="postSub" VALUE=":loadDB_postSub" SIZE=67 MAXLENGTH=1024></TD>
			</TR>
			<TR>
				<TD>User/Pwd: </TD>
				<TD><INPUT TYPE=TEXT NAME="postURLUP" VALUE=":loadDB_postURLUP" SIZE=33></TD>
			</TR>
			</TABLE>
			<INPUT TYPE=HIDDEN NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN">
			<INPUT TYPE=HIDDEN NAME="postSQLUP" VALUE=":loadDB_postSQLUP">
		<iELSE>&nbsp;</iIF></TD>
	</TR>
	<iIF EXPR=':isLocal' ALIAS="showSQL">
		<TR>
			<TD CLASS="tableHeading" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postSubType" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_postSubType" DST="1">>CHECKED</iIF> onClick='this.form.submit()'> SQL &nbsp;</TD>
			<TD><iIF COND=<iSTRCMP SRC=":loadDB_postSubType" DST="1">>
				<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
				<TR>
					<TD>DataSource: </TD>
					<TD><INPUT TYPE=TEXT NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN" SIZE=33></TD>
				</TR>
				<TR>
					<TD>User/Pwd: </TD>
					<TD><INPUT TYPE=TEXT NAME="postSQLUP" VALUE=":loadDB_postSQLUP" SIZE=33></TD>
				</TR>
				<TR>
					<TD VALIGN=TOP>Query: </TD>
					<TD><TEXTAREA NAME="postSub" ROWS=3 COLS=51 WRAP=SOFT>:loadDB_postSub</TEXTAREA></TD>
				</TR>
				</TABLE>
				<INPUT TYPE=HIDDEN NAME="postURLUP" VALUE=":loadDB_postURLUP">
			<iELSE>&nbsp;</iIF></TD>
		</TR>
	</iIF ALIAS="showSQL">
<iELSE ALIAS="showSub">
	<TR><TD COLSPAN=2><BR>List members are not allowed to self-subscribe to this job.</TD></TR>
	<INPUT TYPE=HIDDEN NAME="postSubType" VALUE=":loadDB_postSubType">
	<INPUT TYPE=HIDDEN NAME="postSub" VALUE=":loadDB_postSub">
	<INPUT TYPE=HIDDEN NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN">
	<INPUT TYPE=HIDDEN NAME="postSQLUP" VALUE=":loadDB_postSQLUP">
	<INPUT TYPE=HIDDEN NAME="postURLUP" VALUE=":loadDB_postURLUP">
</iIF ALIAS="showSub">

<TR><TD COLSPAN=2>&nbsp;</TD></TR>

<TR><TD CLASS="tableHeading" COLSPAN=2><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Post Unsubscribe')" onMouseOut="noHelp()">Post Unsubscription Processing</A> &nbsp;</TD></TR>
<iIF EXPR=':loadDB_allowSelfUnsub' ALIAS="showUnsub">
	<TR>
		<TD ALIAS="loadDB" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postUnsubType" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_postUnsubType" DST="0">>CHECKED</iIF> onClick='this.form.submit()'> URL &nbsp;</TD>
		<TD><iIF COND=<iSTRCMP SRC=":loadDB_postUnsubType" DST="0">>
			<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
			<TR>
				<TD>URL: </TD>
				<TD><INPUT TYPE=TEXT NAME="postUnsub" VALUE=":loadDB_postUnsub" SIZE=67 MAXLENGTH=1024></TD>
			</TR>
			<TR>
				<TD>User/Pwd: </TD>
				<TD><INPUT TYPE=TEXT NAME="postURLUP" VALUE=":loadDB_postURLUP" SIZE=33></TD>
			</TR>
			</TABLE>
			<INPUT TYPE=HIDDEN NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN">
			<INPUT TYPE=HIDDEN NAME="postSQLUP" VALUE=":loadDB_postSQLUP">
		<iELSE>&nbsp;</iIF></TD>
	</TR>
	<iIF EXPR=':isLocal' ALIAS="showSQL">
		<TR>
			<TD CLASS="tableHeading" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postUnsubType" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_postUnsubType" DST="1">>CHECKED</iIF> onClick='this.form.submit()'> SQL &nbsp;</TD>
			<TD><iIF COND=<iSTRCMP SRC=":loadDB_postUnsubType" DST="1">>
				<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
				<TR>
					<TD>DataSource: </TD>
					<TD><INPUT TYPE=TEXT NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN" SIZE=33></TD>
				</TR>
				<TR>
					<TD>User/Pwd: </TD>
					<TD><INPUT TYPE=TEXT NAME="postSQLUP" VALUE=":loadDB_postSQLUP" SIZE=33></TD>
				</TR>
				<TR>
					<TD VALIGN=TOP>Query: </TD>
					<TD><TEXTAREA NAME="postUnsub" ROWS=3 COLS=51 WRAP=SOFT>:loadDB_postUnsub</TEXTAREA></TD>
				</TR>
				</TABLE>
				<INPUT TYPE=HIDDEN NAME="postURLUP" VALUE=":loadDB_postURLUP">
			<iELSE>&nbsp;</iIF></TD>
		</TR>
	</iIF ALIAS="showSQL">
<iELSE ALIAS="showUnsub">
	<TR><TD COLSPAN=2><BR>List members are not allowed to self-unsubscribe from this job.</TD></TR>
	<INPUT TYPE=HIDDEN NAME="postUnsubType" VALUE=":loadDB_postUnsubType">
	<INPUT TYPE=HIDDEN NAME="postUnsub" VALUE=":loadDB_postUnsub">
	<INPUT TYPE=HIDDEN NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN">
	<INPUT TYPE=HIDDEN NAME="postSQLUP" VALUE=":loadDB_postSQLUP">
	<INPUT TYPE=HIDDEN NAME="postURLUP" VALUE=":loadDB_postURLUP">
</iIF ALIAS="showUnsub">

<TR><TD COLSPAN=2>&nbsp;</TD></TR>

<TR><TD CLASS="tableHeading" COLSPAN=2><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Post Bounce')" onMouseOut="noHelp()">Post Bounce Processing</A> &nbsp;</TD></TR>
<TR>
	<TD CLASS="tableHeading" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postBounceType" VALUE="0" <iIF COND=<iSTRCMP SRC=":loadDB_postBounceType" DST="0">>CHECKED</iIF> onClick='this.form.submit()'> URL &nbsp;</TD>
	<TD><iIF COND=<iSTRCMP SRC=":loadDB_postBounceType" DST="0">>
		<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
		<TR>
			<TD>URL: </TD>
			<TD><INPUT TYPE=TEXT NAME="postBounce" VALUE=":loadDB_postBounce" SIZE=67 MAXLENGTH=1024></TD>
		</TR>
		<TR>
			<TD>User/Pwd: </TD>
			<TD><INPUT TYPE=TEXT NAME="postURLUP" VALUE=":loadDB_postURLUP" SIZE=33></TD>
		</TR>
		</TABLE>
		<INPUT TYPE=HIDDEN NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN">
		<INPUT TYPE=HIDDEN NAME="postSQLUP" VALUE=":loadDB_postSQLUP">
	<iELSE>&nbsp;</iIF></TD>
</TR>
<iIF EXPR=':isLocal' ALIAS="showSQL">
	<TR>
		<TD CLASS="tableHeading" VALIGN=TOP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="postBounceType" VALUE="1" <iIF COND=<iSTRCMP SRC=":loadDB_postBounceType" DST="1">>CHECKED</iIF> onClick='this.form.submit()'> SQL &nbsp;</TD>
		<TD><iIF COND=<iSTRCMP SRC=":loadDB_postBounceType" DST="1">>
			<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
			<TR>
				<TD>DataSource: </TD>
				<TD><INPUT TYPE=TEXT NAME="postSQLDSN" VALUE=":loadDB_postSQLDSN" SIZE=33></TD>
			</TR>
			<TR>
				<TD>User/Pwd: </TD>
				<TD><INPUT TYPE=TEXT NAME="postSQLUP" VALUE=":loadDB_postSQLUP" SIZE=33></TD>
			</TR>
			<TR>
				<TD VALIGN=TOP>Query: </TD>
				<TD><TEXTAREA NAME="postBounce" ROWS=3 COLS=51 WRAP=SOFT>:loadDB_postBounce</TEXTAREA></TD>
			</TR>
			</TABLE>
			<INPUT TYPE=HIDDEN NAME="postURLUP" VALUE=":loadDB_postURLUP">
		<iELSE>&nbsp;</iIF></TD>
	</TR>
</iIF ALIAS="showSQL">

<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doSave" VALUE="Save Changes"></TD></TR>
</TABLE>
</FORM>
