<iREM -- Post Insert/Update Tasks -- >

<iREM -- Set verified=1 due to DBA field validation -- >

<iREM -- Set GUID -- >
<iSET guid="">
<iLOOP INITIAL=1 FINAL=4>
	<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=65 HIGH=90>>`>
	<iSTRCAT DST="guid" SRC=`<iRNDNUM LOW=0 HIGH=9>`>
	<iSTRCAT DST="guid" SRC=`<iCHR ASC=<iRNDNUM LOW=97 HIGH=122>>`>
</iLOOP>

<iSQLMORE SQL="UPDATE :targetTable SET guid=':guid', verified=1 WHERE id=:id ;" ALIAS="loadDB">
<iSQLFETCH ALIAS="loadDB">
