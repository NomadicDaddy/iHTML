<iREMBLOCK>
adminware FAQ Manager (Engine Module)
Copyright � 1997-2002 adminware, llc
</iREMBLOCK>

<iSET AWPV="FAQ Manager v1.15.107.1" demoDSN="adminware_faqmgr" demoLogin="Administrator/zzz" demo=0 AWPID="faqmanager">

<iIF COND=<iSTRCMP SRC=":faq_dsn" DST=":demoDSN">><iSET demo=1 faq_dbup=":demoLogin"></iIF>

<iSET showErrors=0><iINCLUDE NAME="w:\ifuncs\errorHandler.inc">

<iDEFAULT NAME="faq_dbup" VALUE="/">
<iDEFAULT NAME="faq_img" VALUE="/images/adminware">
<iDEFAULT NAME="faq_font" VALUE="Arial, Helvetica, Sans-Serif">
<iDEFAULT NAME="faq_abgc" VALUE="#FFFFEE">
<iDEFAULT NAME="faq_prompt" VALUE=`Please choose the category of your question below <B>or</B> use the search tool below.`>
<iDEFAULT NAME="faq_autoOpen" VALUE="">
<iDEFAULT NAME="faq_hideEmail" VALUE="0">
<iDEFAULT NAME="notifyEmail" VALUE="">
<iDEFAULT NAME="ck_email" VALUE="">

<iREM -- Auto-Open Category as Default -- >
<iIF NOTCOND=<iSTRCMP SRC=":faq_autoopen" DST="">><iDEFAULT NAME="showCat" VALUE=":faq_autoopen"></iIF>

<iREM -- For Match Highlighting: <B STYLE="background:#FFFF99"></B> -- >

<iIF NOTCOND=<iSTRCMP SRC=":hideHeader" DST="1"> ALIAS="hideHeader"><TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":faq_bgc"><TD><FONT FACE=":faq_font" SIZE="-1" COLOR="#FFFFFF"><B>Frequently Asked Questions &amp; Answers</B></FONT></TD></TR></TABLE><BR></iIF ALIAS="hideHeader">
<CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=0>

<iREM -- Browse Questions -- >
<TR><TD COLSPAN=3><FONT FACE=":faq_font">:faq_prompt<BR><BR></FONT></TD></TR>
<iSQL DBNAME=":faq_dsn" LOGIN=":faq_dbup" SQL="SELECT catID, name FROM categories ;" ALIAS="cats">
<iSQLFETCH ALIAS="cats" EMPTY="cats_empty">
<iWHILE NOTALIAS=cats_empty>
	<iURLENCODE SRC=":cats_name" OUTVAR="ecats_name">
	<iIF COND=<iSTRCMP SRC=":showCat" DST=":cats_name"> ALIAS="showCats">
		<TR><TD COLSPAN=3><FONT FACE=":faq_font"><A HREF=':i_script_name'><IMG SRC=":faq_img/minus.gif" ALT="-" WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0></A>:cats_name<BR><BR></FONT></TD></TR>
		<iSQL DBNAME=":faq_dsn" LOGIN=":faq_dbup" SQL="SELECT id, question, answer FROM qActive WHERE catID=:cats_catID ;" ALIAS="qs">
		<iSQLFETCH ALIAS="qs" EMPTY="qs_empty">
		<iIF NOTCOND=:qs_empty><iSET qCount=0></iIF>
		<iWHILE NOTALIAS=qs_empty>
			<iEVAL EXPR=':qCount + 1' OUTVAR="qCount">
			<TR>
				<TD ALIGN=RIGHT VALIGN=TOP><FONT FACE=":faq_font"><IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=20 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0><A NAME=":qs_id"><B>:qCount</B></A>.</FONT></TD>
				<TD><IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=5 HEIGHT=10 BORDER=0 HSPACE=0 VSPACE=0></TD>
				<TD ALIGN=LEFT VALIGN=TOP><FONT FACE=":faq_font" SIZE="-1"><A HREF=":i_script_name?awpid=:awpid&client_id=:client_id&go=FAQ&showCat=:eCats_name&showQ=:qs_id#:qs_id">:qs_question</A></FONT></TD>
			</TR>
			<iIF COND=<iSTRCMP SRC=":showQ" DST=":qs_id"> ALIAS="showQs">
				<TR>
					<TD COLSPAN=2>&nbsp;</TD>
					<TD BGCOLOR=":faq_abgc">
						<FONT FACE=":faq_font"><BR><BLOCKQUOTE>
						<iIF EXPR=':faq_bld' ALIAS="answerBold"><B>:qs_answer</B><iELSE ALIAS="answerBold">:qs_answer</iIF ALIAS="answerBold">
						</BLOCKQUOTE></FONT>
					</TD>
				</TR>
			</iIF ALIAS="showQs">
			<iSQLFETCH ALIAS="qs" EMPTY="qs_empty">
			<iIF COND=:qs_empty><TR><TD COLSPAN=3><FONT FACE=":faq_font"><BR></FONT></TD></TR></iIF>
		</iWHILE ALIAS=qs_empty>
		</iSQL ALIAS="qs">
	<iELSE ALIAS="showCats">
		<TR><TD COLSPAN=3><FONT FACE=":faq_font"><A HREF=":i_script_name?awpid=:awpid&client_id=:client_id&go=FAQ&showCat=:ecats_name"><IMG SRC=":faq_img/plus.gif" ALT="+" WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0>:cats_name</A></FONT></TD></TR>
	</iIF ALIAS="showCats">
	<iSQLFETCH ALIAS="cats" EMPTY="cats_empty">
	<iIF COND=:cats_empty><TR><TD COLSPAN=3><FONT FACE=":faq_font"><BR></FONT></TD></TR></iIF>
</iWHILE ALIAS=cats_empty>
</iSQL ALIAS="cats">

<iREM -- Search Questions and Answers -- >
<iIF EXPR='<iISDEF VAR="searchFor"> AND NOT <iSTRCMP SRC=":searchFor" DST="">' ALIAS="searched">
	<TR><TD COLSPAN=3><FONT FACE=":faq_font" SIZE="-1"><A NAME="SearchResults"><B>Matches for '<I>:searchfor</I>':<BR><BR></B></A></FONT></TD></TR>
	<iSQL DBNAME=":faq_dsn" LOGIN=":faq_dbup" SQL="SELECT * FROM qActive WHERE question LIKE '%:searchFor%' OR answer LIKE '%:searchFor%' ORDER BY catID ;" ALIAS="matches">
	<iSQLFETCH ALIAS="matches" EMPTY="matches_empty">
	<iSET qCount=0>
	<iWHILE NOTALIAS=matches_empty>
		<iEVAL EXPR=':qCount + 1' OUTVAR="qCount">
		<iHTML DBNAME=":faq_dsn" LOGIN=":faq_dbup" SQL="SELECT name FROM categories WHERE catID=:matches_catID ;" OUTPUT=":1" OUTVAR="z">
		<iURLENCODE SRC=":z" OUTVAR="ecats_name">
		<TR BGCOLOR=":faq_abgc">
			<TD ALIGN=RIGHT VALIGN=TOP NOWRAP><FONT FACE=":faq_font" SIZE="-1">In <B>:z</B>:</FONT></TD>
			<TD><IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=5 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0></TD>
			<TD ALIGN=LEFT VALIGN=TOP><FONT FACE=":faq_font" SIZE="-1"><A HREF=':i_script_name?showCat=:ecats_name&showQ=:matches_id#:matches_id'>:matches_question</A></FONT></TD>
		</TR>
		<iSQLFETCH ALIAS="matches" EMPTY="matches_empty">
	</iWHILE ALIAS=matches_empty>
	</iSQL ALIAS="Matches">
	<TR><TD COLSPAN=3><FONT FACE=":faq_font" SIZE="-1" COLOR="#FF0000"><BR><B><iIF EXPR=":qCount LT 1">None<iELSEIF EXPR=":qCount > 1">:qCount matches<iELSE>1 match</iIF> found.</B><BR><BR></FONT></TD></TR>
</iIF ALIAS="searched">

<iREM -- Form Validation JavaScript -- >
<iINCLUDE NAME="w:\faqmanager\formcheck.js" PARSE=FALSE>

<iREM -- Search Form -- >
<TR><TD COLSPAN=3><FONT FACE=":faq_font">
<iSET searchFor="">
<FORM NAME="sform" ACTION=':i_script_name#SearchResults' METHOD=POST onSubmit="return sFormCheck(this)"><TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>

<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE="FAQ">

<TR><TD COLSPAN=2><FONT FACE=":faq_font" SIZE="-1"><A NAME="SearchTool"><B>Search For</B></A></FONT></TD><TD><FONT FACE=":faq_font" SIZE="-1"><INPUT TYPE=TEXT NAME="searchFor" SIZE=30 VALUE=":searchFor"></FONT></TD><TD><FONT FACE=":faq_font" SIZE="-1"><INPUT TYPE=SUBMIT NAME="Search" VALUE="Go!"></FONT></TD></TR>
</TABLE></FORM>
</TD></TR>

<iREM -- Enter New Question Form -- >
<TR><TD COLSPAN=3><FONT FACE=":faq_font">:faq_ask<BR>
<FORM NAME="newqform" ACTION=':i_script_name' METHOD=POST <iIF EXPR='NOT :faq_hideEmail' ALIAS="hideEmail">onSubmit="return newQFormCheck(this)"</iIF ALIAS="hideEmail">>

<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE="FAQ">

<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
<TR>
	<TD VALIGN=TOP ALIGN=CENTER><FONT FACE=":faq_font" SIZE="-1"><B>New Question</B></FONT></TD>
	<TD COLSPAN=2><FONT FACE=":faq_font" SIZE="-1"><TEXTAREA NAME="nQuestion" ROWS=2 COLS=47 WRAP=SOFT></TEXTAREA></FONT></TD>
</TR>
<iIF EXPR='NOT :faq_hideEmail' ALIAS="hideEmail">
	<TR>
		<TD VALIGN=TOP ALIGN=CENTER><FONT FACE=":faq_font" SIZE="-1"><B>Email Address</B></FONT></TD>
		<TD><FONT FACE=":faq_font" SIZE="-1"><INPUT TYPE=TEXT NAME="notifyEmail" VALUE=":ck_email" SIZE=45></FONT></TD>
		<TD ALIGN=RIGHT><FONT FACE=":faq_font" SIZE="-1"><INPUT TYPE=SUBMIT NAME="newQ" VALUE="Go!"></FONT></TD>
	</TR>
<iELSE ALIAS="hideEmail">
	<INPUT TYPE=HIDDEN NAME="notifyEmail" VALUE=":ck_email">
	<TR>
		<TD COLSPAN=3 ALIGN=RIGHT><FONT FACE=":faq_font" SIZE="-1"><INPUT TYPE=SUBMIT NAME="newQ" VALUE="Go!"></FONT></TD>
	</TR>
</iIF ALIAS="hideEmail">
</TABLE></FORM>
</FONT></TD></TR>

<iREM -- Add New Question to Pending -- >
<iIF EXPR='<iISDEF VAR="nQuestion"> AND NOT <iSTRCMP SRC=":nQuestion" DST="">' ALIAS="addNewQ">
	<iHTML DBNAME=":faq_dsn" LOGIN=":faq_dbup" SQL="INSERT INTO qPending (question, notifyEmail) VALUES (':nQuestion', ':notifyEmail');">
	<iSET stat="Added New Question!  It will be answered shortly.">
	<iMAIL ADDRESS=":faq_mgr" FROM=":faq_emf" SUBJECT="New FAQ Question Asked!" PRIORITY="1 (Highest)"><iINCLUDE NAME=":faq_loc\notifymanager.txt"></iMAIL>
<iELSEIF COND=<iISDEF VAR="nQuestion"> ALIAS="addNewQ">
	<iSET stat="Failed!  The question cannot be blank!">
</iIF ALIAS="addNewQ">
<iIF COND=<iISDEF VAR="stat">>
	<iCOOKIE NAME="ck_email" VALUE=":notifyEmail" PATH="/">
	<TR><TD COLSPAN=3 ALIGN=CENTER><FONT FACE=":faq_font" COLOR="#FF0000" SIZE="+1"><B>:stat</B></FONT></TD></TR>
</iIF>

</FONT></TD></TR></TABLE></CENTER>
<iSET AWPVc="#FFFFFF"><iIF COND=<iSTRIN SRC=":faq_bgc" DST="FFFFFF">><iSET AWPVc="#000000"></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":hideFooter" DST="1"> ALIAS="hideFooter"><TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":faq_bgc" ALIGN=RIGHT><TD COLSPAN=3><FONT FACE=":faq_font" SIZE="-1" COLOR=":AWPVc"><B>:AWPV</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE="Arial, Helvetica" SIZE="-2"><B>Copyright &copy; 1997-2002 adminware, llc</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE="Arial, Helvetica" SIZE="-2"><B><A HREF="http://www.faqmanager.com/" onMouseOver="status='adminware :AWPV'; return true;" onMouseOut="status='';">http://www.faqmanager.com/</A></B></FONT></TD></TR></TABLE></iIF ALIAS="hideFooter">
