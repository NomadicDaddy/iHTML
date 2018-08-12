<iSQLMORE ALIAS="loadDB" SQL="SELECT * FROM dbo.jobs (NOLOCK) WHERE client_id = :client_id AND id = :job ;">
<iSQLFETCH ALIAS="loadDB" EMPTY="loadDB_empty">

<iSET costLevel = ":loadDB_costLevel">

<TABLE ID="copyTable" BORDER=0 CELLSPACING=0 CELLPADDING=4>

<iHTML DBNAME=":appConn" SQL="SELECT COUNT(*) FROM dbo._job_:loadDB_id (NOLOCK) WHERE unsubscribed=0 AND bounced=0 AND verified=1 ;" OUTPUT=":1" FAILURE="0" OUTVAR="sendPieces">
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP># of Sendable Pieces:</TD>
	<TD ALIGN=RIGHT>&nbsp; :sendPieces</TD>
</TR>

<iEVAL EXPR=':loadDB_mailSize/1024' PREC=2 OUTVAR="kilobytes">
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>Mail Size:</TD>
	<TD ALIGN=RIGHT>&nbsp; :loadDB_mailSize bytes (:kilobytes KB)</TD>
</TR>

<iREM -- Calculate Run Charge -- >
<iINCLUDE NAME="w:\:appDir\jobcost.inc">

<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>Base Run Charge:</TD>
	<TD ALIGN=RIGHT>&nbsp; $ :baseRunCharge</TD>
</TR>

<iEVAL EXPR=':loadDB_mailSize/1024' PREC=2 OUTVAR="kilobytes">
<iEVAL EXPR=':kilobytes - 1' PREC=2 OUTVAR="overSize">
<iIF EXPR='1 GT :overSize'><iSET overSize=0></iIF>
<iSQL DBNAME=":appConn" SQL="EXEC dbo.getCost:costLevel :sendPieces, :overSize ;" ALIAS="getPricing">
<iSQLFETCH ALIAS="getPricing">
<iEVAL EXPR='0.:getPricing_pieceCost' PREC=3 OUTVAR="pieceCost">
<iIF EXPR=':overSize'><iEVAL EXPR='0.:getPricing_additionalKBCost * :overSize * :getPricing_multiplier' PREC=3 OUTVAR="addedCost"><iELSE><iSET addedCost="0.000"></iIF>
<iEVAL EXPR=':baseRunCharge / :sendPieces' PREC=3 OUTVAR="totalPieceCost">
<TR>
	<TD COLSPAN=2>
		<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
			<TR><TD>&nbsp; &nbsp; Base Per Piece Cost &nbsp; </TD>			<TD ALIGN=RIGHT>$ :pieceCost</TD></TR>
			<TR><TD>&nbsp; &nbsp; Additional KB Per Piece Cost &nbsp; </TD>	<TD ALIGN=RIGHT>$ :addedCost</TD></TR>
			<TR><TD>&nbsp; &nbsp; Total Per Piece Cost &nbsp; </TD>		<TD ALIGN=RIGHT>$ :totalPieceCost</TD></TR>
		</TABLE>
	</TD>
</TR>

<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>Feature Discount/Surcharge (<iEVAL EXPR=':runDiscount * 100' PREC=0>%):</TD>
	<TD ALIGN=RIGHT>&nbsp; $ <iEVAL EXPR=':baseRunCharge * :runDiscount' PREC=2></TD>
</TR>
<TR>
	<TD COLSPAN=2>
		<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f1>No </iIF>Field Token Usage &nbsp; </TD>						<TD ALIGN=RIGHT><iIF COND=:f1>-5%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f2>No </iIF>Post Processing &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:f2>-8%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f3>No </iIF>Link Tracking &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:f3>-10%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f4>No </iIF>View Tracking &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:f4>-2%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f5>No </iIF>Automated Bounce Handling &nbsp; </TD>					<TD ALIGN=RIGHT><iIF COND=:f5>-5%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF COND=:f6>No </iIF>Self-Sub/Unsub &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:f6>-5%<iELSE>--</iIF></TD></TR>
			<TR><TD>&nbsp; &nbsp; <iIF NOTCOND=<iSTRCMP SRC=":f7" DST="-2">>No </iIF>Image/File Hosting &nbsp; </TD>	<TD ALIGN=RIGHT><iIF NOTCOND=<iSTRCMP SRC=":f7" DST="-2">>--<iELSE>+2%</iIF></TD></TR>
		</TABLE>
	</TD>
</TR>

<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP>Final Run Charge:</TD>
	<TD ALIGN=RIGHT>&nbsp; $ :runCharge</TD>
</TR>

</TABLE>

<iREM -- Show Clipboard Copy Option if Browser Supported -- >
<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/copyData.js"></SCRIPT>
