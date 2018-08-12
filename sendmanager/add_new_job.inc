<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="doAdd"> ALIAS="doAdd">

	<iHTML DBNAME=":appConn" SQL="SET nocount ON INSERT INTO dbo.jobs (client_id, title, description, sentTo, sentFromAddress, subject, body) VALUES (:client_id, ':title', ':description', '', '', '', '') SELECT @@identity ;" OUTPUT=":1" OUTVAR="newJob">

	<iIF NOTCOND=<iSTRCMP SRC=":newJob" DST=""> ALIAS="notAdded">

		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'id',			'ID',			'Integer',	'',						10,	1, 0, 0, 0, 1, 0, 0, 0, 1, 0) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'email',		'Email Address',	'Email',		'',						100,	1, 1, 1, 1, 1, 0, 0, 0, 0, 1) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'addressee',		'Addressee',		'Text',		'',						100,	1, 1, 1, 1, 1, 0, 1, 0, 0, 2) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'company',		'Company',		'Text',		'',						100,	1, 1, 1, 1, 0, 1, 1, 1, 0, 3) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'tester',		'Tester',			'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 4) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'guid',			'GUID',			'Text',		'',						12,	1, 0, 0, 0, 0, 0, 1, 0, 0, 5) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'sent',			'Sent',			'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 6) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'unsubscribed',	'Unsubscribed',	'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 7) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'verified',		'Verified',		'Toggle',		'Unchecked,Invalid,Valid',	2,	1, 0, 1, 0, 0, 0, 1, 1, 0, 8) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'bounced',		'Bounced',		'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 9) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'viewed',		'Viewed',			'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 10) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'subDate',		'Subscribe Date',	'DateTime',	'',						25,	1, 0, 1, 0, 0, 0, 1, 0, 0, 11) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'unsubDate',		'Unsubscribe Date',	'DateTime',	'',						25,	1, 0, 1, 0, 0, 0, 1, 0, 0, 12) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'lastBounced',	'Last Bounced',	'DateTime',	'',						25,	1, 0, 1, 0, 0, 0, 1, 0, 0, 13) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'lastViewed',	'Last Viewed',		'DateTime',	'',						25,	1, 0, 1, 0, 0, 0, 1, 0, 0, 14) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'mailType',		'Mail Type',		'smallList',	'HTML,Rich,Text-Only',		2,	1, 1, 1, 0, 0, 0, 1, 0, 0, 15) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'comments',		'Comments',		'Text',		'',						50,	1, 1, 1, 0, 1, 0, 1, 0, 0, 16) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'priority',		'Priority',		'Integer',	'',						10,	1, 1, 1, 0, 1, 0, 1, 0, 0, 17) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'Delivered',		'Delivered',		'Toggle',		'',						2,	1, 1, 1, 0, 1, 0, 1, 0, 0, 18) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'lastDelivered',	'Last Delivered',	'DateTime',	'',						25,	1, 0, 1, 0, 0, 0, 1, 0, 0, 19) ;">
		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo._fields (parent, fName, fViewName, fType, fValueTitles, fSize, allowView, allowEdit, allowDelete, allowInsert, allowList, allowAlter, allowDupes, allowNulls, primaryKey, listWeight) VALUES ('_job_:newJob', 'undeliveryReason','Undelivery Reason','Text',		'',						128,	1, 0, 1, 0, 0, 0, 1, 0, 0, 20) ;">

		<iHTML DBNAME=":appConn" SQL="
			CREATE TABLE dbo._job_:newJob (
				id int IDENTITY (1, 1) NOT NULL,
				addressee varchar (100) NULL,
				email varchar (100) NOT NULL,
				unsubscribed bit NOT NULL DEFAULT(0),
				bounced tinyint NOT NULL DEFAULT(0),
				sent bit NOT NULL DEFAULT(0),
				verified bit NULL DEFAULT(0),
				tester bit NOT NULL DEFAULT(0),
				viewed bit NOT NULL DEFAULT(0),
				company varchar (100) NULL,
				guid char (12) NULL,
				subDate smalldatetime NOT NULL DEFAULT (GETDATE()),
				unsubDate smalldatetime NULL,
				lastBounced smalldatetime NULL,
				lastViewed smalldatetime NULL,
				mailType tinyint NOT NULL DEFAULT (1),
				comments varchar(50) NULL,
				priority tinyint NOT NULL DEFAULT (1),
				delivered bit NOT NULL DEFAULT (0),
				lastDelivered smalldatetime NULL,
				undeliveryReason varchar(128) NULL
			) ;
		">
		<iHTML DBNAME=":appConn" SQL="ALTER TABLE dbo._job_:newJob WITH NOCHECK ADD CONSTRAINT [pk__job_:newJob] PRIMARY KEY CLUSTERED (id) WITH FILLFACTOR=90 ;">
		<iHTML DBNAME=":appConn" SQL="CREATE INDEX ix__job_:newJob ON dbo._job_:newJob (email, unsubscribed, bounced, sent, verified, viewed, tester, priority) ;">

		<iSET i1=":newJob" i2=":newJob" i3=":newJob">
		<iSTRCAT DST="i1" SRC="_sending">
		<iSTRCAT DST="i2" SRC="_verified">
		<iSTRCAT DST="i3" SRC="_unsubscribed">
		<iHTML DBNAME=":appConn" SQL="CREATE NONCLUSTERED INDEX ix__job_:i1 ON dbo._job_:newJob (verified ASC, unsubscribed ASC, bounced ASC, sent ASC, priority DESC) ;">
		<iHTML DBNAME=":appConn" SQL="CREATE NONCLUSTERED INDEX ix__job_:i2 ON dbo._job_:newJob (verified ASC) ;">
		<iHTML DBNAME=":appConn" SQL="CREATE NONCLUSTERED INDEX ix__job_:i3 ON dbo._job_:newJob (unsubscribed ASC) ;">

		<iHTML DBNAME=":appConn" SQL="INSERT INTO dbo.transactions (job_id) VALUES (:newJob) ;">

		<iREDIR URL=":thisPage?awpid=:awpid&client_id=:client_id&showMenu=Job%20List">

	<iELSE ALIAS="notAdded">

		<DIV CLASS="errorText">Area ':title' could not be added.&nbsp; Support has been notified.</DIV>

	</iIF ALIAS="notAdded">

<iELSE ALIAS="doAdd">

	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
	<TR>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Title')" onMouseOut="noHelp()">Job Title</A> &nbsp;</TD>
		<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="title" SIZE=50 MAXLENGTH=50></TD>
	</TR>
	<TR>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Job Description')" onMouseOut="noHelp()">Job Description</A> &nbsp;</TD>
		<TD STYLE="padding-left : 9px;"><TEXTAREA NAME="description" COLS=51 ROWS=5 WRAP=SOFT></TEXTAREA></TD>
	</TR>
	<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doAdd" VALUE="Add New Job"></TD></TR>
	</TABLE>
	</FORM>
	</CENTER></TD></TR></TABLE>

</iIF ALIAS="doAdd">
