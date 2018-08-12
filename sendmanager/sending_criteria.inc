<iDEFAULT NAME="step" VALUE="1">
<iDEFAULT NAME="showFields" VALUE="">

<iSET dbConn = ":appConn" targetTable = "_job_:job">

<iINCLUDE NAME="w:\dbalchemist\custom_field_array.inc">

<iIF COND=<iSTRCMP SRC=":customFieldCount" DST="0"> ALIAS="noCustom">

	There are no custom fields defined for this job.

<iELSE ALIAS="noCustom">

	<TABLE WIDTH="100%" BORDER=0><TR><TD>
	<TABLE BORDER=0>

	<iCASE ALIAS="step" VALUE="2">

		<iSET criteria="">
		<iLOOP INITIAL=1 FINAL=:customFieldCount ALIAS="customFieldLoop">
			<iLISTGET NAME="customFieldArray" OP=GETAT INDEX=:customFieldLoop DELIM="" OUTVAR="curField">
			<iEQ NAME="curOp" VALUE=":op_:customFieldLoop" EVAL=TRUE>
			<iEQ NAME="curVal" VALUE=":val_:customFieldLoop" EVAL=TRUE>
			<iIF EXPR='NOT <iSTRCMP SRC=":curOp" DST=""> AND NOT <iSTRCMP SRC=":curVal" DST="">' ALIAS="use">
				<iLISTGET NAME="customFieldTypeArray" OP=GETAT INDEX=:customFieldLoop DELIM="" OUTVAR="curFieldType">
				<iIF COND=<iSTRIN SRC="SMALLDATETIME,DATETIME,VARCHAR,LONGCHAR,TEXT" DST=":curFieldType" CASE=FALSE>><iSET fQual="'"><iELSE><iSET fQual=""></iIF>
				<iSTRCAT DST="criteria" SRC=" AND :curField :curOp :fQual:curVal:fQual">
			</iIF ALIAS="use">
		</iLOOP ALIAS="customFieldLoop">

		<iHTML DBNAME=":appConn" SQL="UPDATE _job_:job SET sent=1 WHERE sent=0 AND bounced=0 AND unsubscribed=0 AND verified=1 ;">
		<iSET showCriteria=":criteria">
		<iREPLACE VAR="showCriteria" SRC="AND " DST="">
		<TR><TD>
			Updated send queue to send only to recipients matching the following criteria:<BR><BR>
			<BLOCKQUOTE><B>:showCriteria</B></BLOCKQUOTE>
			<iHTML DBNAME=":appConn" SQL="SET NOCOUNT ON UPDATE _job_:job SET sent=0 WHERE bounced=0 AND unsubscribed=0 AND verified=1 :criteria SELECT @@rowcount ;" ESC=FALSE OUTPUT=":1 records affected." NOOUTPUT="0 records affected." FAILURE="ERROR: :i_sqlerrortext" OUTVAR="statusMsg">
			<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="">
			:statusMsg
		</TD></TR>

	</iCASE ALIAS="step">

	<iCASE ALIAS="step" VALUE="1">

		<FORM METHOD=POST ACTION=':thisPage'>
		<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
		<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
		<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
		<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
		<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
		<INPUT TYPE=HIDDEN NAME="step" VALUE="2">
		<TR><TD COLSPAN=3>Update send queue to send only to recipients matching the following criteria...<BR><BR></TD></TR>
		<iLOOP INITIAL=1 FINAL=:customFieldCount ALIAS="customFieldLoop">
			<iLISTGET NAME="customFieldArray" OP=GETAT INDEX=:customFieldLoop DELIM="" OUTVAR="curField">
			<TR>
				<TD>:curField</TD>
				<TD><SELECT NAME="op_:customFieldLoop"><OPTION VALUE="">-</OPTION><OPTION VALUE="=">IS</OPTION><OPTION VALUE="!=">IS NOT</OPTION></SELECT></TD>
				<TD><SELECT NAME="val_:customFieldLoop">
					<OPTION VALUE="">-</OPTION>
					<iSQLMORE ALIAS="loadDB" SQL="SELECT DISTINCT :curField FROM _job_:job (NOLOCK) ORDER BY :curField ;" ESC=FALSE>
					<iSQLFETCH ALIAS="loadDB">
					<iWHILE NOTALIAS=i_sqlempty>
						<iEQ NAME="unique" VALUE=":loadDB_:curField" EVAL=TRUE>
						<OPTION VALUE=":unique">:unique</OPTION>
						<iSQLFETCH ALIAS="loadDB">
					</iWHILE ALIAS=i_sqlempty>
				</SELECT></TD>
			</TR>
		</iLOOP ALIAS="customFieldLoop">
		<TR><TD COLSPAN=3 ALIGN=RIGHT><BR><INPUT TYPE=SUBMIT VALUE="Set Sending Criteria"></TD></TR>
		</FORM>

	</iCASE ALIAS="step">

	</TABLE>
	</TD></TR></TABLE>

</iIF ALIAS="noCustom">
