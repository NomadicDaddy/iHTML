<iREM -- Calculate Estimate -- >
<iIF COND=<iISDEF VAR="doCalc"> ALIAS="doCalc">

<iDEFAULT NAME="costLevel" VALUE="">

	<DIV CLASS="errorText">
	Please note that this is only an estimate.<BR><BR>
	Many factors determine this figure and the only reliable method for providing an accurate cost is to prepare an actual run.
	</DIV><BR>

<iEVAL EXPR=':kilobytes * 1024' PREC=0 OUTVAR="loadDB_mailSize">

	<TABLE ID="copyTable" BORDER=0 CELLSPACING=0 CELLPADDING=4>

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

<iIF COND=<iSTRCMP SRC=":i_ip" DST="24.1.102.150">>
	EXEC dbo.getCost:costLevel :sendPieces, :overSize ;
	0.:getPricing_additionalKBCost * :overSize * :getPricing_multiplier
</iIF>

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
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf1>No </iIF>Field Token Usage &nbsp; </TD>						<TD ALIGN=RIGHT><iIF COND=:zf1>-5%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf2>No </iIF>Post Processing &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:zf2>-8%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf3>No </iIF>Link Tracking &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:zf3>-10%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf4>No </iIF>View Tracking &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:zf4>-2%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf5>No </iIF>Automated Bounce Handling &nbsp; </TD>					<TD ALIGN=RIGHT><iIF COND=:zf5>-5%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF COND=:zf6>No </iIF>Self-Sub/Unsub &nbsp; </TD>							<TD ALIGN=RIGHT><iIF COND=:zf6>-5%<iELSE>--</iIF></TD></TR>
				<TR><TD>&nbsp; &nbsp; <iIF NOTCOND=<iSTRCMP SRC=":zf7" DST="-2">>No </iIF>Image/File Hosting &nbsp; </TD>	<TD ALIGN=RIGHT><iIF NOTCOND=<iSTRCMP SRC=":zf7" DST="-2">>--<iELSE>+2%</iIF></TD></TR>
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

<iELSE ALIAS="doCalc">

	<FORM METHOD=POST ACTION=':thisPage'>
	<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
	<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
	<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
	<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
	<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<iIF COND=<iSTRCMP SRC=":i_ip" DST="24.1.102.150"> ALIAS="isAdmin">
	<TR>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Cost Level')" onMouseOut="noHelp()">Cost Level</A> &nbsp;</TD>
		<TD STYLE="padding-left : 9px;"><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="costLevel" VALUE="" CHECKED> 1 &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="costLevel" VALUE="2"> 2 &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="costLevel" VALUE="3"> 3</TD>
	</TR>
</iIF ALIAS="isAdmin">
	<TR>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Mail Size')" onMouseOut="noHelp()">Mail Size (KB)</A> &nbsp;</TD>
		<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="kilobytes" SIZE=8 MAXLENGTH=8 VALUE="1.0"></TD>
	</TR>
	<TR>
		<TD CLASS="tableHeading" WIDTH="1%" NOWRAP VALIGN=TOP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Intended Recipients')" onMouseOut="noHelp()">Intended Recipients</A> &nbsp;</TD>
		<TD STYLE="padding-left : 9px;"><INPUT TYPE=TEXT NAME="sendPieces" SIZE=8 MAXLENGTH=8 VALUE="1000"></TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Field Token Usage')" onMouseOut="noHelp()">Field Token Usage</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf1" VALUE="5" CHECKED> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf1" VALUE="0"> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Post Processing')" onMouseOut="noHelp()">Post Processing</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf2" VALUE="8" CHECKED> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf2" VALUE="0"> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Link Tracking')" onMouseOut="noHelp()">Link Tracking</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf3" VALUE="10" CHECKED> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf3" VALUE="0"> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('View Tracking')" onMouseOut="noHelp()">View Tracking</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf4" VALUE="2" CHECKED> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf4" VALUE="0"> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Automated Bounce Handling')" onMouseOut="noHelp()">Automated Bounce Handling</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf5" VALUE="5"> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf5" VALUE="0" CHECKED> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Self-Sub/Unsub')" onMouseOut="noHelp()">Self-Sub/Unsub</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf6" VALUE="5"> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf6" VALUE="0" CHECKED> Yes</TD>
	</TR>
	<TR>
		<TD WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('Image/File Hosting')" onMouseOut="noHelp()">Image/File Hosting</A> &nbsp;</TD>
		<TD NOWRAP><INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf7" VALUE="0" CHECKED> No &nbsp;<INPUT CLASS="backgroundColor" TYPE=RADIO NAME="zf7" VALUE="-2"> Yes</TD>
	</TR>



	<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doCalc" VALUE="Calculate Estimate"></TD></TR>
	</TABLE>
	</FORM>
	</CENTER></TD></TR></TABLE>

</iIF ALIAS="doCalc">
