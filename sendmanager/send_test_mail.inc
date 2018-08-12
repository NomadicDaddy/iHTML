<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) FROM _job_:job WHERE tester=1 ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="pieces">
<iIF EXPR=':pieces > 0' ALIAS="doIt">

	<iREM -- Add to queue -- >
	<iHTML DBNAME=":appConn" SQL="UPDATE jobs SET inProgress=1 WHERE id=:job ;">
	<iHTML DBNAME=":appConn" SQL="INSERT INTO queue (job_id, type, totalRecords) VALUES (:job, 0, :pieces) ;">

	<iREM -- Redirect to Job List -- >
	<iREDIR URL=":thisPage?awpid=:awpid&client_id=:client_id&showMenu=Job%20List&refreshAfter=60">

<iELSE ALIAS="doIt">

	There are no tester accounts setup for this job.&nbsp; Go to Manage Recipients to set tester accounts.

</iIF ALIAS="doIt">
